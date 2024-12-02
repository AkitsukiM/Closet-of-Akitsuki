# coding=utf-8

import os
import datetime
import argparse
from tqdm import tqdm

import numpy as np

import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms
import torch.distributed as dist
from torch.nn.parallel import DistributedDataParallel as DDP

from resnet import ResNet_cifar10

import torch_npu
from torch_npu.contrib import transfer_to_npu


def dist_print(*args, 
               use_ddp: bool = True, 
               rank: int = 0, 
               world_size: int = 1, 
               **kwargs, 
               ):
    if not use_ddp: print(*args, **kwargs)
    elif rank % world_size == 0: print(*args, **kwargs)
    else: pass


def init_ddp():
    dist.init_process_group(backend='nccl')

    rank = os.environ['RANK']
    world_size = os.environ['WORLD_SIZE']
    master_addr = os.environ['MASTER_ADDR']
    master_port = os.environ['MASTER_PORT']
    print("rank {} / {} has been initialized in {}:{}.".format(
        rank, 
        world_size, 
        master_addr, 
        master_port))

    return int(rank), int(world_size)


def cleanup_ddp():
    dist.destroy_process_group()


class Trainer(object):
    """
    """
    def __init__(self, 
                 batch_size: int = 256, 
                 num_layers: int = 50, 
                 pretrained: bool = True, 
                 use_ddp: bool = True, 
                 save_path: str = "./work_dirs/", 
                 ):
        # 设备超参
        self.use_cuda = torch.cuda.is_available()
        self.use_ddp = (self.use_cuda and use_ddp)

        if self.use_ddp:
            self.rank, self.world_size = init_ddp()
            self.device = "cuda:{}".format(self.rank)
            torch.cuda.set_device(self.rank)
            self.samples_per_gpu = batch_size // self.world_size
        else:
            self.rank, self.world_size = 0, 1
            self.device = torch.device("cuda" if self.use_cuda else "cpu")
            self.samples_per_gpu = batch_size

        self.num_workers = 4

        # 训练集超参
        self.transform_train = transforms.Compose([
            transforms.Resize(224),
            transforms.RandomHorizontalFlip(),
            transforms.RandomCrop(224, padding = 28),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])])
        self.trainset = torchvision.datasets.CIFAR10(
            root = './data/', 
            train = True, 
            download = True, 
            transform = self.transform_train)
        if self.use_ddp:
            self.trainsampler = torch.utils.data.distributed.DistributedSampler(
                dataset = self.trainset, 
                num_replicas = self.world_size, 
                rank = self.rank, 
                shuffle = True)
            self.trainloader = torch.utils.data.DataLoader(
                dataset = self.trainset, 
                batch_size = self.samples_per_gpu, 
                num_workers = self.num_workers, 
                shuffle = False, 
                sampler = self.trainsampler)
        else:
            self.trainloader = torch.utils.data.DataLoader(
                dataset = self.trainset, 
                batch_size = self.samples_per_gpu, 
                num_workers = self.num_workers, 
                shuffle = True)

        # 测试集超参
        self.transform_val = transforms.Compose([
            transforms.Resize(224),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])])
        self.valset = torchvision.datasets.CIFAR10(
            root = './data/', 
            train = False, 
            download = True, 
            transform = self.transform_val)
        self.valloader = torch.utils.data.DataLoader(
            dataset = self.valset, 
            batch_size = 1, 
            num_workers = self.num_workers, 
            shuffle = False)

        # 模型超参
        self.num_layers = num_layers
        self.pretrained = pretrained
        self.classes = (
            "airplane",
            "automobile",
            "bird",
            "cat",
            "deer",
            "dog",
            "frog",
            "horse",
            "ship",
            "truck")
        self.num_classes = len(self.classes)

        self.lr_init = 0.1 * self.samples_per_gpu / 256
        self.momentum = 0.9
        self.weight_decay = 1e-4

        self.model = ResNet_cifar10(num_layers=self.num_layers, pretrained=self.pretrained).to(self.device)
        if self.use_ddp: self.model = DDP(self.model, device_ids=[self.rank])
        dist_print(self.model, 
                   use_ddp=self.use_ddp, rank=self.rank, world_size=self.world_size)

        self.optimizer = optim.SGD(self.model.parameters(), lr=self.lr_init, momentum=self.momentum, weight_decay=self.weight_decay)
        self.criterion = nn.CrossEntropyLoss()

        self.max_epochs = 160
        self.checkpoint_interval = 8
        self.warmup_iters = 500
        self.print_iters = 50
        self.save_path = save_path

        if not os.path.exists(self.save_path):
            os.makedirs(self.save_path)

    def train(self):
        current_lr = 0.0
        running_loss = 0.0
        best_acc = 0.0

        count_epoch = 0
        count_iter_global = 0
        t1 = datetime.datetime.now()

        while True:
            # train
            self.model.train()
            max_iters = len(self.trainloader)

            count_iter_local = 0

            for i, data in enumerate(self.trainloader, 0):
                # 基于count_iter_global的学习率warmup控制
                if count_iter_global < self.warmup_iters:
                    current_lr = (count_iter_global + 1) / self.warmup_iters * self.lr_init
                    for param_group in self.optimizer.param_groups: param_group["lr"] = current_lr

                # 基于count_epoch的学习率decay控制
                if count_epoch == self.max_epochs:
                    cleanup_ddp()
                    return best_acc
                elif count_epoch == int(self.max_epochs * 0.50):
                    current_lr = self.lr_init / 10.0
                    for param_group in self.optimizer.param_groups: param_group["lr"] = current_lr
                elif count_epoch == int(self.max_epochs * 0.75):
                    current_lr = self.lr_init / 100.0
                    for param_group in self.optimizer.param_groups: param_group["lr"] = current_lr
                else:
                    pass

                # 训练前传与反传
                inputs, labels = data[0].to(self.device), data[1].to(self.device)

                self.optimizer.zero_grad()
                outputs = self.model(inputs)
                loss_mean = self.criterion(outputs, labels)
                loss_mean.backward()
                self.optimizer.step()

                # 计数+1
                count_iter_global += 1
                count_iter_local += 1

                # 打印loss
                running_loss += loss_mean.item()

                if count_iter_global == 1:
                    dist_print(running_loss, flush = True, 
                               use_ddp=self.use_ddp, rank=self.rank, world_size=self.world_size)

                if count_iter_local % self.print_iters == 0:
                    t2 = datetime.datetime.now()
                    t_eta = (t2 - t1) \
                        * ((self.max_epochs - count_epoch) * max_iters - count_iter_local) \
                        / (count_epoch * max_iters + count_iter_local)
                    dist_print("{} - Epoch [{}][{}/{}] \tlr: {:.6f}, eta: {}, loss: {:.6f}".format(
                        t2,
                        count_epoch + 1,
                        count_iter_local,
                        max_iters,
                        current_lr,
                        t_eta,
                        running_loss / self.print_iters), 
                               use_ddp=self.use_ddp, rank=self.rank, world_size=self.world_size)
                    running_loss = 0.0

            # eval
            count_epoch += 1

            if not self.use_ddp: pass
            elif self.rank % self.world_size == 0: pass
            else: continue

            # 以下eval只在0号卡上操作
            if True:
                last_pth_path = os.path.join(self.save_path, "last.pth")
                torch.save(self.model.module.state_dict(), last_pth_path)
                print("Epoch {} has been saved to {}.\n".format(count_epoch, last_pth_path))

                if count_epoch % self.checkpoint_interval == 0:
                    self.model.eval()

                    cls_correct = np.zeros(self.num_classes, dtype = int)
                    cls_total = np.zeros(self.num_classes, dtype = int)

                    # 前传与推理
                    with torch.no_grad():
                        for data in tqdm(self.valloader):
                            inputs, labels = data[0].to(self.device), data[1].to(self.device)

                            outputs = self.model(inputs)
                            _, preds = torch.max(outputs.data, 1)

                            # batch_size = 1
                            pred = int(preds[0])
                            label = int(labels[0])
                            cls_total[label] += 1
                            if pred == label: cls_correct[label] += 1

                    # 打印结果
                    for cls_ind in range(self.num_classes):
                        print("{:18}: {} / {}".format(self.classes[cls_ind], cls_correct[cls_ind], cls_total[cls_ind]))

                    set_correct = cls_correct.sum()
                    set_total = cls_total.sum()
                    set_acc = 1.0 * set_correct / set_total
                    print("{:18}: {} / {} = {}".format("accuracy", set_correct, set_total, set_acc))

                    if set_acc > best_acc:
                        best_pth_path = os.path.join(self.save_path, "best.pth")
                        torch.save(self.model.module.state_dict(), best_pth_path)
                        best_acc = set_acc
                    print("{:18}: {}\n".format("[BEST]", best_acc))


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--batch_size", type = int, default = 256, help = None)
    parser.add_argument("--num_layers", type = int, default = 50, help = None)
    parser.add_argument("--pretrained", type = int, default = 1, help = None)
    parser.add_argument("--use_ddp", type = int, default = 1, help = None)
    parser.add_argument("--save_path", type = str, default = "./work_dirs/", help = None)
    parser.add_argument("--local_rank", type = int, default = 0, help = None)
    parser.add_argument("--local-rank", type = int, default = 0, help = None)
    opt = parser.parse_args()

    Trainer(
        batch_size = opt.batch_size, 
        num_layers = opt.num_layers, 
        pretrained = opt.pretrained, 
        use_ddp = opt.use_ddp, 
        save_path = opt.save_path, 
    ).train()


# https://pytorch.org/tutorials/intermediate/ddp_tutorial.html
# CUDA_VISIBLE_DEVICES=0,1,2,3 python -m torch.distributed.launch --nnodes 1 --nproc_per_node 4 --master_addr 127.0.0.1 --master_port 29501 main.py --save_path "./work_dirs/ddp_1/"
# CUDA_VISIBLE_DEVICES=4 python main.py --use_ddp 0 --save_path "./work_dirs/ddp_0/"

