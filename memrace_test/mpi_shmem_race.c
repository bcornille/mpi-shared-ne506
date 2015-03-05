#include <stdio.h>
#include "mpi.h"

#define NPERP 1000;

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
		size = sizeof(long long);
	}
	MPI_Win shwin;
	long long *shptr;
	int disp_unit = sizeof(long long);
	MPI_Win_allocate_shared(size, disp_unit, MPI_INFO_NULL, shmcomm, &shptr, &shwin);
	MPI_Win_shared_query(shwin, 0, &size, &disp_unit, &shptr);

	long long i = 0;
	long long nperp = NPERP;
	/* Here we intentionally will try to write to one memory location from several processors.
	 * This is a very bad thing to do if care is not taken to ensure updating between loads
	 * and saves.  The output from this program will demonstrate why this way of programming
	 * will not produce the desired result, and even worse it will produce an indeterminate
	 * result. */
	for(i = 0; i < nperp; i++) {
		shptr[0]++;
	}

	int ssize;
	MPI_Comm_size(shmcomm, &ssize);
	long long Ntot = nperp*ssize;
	if(srank == 0) {
		if(shptr[0] == Ntot) {
			printf("This might actually work...it really shouldn't.\n");
		} else {
			printf("The shared accumulator only counted to %lld, "
					"when it should have gotten to %lld.\n"
					"This message from global rank %d.\n",
					shptr[0], Ntot, rank);
		}
	}

	MPI_Win_free(&shwin);
	MPI_Finalize();

	return 0;
}
