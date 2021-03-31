#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 12
#SBATCH --time=04:30:00
#SBATCH --partition=plgrid
#SBATCH --account=plgmpr21zeus
#SBATCH --constraint="intel"

# Add open MPI library
module add plgrid/tools/openmpi

# points quantity equals 1e10
POINTS_QUANTITY=10000000000

NODES_QUAN=7
for i in {1..10..1}
do
    echo ----- >> parallel_weak_${NODES_QUAN}_nodes_points_1e10.log
    mpiexec -np $NODES_QUAN ./homework_pi_parallel.out $(($NODES_QUAN * $POINTS_QUANTITY)) >> parallel_weak_${NODES_QUAN}_nodes_points_1e10.log
done
