#!/bin/bash
#SBATCH --job-name=kmeans
#SBATCH --mail-type=ALL
#SBATCH --mail-user=lorenzo.borelli@studio.unibo.it
#SBATCH --time=01:00:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4
#SBATCH --output=kmeans_stats
#SBATCH --gres=gpu:1

make -f ./Makefile
./strong-scaling.sh
./weak-scaling.sh