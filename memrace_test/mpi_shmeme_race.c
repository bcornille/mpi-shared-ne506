#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
	// This block initializes MPI and defines rank and size in the global communicator.
	MPI_Init(&argc, &argv);
	int rank;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &rank);
