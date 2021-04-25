# SET POINTS RANGE
POINTS_QUANTITY_MAX=128000000
POINTS_QUANTITY_START=1000000

# GATHER LOGS
buffer_size=$POINTS_QUANTITY_START
while [ $buffer_size -le $POINTS_QUANTITY_MAX ]
do
    for i in {1..10}
    do
        ./bucket_sort_basic.out $buffer_size >> logs/basic_points_$buffer_size.log
    done
    buffer_size=$(($buffer_size * 2))
done

