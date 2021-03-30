#!/bin/bash

# POINTS_QUANTITY=1000000000000
POINTS_QUANTITY=1000

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

for NODES_QUAN in {1..12..1}
do
    update_config_file
    for i in {1..1000..1}
    do
        echo ----- >> parallel_${NODES_QUAN}_nodes.log
	    mpiexec -np $NODES_QUAN ./homework_pi_parallel.out $POINTS_QUANTITY >> parallel_${NODES_QUAN}_nodes.log
    done
done
