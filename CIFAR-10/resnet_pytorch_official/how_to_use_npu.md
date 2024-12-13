# How to use Ascend 910B

## CIFAR-10 with ResNet-50

```shell
# mirror: cann8.0.RC2-torch2.1.0-conda24.7.1-vscode4.12.0-ubuntu22.04-arm64
# Execute this command every time a new console is opened!
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

## OpenMMLab Series

已支持：mmengine-0.10.4, mmcv-latest (>2.2.0, date-241212), mmdetection-3.3.0, mmyolo-0.6.0, mmrotate-1.x。

```
# mirror: cann8.0.RC2-torch2.1.0-conda24.7.1-vscode4.12.0-ubuntu22.04-arm64
# Execute this command every time a new console is opened!
source /usr/local/Ascend/ascend-toolkit/set_env.sh

conda create -n openmmlab210p6b python=3.9 -y
mv /home/miniconda3/envs/openmmlab210p6b/ /workspace/all-data/envs/
ln -s /workspace/all-data/envs/openmmlab210p6b/ /home/miniconda3/envs/
conda activate openmmlab210p6b
mkdir -p "/workspace/openmmlab210p6b/"
cd "/workspace/openmmlab210p6b/"

# ref: https://www.hiascend.com/document/detail/zh/Pytorch/60RC3/configandinstg/instg/insg_0001.html
# 下载PyTorch安装包
wget https://download.pytorch.org/whl/cpu/torch-2.1.0-cp39-cp39-manylinux_2_17_aarch64.manylinux2014_aarch64.whl
# 下载torch_npu插件包
wget https://gitee.com/ascend/pytorch/releases/download/v6.0.rc2-pytorch2.1.0/torch_npu-2.1.0.post6-cp39-cp39-manylinux_2_17_aarch64.manylinux2014_aarch64.whl
# 安装命令
pip3 install torch-2.1.0-cp39-cp39-manylinux_2_17_aarch64.manylinux2014_aarch64.whl
pip3 install torch_npu-2.1.0.post6-cp39-cp39-manylinux_2_17_aarch64.manylinux2014_aarch64.whl

# ref: https://pytorch.org/get-started/previous-versions/#v210
pip install torchvision==0.16.0 --index https://pypi.tuna.tsinghua.edu.cn/simple/

# ref: https://gitee.com/ascend/MindSpeed
git clone https://gitee.com/ascend/MindSpeed.git
pip install -e MindSpeed

pip install numpy==1.26.4 ninja==1.11.1.1 psutil==6.1.0 pandas libcst prettytable jedi

pip install mmengine==0.10.4

# ref: https://mmcv.readthedocs.io/zh-cn/v2.0.1/get_started/build.html#npu-mmcv
git clone https://github.com/open-mmlab/mmcv.git
cd mmcv/
MMCV_WITH_OPS=1 MAX_JOBS=8 FORCE_NPU=1 python setup.py build_ext
MMCV_WITH_OPS=1 FORCE_NPU=1 python setup.py develop
cd ../

wget https://github.com/open-mmlab/mmdetection/archive/refs/tags/v3.3.0.zip -O mmdetection-3.3.0.zip
unzip mmdetection-3.3.0.zip
cd mmdetection-3.3.0/
pip install -r requirements/build.txt
pip install -v -e .

# 更改./mmdet/__init__.py中的mmcv版本上限要求为'3.0.0'
# 训练
# ./tools/dist_train.sh ./configs/swin/retinanet_swin-t-p4-w7_fpn_1x_coco.py 4
# nohup ./tools/dist_train.sh ./configs/swin/retinanet_swin-t-p4-w7_fpn_1x_coco.py 4 > nohup.log 2>&1 &
cd ../

# ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### #

wget https://github.com/open-mmlab/mmyolo/archive/refs/tags/v0.6.0.zip -O mmyolo-0.6.0.zip
unzip mmyolo-0.6.0.zip
cd mmyolo-0.6.0/
# ref: https://github.com/open-mmlab/mmyolo/issues/1018
pip install albumentations==1.4.0
pip install -r requirements/albu.txt
pip install -v -e .

# 更改./mmyolo/__init__.py中的mmcv版本上限要求为'3.0.0'
# 训练
# ./tools/dist_train.sh ./configs/yolov8/yolov8_s_syncbn_fast_8xb16-500e_coco.py 4
# nohup ./tools/dist_train.sh ./configs/yolov8/yolov8_s_syncbn_fast_8xb16-500e_coco.py 4 > nohup.log 2>&1 &
cd ../

# ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### #

pip install ../whl/mx_driving-1.0.0+gitb771879-cp39-cp39-linux_aarch64.whl
export ASCEND_CUSTOM_OPP_PATH=/home/miniconda3/envs/openmmlab210p6b/lib/python3.9/site-packages/mx_driving/packages/vendors/customize/
export LD_LIBRARY_PATH=/home/miniconda3/envs/openmmlab210p6b/lib/python3.9/site-packages/mx_driving/packages/vendors/customize/op_api/lib/:$LD_LIBRARY_PATH

wget https://github.com/open-mmlab/mmrotate/archive/refs/heads/1.x.zip -O mmrotate-1.x.zip
unzip mmrotate-1.x.zip
cd mmrotate-1.x/
pip install -r requirements/build.txt
pip install -v -e .

# 更改./mmrotate/__init__.py中的mmcv版本上限要求为'3.0.0'，mmdet版本上限要求为'4.0.0'
# 训练
# chmod +x ./tools/*.sh
# ASCEND_RT_VISIBLE_DEVICES=4,5,6,7 ./tools/dist_train.sh ./configs/rotated_retinanet/rotated-retinanet-rbox-le90_r50_fpn_1x_dota.py 4
# nohup ASCEND_RT_VISIBLE_DEVICES=4,5,6,7 ./tools/dist_train.sh ./configs/rotated_retinanet/rotated-retinanet-rbox-le90_r50_fpn_1x_dota.py 4 > nohup.log 2>&1 &
cd ../
```

## Dataset

MSCOCO2017:

```
scp -r -P xxxxx ubuntu@124.16.xxxxx:"/media/e/Dataset/MSCOCO2017/" "/workspace/all-data/data/"
```

DOTA-v1.0:

```
scp -r -P xxxxx ubuntu@124.16.xxxxx:"/media/e/Dataset/DOTA/" "/workspace/all-data/data/"

ln -s /workspace/all-data/data/ ./
ln -s /workspace/all-data/work_dirs/ ./
# 
python ../../test-tools/md5_calc.py --path ./data/DOTA/train.tar.gz
# cfb5007ada913241e02c24484e12d5d2
python ../../test-tools/md5_calc.py --path ./data/DOTA/val.tar.gz
# a53e74b0d69dacf3ffcb438accd60c45
python ../../test-tools/md5_calc.py --path ./data/DOTA/test/part1.zip
# d3028e48da64b37ad2f2f5f31059e0da
python ../../test-tools/md5_calc.py --path ./data/DOTA/test/part2.zip
# 99f779850cc44b8f8b28d348494c6b41
# 
tar -xzf ./data/DOTA/train.tar.gz -C ./data/DOTA/
tar -xzf ./data/DOTA/val.tar.gz -C ./data/DOTA/
unzip ./data/DOTA/test/part1.zip -d ./data/DOTA/test/
unzip ./data/DOTA/test/part2.zip -d ./data/DOTA/test/
# 
python ../../test-tools/dir_list.py --path ./data/DOTA/train/images/ --output ./data/DOTA/train/trainset.txt
# 1411
python ../../test-tools/dir_list.py --path ./data/DOTA/val/images/ --output ./data/DOTA/val/valset.txt
# 458
python ../../test-tools/dir_list.py --path ./data/DOTA/test/images/ --output ./data/DOTA/test/testset.txt
# 937

python tools/data/dota/split/img_split.py --base-json tools/data/dota/split/split_configs/ss_train.json
# Total images number: 15749
python tools/data/dota/split/img_split.py --base-json tools/data/dota/split/split_configs/ss_val.json
# Total images number: 5297
python tools/data/dota/split/img_split.py --base-json tools/data/dota/split/split_configs/ss_trainval.json
# Total images number: 21046
python tools/data/dota/split/img_split.py --base-json tools/data/dota/split/split_configs/ss_test.json
# Total images number: 10833
python tools/data/dota/split/img_split.py --base-json tools/data/dota/split/split_configs/ms_trainval.json
# Total images number: 138883
python tools/data/dota/split/img_split.py --base-json tools/data/dota/split/split_configs/ms_test.json
# Total images number: 71888
```

Others:

```
scp -r -P xxxxx ubuntu@124.16.xxxxx:"/media/e/Dataset/DOTA-v1.0/" "/workspace/all-data/data/"
scp -r -P xxxxx ubuntu@124.16.xxxxx:"/media/e/Dataset/DOTA-v1.5/" "/workspace/all-data/data/"
scp -r -P xxxxx ubuntu@124.16.xxxxx:"/media/e/Dataset/DOTA-v2.0/" "/workspace/all-data/data/"
scp -r -P xxxxx ubuntu@124.16.xxxxx:"/media/e/HEPDataset/Neutron_sample_full_zip/" "/workspace/all-data/data/"
scp -r -P xxxxx ubuntu@124.16.xxxxx:"/media/e/HEPDataset/HFtag_sample/" "/workspace/all-data/data/"
```
