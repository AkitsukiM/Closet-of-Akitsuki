# Original code from https://pytorch.org/tutorials/beginner/blitz/cifar10_tutorial.html
# Original notes from https://pytorch-cn.readthedocs.io/zh/latest/

# Part.1 加载和标准化CIFAR10

import torch
import torchvision
import torchvision.transforms as transforms

# device detecting
gpu = True if torch.cuda.is_available() else False
device = torch.device("cuda:0" if gpu else "cpu")
# Assuming that we are on a CUDA machine, this should print a CUDA device:
print(gpu, device)

#
# torchvision.transforms.Compose(transforms)
# 将多个transform组合起来使用
#
# class torchvision.transforms.Normalize(mean, std)
# 对Tensor进行变换. 给定mean(均值)(R,G,B)与std(方差)(R，G，B), 将会把Tensor正则化. i.e. Normalized_image=(image-mean)/std
#
# class torchvision.transforms.ToTensor
# Conversion Transforms. 把一个取值范围是[0,255]的PIL.Image或者shape为(H,W,C)的numpy.ndarray, 转换成形状为[C,H,W], 取值范围是[0,1.0]的torch.FloadTensor
#
transform = transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5))])

#
# torchvision.datasets.CIFAR10(root, train=True, transform=None, target_transform=None, download=False)
# torchvision.datasets.CIFAR100(root, train=True, transform=None, target_transform=None, download=False)
# Parameters:
# -root: cifar-10-batches-py的根目录
# -train: True = 训练集, False = 测试集
# -download: True = 从互联上下载数据, 并将其放在root目录下; 如果数据集已经下载, 什么都不干.
#
trainset = torchvision.datasets.CIFAR10(root="./data", train=True, download=True, transform=transform)
#
# class torch.utils.data.DataLoader(dataset, batch_size=1, shuffle=False, sampler=None, num_workers=0, collate_fn=<function default_collate>, pin_memory=False, drop_last=False)
# 数据加载器. 组合数据集和采样器, 并在数据集上提供单进程或多进程迭代器.
# Parameters:
# dataset (Dataset) - 加载数据的数据集.
# batch_size (int, optional) - 每个batch加载多少个样本.
# shuffle (bool, optional) - 设置为True时会在每个epoch重新打乱数据.
# sampler (Sampler, optional) - 定义从数据集中提取样本的策略. 如果指定, 则忽略shuffle参数.
# num_workers (int, optional) - 用多少个子进程加载数据. 0表示数据将在主进程中加载.
# collate_fn (callable, optional) - ?
# pin_memory (bool, optional) - ?
# drop_last (bool, optional)
# - 如果数据集大小不能被batch size整除, 则设置为True后可删除最后一个不完整的batch.
# - 如果设为False并且数据集的大小不能被batch size整除, 则最后一个batch将更小.
#
trainloader = torch.utils.data.DataLoader(trainset, batch_size=4, shuffle=True, num_workers=(2 if gpu else 0))

testset = torchvision.datasets.CIFAR10(root="./data", train=False, download=True, transform=transform)
testloader = torch.utils.data.DataLoader(testset, batch_size=4, shuffle=False, num_workers=(2 if gpu else 0))

classes = ("plane", "car", "bird", "cat", "deer", "dog", "frog", "horse", "ship", "truck")

# Part.2 定义卷积神经网络

import torch.nn as nn
import torch.nn.functional as F

class Net(nn.Module):
    # 总的来说, 即为:
    # input -> conv2d -> relu -> maxpool2d -> conv2d -> relu -> maxpool2d 
    # -> view -> linear -> relu -> linear -> relu -> linear 
    # -> loss

    # 这里定义的是权值(初始化)
    def __init__(self):
        #
        # super() 函数是用于调用父类(超类)的一个方法
        # super(type[, object-or-type])
        # Parameters:
        # type -- 类
        # object-or-type -- 类, 一般是self
        # Python3 可以使用直接使用 super().xxx 代替 super(Class, self).xxx
        #
        super(Net, self).__init__()

        # 3 input image channel(R, G, B), 6 output channels, 5x5 square convolution
        #
        # class torch.nn.Conv2d(in_channels, out_channels, kernel_size, stride=1, padding=0, dilation=1, groups=1, bias=True)
        # Parameters:
        # in_channels(int) - 输入信号的通道
        # out_channels(int) - 卷积产生的通道
        # kerner_size(int or tuple) - 卷积核的尺寸
        # stride(int or tuple, optional) - 卷积步长
        # padding(int or tuple, optional) - 输入的每一条边补充0的层数
        # dilation(int or tuple, optional) - 卷积核元素之间的间距
        # groups(int, optional) - 从输入通道到输出通道的阻塞连接数
        # bias(bool, optional) - 如果bias=True, 添加偏置
        # 
        self.conv1 = nn.Conv2d(3, 6, 5)
        # 6 input channels(from previous), 16 out channels, 5x5 square convolution
        self.conv2 = nn.Conv2d(6, 16, 5)

        # 池化层: 使用最大池化方式, 池化窗口为2x2, 步长为2
        #
        # class torch.nn.MaxPool2d(kernel_size, stride=None, padding=0, dilation=1, return_indices=False, ceil_mode=False)
        # Parameters:
        # kernel_size(int or tuple) - max pooling的窗口大小
        # stride(int or tuple, optional) - max pooling的窗口移动的步长, 默认值是kernel_size
        # padding(int or tuple, optional) - 输入的每一条边补充0的层数
        # dilation(int or tuple, optional) - 一个控制窗口中元素步幅的参数
        # return_indices - 如果等于True, 会返回输出最大值的序号, 对于上采样操作会有帮助
        # ceil_mode - 如果等于True, 计算输出信号大小的时候, 会使用向上取整, 代替默认的向下取整的操作
        #
        self.pool = nn.MaxPool2d(2, 2)

        # 3 fully connected layers
        # 32*32->(conv1)->28*28->(pool)->14*14->(conv2)->10*10->(pool)->5*5
        #
        # class torch.nn.Linear(in_features, out_features, bias=True)
        # 对输入数据做线性变换: y=Ax+b
        # Parameters:
        # in_features - 每个输入样本的大小
        # out_features - 每个输出样本的大小
        # bias - 若设置为False, 这层不会学习偏置, 默认值True
        #
        self.fc1 = nn.Linear(16 * 5 * 5, 120)
        self.fc2 = nn.Linear(120, 84)
        self.fc3 = nn.Linear(84, 10)
        # 输出形式与标签形式?

    # 这里定义的是运算
    def forward(self, x):
        #
        # 非线性激活函数
        # torch.nn.functional.relu(input, inplace=False)
        #
        # conv1->relu->pool
        x = self.pool(F.relu(self.conv1(x)))

        # Max pooling over a (2, 2) window, also: x = F.max_pool2d(F.relu(self.conv1(x)), (2, 2))
        # If the size is a square you can only specify a single number: x = F.max_pool2d(F.relu(self.conv1(x)), 2)
        # However, there is a function .pool() defined before.

        # conv2->relu->pool
        x = self.pool(F.relu(self.conv2(x)))
        # 将矩阵转换成列向量形式(.view()操作)
        x = x.view(-1, 16 * 5 * 5)
        # fc1->relu
        x = F.relu(self.fc1(x))
        # fc2->relu
        x = F.relu(self.fc2(x))
        # fc3->relu
        x = self.fc3(x)
        return x

# 定义一个Net类的神经网络
net = Net()

# 把这个神经网络传输到设备上(如果有GPU的话)
if gpu: net.to(device)

# Part.3 定义Loss函数和权值更新

import torch.optim as optim

# 此处以交叉熵作为损失函数
# 又如.MSELoss()是以均方差作为损失函数
criterion = nn.CrossEntropyLoss()

# 更新权值
# 实践中使用的最简单的更新规则是随机梯度下降(SGD): weight = weight - learning_rate * gradient
# torch.optim中包含多种更新规则, 如SGD，Nesterov-SGD，Adam，RMSProp等.
# 使用例
#
"""
import torch.optim as optim

# create your optimizer
optimizer = optim.SGD(net.parameters(), lr=0.01)

# in your training loop:
optimizer.zero_grad() # zero the gradient buffers
output = net(input)
loss = criterion(output, target)
loss.backward()
optimizer.step() # Does the update
"""
#
# Notes: 使用optimizer.zero_grad()手动将梯度缓冲区设置为零, 这是因为梯度是按Backprop部分中的说明累积的.
#
# class torch.optim.SGD(params, lr, momentum=0, dampening=0, weight_decay=0, nesterov=False)
# Parameters:
# params(iterable) - 待优化参数的iterable或者是定义了参数组的dict
# lr(float) - 学习率(步长)
# momentum(float, optional) - 动量因子
# weight_decay(float, optional) - 权重衰减(L2惩罚)
# dampening(float, optional) - 动量的抑制因子
# nesterov(bool, optional) - 使用nesterov动量
#
optimizer = optim.SGD(net.parameters(), lr=0.001, momentum=0.9)

# Part.4 训练网络

for epoch in range(2): # loop over the dataset multiple times
    running_loss = 0.0
    #
    # enumerate() 函数用于将一个可遍历的数据对象(如列表、元组或字符串)组合为一个索引序列, 同时列出数据和数据下标
    # enumerate(sequence, [start=0])
    # Parameters:
    # sequence -- 一个序列, 迭代器或其他支持迭代对象.
    # start -- 下标起始位置.
    # 返回值
    # 返回 enumerate(枚举) 对象.
    #
    for i, data in enumerate(trainloader, 0):
        # get the inputs; data is a list of [inputs, labels]
        if gpu:
            inputs, labels = data[0].to(device), data[1].to(device)
        else:
            inputs, labels = data

        # zero the parameter gradients
        optimizer.zero_grad()

        # forward + backward + optimize
        outputs = net(inputs)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        # print statistics
        running_loss += loss.item()
        if i % 2000 == 1999: # print every 2000 mini-batches
            print("[%d, %5d] loss: %.3f" % (epoch + 1, i + 1, running_loss / 2000))
            running_loss = 0.0

print("Finished Training")

# Part.5 在测试数据上测试网络

set_correct = 0.0
set_total = 0.0
class_correct = [0.0 for i in range(10)]
class_total = [0.0 for i in range(10)]

# 通过使用torch.no_grad()包装代码块来停止使用.requires_grad = True跟踪历史记录上的autograd.
with torch.no_grad():
    for data in testloader:
        if gpu:
            inputs, labels = data[0].to(device), data[1].to(device)
        else:
            inputs, labels = data

        outputs = net(inputs)
        #
        # torch.max(input, dim, max=None, max_indices=None) -> (Tensor, LongTensor)
        # 返回输入张量给定维度上每行的最大值, 并同时返回每个最大值的位置索引.
        # 输出形状中, 将dim(维数)设定为1, 其它与输入形状保持一致.
        # Parameters:
        # input (Tensor) - 输入张量
        # dim (int) - 指定的维度
        # max (Tensor, optional) - 结果张量，包含给定维度上的最大值
        # max_indices (LongTensor, optional) - 结果张量，包含给定维度上每个最大值的位置索引
        #
        _, predictions = torch.max(outputs.data, 1)

        for i in range(4):
            label = labels[i]
            set_total += 1
            class_total[label] += 1
            if predictions[i] == labels[i]:
                set_correct += 1
                class_correct[label] += 1

print("Accuracy of the network: %d/%d = %.1f %%" % (set_correct, set_total, 100 * set_correct / set_total))
for i in range(10):
    print("Accuracy of %-5s : %d/%d = %.1f %%" % (classes[i], class_correct[i], class_total[i], 100 * class_correct[i] / class_total[i]))
