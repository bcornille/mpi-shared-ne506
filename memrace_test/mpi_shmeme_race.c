#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	// This block initializes MPI and gets the processor rank in the global communicator.
	MPI_Init(&argc, &argv);
	int rank;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &rank);

	// Set up the shared memory communicator and get shared memory rank.
	MPI_Comm shmcomm;
	MPI_Comm_split_type(comm, MPI_COMM_TYPE_SHARED, 0, MPI_INFO_NULL, &shmcomm);
	int srank;
	MPI_Comm_rank(shmcomm, &srank);
