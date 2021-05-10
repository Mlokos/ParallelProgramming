# SET POINTS RANGE
# POINTS_QUANTITY_MAX=128000000
POINTS_QUANTITY_MAX=8000000
POINTS_QUANTITY_START=1000000

OMP_NUM_THREADS=4

# ALGORITHM 0 - SEQUENTIAL
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    chunk_size=$(($buffer_size / 4))
    export OMP_SCHEDULE="static,${chunk_size}"
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size 0 >> logs/sequential_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

# ALGORITHM 1
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    chunk_size=$(($buffer_size / 4))
    export OMP_SCHEDULE="static,${chunk_size}"
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size 1 4 >> logs/algorithm_1_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

# ALGORITHM 2
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    chunk_size=$(($buffer_size / 4))
    export OMP_SCHEDULE="static,${chunk_size}"
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size 2 4 >> logs/algorithm_2_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done
