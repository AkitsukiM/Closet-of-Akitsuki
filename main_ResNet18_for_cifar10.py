# ResNet version 18.1.01e for cifar10
# 
# Copyright (c) 2020 Marina Akitsuki. All rights reserved.
# Date modified: 2020/08/17
# 

datasetsMean = (0.4914, 0.4822, 0.4465) # (0.485, 0.456, 0.406) # datasetsMean for ImageNet
datasetsStd = (0.2023, 0.1994, 0.2010) # (0.229, 0.224, 0.225) # datasetsStd for ImageNet

blocks = (1, 2, 2, 2, 2) # 2 + 2 * (2 + 2 + 2 + 2) = 18
ioplanes = (16, 16, 32, 64, 128)
fcOut = 10
ConvBlock_kernel_size = 3
ConvBlock_stride = 1

iLearningRate = 0.1
iMomentum = 0.9
iWeightDecay = 1e-4
iterationWhenPrintRunningLoss = 100
iterationWhenEvaluate = 1000
iterationWhenLearningRateDacay = (32000, 48000)
iterationWhenMissionAccomplished = 64000

ROOT_PATH = "../../Dataset/"

import sys
import datetime

import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms

import myResNet

gpu = True if torch.cuda.is_available() else False
device = torch.device("cuda" if gpu else "cpu")
workers = 2 if gpu else 0
print(gpu, device, workers)

batchSizeTrain = 128
batchSizeTest = 100

transform = transforms.Compose([
    transforms.ToTensor(), transforms.Normalize(datasetsMean, datasetsStd)])

transformTrain = transforms.Compose([
    transforms.RandomCrop(32, padding = 4),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(), transforms.Normalize(datasetsMean, datasetsStd)])

trainset = torchvision.datasets.CIFAR10(root = ROOT_PATH, train = True, download = True, transform = transformTrain)
trainloader = torch.utils.data.DataLoader(trainset, batch_size = batchSizeTrain, shuffle = True, num_workers = workers)

trastset = torchvision.datasets.CIFAR10(root = ROOT_PATH, train = True, download = True, transform = transform)
trastloader = torch.utils.data.DataLoader(trastset, batch_size = batchSizeTest, shuffle = False, num_workers = workers)
testset = torchvision.datasets.CIFAR10(root = ROOT_PATH, train = False, download = True, transform = transform)
testloader = torch.utils.data.DataLoader(testset, batch_size = batchSizeTest, shuffle = False, num_workers = workers)

net = myResNet.ResNet(myResNet.BasicBlock, blocks, ioplanes, fcOut, ConvBlock_kernel_size = ConvBlock_kernel_size)
if gpu: net.to(device)

criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(net.parameters(), lr = iLearningRate, momentum = iMomentum, weight_decay = iWeightDecay)

runningLoss = 0.0
iterationCount = 0

def toEvaluate(loader, loadername = ""):
    set_correct = 0.0
    set_total = 0.0

    with torch.no_grad():
        for data in loader:
            if gpu:
                inputs, labels = data[0].to(device), data[1].to(device)
            else:
                inputs, labels = data

            outputs = net(inputs)
            _, predictions = torch.max(outputs.data, 1)

            # assert outputs.size(0) == labels.size(0) == batchSizeTest
            for i in range(outputs.size(0)):
                set_total += 1
                if predictions[i] == labels[i]: set_correct += 1

    set_accuracy = 100 * set_correct / set_total
    print(loadername, "accuracy: %d/%d = %.1f %%" % (set_correct, set_total, set_accuracy))

t1 = datetime.datetime.now()

while True:
    for i, data in enumerate(trainloader, 0):
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

        # 第一个iteration测试用
        if iterationCount == 1:
            # torch.save(net, "./ResNet18.pth")
            print(runningLoss, flush = True)

        if iterationCount % iterationWhenPrintRunningLoss == 0:
            print(">> %.3f " % (runningLoss / iterationWhenPrintRunningLoss), end = "", flush = True)
            runningLoss = 0.0

        if iterationCount % iterationWhenEvaluate == 0:
            torch.save(net, "./ResNet18_iteration" + str(iterationCount) + ".pth") # temporary save
            print("")
            print("iteration %d:" % (iterationCount))

            toEvaluate(trastloader, "trastloader")
            toEvaluate(testloader, "testloader")

            t2 = datetime.datetime.now()
            print(t2 - t1)

        if iterationCount in iterationWhenLearningRateDacay:
            iLearningRate /= 10
            for params in optimizer.param_groups:
                params["lr"] = iLearningRate

        if iterationCount == iterationWhenMissionAccomplished:
            torch.save(net, "./ResNet18.pth") # final save
            sys.exit(0)

