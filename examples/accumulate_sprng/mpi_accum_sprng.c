#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIMPLE_SPRNG
#define USE_MPI
#include "sprng.h"

#define SEED 987654321

int rank;
int srank;
int ssize;

void usage()
{
	if(rank == 0) {
		perror("USAGE: accum_sprng <gtype> [<nrand>]\n");
	}

	exit(1);
}

int main(int argc, char *argv[])
{
	double rn;
	long long i;
	long long nrand, Ntot;
	int gtype;
	double *shptr;
	double avg;
	int disp_unit = sizeof(double);

	// MPI initialization calls
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &rank);

	// MPI variables
	MPI_Aint size = 0;
	MPI_Win shwin;
	MPI_Comm shmcomm;

	if(argc == 2) {
		gtype = atoi(argv[1]);
		nrand = 1000;
	} else if(argc == 3) {
		gtype = atoi(argv[1]);
		nrand = atoi(argv[2]);
	} else {
		usage();
	}

	init_sprng(SEED,SPRNG_DEFAULT,gtype);

	MPI_Comm_split_type(comm, MPI_COMM_TYPE_SHARED, 0, MPI_INFO_NULL, &shmcomm);
	MPI_Comm_rank(shmcomm, &srank);

	if(rank == 0) {
		size = sizeof(double);
	}
	MPI_Win_allocate_shared(size, disp_unit, MPI_INFO_NULL, shmcomm, &shptr, &shwin);
	MPI_Win_shared_query(shwin, 0, &size, &disp_unit, &shptr);

	MPI_Win_fence(0, shwin);
	double time = -MPI_Wtime();
	for(i = 0; i < nrand; i++) {
		rn = sprng();
		MPI_Accumulate(&rn, 1, MPI_DOUBLE, 0, 0, 1, MPI_DOUBLE, MPI_SUM, shwin);
	}
	MPI_Win_fence(0, shwin);
	time += MPI_Wtime();

	MPI_Comm_size(shmcomm, &ssize);
	Ntot = nrand*ssize;
	if(srank == 0) {
		avg = shptr[0]/(float)Ntot;
		printf("From global rank %d:\n"
				"	The average value of %lld generated random numbers was %f.\n"
				"	This calculation took %f seconds.\n",
				rank, Ntot, avg, time);
	}

	MPI_Win_free(&shwin);
	MPI_Finalize();

	return 0;
}
