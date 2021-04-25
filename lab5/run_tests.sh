# SET POINTS RANGE
POINTS_QUANTITY_MAX=128000000
POINTS_QUANTITY_START=1000000

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

# SET OPENMP SCHEDULE TYPE
export OMP_SCHEDULE="static"
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/static_chunk_auto_points_$buffer_size.log
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

# SET OPENMP SCHEDULE TYPE
export OMP_SCHEDULE="dynamic"
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/dynamic_chunk_auto_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

# SET OPENMP SCHEDULE TYPE
export OMP_SCHEDULE="auto"
# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort.out $buffer_size >> logs/auto_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done
