#!/bin/bash

echo '' > async.log

for buffer_size in {1000..2000000..1000}
do
    mpiexec -machinefile ./allnodes -np 2 ./homework_async.out $buffer_size 1000 >> async_two_nodes_second_processors.log
done
