# myComplexNet version 1.02a
# 
# Based on myResNet version 1.25a
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

        self.conv1_real = nn.Conv2d(inplanes, outplanes, kernel_size = kernel_size, stride = stride, padding = kernel_size // 2, bias = False)
        self.conv1_imag = nn.Conv2d(inplanes, outplanes, kernel_size = kernel_size, stride = stride, padding = kernel_size // 2, bias = False)
        self.bn1_real = normlayer(outplanes);
        self.bn1_imag = normlayer(outplanes);
        self.relu = nn.ReLU()

    def forward(self, x):
        x_real = x[0];
        x_imag = x[1];

        out_real = self.conv1_real(x_real) - self.conv1_imag(x_imag)
        out_imag = self.conv1_imag(x_real) + self.conv1_real(x_imag)
        out_real = self.bn1_real(out_real)
        out_imag = self.bn1_imag(out_imag)
        out_real = self.relu(out_real)
        out_imag = self.relu(out_imag)
        return [out_real, out_imag]

class BasicBlock(nn.Module):
    def __init__(self, inplanes, outplanes, stride = 1, hasdownsample = False):
        super(BasicBlock, self).__init__()

        self.hasdownsample = hasdownsample
        self.convres_real = conv1x1(inplanes, outplanes, stride)
        self.convres_imag = conv1x1(inplanes, outplanes, stride)
        self.bnres_real = normlayer(outplanes)
        self.bnres_imag = normlayer(outplanes)

        self.conv1_real = conv3x3(inplanes, outplanes, stride)
        self.conv1_imag = conv3x3(inplanes, outplanes, stride)
        self.bn1_real = normlayer(outplanes)
        self.bn1_imag = normlayer(outplanes)
        self.conv2_real = conv3x3(outplanes, outplanes)
        self.conv2_imag = conv3x3(outplanes, outplanes)
        self.bn2_real = normlayer(outplanes)
        self.bn2_imag = normlayer(outplanes)
        self.relu = nn.ReLU()

    def forward(self, x):
        x_real = x[0];
        x_imag = x[1];

        identity_real = x_real
        identity_imag = x_imag
        if self.hasdownsample is True:
            identity_real = self.convres_real(x_real) - self.convres_imag(x_imag)
            identity_imag = self.convres_imag(x_real) + self.convres_real(x_imag)
            identity_real = self.bnres_real(identity_real)
            identity_imag = self.bnres_imag(identity_imag)

        out_real = self.conv1_real(x_real) - self.conv1_imag(x_imag)
        out_imag = self.conv1_imag(x_real) + self.conv1_real(x_imag)
        out_real = self.bn1_real(out_real)
        out_imag = self.bn1_imag(out_imag)
        out_real = self.relu(out_real)
        out_imag = self.relu(out_imag)
        out_real_temp = self.conv2_real(out_real) - self.conv2_imag(out_imag)
        out_imag_temp = self.conv2_imag(out_real) + self.conv2_real(out_imag)
        out_real = out_real_temp
        out_imag = out_imag_temp
        out_real = self.bn2_real(out_real)
        out_imag = self.bn2_imag(out_imag)
        out_real += identity_real
        out_imag += identity_imag
        out_real = self.relu(out_real)
        out_imag = self.relu(out_imag)
        return [out_real, out_imag]

class BottleBlock(nn.Module):
    def __init__(self, inplanes, outplanes, stride = 1, hasdownsample = False):
        super(BottleBlock, self).__init__()
        midplanes = outplanes // 4

        self.hasdownsample = hasdownsample
        self.convres_real = conv1x1(inplanes, outplanes, stride)
        self.convres_imag = conv1x1(inplanes, outplanes, stride)
        self.bnres_real = normlayer(outplanes)
        self.bnres_imag = normlayer(outplanes)

        self.conv1_real = conv1x1(inplanes, midplanes, stride)
        self.conv1_imag = conv1x1(inplanes, midplanes, stride)
        self.bn1_real = normlayer(midplanes)
        self.bn1_imag = normlayer(midplanes)
        self.conv2_real = conv3x3(midplanes, midplanes)
        self.conv2_imag = conv3x3(midplanes, midplanes)
        self.bn2_real = normlayer(midplanes)
        self.bn2_imag = normlayer(midplanes)
        self.conv3_real = conv1x1(midplanes, outplanes)
        self.conv3_imag = conv1x1(midplanes, outplanes)
        self.bn3_real = normlayer(outplanes)
        self.bn3_imag = normlayer(outplanes)
        self.relu = nn.ReLU()

    def forward(self, x):
        x_real = x[0];
        x_imag = x[1];

        identity_real = x_real
        identity_imag = x_imag
        if self.hasdownsample is True:
            identity_real = self.convres_real(x_real) - self.convres_imag(x_imag)
            identity_imag = self.convres_imag(x_real) + self.convres_real(x_imag)
            identity_real = self.bnres_real(identity_real)
            identity_imag = self.bnres_imag(identity_imag)

        out_real = self.conv1_real(x_real) - self.conv1_imag(x_imag)
        out_imag = self.conv1_imag(x_real) + self.conv1_real(x_imag)
        out_real = self.bn1_real(out_real)
        out_imag = self.bn1_imag(out_imag)
        out_real = self.relu(out_real)
        out_imag = self.relu(out_imag)
        out_real_temp = self.conv2_real(out_real) - self.conv2_imag(out_imag)
        out_imag_temp = self.conv2_imag(out_real) + self.conv2_real(out_imag)
        out_real = out_real_temp
        out_imag = out_imag_temp
        out_real = self.bn2_real(out_real)
        out_imag = self.bn2_imag(out_imag)
        out_real_temp = self.conv3_real(out_real) - self.conv3_imag(out_imag)
        out_imag_temp = self.conv3_imag(out_real) + self.conv3_real(out_imag)
        out_real = out_real_temp
        out_imag = out_imag_temp
        out_real = self.bn3_real(out_real)
        out_imag = self.bn3_imag(out_imag)
        out_real += identity_real
        out_imag += identity_imag
        out_real = self.relu(out_real)
        out_imag = self.relu(out_imag)
        return [out_real, out_imag]

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
        self.fc_real = nn.Linear(self.fcIn, fcOut)
        self.fc_imag = nn.Linear(self.fcIn, fcOut)

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

        out_real = out[0]
        out_imag = out[1]
        out_real = F.adaptive_avg_pool2d(out_real, 1)
        out_imag = F.adaptive_avg_pool2d(out_imag, 1)
        out_real = out_real.view(-1, self.fcIn)
        out_imag = out_imag.view(-1, self.fcIn)
        out_real_temp = self.fc_real(out_real) - self.fc_imag(out_imag)
        out_imag_temp = self.fc_imag(out_real) + self.fc_real(out_imag)
        out_real = out_real_temp
        out_imag = out_imag_temp
        out = (out_real ** 2 + out_imag ** 2) ** 0.5
        return out
