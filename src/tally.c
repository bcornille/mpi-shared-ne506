/***************************************************************************//*!
 * \file
 * \brief This file will hold all routines related to the tally definition.
 *
 *
 ******************************************************************************/

#include <stdlib.h>
#include "dbg.h"
#include "comms.h"
#include "trans.h"
#include "tally.h"

#define nmesh 100

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
	MPI_Win_fence(0, *win);

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

Indices_3D Get_XYZMesh_IJK(Point r)
{
	int i;
	Indices_3D ijk;

	if(r.x < xyztallies->xbins[0]) {
		ijk.i = -1;
	} else if(xyztallies->xbins[xyztallies->nx] < r.x) {
		ijk.i = xyztallies->nx;
	} else {
		for(i = 0; i < xyztallies->nx; i++) {
			if(xyztallies->xbins[i] <= r.x && r.x <= xyztallies->xbins[i+1]) {
				ijk.i = i;
				break;
			}
		}
	}

	if(r.y < xyztallies->ybins[0]) {
		ijk.j = -1;
	} else if(xyztallies->ybins[xyztallies->ny] < r.y) {
		ijk.j = xyztallies->ny;
	} else {
		for(i = 0; i < xyztallies->ny; i++) {
			if(xyztallies->ybins[i] <= r.y && r.y <= xyztallies->ybins[i+1]) {
				ijk.j = i;
				break;
			}
		}
	}

	if(r.z < xyztallies->zbins[0]) {
		ijk.k = -1;
	} else if(xyztallies->zbins[xyztallies->nz] < r.z) {
		ijk.k = xyztallies->nz;
	} else {
		for(i = 0; i < xyztallies->nz; i++) {
			if(xyztallies->zbins[i] <= r.z && r.z <= xyztallies->zbins[i+1]) {
				ijk.k = i;
				break;
			}
		}
	}

	return ijk;
}

Point Next_Cross(Indices_3D ijk, Vector n, XYZMesh *mesh)
{
	Point cross;

	if(n.u > 0) {
		cross.x = mesh->xbins[ijk.i + 1];
	} else {
		cross.x = mesh->xbins[ijk.i];
	}

	if(n.v > 0) {
		cross.y = mesh->ybins[ijk.j + 1];
	} else {
		cross.y = mesh->ybins[ijk.j];
	}

	if(n.w > 0) {
		cross.z = mesh->zbins[ijk.k + 1];
	} else {
		cross.z = mesh->zbins[ijk.k];
	}

	return cross;
}

Dir Min_Dir(double d[3])
{
	if(d[0] < d[1]) {
		if(d[0] < d[2]) {
			return X;
		} else {
			return Z;
		}
	} else if(d[1] < d[2]) {
		return Y;
	} else {
		return Z;
	}
}

void Score_XYZMesh(XYZMesh *mesh, Indices_3D ijk, double *score)
{
	MPI_Aint disp = mesh->ny*mesh->nz*ijk.i + mesh->nz*ijk.j + ijk.k;

	MPI_Accumulate(score, 1, MPI_DOUBLE, 0, disp, 1, MPI_DOUBLE, MPI_SUM,
			mesh->tally_win);

	return;
}

int sign(double x)
{
	return (x > 0) - (x < 0);
}

void Score_Tallies(Point r_0, Point r_1)
{
	int i;
	double d[3];
	double dist;
	double flux;
	Indices_3D ijk0 = Get_XYZMesh_IJK(r_0);
	Indices_3D ijk1 = Get_XYZMesh_IJK(r_1);
	int n_cross = ijk1.i - ijk0.i + ijk1.j - ijk0.j + ijk1.k - ijk0.k;
	Vector uvw = curr_part->v_hat;
	Point r_cross;

	for(i = 0; i <= n_cross; i++) {
		r_cross = Next_Cross(ijk0, uvw, xyztallies);
		if(i == n_cross) r_cross = r_1;
		d[0] = (r_cross.x - r_0.x)/uvw.u;
		d[1] = (r_cross.y - r_0.y)/uvw.v;
		d[2] = (r_cross.z - r_0.z)/uvw.w;
		Dir dir_cross = Min_Dir(d);
		dist = d[dir_cross];
		flux = dist;
		Score_XYZMesh(xyztallies, ijk0, &flux);
		switch(dir_cross) {
			case X:
				ijk0.i += sign(uvw.u);
				break;
			case Y:
				ijk0.j += sign(uvw.v);
				break;
			case Z:
				ijk0.k += sign(uvw.w);
				break;
		}
		r_0.x += dist*uvw.u;
		r_0.y += dist*uvw.v;
		r_0.z += dist*uvw.w;
	}

	return;
}

void Free_Tallies()
{
	/*
	if(shmem_rank == 0) {
		int i, j, k;
		for(i = 0; i < xyztallies->nx; i++) {
			for(j = 0; j < xyztallies->ny; j++) {
				for(k = 0; k < xyztallies->nz; k++) {
					printf("%9.4f ",xyztallies->tally[xyztallies->ny*xyztallies->nz*i
							+ xyztallies->nz*j + k]);
				}
				printf("\n");
			}
			printf("\n");
		}
	}
	*/

	MPI_Win_fence(0, xyztallies->xwin);
	MPI_Win_free(&(xyztallies->xwin));

	MPI_Win_fence(0, xyztallies->ywin);
	MPI_Win_free(&(xyztallies->ywin));

	MPI_Win_fence(0, xyztallies->zwin);
	MPI_Win_free(&(xyztallies->zwin));

	free(xyztallies);

	return;
}
