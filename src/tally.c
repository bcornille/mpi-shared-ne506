/***************************************************************************//*!
 * \file
 * \brief This file will hold all routines related to the tally definition.
 *
 *
 ******************************************************************************/

#include <stdlib.h>
#include "dbg.h"
#include "comms.h"
#include "tally.h"

#define nmesh 10

XYZMesh *xyztallies = NULL;

double *Allocate_Bins(int n, MPI_Win *win)
{
	double *bins = NULL;
	MPI_Aint bins_size = 0;
	int bins_disp = sizeof(double);

	if(shmem_rank == 0) {
		bins_size = n*sizeof(double);
	}
	MPI_Win_allocate_shared(bins_size, bins_disp, MPI_INFO_NULL, shmem_comm,
			&bins, win);
	MPI_Win_shared_query(*win, 0, &bins_size, &bins_disp, &bins);
	MPI_Barrier(shmem_comm);

	return bins;
}

void Default_Tally()
{
	int i = 0;

	xyztallies = (XYZMesh*)malloc(sizeof(XYZMesh));
	check(xyztallies != NULL, "Could not allocate space for xyztallies.");

	xyztallies->nx = nmesh;
	xyztallies->ny = nmesh;
	xyztallies->nz = nmesh;

	xyztallies->xbins = Allocate_Bins(xyztallies->nx + 1, &(xyztallies->xwin));
	xyztallies->ybins = Allocate_Bins(xyztallies->ny + 1, &(xyztallies->ywin));
	xyztallies->zbins = Allocate_Bins(xyztallies->nz + 1, &(xyztallies->zwin));

	xyztallies->tally = Allocate_Bins(xyztallies->nx*xyztallies->ny*xyztallies->nz,
									&(xyztallies->tally_win));

	if(shmem_rank == 0) {
		for(i = 0; i <= nmesh; i++) {
			xyztallies->xbins[i] = -1.0 + (2.0*i)/nmesh;
			xyztallies->ybins[i] = -1.0 + (2.0*i)/nmesh;
			xyztallies->zbins[i] = -1.0 + (2.0*i)/nmesh;
		}
		for(i = 0; i < xyztallies->nx*xyztallies->ny*xyztallies->nz; i++) {
			xyztallies->tally[i] = 0.0;
		}
	}

	return;

error:
	exit(1);
}

void Tally_Init(char *File_in)
{
	log_info("Tally based on input is not currently available.");
	exit(1);
}
