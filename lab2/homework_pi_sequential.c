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
   * Arguments handle
   */
  if(argc != 2) {
    printf("Run program with a points quantity argument!");
    exit(1);
  }
  char *ptr;
  LLONG_UINT points_quantity = strtol(argv[1], &ptr, 10);

  mt_seed();

  long double points_inside = (long double)calculate_pi_monte_carlo(points_quantity);
  long double pi_approx = points_inside/(long double)points_quantity;
  pi_approx = 4 * pi_approx;
  printf("%Lf\n", pi_approx);
}
