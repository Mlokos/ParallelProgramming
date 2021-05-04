# SET POINTS RANGE
POINTS_QUANTITY_MAX=128000000
POINTS_QUANTITY_START=1000000

# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    chunk_size=$(($buffer_size / 4))
    export OMP_SCHEDULE="static,${chunk_size}"
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/static_chunk_0_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done


# SET OPENMP SCHEDULE TYPE
export OMP_SCHEDULE="static,8"
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/static_chunk_8_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

# SET OPENMP SCHEDULE TYPE
export OMP_SCHEDULE="static,4"
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/static_chunk_4_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

# SET OPENMP SCHEDULE TYPE
export OMP_SCHEDULE="static,1"
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/static_chunk_1_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    chunk_size=$(($buffer_size / 4))
    export OMP_SCHEDULE="dynamic,${chunk_size}"
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/dynamic_chunk_0_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

# SET OPENMP SCHEDULE TYPE
export OMP_SCHEDULE="dynamic,8"
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/dynamic_chunk_8_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

# SET OPENMP SCHEDULE TYPE
export OMP_SCHEDULE="dynamic,4"
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/dynamic_chunk_4_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

# SET OPENMP SCHEDULE TYPE
export OMP_SCHEDULE="dynamic,1"
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/dynamic_chunk_1_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done
