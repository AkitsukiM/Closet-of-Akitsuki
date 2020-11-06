# Customized ResNet version 1.00b
# 
# ResNet form torchvision.models.resnet, simplified version
# 
# Copyright (c) 2020 Marina Akitsuki. All rights reserved.
# Date modified: 2020/11/05
# 

import torch.nn as nn
import torch.nn.functional as F

def conv3x3(inplanes, outplanes, stride = 1):
    return nn.Conv2d(inplanes, outplanes, kernel_size = 3, stride = stride, padding = 1, bias = False)

def conv1x1(inplanes, outplanes, stride = 1):
    return nn.Conv2d(inplanes, outplanes, kernel_size = 1, stride = stride, padding = 0, bias = False)

def normlayer(planes):
    return nn.BatchNorm2d(planes)

def activatelayer():
    return nn.ReLU(inplace = True)

class ConvBlock(nn.Module):
    def __init__(self, inplanes, outplanes, kernel_size = 3, stride = 1):
        super(ConvBlock, self).__init__()

        self.conv1 = nn.Conv2d(inplanes, outplanes, kernel_size = kernel_size, stride = stride, padding = kernel_size // 2, bias = False)
        self.bn1 = normlayer(outplanes)
        self.relu1 = activatelayer()

    def forward(self, x):
        out = self.conv1(x)
        out = self.bn1(out)
        out = self.relu1(out)
        return out

class BasicBlock(nn.Module):
    def __init__(self, inplanes, outplanes, stride = 1, hasdownsample = False):
        super(BasicBlock, self).__init__()

        self.hasdownsample = hasdownsample
        self.convres = conv1x1(inplanes, outplanes, stride)
        self.bnres = normlayer(outplanes)
        self.relures = activatelayer()

        self.conv1 = conv3x3(inplanes, outplanes, stride)
        self.bn1 = normlayer(outplanes)
        self.relu1 = activatelayer()
        self.conv2 = conv3x3(outplanes, outplanes)
        self.bn2 = normlayer(outplanes)
        self.relu2 = activatelayer()

    def forward(self, x):
        identity = x
        if self.hasdownsample is True:
            identity = self.convres(x)
            identity = self.bnres(identity)
            # identity = self.relures(identity)

        y = self.conv1(x)
        y = self.bn1(y)
        y = self.relu1(y)
        y = self.conv2(y)
        y = self.bn2(y)
        out = y + identity
        out = self.relu2(out)
        return out

class BottleBlock(nn.Module):
    def __init__(self, inplanes, outplanes, stride = 1, hasdownsample = False):
        super(BottleBlock, self).__init__()
        midplanes = outplanes // 4

        self.hasdownsample = hasdownsample
        self.convres = conv1x1(inplanes, outplanes, stride)
        self.bnres = normlayer(outplanes)
        self.relures = activatelayer()

        self.conv1 = conv1x1(inplanes, midplanes, stride)
        self.bn1 = normlayer(midplanes)
        self.relu1 = activatelayer()
        self.conv2 = conv3x3(midplanes, midplanes)
        self.bn2 = normlayer(midplanes)
        self.relu2 = activatelayer()
        self.conv3 = conv1x1(midplanes, outplanes)
        self.bn3 = normlayer(outplanes)
        self.relu3 = activatelayer()

    def forward(self, x):
        identity = x
        if self.hasdownsample is True:
            identity = self.convres(x)
            identity = self.bnres(identity)
            # identity = self.relures(identity)

        y = self.conv1(x)
        y = self.bn1(y)
        y = self.relu1(y)
        y = self.conv2(y)
        y = self.bn2(y)
        y = self.relu2(y)
        y = self.conv3(y)
        y = self.bn3(y)
        out = y + identity
        out = self.relu3(out)
        return out

class ResNet(nn.Module):
    """
    Customized ResNet
    __init__ args:
        blocktype: "BasicBlock" or "BottleBlock"
        num_blocks: a tuple containing the number of blocks in every layer
        num_outplanes: a tuple containing the number of outplanes in every layer
        num_classes: number of classes i.e. out_features of fully connected layer
    """
    def __init__(self, blocktype, num_blocks, num_outplanes, num_classes):
        super(ResNet, self).__init__()
        assert blocktype in ["BasicBlock", "BottleBlock"]
        if blocktype == "BasicBlock":
            self.blocktype = BasicBlock
        else:
            self.blocktype = BottleBlock

        self.layer0 = ConvBlock(3, num_outplanes[0], kernel_size = 3, stride = 1)
        self.inplanes = num_outplanes[0]

        self.layer1 = self._make_layer(self.blocktype, num_blocks[1], num_outplanes[1])
        self.layer2 = self._make_layer(self.blocktype, num_blocks[2], num_outplanes[2], stride = 2)
        self.layer3 = self._make_layer(self.blocktype, num_blocks[3], num_outplanes[3], stride = 2)
        self.layer4 = self._make_layer(self.blocktype, num_blocks[4], num_outplanes[4], stride = 2)

        self.fcIn = num_outplanes[4]
        self.fcOut = num_classes
        self.fc = nn.Linear(self.fcIn, self.fcOut)

    def _make_layer(self, blocktype, blocks, outplanes, stride = 1):
        hasdownsample = False
        if stride != 1 or self.inplanes != outplanes: hasdownsample = True

        layers = []
        layers.append(blocktype(self.inplanes, outplanes, stride, hasdownsample))
        self.inplanes = outplanes
        for _ in range(1, blocks): layers.append(blocktype(self.inplanes, outplanes))

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

