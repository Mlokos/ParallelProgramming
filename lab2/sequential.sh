#!/bin/bash

for i in {1..1000}
do
    ./homework_pi_sequential.out 100 >> sequential_1e2.log
done

for i in {1..1000}
do
    ./homework_pi_sequential.out 10000 >> sequential_1e4.log
done

for i in {1..1000}
do
    ./homework_pi_sequential.out 1000000 >> sequential_1e6.log
done

for i in {1..1000}
do
    ./homework_pi_sequential.out 100000000 >> sequential_1e8.log
done