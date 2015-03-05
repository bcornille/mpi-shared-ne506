#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define SIMPLE_SPRNG
#define USE_MPI
#include "sprng.h"

#define SEED 987654321

int rank;

void usage()
{
	if(rank == 0) {
		perror("USAGE: sprng_mpi_HelloWorld <gtype> [<nrand>]\n");
	}

	exit(1);
}

int main(int argc, char *argv[])
{
	double rn;
	int i;
	int gtype, nrand;

	// MPI initialization calls
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &rank);

	if(argc == 2) {
		gtype = atoi(argv[1]);
		nrand = 3;
	} else if(argc == 3) {
		gtype = atoi(argv[1]);
		nrand = atoi(argv[2]);
	} else {
		usage();
	}

	init_sprng(SEED,SPRNG_DEFAULT,gtype);

	for(i = 0; i < nrand; i++) {
		rn = sprng();
		printf("Process %d, random number %d: %.14f\n", rank, i+1, rn);
	}

	MPI_Finalize();
	return 0;
}
