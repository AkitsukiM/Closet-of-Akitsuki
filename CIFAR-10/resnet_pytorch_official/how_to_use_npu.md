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

已支持：mmengine-0.10.4, mmcv-2.2.0, mmdetection-3.3.0, mmyolo-0.6.0；尚未支持：mmrotate-1.x。

```
# mirror: cann8.0.RC2-torch2.1.0-conda24.7.1-vscode4.12.0-ubuntu22.04-arm64
# Execute this command every time a new console is opened!
source /usr/local/Ascend/ascend-toolkit/set_env.sh

conda create -n openmmlab210p6a python=3.9 -y
conda activate openmmlab210p6a

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

pip install numpy==1.26.4 ninja==1.11.1.1 psutil==6.1.0

wget https://github.com/open-mmlab/mmengine/archive/refs/tags/v0.10.4.zip -O mmengine-0.10.4.zip
unzip mmengine-0.10.4.zip
cd mmengine-0.10.4/
pip install -v -e .
cd ../

# ref: https://mmcv.readthedocs.io/zh-cn/v2.0.1/get_started/build.html#npu-mmcv
wget https://github.com/open-mmlab/mmcv/archive/refs/tags/v2.2.0.zip -O mmcv-2.2.0.zip
unzip mmcv-2.2.0.zip
cd mmcv-2.2.0/
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

wget https://github.com/open-mmlab/mmrotate/archive/refs/heads/1.x.zip -O mmrotate-1.x.zip
unzip mmrotate-1.x.zip
cd mmrotate-1.x/
pip install -r requirements/build.txt
pip install -v -e .

# 更改./mmrotate/__init__.py中的mmcv版本上限要求为'3.0.0'，mmdet版本上限要求为'4.0.0'
# 训练
# ./tools/dist_train.sh ./configs/rotated_retinanet/rotated-retinanet-rbox-le90_r50_fpn_1x_dota.py 4
# nohup ./tools/dist_train.sh ./configs/rotated_retinanet/rotated-retinanet-rbox-le90_r50_fpn_1x_dota.py 4 > nohup.log 2>&1 &
```

其中DOTA-v1.0数据集可从[官网](https://captain-whu.github.io/DOTA/dataset.html)下载。解压后的文件组织结构：

```
mmrotate/data/DOTA/  
    ├ train  
        ├ images  
            ├ P0000.png    ┐  
            ├ ...          ├ 1411 images  
            └ P2805.png    ┘  
        └ labelTxt  
            ├ P0000.txt  
            ├ ...  
            └ P2805.txt  
    ├ val  
        ├ images  
            ├ P0003.png    ┐  
            ├ ...          ├ 458 images  
            └ P2802.png    ┘  
        └ labelTxt  
            ├ P0000.txt  
            ├ ...  
            └ P2802.txt  
    └ test  
        └ images  
            ├ P0006.png    ┐  
            ├ ...          ├ 937 images  
            └ P2806.png    ┘  
```

对数据集进行切片操作：

```
python tools/data/dota/split/img_split.py --base-json tools/data/dota/split/split_configs/ss_trainval.json
# Total images number: 21046
```

训练报错并弹窗"Cannot reconnect. Please reload the window."：

```
(openmmlab210p6a) root@ide-606bd550-ae7e-44de-9225-8c55c9aca344-544648fff6-vdj6n:/workspace/openmmlab210p6a/mmrotate-1.x# ./tools/dist_train.sh ./configs/rotated_retinanet/rotated-retinanet-rbox-le90_r50_fpn_1x_dota.py 4
/home/miniconda3/envs/openmmlab210p6a/lib/python3.9/site-packages/torch/distributed/launch.py:181: FutureWarning: The module torch.distributed.launch is deprecated
and will be removed in future. Use torchrun.
Note that --use-env is set by default in torchrun.
If your script expects `--local-rank` argument to be set, please
change it to read from `os.environ['LOCAL_RANK']` instead. See 
https://pytorch.org/docs/stable/distributed.html#launch-utility for 
further instructions

  warnings.warn(
[2024-12-09 17:26:10,288] torch.distributed.run: [WARNING] 
[2024-12-09 17:26:10,288] torch.distributed.run: [WARNING] *****************************************
[2024-12-09 17:26:10,288] torch.distributed.run: [WARNING] Setting OMP_NUM_THREADS environment variable for each process to be 1 in default, to avoid your system being overloaded, please further tune the variable for optimal performance in your application as needed. 
[2024-12-09 17:26:10,288] torch.distributed.run: [WARNING] *****************************************
[W compiler_depend.ts:623] Warning: expandable_segments currently defaults to false. You can enable this feature by `export PYTORCH_NPU_ALLOC_CONF = expandable_segments:True`. (function operator())
[W compiler_depend.ts:623] Warning: expandable_segments currently defaults to false. You can enable this feature by `export PYTORCH_NPU_ALLOC_CONF = expandable_segments:True`. (function operator())
[W compiler_depend.ts:623] Warning: expandable_segments currently defaults to false. You can enable this feature by `export PYTORCH_NPU_ALLOC_CONF = expandable_segments:True`. (function operator())
[W compiler_depend.ts:623] Warning: expandable_segments currently defaults to false. You can enable this feature by `export PYTORCH_NPU_ALLOC_CONF = expandable_segments:True`. (function operator())
/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/utils/dl_utils/setup_env.py:56: UserWarning: Setting MKL_NUM_THREADS environment variable for each process to be 1 in default, to avoid your system being overloaded, please further tune the variable for optimal performance in your application as needed.
  warnings.warn(
/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/utils/dl_utils/setup_env.py:56: UserWarning: Setting MKL_NUM_THREADS environment variable for each process to be 1 in default, to avoid your system being overloaded, please further tune the variable for optimal performance in your application as needed.
  warnings.warn(
/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/utils/dl_utils/setup_env.py:56: UserWarning: Setting MKL_NUM_THREADS environment variable for each process to be 1 in default, to avoid your system being overloaded, please further tune the variable for optimal performance in your application as needed.
  warnings.warn(
/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/utils/dl_utils/setup_env.py:56: UserWarning: Setting MKL_NUM_THREADS environment variable for each process to be 1 in default, to avoid your system being overloaded, please further tune the variable for optimal performance in your application as needed.
  warnings.warn(
12/09 17:26:45 - mmengine - INFO - 
------------------------------------------------------------
System environment:
    sys.platform: linux
    Python: 3.9.20 (main, Oct  3 2024, 07:31:44) [GCC 11.2.0]
    CUDA available: False
    MUSA available: False
    numpy_random_seed: 2145455135
    GCC: gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
    PyTorch: 2.1.0
    PyTorch compiling details: PyTorch built with:
  - GCC 10.2
  - C++ Version: 201703
  - Intel(R) MKL-DNN v3.1.1 (Git Hash 64f6bcbcbab628e96f33a62c3e975f8535a7bde4)
  - OpenMP 201511 (a.k.a. OpenMP 4.5)
  - LAPACK is enabled (usually provided by MKL)
  - NNPACK is enabled
  - CPU capability usage: NO AVX
  - Build settings: BLAS_INFO=open, BUILD_TYPE=Release, CXX_COMPILER=/opt/rh/devtoolset-10/root/usr/bin/c++, CXX_FLAGS= -D_GLIBCXX_USE_CXX11_ABI=0 -fabi-version=11 -fvisibility-inlines-hidden -DUSE_PTHREADPOOL -DNDEBUG -DUSE_KINETO -DLIBKINETO_NOCUPTI -DLIBKINETO_NOROCTRACER -DUSE_QNNPACK -DUSE_PYTORCH_QNNPACK -DUSE_XNNPACK -DSYMBOLICATE_MOBILE_DEBUG_HANDLE -O2 -fPIC -Wall -Wextra -Werror=return-type -Werror=non-virtual-dtor -Werror=bool-operation -Wnarrowing -Wno-missing-field-initializers -Wno-type-limits -Wno-array-bounds -Wno-unknown-pragmas -Wno-unused-parameter -Wno-unused-function -Wno-unused-result -Wno-strict-overflow -Wno-strict-aliasing -Wno-stringop-overflow -Wno-psabi -Wno-error=pedantic -Wno-error=old-style-cast -Wno-invalid-partial-specialization -Wno-unused-private-field -Wno-aligned-allocation-unavailable -Wno-missing-braces -fdiagnostics-color=always -faligned-new -Wno-unused-but-set-variable -Wno-maybe-uninitialized -fno-math-errno -fno-trapping-math -Werror=format -Werror=cast-function-type -Wno-stringop-overflow, LAPACK_INFO=open, TORCH_DISABLE_GPU_ASSERTS=ON, TORCH_VERSION=2.1.0, USE_CUDA=OFF, USE_CUDNN=OFF, USE_EIGEN_FOR_BLAS=ON, USE_EXCEPTION_PTR=1, USE_GFLAGS=OFF, USE_GLOG=OFF, USE_MKL=OFF, USE_MKLDNN=ON, USE_MPI=OFF, USE_NCCL=OFF, USE_NNPACK=ON, USE_OPENMP=ON, USE_ROCM=OFF, 

    TorchVision: 0.16.0
    OpenCV: 4.10.0
    MMEngine: 0.10.4

Runtime environment:
    cudnn_benchmark: False
    mp_cfg: {'mp_start_method': 'fork', 'opencv_num_threads': 0}
    dist_cfg: {'backend': 'nccl'}
    seed: 2145455135
    Distributed launcher: pytorch
    Distributed training: True
    GPU number: 4
------------------------------------------------------------

12/09 17:26:46 - mmengine - INFO - Config:
angle_version = 'le90'
backend_args = None
data_root = 'data/split_ss_dota/'
dataset_type = 'DOTADataset'
default_hooks = dict(
    checkpoint=dict(interval=1, type='CheckpointHook'),
    logger=dict(interval=50, type='LoggerHook'),
    param_scheduler=dict(type='ParamSchedulerHook'),
    sampler_seed=dict(type='DistSamplerSeedHook'),
    timer=dict(type='IterTimerHook'),
    visualization=dict(type='mmdet.DetVisualizationHook'))
default_scope = 'mmrotate'
env_cfg = dict(
    cudnn_benchmark=False,
    dist_cfg=dict(backend='nccl'),
    mp_cfg=dict(mp_start_method='fork', opencv_num_threads=0))
launcher = 'pytorch'
load_from = None
log_level = 'INFO'
log_processor = dict(by_epoch=True, type='LogProcessor', window_size=50)
model = dict(
    backbone=dict(
        depth=50,
        frozen_stages=1,
        init_cfg=dict(checkpoint='torchvision://resnet50', type='Pretrained'),
        norm_cfg=dict(requires_grad=True, type='BN'),
        norm_eval=True,
        num_stages=4,
        out_indices=(
            0,
            1,
            2,
            3,
        ),
        style='pytorch',
        type='mmdet.ResNet'),
    bbox_head=dict(
        anchor_generator=dict(
            angle_version='le90',
            octave_base_scale=4,
            ratios=[
                1.0,
                0.5,
                2.0,
            ],
            scales_per_octave=3,
            strides=[
                8,
                16,
                32,
                64,
                128,
            ],
            type='FakeRotatedAnchorGenerator'),
        bbox_coder=dict(
            angle_version='le90',
            edge_swap=True,
            norm_factor=None,
            proj_xy=True,
            target_means=(
                0.0,
                0.0,
                0.0,
                0.0,
                0.0,
            ),
            target_stds=(
                1.0,
                1.0,
                1.0,
                1.0,
                1.0,
            ),
            type='DeltaXYWHTRBBoxCoder'),
        feat_channels=256,
        in_channels=256,
        loss_bbox=dict(loss_weight=1.0, type='mmdet.L1Loss'),
        loss_cls=dict(
            alpha=0.25,
            gamma=2.0,
            loss_weight=1.0,
            type='mmdet.FocalLoss',
            use_sigmoid=True),
        num_classes=15,
        stacked_convs=4,
        type='mmdet.RetinaHead'),
    data_preprocessor=dict(
        bgr_to_rgb=True,
        boxtype2tensor=False,
        mean=[
            123.675,
            116.28,
            103.53,
        ],
        pad_size_divisor=32,
        std=[
            58.395,
            57.12,
            57.375,
        ],
        type='mmdet.DetDataPreprocessor'),
    neck=dict(
        add_extra_convs='on_input',
        in_channels=[
            256,
            512,
            1024,
            2048,
        ],
        num_outs=5,
        out_channels=256,
        start_level=1,
        type='mmdet.FPN'),
    test_cfg=dict(
        max_per_img=2000,
        min_bbox_size=0,
        nms=dict(iou_threshold=0.1, type='nms_rotated'),
        nms_pre=2000,
        score_thr=0.05),
    train_cfg=dict(
        allowed_border=-1,
        assigner=dict(
            ignore_iof_thr=-1,
            iou_calculator=dict(type='RBboxOverlaps2D'),
            min_pos_iou=0,
            neg_iou_thr=0.4,
            pos_iou_thr=0.5,
            type='mmdet.MaxIoUAssigner'),
        debug=False,
        pos_weight=-1,
        sampler=dict(type='mmdet.PseudoSampler')),
    type='mmdet.RetinaNet')
optim_wrapper = dict(
    clip_grad=dict(max_norm=35, norm_type=2),
    optimizer=dict(lr=0.0025, momentum=0.9, type='SGD', weight_decay=0.0001),
    type='OptimWrapper')
param_scheduler = [
    dict(
        begin=0,
        by_epoch=False,
        end=500,
        start_factor=0.3333333333333333,
        type='LinearLR'),
    dict(
        begin=0,
        by_epoch=True,
        end=12,
        gamma=0.1,
        milestones=[
            8,
            11,
        ],
        type='MultiStepLR'),
]
resume = False
test_cfg = dict(type='TestLoop')
test_dataloader = dict(
    batch_size=1,
    dataset=dict(
        ann_file='trainval/annfiles/',
        data_prefix=dict(img_path='trainval/images/'),
        data_root='data/split_ss_dota/',
        pipeline=[
            dict(backend_args=None, type='mmdet.LoadImageFromFile'),
            dict(keep_ratio=True, scale=(
                1024,
                1024,
            ), type='mmdet.Resize'),
            dict(
                box_type='qbox', type='mmdet.LoadAnnotations', with_bbox=True),
            dict(
                box_type_mapping=dict(gt_bboxes='rbox'),
                type='ConvertBoxType'),
            dict(
                meta_keys=(
                    'img_id',
                    'img_path',
                    'ori_shape',
                    'img_shape',
                    'scale_factor',
                ),
                type='mmdet.PackDetInputs'),
        ],
        test_mode=True,
        type='DOTADataset'),
    drop_last=False,
    num_workers=2,
    persistent_workers=True,
    sampler=dict(shuffle=False, type='DefaultSampler'))
test_evaluator = dict(metric='mAP', type='DOTAMetric')
test_pipeline = [
    dict(backend_args=None, type='mmdet.LoadImageFromFile'),
    dict(keep_ratio=True, scale=(
        1024,
        1024,
    ), type='mmdet.Resize'),
    dict(
        meta_keys=(
            'img_id',
            'img_path',
            'ori_shape',
            'img_shape',
            'scale_factor',
        ),
        type='mmdet.PackDetInputs'),
]
train_cfg = dict(max_epochs=12, type='EpochBasedTrainLoop', val_interval=1)
train_dataloader = dict(
    batch_sampler=None,
    batch_size=2,
    dataset=dict(
        ann_file='trainval/annfiles/',
        data_prefix=dict(img_path='trainval/images/'),
        data_root='data/split_ss_dota/',
        filter_cfg=dict(filter_empty_gt=True),
        pipeline=[
            dict(backend_args=None, type='mmdet.LoadImageFromFile'),
            dict(
                box_type='qbox', type='mmdet.LoadAnnotations', with_bbox=True),
            dict(
                box_type_mapping=dict(gt_bboxes='rbox'),
                type='ConvertBoxType'),
            dict(keep_ratio=True, scale=(
                1024,
                1024,
            ), type='mmdet.Resize'),
            dict(
                direction=[
                    'horizontal',
                    'vertical',
                    'diagonal',
                ],
                prob=0.75,
                type='mmdet.RandomFlip'),
            dict(type='mmdet.PackDetInputs'),
        ],
        type='DOTADataset'),
    num_workers=2,
    persistent_workers=True,
    sampler=dict(shuffle=True, type='DefaultSampler'))
train_pipeline = [
    dict(backend_args=None, type='mmdet.LoadImageFromFile'),
    dict(box_type='qbox', type='mmdet.LoadAnnotations', with_bbox=True),
    dict(box_type_mapping=dict(gt_bboxes='rbox'), type='ConvertBoxType'),
    dict(keep_ratio=True, scale=(
        1024,
        1024,
    ), type='mmdet.Resize'),
    dict(
        direction=[
            'horizontal',
            'vertical',
            'diagonal',
        ],
        prob=0.75,
        type='mmdet.RandomFlip'),
    dict(type='mmdet.PackDetInputs'),
]
val_cfg = dict(type='ValLoop')
val_dataloader = dict(
    batch_size=1,
    dataset=dict(
        ann_file='trainval/annfiles/',
        data_prefix=dict(img_path='trainval/images/'),
        data_root='data/split_ss_dota/',
        pipeline=[
            dict(backend_args=None, type='mmdet.LoadImageFromFile'),
            dict(keep_ratio=True, scale=(
                1024,
                1024,
            ), type='mmdet.Resize'),
            dict(
                box_type='qbox', type='mmdet.LoadAnnotations', with_bbox=True),
            dict(
                box_type_mapping=dict(gt_bboxes='rbox'),
                type='ConvertBoxType'),
            dict(
                meta_keys=(
                    'img_id',
                    'img_path',
                    'ori_shape',
                    'img_shape',
                    'scale_factor',
                ),
                type='mmdet.PackDetInputs'),
        ],
        test_mode=True,
        type='DOTADataset'),
    drop_last=False,
    num_workers=2,
    persistent_workers=True,
    sampler=dict(shuffle=False, type='DefaultSampler'))
val_evaluator = dict(metric='mAP', type='DOTAMetric')
val_pipeline = [
    dict(backend_args=None, type='mmdet.LoadImageFromFile'),
    dict(keep_ratio=True, scale=(
        1024,
        1024,
    ), type='mmdet.Resize'),
    dict(box_type='qbox', type='mmdet.LoadAnnotations', with_bbox=True),
    dict(box_type_mapping=dict(gt_bboxes='rbox'), type='ConvertBoxType'),
    dict(
        meta_keys=(
            'img_id',
            'img_path',
            'ori_shape',
            'img_shape',
            'scale_factor',
        ),
        type='mmdet.PackDetInputs'),
]
vis_backends = [
    dict(type='LocalVisBackend'),
]
visualizer = dict(
    name='visualizer',
    type='RotLocalVisualizer',
    vis_backends=[
        dict(type='LocalVisBackend'),
    ])
work_dir = './work_dirs/rotated-retinanet-rbox-le90_r50_fpn_1x_dota'

12/09 17:26:47 - mmengine - INFO - Hooks will be executed in the following order:
before_run:
(VERY_HIGH   ) RuntimeInfoHook                    
(BELOW_NORMAL) LoggerHook                         
 -------------------- 
before_train:
(VERY_HIGH   ) RuntimeInfoHook                    
(NORMAL      ) IterTimerHook                      
(VERY_LOW    ) CheckpointHook                     
 -------------------- 
before_train_epoch:
(VERY_HIGH   ) RuntimeInfoHook                    
(NORMAL      ) IterTimerHook                      
(NORMAL      ) DistSamplerSeedHook                
 -------------------- 
before_train_iter:
(VERY_HIGH   ) RuntimeInfoHook                    
(NORMAL      ) IterTimerHook                      
 -------------------- 
after_train_iter:
(VERY_HIGH   ) RuntimeInfoHook                    
(NORMAL      ) IterTimerHook                      
(BELOW_NORMAL) LoggerHook                         
(LOW         ) ParamSchedulerHook                 
(VERY_LOW    ) CheckpointHook                     
 -------------------- 
after_train_epoch:
(NORMAL      ) IterTimerHook                      
(LOW         ) ParamSchedulerHook                 
(VERY_LOW    ) CheckpointHook                     
 -------------------- 
before_val:
(VERY_HIGH   ) RuntimeInfoHook                    
 -------------------- 
before_val_epoch:
(NORMAL      ) IterTimerHook                      
 -------------------- 
before_val_iter:
(NORMAL      ) IterTimerHook                      
 -------------------- 
after_val_iter:
(NORMAL      ) IterTimerHook                      
(NORMAL      ) DetVisualizationHook               
(BELOW_NORMAL) LoggerHook                         
 -------------------- 
after_val_epoch:
(VERY_HIGH   ) RuntimeInfoHook                    
(NORMAL      ) IterTimerHook                      
(BELOW_NORMAL) LoggerHook                         
(LOW         ) ParamSchedulerHook                 
(VERY_LOW    ) CheckpointHook                     
 -------------------- 
after_val:
(VERY_HIGH   ) RuntimeInfoHook                    
 -------------------- 
after_train:
(VERY_HIGH   ) RuntimeInfoHook                    
(VERY_LOW    ) CheckpointHook                     
 -------------------- 
before_test:
(VERY_HIGH   ) RuntimeInfoHook                    
 -------------------- 
before_test_epoch:
(NORMAL      ) IterTimerHook                      
 -------------------- 
before_test_iter:
(NORMAL      ) IterTimerHook                      
 -------------------- 
after_test_iter:
(NORMAL      ) IterTimerHook                      
(NORMAL      ) DetVisualizationHook               
(BELOW_NORMAL) LoggerHook                         
 -------------------- 
after_test_epoch:
(VERY_HIGH   ) RuntimeInfoHook                    
(NORMAL      ) IterTimerHook                      
(BELOW_NORMAL) LoggerHook                         
 -------------------- 
after_test:
(VERY_HIGH   ) RuntimeInfoHook                    
 -------------------- 
after_run:
(BELOW_NORMAL) LoggerHook                         
 -------------------- 
12/09 17:27:22 - mmengine - WARNING - Failed to search registry with scope "mmrotate" in the "optim_wrapper" registry tree. As a workaround, the current "optim_wrapper" registry in "mmengine" is used to build instance. This may cause unexpected failure when running the built modules. Please check whether "mmrotate" is a correct scope, or whether the registry is initialized.
12/09 17:27:34 - mmengine - INFO - load model from: torchvision://resnet50
12/09 17:27:34 - mmengine - INFO - Loads checkpoint by torchvision backend from path: torchvision://resnet50
Downloading: "https://download.pytorch.org/models/resnet50-0676ba61.pth" to /root/.cache/torch/hub/checkpoints/resnet50-0676ba61.pth
100%|█████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████| 97.8M/97.8M [00:06<00:00, 16.7MB/s]
12/09 17:27:41 - mmengine - WARNING - The model and loaded state dict do not match exactly

unexpected key in source state_dict: fc.weight, fc.bias

12/09 17:27:41 - mmengine - WARNING - "FileClient" will be deprecated in future. Please use io functions in https://mmengine.readthedocs.io/en/latest/api/fileio.html#file-io
12/09 17:27:41 - mmengine - WARNING - "HardDiskBackend" is the alias of "LocalBackend" and the former will be deprecated in future.
12/09 17:27:41 - mmengine - INFO - Checkpoints will be saved to /workspace/openmmlab210p6a/mmrotate-1.x/work_dirs/rotated-retinanet-rbox-le90_r50_fpn_1x_dota.
/workspace/openmmlab210p6a/mmrotate-1.x/mmrotate/structures/bbox/rotated_boxes.py:192: UserWarning: The `clip` function does nothing in `RotatedBoxes`.
  warnings.warn('The `clip` function does nothing in `RotatedBoxes`.')
/workspace/openmmlab210p6a/mmrotate-1.x/mmrotate/structures/bbox/rotated_boxes.py:192: UserWarning: The `clip` function does nothing in `RotatedBoxes`.
  warnings.warn('The `clip` function does nothing in `RotatedBoxes`.')
/workspace/openmmlab210p6a/mmrotate-1.x/mmrotate/structures/bbox/rotated_boxes.py:192: UserWarning: The `clip` function does nothing in `RotatedBoxes`.
  warnings.warn('The `clip` function does nothing in `RotatedBoxes`.')
/workspace/openmmlab210p6a/mmrotate-1.x/mmrotate/structures/bbox/rotated_boxes.py:192: UserWarning: The `clip` function does nothing in `RotatedBoxes`.
  warnings.warn('The `clip` function does nothing in `RotatedBoxes`.')
/workspace/openmmlab210p6a/mmrotate-1.x/mmrotate/structures/bbox/rotated_boxes.py:192: UserWarning: The `clip` function does nothing in `RotatedBoxes`.
  warnings.warn('The `clip` function does nothing in `RotatedBoxes`.')
/workspace/openmmlab210p6a/mmrotate-1.x/mmrotate/structures/bbox/rotated_boxes.py:192: UserWarning: The `clip` function does nothing in `RotatedBoxes`.
  warnings.warn('The `clip` function does nothing in `RotatedBoxes`.')
/workspace/openmmlab210p6a/mmrotate-1.x/mmrotate/structures/bbox/rotated_boxes.py:192: UserWarning: The `clip` function does nothing in `RotatedBoxes`.
  warnings.warn('The `clip` function does nothing in `RotatedBoxes`.')
/workspace/openmmlab210p6a/mmrotate-1.x/mmrotate/structures/bbox/rotated_boxes.py:192: UserWarning: The `clip` function does nothing in `RotatedBoxes`.
  warnings.warn('The `clip` function does nothing in `RotatedBoxes`.')
/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/task_modules/prior_generators/anchor_generator.py:470: UserWarning: AutoNonVariableTypeMode is deprecated and will be removed in 1.10 release. For kernel implementations please use AutoDispatchBelowADInplaceOrView instead, If you are looking for a user facing API to enable running your inference-only workload, please use c10::InferenceMode. Using AutoDispatchBelowADInplaceOrView in user code is under risk of producing silent wrong result in some edge cases. See Note [AutoDispatchBelowAutograd] for more details. (Triggered internally at build/CMakeFiles/torch_npu.dir/compiler_depend.ts:74.)
  valid_x[:valid_w] = 1
/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/task_modules/prior_generators/anchor_generator.py:470: UserWarning: AutoNonVariableTypeMode is deprecated and will be removed in 1.10 release. For kernel implementations please use AutoDispatchBelowADInplaceOrView instead, If you are looking for a user facing API to enable running your inference-only workload, please use c10::InferenceMode. Using AutoDispatchBelowADInplaceOrView in user code is under risk of producing silent wrong result in some edge cases. See Note [AutoDispatchBelowAutograd] for more details. (Triggered internally at build/CMakeFiles/torch_npu.dir/compiler_depend.ts:74.)
  valid_x[:valid_w] = 1
/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/task_modules/prior_generators/anchor_generator.py:470: UserWarning: AutoNonVariableTypeMode is deprecated and will be removed in 1.10 release. For kernel implementations please use AutoDispatchBelowADInplaceOrView instead, If you are looking for a user facing API to enable running your inference-only workload, please use c10::InferenceMode. Using AutoDispatchBelowADInplaceOrView in user code is under risk of producing silent wrong result in some edge cases. See Note [AutoDispatchBelowAutograd] for more details. (Triggered internally at build/CMakeFiles/torch_npu.dir/compiler_depend.ts:74.)
  valid_x[:valid_w] = 1
/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/task_modules/prior_generators/anchor_generator.py:470: UserWarning: AutoNonVariableTypeMode is deprecated and will be removed in 1.10 release. For kernel implementations please use AutoDispatchBelowADInplaceOrView instead, If you are looking for a user facing API to enable running your inference-only workload, please use c10::InferenceMode. Using AutoDispatchBelowADInplaceOrView in user code is under risk of producing silent wrong result in some edge cases. See Note [AutoDispatchBelowAutograd] for more details. (Triggered internally at build/CMakeFiles/torch_npu.dir/compiler_depend.ts:74.)
  valid_x[:valid_w] = 1
Inner error, see details in Ascend logs.EZ9999: Inner Error!
EZ9999: 2024-12-09-17:28:22.114.456  The error from device(chipId:6, dieId:0), serial number is 1, there is an aivec error exception, core id is 28, error code = 0, dump info: pc start: 0x12424094b000, current: 0x12424094c110, vec error info: 0x6b16640b4c, mte error info: 0x741137827f, ifu error info: 0x200000157b240, ccu error info: 0x8bbf60b200000000, cube error info: 0, biu error info: 0, aic error mask: 0x6500020bd000288, para base: 0x1242805b6800.[FUNC:ProcessStarsCoreErrorInfo][FILE:device_error_proc.cc][LINE:1212]
        TraceBack (most recent call last):
        The extend info: errcode:(0, 0x8000, 0) errorStr: When the D-cache reads and writes data to the UB, the response value returned by the bus is a non-zero value. fixp_error0 info: 0x137827f, fixp_error1 info: 0x74 fsmId:1, tslot:0, thread:0, ctxid:0, blk:0, sublk:0, subErrType:4.[FUNC:ProcessStarsCoreErrorInfo][FILE:device_error_proc.cc][LINE:1224]
        Kernel task happen error, retCode=0x31, [vector core exception].[FUNC:PreCheckTaskErr][FILE:davinic_kernel_task.cc][LINE:1220]
        AIV Kernel happen error, retCode=0x31.[FUNC:GetError][FILE:stream.cc][LINE:1082]
        Aicore kernel execute failed, device_id=2, stream_id=2, report_stream_id=2, task_id=3802, flip_num=0, fault kernel_name=te_rotatediou_43b143781836a3798030e0aa350886a405d0eb3dd1b2025ecba774f1797b974e_1d1394e0d123c76d62e4359a7fab0dd18194b933d1c2e5f7b2390c79380a82bdc, fault kernel info ext=te_rotatediou_43b143781836a3798030e0aa350886a405d0eb3dd1b2025ecba774f1797b974e_1__kernel0, program id=53, hash=17474412777910356564.[FUNC:GetError][FILE:stream.cc][LINE:1082]
        [AIC_INFO] after execute:args print end[FUNC:GetError][FILE:stream.cc][LINE:1082]
        rtStreamSynchronize execute failed, reason=[vector core exception][FUNC:FuncErrorReason][FILE:error_message_manage.cc][LINE:53]
        synchronize stream failed, runtime result = 507035[FUNC:ReportCallError][FILE:log_inner.cpp][LINE:161]

Traceback (most recent call last):
  File "/workspace/openmmlab210p6a/mmrotate-1.x/./tools/train.py", line 125, in <module>
    main()
  File "/workspace/openmmlab210p6a/mmrotate-1.x/./tools/train.py", line 121, in main
    runner.train()
  File "/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/runner/runner.py", line 1777, in train
    model = self.train_loop.run()  # type: ignore
  File "/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/runner/loops.py", line 96, in run
    self.run_epoch()
  File "/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/runner/loops.py", line 113, in run_epoch
    self.run_iter(idx, data_batch)
  File "/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/runner/loops.py", line 129, in run_iter
    outputs = self.runner.model.train_step(
  File "/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/model/wrappers/distributed.py", line 121, in train_step
    losses = self._run_forward(data, mode='loss')
  File "/workspace/openmmlab210p6a/mmengine-0.10.4/mmengine/model/wrappers/distributed.py", line 161, in _run_forward
    results = self(**data, mode=mode)
  File "/home/miniconda3/envs/openmmlab210p6a/lib/python3.9/site-packages/torch/nn/modules/module.py", line 1518, in _wrapped_call_impl
    return self._call_impl(*args, **kwargs)
  File "/home/miniconda3/envs/openmmlab210p6a/lib/python3.9/site-packages/torch/nn/modules/module.py", line 1527, in _call_impl
    return forward_call(*args, **kwargs)
  File "/home/miniconda3/envs/openmmlab210p6a/lib/python3.9/site-packages/torch/nn/parallel/distributed.py", line 1519, in forward
    else self._run_ddp_forward(*inputs, **kwargs)
  File "/home/miniconda3/envs/openmmlab210p6a/lib/python3.9/site-packages/torch/nn/parallel/distributed.py", line 1355, in _run_ddp_forward
    return self.module(*inputs, **kwargs)  # type: ignore[index]
  File "/home/miniconda3/envs/openmmlab210p6a/lib/python3.9/site-packages/torch/nn/modules/module.py", line 1518, in _wrapped_call_impl
    return self._call_impl(*args, **kwargs)
  File "/home/miniconda3/envs/openmmlab210p6a/lib/python3.9/site-packages/torch/nn/modules/module.py", line 1527, in _call_impl
    return forward_call(*args, **kwargs)
  File "/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/detectors/base.py", line 92, in forward
    return self.loss(inputs, data_samples)
  File "/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/detectors/single_stage.py", line 78, in loss
    losses = self.bbox_head.loss(x, batch_data_samples)
  File "/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/dense_heads/base_dense_head.py", line 123, in loss
    losses = self.loss_by_feat(*loss_inputs)
  File "/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/dense_heads/anchor_head.py", line 502, in loss_by_feat
    cls_reg_targets = self.get_targets(
  File "/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/dense_heads/anchor_head.py", line 378, in get_targets
    results = multi_apply(
  File "/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/utils/misc.py", line 219, in multi_apply
    return tuple(map(list, zip(*map_results)))
  File "/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/dense_heads/anchor_head.py", line 252, in _get_targets_single
    assign_result = self.assigner.assign(pred_instances, gt_instances,
  File "/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/task_modules/assigners/max_iou_assigner.py", line 234, in assign
    assign_result = self.assign_wrt_overlaps(overlaps, gt_labels)
  File "/workspace/openmmlab210p6a/mmdetection-3.3.0/mmdet/models/task_modules/assigners/max_iou_assigner.py", line 286, in assign_wrt_overlaps
    assigned_gt_inds[(max_overlaps >= 0)
RuntimeError: ACL stream synchronize failed, error code:507035
[W compiler_depend.ts:409] Warning: NPU warning, error code is 507035[Error]: 
[Error]: The vector core execution is abnormal. 
        Rectify the fault based on the error information in the ascend log.
EH9999: Inner Error!
        rtDeviceSynchronize execute failed, reason=[vector core exception][FUNC:FuncErrorReason][FILE:error_message_manage.cc][LINE:53]
EH9999: 2024-12-09-17:28:22.166.653  wait for compute device to finish failed, runtime result = 507035.[FUNC:ReportCallError][FILE:log_inner.cpp][LINE:161]
        TraceBack (most recent call last):
 (function npuSynchronizeUsedDevices)
[W compiler_depend.ts:392] Warning: NPU warning, error code is 507035[Error]: 
[Error]: The vector core execution is abnormal. 
        Rectify the fault based on the error information in the ascend log.
EH9999: Inner Error!
        rtDeviceSynchronize execute failed, reason=[vector core exception][FUNC:FuncErrorReason][FILE:error_message_manage.cc][LINE:53]
EH9999: 2024-12-09-17:28:22.168.044  wait for compute device to finish failed, runtime result = 507035.[FUNC:ReportCallError][FILE:log_inner.cpp][LINE:161]
        TraceBack (most recent call last):
 (function npuSynchronizeDevice)
[W compiler_depend.ts:392] Warning: NPU warning, error code is 507035[Error]: 
[Error]: The vector core execution is abnormal. 
        Rectify the fault based on the error information in the ascend log.
EH9999: Inner Error!
        rtDeviceSynchronize execute failed, reason=[vector core exception][FUNC:FuncErrorReason][FILE:error_message_manage.cc][LINE:53]
EH9999: 2024-12-09-17:28:22.169.178  wait for compute device to finish failed, runtime result = 507035.[FUNC:ReportCallError][FILE:log_inner.cpp][LINE:161]
        TraceBack (most recent call last):
 (function npuSynchronizeDevice)
[W compiler_depend.ts:392] Warning: NPU warning, error code is 507035[Error]: 
[Error]: The vector core execution is abnormal. 
        Rectify the fault based on the error information in the ascend log.
EH9999: Inner Error!
        rtDeviceSynchronize execute failed, reason=[vector core exception][FUNC:FuncErrorReason][FILE:error_message_manage.cc][LINE:53]
EH9999: 2024-12-09-17:28:22.170.192  wait for compute device to finish failed, runtime result = 507035.[FUNC:ReportCallError][FILE:log_inner.cpp][LINE:161]
        TraceBack (most recent call last):
 (function npuSynchronizeDevice)
[W compiler_depend.ts:392] Warning: NPU warning, error code is 507035[Error]: 
[Error]: The vector core execution is abnormal. 
        Rectify the fault based on the error information in the ascend log.
EH9999: Inner Error!
        rtDeviceSynchronize execute failed, reason=[vector core exception][FUNC:FuncErrorReason][FILE:error_message_manage.cc][LINE:53]
EH9999: 2024-12-09-17:28:22.171.334  wait for compute device to finish failed, runtime result = 507035.[FUNC:ReportCallError][FILE:log_inner.cpp][LINE:161]
        TraceBack (most recent call last):
 (function npuSynchronizeDevice)
[ERROR] 2024-12-09-17:28:24 (PID:1106, Device:2, RankID:2) ERR99999 UNKNOWN application exception
```

算子支持分析：

```
# ref: https://www.hiascend.com/document/detail/zh/canncommercial/80RC2/devaids/auxiliarydevtool/atlasfmkt_16_0018.html
pip install pandas libcst prettytable jedi

cd /usr/local/Ascend/ascend-toolkit/latest/tools/ms_fmk_transplt/
./pytorch_analyse.sh -i /workspace/openmmlab210p6a/mmrotate-1.x/ -o /workspace/all-data/work_dirs/ -v 2.1.0
# +----------------------------+------------+
# |           files            | statistics |
# +----------------------------+------------+
# | api_performance_advice.csv |     29     |
# |      cuda_op_list.csv      |     0      |
# |    unsupported_api.csv     |     9      |
# |      unknown_api.csv       |    131     |
# |  api_precision_advice.csv  |     13     |
# +----------------------------+------------+
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
