# CIFAR-10 with ResNet-50 on Ascend 910B

```shell
# mirror: cann7.0-pytorch1.11.0-deepSpeed0.9.2-vscode4.22-ubuntu22.04-arm64

# https://www.hiascend.com/document/detail/zh/Pytorch/60RC3/quickstart/useguide/useguide_0001.html
watch npu-smi info
whereis conda
/home/miniconda3/bin/conda init
source /root/.bashrc
conda env list
conda activate ascend-chatglm2-6b-py37

mkdir data
mkdir -p "/root/.cache/torch/hub/checkpoints/"
scp -P xxxxx ubuntu@124.16.xxx.xxx:"/media/e/Dataset/cifar-10-python.tar.gz" "./data/"
scp -P xxxxx ubuntu@124.16.xxx.xxx:"/home/ubuntu/.cache/torch/hub/checkpoints/resnet50-0676ba61.pth" "/root/.cache/torch/hub/checkpoints/resnet50-0676ba61.pth"

pip install torchvision==0.12.0 --index https://pypi.tuna.tsinghua.edu.cn/simple/
python main.py --use_ddp 0 --save_path "./work_dirs/ddp_0/"

export HCCL_WHITELIST_DISABLE=1
python -m torch.distributed.launch --nnodes 1 --nproc_per_node 2 --master_addr 127.0.0.1 --master_port 29501 main.py --save_path "./work_dirs/ddp_1/"
```
