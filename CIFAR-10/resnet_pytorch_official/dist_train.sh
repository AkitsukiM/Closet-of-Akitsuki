CUDA_VISIBLE_DEVICES=0,1,2,3 python -m torch.distributed.launch --nnodes 1 --nproc_per_node 4 --master_addr 127.0.0.1 --master_port 29501 main.py --save_path "./work_dirs/ddp_1/"
