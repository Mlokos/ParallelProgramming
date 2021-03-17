#!/bin/bash

echo '' > std.log

for buffer_size in {1000..2000000..1000}
do
    mpiexec -np 2 ./homework_std.out $buffer_size 1000 >> std.log
done
