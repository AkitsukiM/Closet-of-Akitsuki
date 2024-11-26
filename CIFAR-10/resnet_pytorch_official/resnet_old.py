# coding=utf-8

import torch.nn as nn
import torchvision
# from torchvision.models import (
#     ResNet18_Weights,
#     ResNet34_Weights,
#     ResNet50_Weights,
#     ResNet101_Weights,
#     ResNet152_Weights)


class ResNet_cifar10(nn.Module):
    """
    为cifar10分类任务定义的ResNet

    增加了2层：
        nn.ReLU(inplace=True)
        nn.Linear(in_features=1000, out_features=10, bias=True)

    args:
        num_layers: int
        pretrained: bool = False
    """
    def __init__(self, num_layers, pretrained=False):
        super(ResNet_cifar10, self).__init__()

        self.resnet_official = self.select_resnet(num_layers=num_layers, pretrained=pretrained)

        self.cifar10_relu = nn.ReLU(inplace=True)
        self.cifar10_fc = nn.Linear(in_features=1000, out_features=10, bias=True)

    def select_resnet(self, num_layers, pretrained=False):
        if num_layers == 18:
            # previous version
            return torchvision.models.resnet18(pretrained=pretrained)
            # weights = ResNet18_Weights.IMAGENET1K_V1 if pretrained else None
            # return torchvision.models.resnet18(weights=weights)
        elif num_layers == 34:
            # previous version
            return torchvision.models.resnet34(pretrained=pretrained)
            # weights = ResNet34_Weights.IMAGENET1K_V1 if pretrained else None
            # return torchvision.models.resnet34(weights=weights)
        elif num_layers == 50:
            # previous version
            return torchvision.models.resnet50(pretrained=pretrained)
            # weights = ResNet50_Weights.IMAGENET1K_V1 if pretrained else None
            # return torchvision.models.resnet50(weights=weights)
        elif num_layers == 101:
            # previous version
            return torchvision.models.resnet101(pretrained=pretrained)
            # weights = ResNet101_Weights.IMAGENET1K_V1 if pretrained else None
            # return torchvision.models.resnet101(weights=weights)
        elif num_layers == 152:
            # previous version
            return torchvision.models.resnet152(pretrained=pretrained)
            # weights = ResNet152_Weights.IMAGENET1K_V1 if pretrained else None
            # return torchvision.models.resnet152(weights=weights)
        else:
            raise NotImplementedError

    def forward(self, x):
        y = self.resnet_official(x)
        y = self.cifar10_relu(y)
        y = self.cifar10_fc(y)
        return y


if __name__ == "__main__":
    model = ResNet_cifar10(num_layers=50, pretrained=True)
    print(model)

