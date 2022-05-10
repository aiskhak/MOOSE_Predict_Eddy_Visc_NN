#!/bin/bash
#SBATCH -J "tamu_fv"   # job name
#SBATCH -t 48:00:00    # max wall time
#SBATCH -N 1           # nodes
#SBATCH -n 4          # cores
##SBATCH -p gradq      # queue name - gradq or all

source ~/.bashrc
source ~/mambaforge3/bin/activate /home/aiskhak2/mambaforge3/envs/moose
mpirun -np 4 /home/aiskhak2/projects/fv_app_pynn/fv_app_pynn-opt -i tamu_2d_fv.i

### to run use:
### sbatch fv_app_run.sh
### other commands:
### squeue
### scancel <job_id>
### qstat -a
### qdel
