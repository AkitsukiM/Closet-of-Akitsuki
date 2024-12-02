# How to use Ascend 910B

## CIFAR-10 with ResNet-50

```shell
# mirror: cann8.0.RC2-torch2.1.0-conda24.7.1-vscode4.12.0-ubuntu22.04-arm64
source /usr/local/Ascend/ascend-toolkit/set_env.sh

# ref: https://www.hiascend.com/document/detail/zh/Pytorch/60RC3/quickstart/useguide/useguide_0001.html
watch npu-smi info

# mkdir -p "/workspace/all-data/data/pretrained/"
# scp -P xxxxx ubuntu@124.16.xxx.xxx:"/media/e/Dataset/cifar-10-python.tar.gz" "/workspace/all-data/data/"
# scp -P xxxxx ubuntu@124.16.xxx.xxx:"/home/ubuntu/.cache/torch/hub/checkpoints/resnet50-0676ba61.pth" "/workspace/all-data/data/pretrained/"
# scp -P xxxxx ubuntu@124.16.xxx.xxx:"/home/ubuntu/.cache/torch/hub/checkpoints/swin_tiny_patch4_window7_224.pth" "/workspace/all-data/data/pretrained/"

ln -s "/workspace/all-data/data/" ./
mkdir -p "/root/.cache/torch/hub/checkpoints/"
ln -s "/workspace/all-data/data/pretrained/resnet50-0676ba61.pth" "/root/.cache/torch/hub/checkpoints/"
ln -s "/workspace/all-data/data/pretrained/swin_tiny_patch4_window7_224.pth" "/root/.cache/torch/hub/checkpoints/"

# python main_npu.py --use_ddp 0 --save_path "./work_dirs/ddp_0/"
# export HCCL_WHITELIST_DISABLE=1
python -m torch.distributed.launch --nnodes 1 --nproc_per_node 4 --master_addr 127.0.0.1 --master_port 29501 main_gpu2npu.py --save_path "./work_dirs/ddp_1/"
```

## MMDetection

```
conda create -n py39_torch210p6 python=3.9 -y
conda activate py39_torch210p6

# ref: https://www.hiascend.com/document/detail/zh/Pytorch/60RC3/configandinstg/instg/insg_0001.html
# 下载PyTorch安装包
wget https://download.pytorch.org/whl/cpu/torch-2.1.0-cp39-cp39-manylinux_2_17_aarch64.manylinux2014_aarch64.whl
# 下载torch_npu插件包
wget https://gitee.com/ascend/pytorch/releases/download/v6.0.rc2-pytorch2.1.0/torch_npu-2.1.0.post6-cp39-cp39-manylinux_2_17_aarch64.manylinux2014_aarch64.whl
# 安装命令
pip3 install torch-2.1.0-cp39-cp39-manylinux_2_17_aarch64.manylinux2014_aarch64.whl
pip3 install torch_npu-2.1.0.post6-cp39-cp39-manylinux_2_17_aarch64.manylinux2014_aarch64.whl

pip install -e /root/MindSpeed/

# ref: https://pytorch.org/get-started/previous-versions/#v210
pip install torchvision==0.16.0 --index https://pypi.tuna.tsinghua.edu.cn/simple/

pip install numpy==1.24.4 ninja==1.11.1.1 psutil==6.1.0

wget https://github.com/open-mmlab/mmengine/archive/refs/tags/v0.10.4.zip
cd mmengine-0.10.4/
pip install -v -e .

# ref: https://mmcv.readthedocs.io/zh-cn/v2.0.1/get_started/build.html#npu-mmcv
wget https://github.com/open-mmlab/mmcv/archive/refs/tags/v2.2.0.zip
cd mmcv-2.2.0/
MMCV_WITH_OPS=1 MAX_JOBS=8 FORCE_NPU=1 python setup.py build_ext
MMCV_WITH_OPS=1 FORCE_NPU=1 python setup.py develop

wget https://github.com/open-mmlab/mmdetection/archive/refs/tags/v3.3.0.zip
cd mmdetection-3.1.0/
pip install -r requirements/build.txt
pip install -v -e .

# 更改./mmdet/__init__.py
# 训练
./tools/dist_train.sh ./configs/swin/retinanet_swin-t-p4-w7_fpn_1x_coco.py 4
nohup ./tools/dist_train.sh ./configs/swin/retinanet_swin-t-p4-w7_fpn_1x_coco.py 4 > nohup.log 2>&1 &
```
