#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MESSAGES 1000000

int main(int argc, char** argv) {
  /**
   * Initialization
   */
  MPI_Init(&argc, &argv);  /* starts MPI */
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);  /* get current process id */
  MPI_Comm_size(MPI_COMM_WORLD, &size);  /* get number of processes */

  /**
   * Condition check: at least 2 nodes
   */
  if (size < 2) {
    fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1); 
  }

  /**
   * Communication
   */
  int send_number;
  int recv_number;

  double time_start = MPI_Wtime();
  
  if(rank == 0) {
    for(int i = 0; i < MAX_MESSAGES; ++i) {
      MPI_Bsend(&send_number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      MPI_Recv(&recv_number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
  }
  else {
    for(int i = 0; i < MAX_MESSAGES; ++i) {
      MPI_Recv(&recv_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Bsend(&send_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
  }

  double time_end = MPI_Wtime();
  printf("1 million messages: %1.2f\n", time_end - time_start);

  MPI_Finalize();
}
