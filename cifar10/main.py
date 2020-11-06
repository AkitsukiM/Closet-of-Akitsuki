# ResNet version 18.1.01g for cifar10
# 
# Copyright (c) 2020 Marina Akitsuki. All rights reserved.
# Date modified: 2020/11/05
# 

import os
import sys
import datetime
import shutil

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms

import numpy as np

import ResNet


DATASET_PATH = "/home/marina/Workspace/Dataset"
PROJECT_PATH = "/home/marina/Workspace/cifar10"
WEIGHT_PATH = os.path.join(PROJECT_PATH, "weight")

datasetsMean = (0.4914, 0.4822, 0.4465) # (0.485, 0.456, 0.406) # datasetsMean for ImageNet
datasetsStd = (0.2023, 0.1994, 0.2010) # (0.229, 0.224, 0.225) # datasetsStd for ImageNet

num_blocks = (1, 2, 2, 2, 2) # 2 + 2 * (2 + 2 + 2 + 2) = 18
num_outplanes = (16, 16, 32, 64, 128)
num_classes = 10
CLASSES = (
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

iLearningRate = 0.1
iMomentum = 0.9
iWeightDecay = 1e-4
iterationWhenPrintRunningLoss = 100
iterationWhenEvaluate = 1000
iterationWhenLearningRateDacay = (32000, 48000)
iterationWhenMissionAccomplished = 64000

gpu = True if torch.cuda.is_available() else False
device = torch.device("cuda" if gpu else "cpu")
workers = 0

batchSizeTrain = 128
batchSizeTest = 100

transformTrain = transforms.Compose([
    transforms.RandomCrop(32, padding = 4),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(), transforms.Normalize(datasetsMean, datasetsStd)])

transformTest = transforms.Compose([
    transforms.ToTensor(), transforms.Normalize(datasetsMean, datasetsStd)])

trainset = torchvision.datasets.CIFAR10(root = DATASET_PATH, train = True, download = True, transform = transformTrain)
trainloader = torch.utils.data.DataLoader(trainset, batch_size = batchSizeTrain, shuffle = True, num_workers = workers)

testset = torchvision.datasets.CIFAR10(root = DATASET_PATH, train = False, download = True, transform = transformTest)
testloader = torch.utils.data.DataLoader(testset, batch_size = batchSizeTest, shuffle = False, num_workers = workers)


def remkdir(dir):
    if os.path.exists(dir):
        shutil.rmtree(dir)
    os.mkdir(dir)
    print("remake dir {} is done".format(dir))


def evaluate(model):
    model.eval()

    cls_correct = np.zeros((num_classes), dtype = np.int32)
    cls_total = np.zeros((num_classes), dtype = np.int32)

    with torch.no_grad():
        for data in testloader:
            if gpu:
                inputs, labels = data[0].to(device), data[1].to(device)
            else:
                inputs, labels = data

            outputs = model(inputs)
            _, preds = torch.max(outputs.data, 1)

            for i in range(labels.size(0)): # batch_size
                pred = int(preds[i])
                label = int(labels[i])
                cls_total[label] += 1
                if pred == label: cls_correct[label] += 1

    for cls_index in range(num_classes):
        print("{:12}: {} / {}".format(CLASSES[cls_index], cls_correct[cls_index], cls_total[cls_index]))

    set_correct = cls_correct.sum()
    set_total = cls_total.sum()
    set_acc = 1.0 * set_correct / set_total
    print("{:12}: {} / {} = {}".format("accuracy", set_correct, set_total, set_acc))

    return set_acc


def train():
    net = ResNet.ResNet("BasicBlock", num_blocks, num_outplanes, num_classes)
    if gpu:
        net.to(device)

    criterion = nn.CrossEntropyLoss()
    optimizer = optim.SGD(net.parameters(), lr = iLearningRate, momentum = iMomentum, weight_decay = iWeightDecay)

    runningLoss = 0.0
    iterationCount = 0
    best_acc = 0.0
    t1 = datetime.datetime.now()

    while True:
        for i, data in enumerate(trainloader, 0):
            net.train()

            if gpu:
                inputs, labels = data[0].to(device), data[1].to(device)
            else:
                inputs, labels = data

            optimizer.zero_grad()
            outputs = net(inputs)
            loss = criterion(outputs, labels)
            loss.backward()
            optimizer.step()

            runningLoss += loss.item()
            iterationCount += 1

            if iterationCount == 1:
                # torch.save(net.state_dict(), os.path.join(WEIGHT_PATH, "best.pth"))
                print(runningLoss, flush = True)

            if iterationCount % iterationWhenPrintRunningLoss == 0:
                print(">> {:.3f} ".format(runningLoss / iterationWhenPrintRunningLoss), end = "", flush = True)
                runningLoss = 0.0

            if iterationCount % iterationWhenEvaluate == 0:
                torch.save(net.state_dict(), os.path.join(WEIGHT_PATH, "backup_iter{}.pth".format(iterationCount)))
                print("")
                print("iteration {}:".format(iterationCount))
                
                acc = evaluate(net)
                if acc > best_acc:
                    torch.save(net.state_dict(), os.path.join(WEIGHT_PATH, "best.pth"))
                    best_acc = acc
                print("{:12}: {}".format("[BEST]", best_acc))

                t2 = datetime.datetime.now()
                print("{:12}: {}".format("[TIME]", t2 - t1))

            if iterationCount in iterationWhenLearningRateDacay:
                new_lr = optimizer.param_groups[0]["lr"] / 10
                for params in optimizer.param_groups:
                    params["lr"] = new_lr

            if iterationCount == iterationWhenMissionAccomplished:
                sys.exit(0)



if __name__ == "__main__":
    print(gpu, device, workers)
    remkdir(WEIGHT_PATH)
    train()

