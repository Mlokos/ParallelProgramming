#!/bin/bash

echo '' > std.log

for buffer_size in {1000..2000000..1000}
do
    mpiexec -machinefile ./allnodes -np 2 ./homework_std.out $buffer_size 1000 >> std_two_nodes_second_processors.log
done
