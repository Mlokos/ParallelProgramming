# SET POINTS RANGE
POINTS_QUANTITY_MAX=8000000
POINTS_QUANTITY_START=1000000

# SET BUCKETS RANGE
BUCKET_QUANTITY_MAX=10
BUCKET_QUANTITY_START=1

# SET THREADS RANGE
THREADS_QUANTITY_MAX=4
THREADS_QUANTITY_START=1


# ALGORITHM 1
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    chunk_size=$(($buffer_size / 4))
    export OMP_SCHEDULE="static,${chunk_size}"
    bucket_quantity=$BUCKET_QUANTITY_START
    while [ $bucket_quantity -le $BUCKET_QUANTITY_MAX ]
    do
        threads_quantity=$THREADS_QUANTITY_START
        while [ $threads_quantity -le $THREADS_QUANTITY_MAX ]
        do
            for i in {1..10}
            do
                ./bucket_sort.out $buffer_size 1 $bucket_quantity $threads_quantity >> logs/algorithm_1_points_$(($buffer_size))_buckets_$(($bucket_quantity))_threads_$(($threads_quantity)).log
            done
            threads_quantity=$(($threads_quantity + $THREADS_QUANTITY_START))
        done
        bucket_quantity=$(($bucket_quantity + $BUCKET_QUANTITY_START))
    done
    buffer_size=$(($buffer_size + $POINTS_QUANTITY_START))
done


# ALGORITHM 2
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    chunk_size=$(($buffer_size / 4))
    export OMP_SCHEDULE="static,${chunk_size}"
    bucket_quantity=$BUCKET_QUANTITY_START
    while [ $bucket_quantity -le $BUCKET_QUANTITY_MAX ]
    do
        threads_quantity=$THREADS_QUANTITY_START
        while [ $threads_quantity -le $THREADS_QUANTITY_MAX ]
        do
            for i in {1..10}
            do
                ./bucket_sort.out $buffer_size 2 $bucket_quantity $threads_quantity >> logs/algorithm_2_points_$(($buffer_size))_buckets_$(($bucket_quantity))_threads_$(($threads_quantity)).log
            done
            threads_quantity=$(($threads_quantity + $THREADS_QUANTITY_START))
        done
        bucket_quantity=$(($bucket_quantity + $BUCKET_QUANTITY_START))
    done
    buffer_size=$(($buffer_size + $POINTS_QUANTITY_START))
done
