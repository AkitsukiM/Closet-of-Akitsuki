# code from https://mmcv.readthedocs.io/zh-cn/v2.0.1/get_started/build.html#npu-mmcv

import torch
import torch_npu
from mmcv.ops import softmax_focal_loss

# Init tensor to the NPU
x = torch.randn(3, 10).npu()
y = torch.tensor([1, 5, 3]).npu()
w = torch.ones(10).float().npu()

output = softmax_focal_loss(x, y, 2.0, 0.25, w, 'none')
print(output)
