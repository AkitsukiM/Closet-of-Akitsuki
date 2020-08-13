# ResNet version 18.1.01c for cifar10
# 
# 1.00b Update Information:
# (i) Rewrite based on myResNet version 1.25a.
# 
# 1.01a Update Information:
# (i) Change counting unit to iteration instead of epoch;
# (ii) Add some information of ImageNet for reference.
# 
# Copyright (c) 2020 Marina Akitsuki. All rights reserved.
# Date modified: 2020/08/12
# 

datasetsMean = (0.4914, 0.4822, 0.4465) # (0.485, 0.456, 0.406) # datasetsMean for ImageNet
datasetsStd = (0.2023, 0.1994, 0.2010) # (0.229, 0.224, 0.225) # datasetsStd for ImageNet
batchSize = 100
batchSizeTrain = 128

blocks = (1, 2, 2, 2, 2) # 2 + 2 * (2 + 2 + 2 + 2) = 18
ioplanes = (16, 16, 32, 64, 128)
fcOut = 10 # 1000 # fcOut for ImageNet
ConvBlock_kernel_size = 3 # 7 # ConvBlock_kernel_size for ImageNet
ConvBlock_stride = 1

iLearningRate = 0.1
iMomentum = 0.9
iWeightDecay = 1e-4
iterationWhenPrintRunningLoss = 100
iterationWhenCalcAccuracy = 1000
iterationWhenLearningRateDacay = (32000, 64000)
iterationWhenMissionAccomplished = 96000

ROOT_PATH = "../../Dataset/"

import torch
import torchvision
import torchvision.transforms as transforms

gpu = True if torch.cuda.is_available() else False
device = torch.device("cuda" if gpu else "cpu")
print(gpu, device)

transform = transforms.Compose([
    transforms.ToTensor(), transforms.Normalize(datasetsMean, datasetsStd)])

# """
transformTrain = transforms.Compose([
    transforms.RandomCrop(32, padding = 4),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(), transforms.Normalize(datasetsMean, datasetsStd)])

trainset = torchvision.datasets.CIFAR10(root = ROOT_PATH, train = True, download = True, transform = transformTrain)
trainloader = torch.utils.data.DataLoader(trainset, batch_size = batchSizeTrain, shuffle = True, num_workers = (2 if gpu else 0))

traintestset = torchvision.datasets.CIFAR10(root = ROOT_PATH, train = True, download = True, transform = transform)
traintestloader = torch.utils.data.DataLoader(traintestset, batch_size = batchSize, shuffle = False, num_workers = (2 if gpu else 0))
testset = torchvision.datasets.CIFAR10(root = ROOT_PATH, train = False, download = True, transform = transform)
testloader = torch.utils.data.DataLoader(testset, batch_size = batchSize, shuffle = False, num_workers = (2 if gpu else 0))

"""

# Data Augmentation Strategy for ImageNet
transformTrain = transforms.Compose([
    transforms.Resize(256),
    transforms.RandomCrop(224),
    transforms.RandomHorizontalFlip(),
    transforms.ToTensor(), transforms.Normalize(datasetsMean, datasetsStd)])

transformVal = transforms.Compose([
    transforms.Resize(256),
    transforms.CenterCrop(224),
    transforms.ToTensor(), transforms.Normalize(datasetsMean, datasetsStd)])

trainset = torchvision.datasets.ImageFolder(root = "/home/ubuntu/Workspace/Dataset/ILSVRC2012/train", transform = transformTrain)
trainloader = torch.utils.data.DataLoader(trainset, batch_size = batchSizeTrain, shuffle = True, num_workers = (2 if gpu else 0))

valset = torchvision.datasets.ImageFolder(root = "/home/ubuntu/Workspace/Dataset/ILSVRC2012/val", transform = transformVal)
valloader = torch.utils.data.DataLoader(valset, batch_size = batchSize, shuffle = False, num_workers = (2 if gpu else 0))
# """

import datetime
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
import myResNet

t1 = datetime.datetime.now()

net = myResNet.ResNet(myResNet.BasicBlock, blocks, ioplanes, fcOut, ConvBlock_kernel_size = ConvBlock_kernel_size)
if gpu: net.to(device)

criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(net.parameters(), lr = iLearningRate, momentum = iMomentum, weight_decay = iWeightDecay)

runningLoss = 0.0
iterationCount = 0

def calcAccuracy(loader):
    set_correct = 0.0
    set_total = 0.0

    with torch.no_grad():
        for data in loader:
            if gpu:
                inputs, labels = data[0].to(device), data[1].to(device)
            else:
                inputs, labels = data

            # inputs = [inputs, inputs * 0] # for testing ComplexNet
            outputs = net(inputs)
            _, predictions = torch.max(outputs.data, 1)

            for i in range(batchSize):
                set_total += 1
                if predictions[i] == labels[i]: set_correct += 1

    set_accuracy = 100 * set_correct / set_total
    print("Accuracy of total: %d/%d = %.1f %%" % (set_correct, set_total, set_accuracy))

while True:
    for i, data in enumerate(trainloader, 0):
        if gpu:
            inputs, labels = data[0].to(device), data[1].to(device)
        else:
            inputs, labels = data

        optimizer.zero_grad()

        # inputs = [inputs, inputs * 0] # for testing ComplexNet
        outputs = net(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        runningLoss += loss.item()
        if iterationCount % iterationWhenPrintRunningLoss == 0:
            print(">> %.3f " % (runningLoss / iterationWhenPrintRunningLoss), end = "", flush = True)
            runningLoss = 0.0

        iterationCount += 1

        if iterationCount % iterationWhenCalcAccuracy == 0:
            print("")
            print("iteration %d:" % (iterationCount))

            for loader in (traintestloader, testloader): calcAccuracy(loader)
            # calcAccuracy(valloader) # valloader for ImageNet

            t2 = datetime.datetime.now()
            print(t2 - t1)

        if iterationCount in iterationWhenLearningRateDacay:
            iLearningRate /= 10
            for params in optimizer.param_groups:
                params["lr"] = iLearningRate

        if iterationCount == iterationWhenMissionAccomplished:
            exit(0)
