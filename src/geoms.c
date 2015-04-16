/***************************************************************************//*!
 * \file
 * \brief This file will contain all the subroutines related to both geometry
 * initialization and calculations.
 *
 * Contents:
 *
 *
 *
 ******************************************************************************/

// Dependencies and necessary inclusions.
#include <stdlib.h>
#include <mpi.h>
#include "dbg.h"
#include "geoms.h"
#include "comms.h"

// Define all external varialbles at file scope.
int nsurfs = 0;
Surface *surfs = NULL;
MPI_Win surfs_win;		// This may need to be moved out to a global scope.

//! Define a plane given a point and unit normal.
/*!
 * \param point A given point that lies in the desired plane.
 * \param normal The vector normal to the desired plane.
 */
Surface Create_Plane(Point point,Vector normal)
{
	Surface new_surface;
	new_surface.a = 0;
	new_surface.b = 0;
	new_surface.c = 0;
	new_surface.d = 0;
	new_surface.e = 0;
	new_surface.f = 0;
	new_surface.g = normal.u;
	new_surface.h = normal.v;
	new_surface.i = normal.w;
	new_surface.j = -normal.u*point.x - normal.v*point.y - normal.w*point.z;

	return new_surface;
}

//! General geometry initalization.
/*!
 * This is currently an unusable option.
 */
void Geom_Init(char *File_in)
{
	log_info("Geometry based on input is not currently available.");
	exit(1);
}

//! Default geometry.
/*!
 * The default geometry is currently planned to be a rhombicuboctahedron.
 */
void Default_Geom()
{
	// Temporary variables for shared memory allocation.
	MPI_Aint surfs_size = 0;	// Could be reused for each memory allocation.
	int surfs_disp;				// Array displacement for Surface structure.

	//! A rhombicuboctahedron has 24 faces.
	nsurfs = 24;
	surfs_disp = sizeof(Surface);
	if(shmem_rank == 0 ){
		surfs_size = nsurfs*sizeof(Surface);
	}
	MPI_Win_allocate_shared(surfs_size, surfs_disp, MPI_INFO_NULL, 
			shmem_comm, &surfs, &surfs_win);
	MPI_Win_shared_query(surfs_win, 0, &surfs_size, &surfs_disp, &surfs);
	check(surfs != NULL, "Could not allocate space for surfaces.");
	MPI_Win_fence(0, surfs_win);

	if(shmem_rank == 0) {
		Point temp_point;	// Temporary point used for creating each plane.
		Vector temp_vec;	// Temporary vector used for creating each plane.

		temp_point = (Point){1,0,0};
		temp_vec = (Vector){1,0,0};
		surfs[0] = Create_Plane(temp_point, temp_vec);
	}

	MPI_Win_fence(0, surfs_win);	// Wait until the surfaces have been established.

	return;

error:
	exit(1);
}

//! Free geometry elements.
/*!
 * Arrays that need freed:
 * 	1. surfs
 */
void Free_Geom()
{
	// Free surfs. Free should be safe.
	MPI_Win_free(&surfs_win);

	return;
}
