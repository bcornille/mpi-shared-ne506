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
#include "dbg.h"
#include "geoms.h"

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
	//! A rhombicuboctahedron has 24 faces.
	nsurfs = 24;
	surfs = malloc(nsurfs*sizeof(Suface));
	check(surfs != NULL, "Could not allocate space for surfaces.");

	Point temp_point;	// Temporary point used for creating each plane.
	Vector temp_vec;	// Temporary vector used for creating each plane.

	temp_point = {.x = 1, .y = 0, .z = 0};
	temp_vec = {.u = 1, .v = 0, .w = 0};
	surfs[0] = Create_Plane(temp_point, temp_vec);

	return;

error:
	exit(1);
}
