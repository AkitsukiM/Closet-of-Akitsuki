# myResNet version 1.25a
# 
# ResNet form torchvision.models.resnet, simplified version
# 
# Copyright (c) 2020 Marina Akitsuki. All rights reserved.
# Date modified: 2020/02/10
# 

import torch.nn as nn
import torch.nn.functional as F

def conv3x3(inplanes, outplanes, stride = 1):
    return nn.Conv2d(inplanes, outplanes, kernel_size = 3, stride = stride, padding = 1, bias = False)

def conv1x1(inplanes, outplanes, stride = 1):
    return nn.Conv2d(inplanes, outplanes, kernel_size = 1, stride = stride, padding = 0, bias = False)

def normlayer(planes):
    return nn.BatchNorm2d(planes)

class ConvBlock(nn.Module):
    def __init__(self, inplanes, outplanes, kernel_size = 3, stride = 1):
        super(ConvBlock, self).__init__()

        self.conv1 = nn.Conv2d(inplanes, outplanes, kernel_size = kernel_size, stride = stride, padding = kernel_size // 2, bias = False)
        self.bn1 = normlayer(outplanes)
        self.relu = nn.ReLU()

    def forward(self, x):
        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu(out)
        return out

class BasicBlock(nn.Module):
    def __init__(self, inplanes, outplanes, stride = 1, hasdownsample = False):
        super(BasicBlock, self).__init__()

        self.hasdownsample = hasdownsample
        self.convres = conv1x1(inplanes, outplanes, stride)
        self.bnres = normlayer(outplanes)

        self.conv1 = conv3x3(inplanes, outplanes, stride)
        self.bn1 = normlayer(outplanes)
        self.conv2 = conv3x3(outplanes, outplanes)
        self.bn2 = normlayer(outplanes)
        self.relu = nn.ReLU()

    def forward(self, x):
        identity = x
        if self.hasdownsample is True:
            identity = self.convres(x)
            identity = self.bnres(identity)

        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu(out)
        out = self.conv2(out)
        out = self.bn2(out)
        out += identity
        out = self.relu(out)
        return out

class BottleBlock(nn.Module):
    def __init__(self, inplanes, outplanes, stride = 1, hasdownsample = False):
        super(BottleBlock, self).__init__()
        midplanes = outplanes // 4

        self.hasdownsample = hasdownsample
        self.convres = conv1x1(inplanes, outplanes, stride)
        self.bnres = normlayer(outplanes)

        self.conv1 = conv1x1(inplanes, midplanes, stride)
        self.bn1 = normlayer(midplanes)
        self.conv2 = conv3x3(midplanes, midplanes)
        self.bn2 = normlayer(midplanes)
        self.conv3 = conv1x1(midplanes, outplanes)
        self.bn3 = normlayer(outplanes)
        self.relu = nn.ReLU()

    def forward(self, x):
        identity = x
        if self.hasdownsample is True:
            identity = self.convres(x)
            identity = self.bnres(identity)

        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu(out)
        out = self.conv2(out)
        out = self.bn2(out)
        out = self.conv3(out)
        out = self.bn3(out)
        out += identity
        out = self.relu(out)
        return out

class ResNet(nn.Module):
    def __init__(self, blocktype, blocks, ioplanes, fcOut, ConvBlock_kernel_size = 3, ConvBlock_stride = 1):
        super(ResNet, self).__init__()

        self.layer0 = ConvBlock(3, ioplanes[0], kernel_size = ConvBlock_kernel_size, stride = ConvBlock_stride)
        self.inplanes = ioplanes[0]

        self.layer1 = self._make_layer(blocktype, ioplanes[1], blocks[1])
        self.layer2 = self._make_layer(blocktype, ioplanes[2], blocks[2], stride = 2)
        self.layer3 = self._make_layer(blocktype, ioplanes[3], blocks[3], stride = 2)
        self.layer4 = self._make_layer(blocktype, ioplanes[4], blocks[4], stride = 2)

        self.fcIn = ioplanes[4]
        self.fc = nn.Linear(self.fcIn, fcOut)

    def _make_layer(self, blocktype, planes, blocks_x, stride = 1):
        hasdownsample = False
        if stride != 1 or self.inplanes != planes: hasdownsample = True

        layers = []
        layers.append(blocktype(self.inplanes, planes, stride, hasdownsample))
        self.inplanes = planes
        for _ in range(1, blocks_x): layers.append(blocktype(self.inplanes, planes))

        return nn.Sequential(*layers)

    def forward(self, x):
        out = self.layer0(x)
        out = self.layer1(out)
        out = self.layer2(out)
        out = self.layer3(out)
        out = self.layer4(out)
        out = F.adaptive_avg_pool2d(out, 1)
        out = out.view(-1, self.fcIn)
        out = self.fc(out)
        return out
