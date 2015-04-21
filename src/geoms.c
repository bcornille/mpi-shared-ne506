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
#include <math.h>
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
	nsurfs = 26;
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

		/* This huge chunk of code sets all the planes that make up the
		 * rhombicuboctahedron. */
		temp_point = (Point){0,0,1};
		temp_vec = (Vector){0,0,1};
		surfs[0] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){1/sqrt(2),0,1/sqrt(2)};
		temp_vec = (Vector){1/sqrt(2),0,1/sqrt(2)};
		surfs[1] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){1/sqrt(3),1/sqrt(3),1/sqrt(3)};
		temp_vec = (Vector){1/sqrt(3),1/sqrt(3),1/sqrt(3)};
		surfs[2] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){0,1/sqrt(2),1/sqrt(2)};
		temp_vec = (Vector){0,1/sqrt(2),1/sqrt(2)};
		surfs[3] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){-1/sqrt(3),1/sqrt(3),1/sqrt(3)};
		temp_vec = (Vector){-1/sqrt(3),1/sqrt(3),1/sqrt(3)};
		surfs[4] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){-1/sqrt(2),0,1/sqrt(2)};
		temp_vec = (Vector){-1/sqrt(2),0,1/sqrt(2)};
		surfs[5] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){-1/sqrt(3),-1/sqrt(3),1/sqrt(3)};
		temp_vec = (Vector){-1/sqrt(3),-1/sqrt(3),1/sqrt(3)};
		surfs[6] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){0,1/sqrt(2),1/sqrt(2)};
		temp_vec = (Vector){0,1/sqrt(2),1/sqrt(2)};
		surfs[7] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){1/sqrt(3),-1/sqrt(3),1/sqrt(3)};
		temp_vec = (Vector){1/sqrt(3),-1/sqrt(3),1/sqrt(3)};
		surfs[8] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){1,0,0};
		temp_vec = (Vector){1,0,0};
		surfs[9] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){1/sqrt(2),1/sqrt(2),0};
		temp_vec = (Vector){1/sqrt(2),1/sqrt(2),0};
		surfs[10] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){0,1,0};
		temp_vec = (Vector){0,1,0};
		surfs[11] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){-1/sqrt(2),1/sqrt(2),0};
		temp_vec = (Vector){-1/sqrt(2),1/sqrt(2),0};
		surfs[12] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){-1,0,0};
		temp_vec = (Vector){-1,0,0};
		surfs[13] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){-1/sqrt(2),-1/sqrt(2),0};
		temp_vec = (Vector){-1/sqrt(2),-1/sqrt(2),0};
		surfs[14] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){0,-1,0};
		temp_vec = (Vector){0,-1,0};
		surfs[15] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){1/sqrt(2),-1/sqrt(2),0};
		temp_vec = (Vector){1/sqrt(2),-1/sqrt(2),0};
		surfs[16] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){1/sqrt(2),0,-1/sqrt(2)};
		temp_vec = (Vector){1/sqrt(2),0,-1/sqrt(2)};
		surfs[17] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){1/sqrt(3),1/sqrt(3),-1/sqrt(3)};
		temp_vec = (Vector){1/sqrt(3),1/sqrt(3),-1/sqrt(3)};
		surfs[18] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){0,1/sqrt(2),-1/sqrt(2)};
		temp_vec = (Vector){0,1/sqrt(2),-1/sqrt(2)};
		surfs[19] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){-1/sqrt(3),1/sqrt(3),-1/sqrt(3)};
		temp_vec = (Vector){-1/sqrt(3),1/sqrt(3),-1/sqrt(3)};
		surfs[20] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){-1/sqrt(2),0,-1/sqrt(2)};
		temp_vec = (Vector){-1/sqrt(2),0,-1/sqrt(2)};
		surfs[21] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){-1/sqrt(3),-1/sqrt(3),-1/sqrt(3)};
		temp_vec = (Vector){-1/sqrt(3),-1/sqrt(3),-1/sqrt(3)};
		surfs[22] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){0,-1/sqrt(2),-1/sqrt(2)};
		temp_vec = (Vector){0,-1/sqrt(2),-1/sqrt(2)};
		surfs[23] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){1/sqrt(3),-1/sqrt(3),-1/sqrt(3)};
		temp_vec = (Vector){1/sqrt(3),-1/sqrt(3),-1/sqrt(3)};
		surfs[24] = Create_Plane(temp_point, temp_vec);
		temp_point = (Point){0,0,-1};
		temp_vec = (Vector){0,0,-1};
		surfs[25] = Create_Plane(temp_point, temp_vec);
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
