#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  /**
   * Arguments handle
   */
  if(argc != 3) {
    printf("Run program with a message size and message quantity arguments!");
    exit(1);
  }
  int buffer_size = atoi(argv[1]);
  int message_quantity = atoi(argv[2]);
  printf("[%d, %d]\n", buffer_size, message_quantity);

  /**
   * MPI initialization
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
  MPI_Request myRequest[1000];
  MPI_Status myStatus;
  
  int i;
  if(rank == 0) {
    char * send_number = malloc(sizeof(char) * buffer_size);
    double time_start = MPI_Wtime();
    for(i = 0; i < message_quantity; ++i) {
      MPI_Isend(send_number, buffer_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD, &myRequest[i]);
    }
    for(i = 0; i < message_quantity; ++i) {
      MPI_Wait(&myRequest[i], &myStatus);
    }
    double time_end = MPI_Wtime();
    printf("Sender: %f\n", time_end - time_start);
    free(send_number);
  }
  else {
    char * recv_number = malloc(sizeof(char) * buffer_size);
    double time_start = MPI_Wtime();
    for(i = 0; i < message_quantity; ++i) {
      MPI_Irecv(recv_number, buffer_size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &myRequest[i]);
    }
    for(i = 0; i < message_quantity; ++i) {
      MPI_Wait(&myRequest[i], &myStatus);
    }
    double time_end = MPI_Wtime();
    printf("Receiver: %f\n", time_end - time_start);
    free(recv_number);
  }

  MPI_Finalize();
}
