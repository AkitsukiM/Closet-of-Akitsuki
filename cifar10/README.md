# CIFAR-10 with ResNet-18

## 最新修订

因为没有注释所以花了点时间去理解自己以前到底写了些什么（结果还是没写注释嘛）

## 修订总结

所以一定要写net.train()和net.eval()！（没写这两句准确率降低4个百分点）

所以残差块到底是先加再relu还是先relu再加？（这里的测试结果，先加再relu的显存占用会更少一些，准确率却没什么区别；但在YOLOv3上mAP会降低0.1）

## 测试结果

accuracy ∈ [0.9167, 0.9208] （截至目前共训练-测试了6次）

使用NVIDIA RTX2080Ti：训练时长约40分钟

-----

Copyright (c) 2020 Marina Akitsuki. All rights reserved.

Date modified: 2020/11/06

