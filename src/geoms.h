/*!
 * \file
 * \brief Geometry header file.
 */
#ifndef _geoms_h
#define _geoms_h

//! Sense type definition.
/*!
 * The sense of a face can be positive or negative.
 */
typedef enum Sense {POS = 1, NEG = -1} Sense;

//! Surface structure definition.
/*!
 *  2nd order analytic surface:
 *
 *  \f$F(x,y,z) = ax^2 + by^2 + cz^2 +
 *  			dxy + eyz + fzx +
 *  			gx + hy + iz + j\f$
 *
 *  Defined where \f$F(x,y,z) = 0\f$
 */
typedef struct Surface {
	double a;	//!< coefficient of \f$x^2\f$
	double b;	//!< coefficient of \f$y^2\f$
	double c;	//!< coefficient of \f$z^2\f$
	double d;	//!< coefficient of \f$xy\f$
	double e;	//!< coefficient of \f$yz\f$
	double f;	//!< coefficient of \f$zx\f$
	double g;	//!< coefficient of \f$x\f$
	double h;	//!< coefficient of \f$y\f$
	double i;	//!< coefficient of \f$z\f$
	double j;	//!< final constant
} Surface;

//! Face structure definition.
/*!
 * A face consists of a surface and a positive or negative sense.
 */
typedef struct Face {
	Sense sense;	//!< The sense of the face: POS or NEG
	Surface *surf;	//!< Pointer to the surface that defines this face.
} Face;

//! Cell structure definition.
/*!
 * Cells have a number of faces, those face definitions,
 * and a cell material.
 */
typedef struct Cell {
	//! Number of surfaces defining the cell exterior.
	int nfaces;
	//! Pointer array to all faces.
	Face *faces;
	//! How the cell should be weighted during particle transport.
	double weight;
	//! Cell material.
	Material mat;
} Cell;

//! Point structure definition.
/*!
 * A point has coordinates x, y, and z.
 */
typedef struct Point {
	double x;	//!< x-coordinate.
	double y;	//!< y-coordinate.
	double z;	//!< z-coordinate.
} Point;

//! Vector structure definition.
/*!
 * A vector points a distance u in the x direction,
 * v in the y direction, and w in the z direction.
 */
typedef struct Vector {
	double u;	//!< Magnitude along x-coordinate.
	double v;	//!< Magnitude along y-coordinate.
	double w;	//!< Magnitude along z-coordinate.
} Vector;

//! Number of surfaces defined for the geometry.
/*!
 * These surfaces include more than those that just define the cells.
 * They may also be used for sources, tallies, etc.
 */
extern int nsurfs;

//! All surfaces defined in the geometry.
/*!
 * These surfaces include more than those that just define the cells.
 * They may also be used for sources, tallies, etc.
 */
extern Surface *surfs;

//! Number of cells defined for the geometry.
/*!
 * All cells defined are used for the particle transport.
 */
extern int ncells;

//! All cells defined in the geometry.
/*!
 * Cells must be convex otherwise there will be errors.
 */
extern Cell *cells;

// Routines
void Geom_Init(char *File_in);
void Default_Geom();
void Free_Geom();

#endif
