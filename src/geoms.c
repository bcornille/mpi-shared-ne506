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
Surface *surfs = NULL;	// Initialize surfs as NULL to easily check allocation.
int ncells = 0;
Cell *cells = NULL;		// Initialize cells as NULL to easily check allocation.
MPI_Win surfs_win;		// Window defining the shared memory allocated to surfs.
MPI_Win cells_win;		// Window defining the shared memory allocated to cells.

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

//! Allocates faces.
/*!
 * \param cell Pointer to current cell that needs faces allocated.
 */
Face *Faces_Allocate(Cell *cell)
{
	cell->faces = (Face*)malloc(cell->nfaces*sizeof(Face));
	check(cell->faces != NULL, "Could not allocate space for faces.");

	return cell->faces;

error:
	exit(1);
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
	int i = 0;	// For looping.

	//! A rhombicuboctahedron has 26 faces.
	nsurfs = 26;
	surfs = (Surface*)malloc(nsurfs*sizeof(Surface));
	check(surfs != NULL, "Could not allocate space for surfaces.");

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

	ncells = 1;
	cells = (Cell*)malloc(ncells*sizeof(Cell));
	check(cells != NULL, "Could not allocate space for cells.");

	cells[0].nfaces = 26;
	cells[0].faces = Faces_Allocate(&cells[0]);
	for(i = 0; i < cells[0].nfaces; i++) {
		cells[0].faces[i].sense = NEG;
		cells[0].faces[i].surf = &surfs[i];
	}
	cells[0].weight = 1.0;

	return;

error:
	exit(1);
}

//! Free geometry elements.
/*!
 * Arrays that need freed:
 * 	1. surfs
 * 	2. cells
 * 		a. faces
 */
void Free_Geom()
{
	free(cells->faces);
	free(cells);
	free(surfs);

	return;
}
