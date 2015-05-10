#include <stdio.h>
#include "mpi.h"

#define NPERP 1000000;

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

	MPI_Aint size = 0;
	if(rank == 0) {
		size = sizeof(int);
	}
	MPI_Win shwin;
	int *shptr;
	int disp_unit = sizeof(int);
	MPI_Win_allocate_shared(size, disp_unit, MPI_INFO_NULL, shmcomm, &shptr, &shwin);
	MPI_Win_shared_query(shwin, 0, &size, &disp_unit, &shptr);

	int i = 0;
	int nperp = NPERP;
	int one = 1;
	MPI_Aint disp = 0;
	MPI_Win_fence(0, shwin);
	double time = -MPI_Wtime();
	for(i = 0; i < nperp; i++) {
		MPI_Accumulate(&one, 1, MPI_INT, 0, disp, 1, MPI_INT, MPI_SUM, shwin);
	}
	MPI_Win_fence(0, shwin);
	time += MPI_Wtime();

	int ssize;
	MPI_Comm_size(shmcomm, &ssize);
	int Ntot = nperp*ssize;
	if(srank == 0) {
		if(shptr[0] == Ntot) {
			printf("This message should appear everytime because this works.\n");
			printf("The looping took %f seconds this way.\n", time);
		} else {
			printf("The shared accumulator only counted to %d, "
					"when it should have gotten to %d.\n"
					"This message from global rank %d.\n",
					shptr[0], Ntot, rank);
		}
	}

	MPI_Win_free(&shwin);
	MPI_Finalize();

	return 0;
}
