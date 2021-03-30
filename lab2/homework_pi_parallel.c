#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mtwist-1.5/mtwist.c"

#define LLONG_UINT unsigned long long int
#define UINT16 ushort

/**
 * mt_lrand() function returns at least 4 Bytes integers
 * higher and lower Bytes are scaled with range (0, 2e9)
 */
LLONG_UINT rand_coordinate_generator(void) {
  LLONG_UINT rand_higher_bytes = (UINT16)mt_lrand() & 0x7FFF;
  LLONG_UINT rand_lower_bytes = (UINT16)mt_lrand() & 0xFFFF;

  LLONG_UINT result = (rand_higher_bytes << 16) | rand_lower_bytes;

  return result;
}

/**
 * x_position and y_position in range (0, 2e9)
 */
LLONG_UINT calculate_point_distance(LLONG_UINT x_position, LLONG_UINT y_position) {
  LLONG_UINT squared_sum = (x_position * x_position) + (y_position * y_position);
  if(squared_sum <= 0x3FFFFFFF00000001)
    return 1;
  else
    return 0;
}

LLONG_UINT calculate_pi_monte_carlo(LLONG_UINT points_quan) {
  LLONG_UINT result = 0;
  
  LLONG_UINT x_position;
  LLONG_UINT y_position;

  LLONG_UINT i = points_quan;
  while(i > 0) {
    x_position = rand_coordinate_generator();
    y_position = rand_coordinate_generator();
    if(calculate_point_distance(x_position, y_position) == 1)
      ++result;
    --i;
  }
  return result;
}

int main(int argc, char** argv) {
  /**
   * MPI initialization
   */
  MPI_Init(&argc, &argv);  /* starts MPI */

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  /* get current process id */
  MPI_Comm_size(MPI_COMM_WORLD, &size);  /* get number of processes */

  /**
   * Arguments handle
   */
  if(argc != 2) {
    printf("Run program with a points quantity argument!");
    exit(1);
  }
  LLONG_UINT points_quantity = atoi(argv[1]);

  LLONG_UINT points_quantity_splitted = points_quantity / (LLONG_UINT)size;
  LLONG_UINT points_quantity_for_master = points_quantity_splitted + points_quantity % (LLONG_UINT)size;

  /**
   * Communication
   */
  LLONG_UINT points_inside_circle;

  double time_start_general = MPI_Wtime();
  if(rank == 0) {
    mt_seed();
    double time_start = MPI_Wtime();
    points_inside_circle = calculate_pi_monte_carlo(points_quantity_for_master);
    double time_end = MPI_Wtime();
    printf("Master: %f\n", time_end - time_start);

    /**
     * Receive calculations from other nodes
     */
    LLONG_UINT received_value;
    int i;
    for(i = 1; i < size; ++i){
      MPI_Recv(&received_value, 1, MPI_LONG_LONG_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      points_inside_circle += received_value;
    }

    long double pi_approx = points_inside_circle/(long double)points_quantity;
    pi_approx = 4 * pi_approx;
    printf("Calculated PI: %Lf\n", pi_approx);
  } else {
    mt_seed();
    double time_start = MPI_Wtime();
    points_inside_circle = calculate_pi_monte_carlo(points_quantity_splitted);
    double time_end = MPI_Wtime();
    MPI_Send(&points_inside_circle, 1, MPI_LONG_LONG_INT, 0, 0, MPI_COMM_WORLD);
    printf("Slave: %f\n", time_end - time_start);
  }
  double time_end_general = MPI_Wtime();
  if(rank == 0) {
    printf("General: %f\n", time_end_general - time_start_general);
  }
  
  MPI_Finalize();
}
