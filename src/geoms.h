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
typedef enum Sense {POS, NEG} Sense;

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
	int nfaces;		//!< Number of surfaces defining the cell exterior.
	Face *faces;	//!< Pointer array to all faces.
	Material mat;
} Cell;

// Routines
void Geom_Init(char *File_in);

void Default_Geom()

#endif
