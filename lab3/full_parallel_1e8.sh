#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 12
#SBATCH --time=01:00:00
#SBATCH --partition=plgrid
#SBATCH --account=plgmpr21zeus
#SBATCH --constraint="intel"

# Add open MPI library
module add plgrid/tools/openmpi

# points quantity equals 1e8
POINTS_QUANTITY=100000000

for NODES_QUAN in {1..12..1}
do
    for i in {1..10..1}
    do
        echo ----- >> parallel_strong_${NODES_QUAN}_nodes_points_1e8.log
	    mpiexec -np $NODES_QUAN ./homework_pi_parallel.out $POINTS_QUANTITY >> parallel_strong_${NODES_QUAN}_nodes_points_1e8.log
    done
done
for NODES_QUAN in {1..12..1}
do
    for i in {1..10..1}
    do
        echo ----- >> parallel_weak_${NODES_QUAN}_nodes_points_1e8.log
	    mpiexec -np $NODES_QUAN ./homework_pi_parallel.out $(($NODES_QUAN * $POINTS_QUANTITY)) >> parallel_weak_${NODES_QUAN}_nodes_points_1e8.log
    done
done
