#!/bin/bash

# points quantity equals 1e9
POINTS_QUANTITY=1000000000

function update_config_file {
    rm allnodes
    for i in {1..9}
    do
        if [ $i -le $NODES_QUAN ]
        then
            echo vnode-0$i.dydaktyka.icsr.agh.edu.pl:1 >> allnodes
        else
            echo vnode-0$i.dydaktyka.icsr.agh.edu.pl >> allnodes
        fi
    done
    for i in {10..12}
    do
        if [ $i -le $NODES_QUAN ]
        then
            echo vnode-$i.dydaktyka.icsr.agh.edu.pl:1 >> allnodes
        else
            echo vnode-$i.dydaktyka.icsr.agh.edu.pl >> allnodes
        fi
    done
}
for NODES_QUAN in {1..4..1}
do
    update_config_file
    for i in {1..10..1}
    do
        echo ----- >> parallel_strong_${NODES_QUAN}_nodes.log
	    mpiexec -machinefile ./allnodes -np $NODES_QUAN ./homework_pi_parallel.out $POINTS_QUANTITY >> parallel_strong_${NODES_QUAN}_nodes.log
    done
done
for NODES_QUAN in {1..4..1}
do
    update_config_file
    for i in {1..10..1}
    do
        echo ----- >> parallel_weak_${NODES_QUAN}_nodes.log
	    mpiexec -machinefile ./allnodes -np $NODES_QUAN ./homework_pi_parallel.out $(($NODES_QUAN * $POINTS_QUANTITY)) >> parallel_weak_${NODES_QUAN}_nodes.log
    done
done
