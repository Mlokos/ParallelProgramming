#!/bin/bash

##################################
# Prepare environment for one node
##################################
cat allnodes_configuration/one_node.conf > allnodes

# MPI std communication - shared memory
mpiexec -machinefile ./allnodes -np 2 ./homework_std.out 1 1000 >> std_one_node_shared_memory_small_message.log

# MPI std communication - no shared memory
MPIR_CVAR_NOLOCAL=1 mpiexec -machinefile ./allnodes -np 2 ./homework_std.out 1 1000 >> std_one_node_no_shared_memory_small_message.log

# MPI async communication - shared memory
mpiexec -machinefile ./allnodes -np 2 ./homework_async.out 1 1000 >> async_one_node_shared_memory_small_message.log

# MPI async communication - no shared memory
MPIR_CVAR_NOLOCAL=1 mpiexec -machinefile ./allnodes -np 2 ./homework_async.out 1 1000 >> async_one_node_no_shared_memory_small_message.log

###################################################
# Prepare environment for two nodes on good network
###################################################
cat allnodes_configuration/two_nodes_good_network.conf > allnodes

# MPI std communication good network
mpiexec -machinefile ./allnodes -np 2 ./homework_std.out 1 1000 >> std_two_nodes_good_network_small_message.log

# MPI async communication good network
mpiexec -machinefile ./allnodes -np 2 ./homework_async.out 1 1000 >> async_two_nodes_good_network_small_message.log

##################################################
# Prepare environment for two nodes on bad network
##################################################
cat allnodes_configuration/two_nodes_bad_network.conf > allnodes

# MPI std communication bad network
mpiexec -machinefile ./allnodes -np 2 ./homework_std.out 1 1000 >> std_two_nodes_bad_network_small_message.log

# MPI async communication bad network
mpiexec -machinefile ./allnodes -np 2 ./homework_async.out 1 1000 >> async_two_nodes_bad_network_small_message.log
