#!/bin/bash

BUFFER_SIZE_STEPS=1000
# BUFFER_SIZE_MAX=2000
BUFFER_SIZE_MAX=2000000

##################################
# Prepare environment for one node
##################################
cat allnodes_configuration/one_node.conf > allnodes

# MPI std communication - shared memory
buffer_size=$BUFFER_SIZE_STEPS
while [ $buffer_size -le $BUFFER_SIZE_MAX ]
do
    mpiexec -machinefile ./allnodes -np 2 ./homework_std.out $buffer_size 1000 >> std_one_node_shared_memory.log
    buffer_size=$(($buffer_size + $BUFFER_SIZE_STEPS))
done

# MPI std communication - no shared memory
buffer_size=$BUFFER_SIZE_STEPS
while [ $buffer_size -le $BUFFER_SIZE_MAX ]
do
    MPIR_CVAR_NOLOCAL=1 mpiexec -machinefile ./allnodes -np 2 ./homework_std.out $buffer_size 1000 >> std_one_node_no_shared_memory.log
    buffer_size=$(($buffer_size + $BUFFER_SIZE_STEPS))
done

# MPI async communication - shared memory
buffer_size=$BUFFER_SIZE_STEPS
while [ $buffer_size -le $BUFFER_SIZE_MAX ]
do
    mpiexec -machinefile ./allnodes -np 2 ./homework_async.out $buffer_size 1000 >> async_one_node_shared_memory.log
    buffer_size=$(($buffer_size + $BUFFER_SIZE_STEPS))
done

# MPI async communication - no shared memory
buffer_size=$BUFFER_SIZE_STEPS
while [ $buffer_size -le $BUFFER_SIZE_MAX ]
do
    MPIR_CVAR_NOLOCAL=1 mpiexec -machinefile ./allnodes -np 2 ./homework_async.out $buffer_size 1000 >> async_one_node_no_shared_memory.log
    buffer_size=$(($buffer_size + $BUFFER_SIZE_STEPS))
done

###################################################
# Prepare environment for two nodes on good network
###################################################
cat allnodes_configuration/two_nodes_good_network.conf > allnodes

# MPI std communication good network
buffer_size=$BUFFER_SIZE_STEPS
while [ $buffer_size -le $BUFFER_SIZE_MAX ]
do
    mpiexec -machinefile ./allnodes -np 2 ./homework_std.out $buffer_size 1000 >> std_two_nodes_good_network.log
    buffer_size=$(($buffer_size + $BUFFER_SIZE_STEPS))
done

# MPI async communication good network
buffer_size=$BUFFER_SIZE_STEPS
while [ $buffer_size -le $BUFFER_SIZE_MAX ]
do
    mpiexec -machinefile ./allnodes -np 2 ./homework_async.out $buffer_size 1000 >> async_two_nodes_good_network.log
    buffer_size=$(($buffer_size + $BUFFER_SIZE_STEPS))
done

##################################################
# Prepare environment for two nodes on bad network
##################################################
cat allnodes_configuration/two_nodes_bad_network.conf > allnodes

# MPI std communication bad network
buffer_size=$BUFFER_SIZE_STEPS
while [ $buffer_size -le $BUFFER_SIZE_MAX ]
do
    mpiexec -machinefile ./allnodes -np 2 ./homework_std.out $buffer_size 1000 >> std_two_nodes_bad_network.log
    buffer_size=$(($buffer_size + $BUFFER_SIZE_STEPS))
done

# MPI async communication bad network
buffer_size=$BUFFER_SIZE_STEPS
while [ $buffer_size -le $BUFFER_SIZE_MAX ]
do
    mpiexec -machinefile ./allnodes -np 2 ./homework_async.out $buffer_size 1000 >> async_two_nodes_bad_network.log
    buffer_size=$(($buffer_size + $BUFFER_SIZE_STEPS))
done
