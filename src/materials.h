/*!
 * \file
 * \brief Header file for materials.
 */

#ifndef _materials_h
#define _materials_h

typedef Vector (*Scatter)(Vector v);

typedef struct Material {
	double lac;
	Scatter scat_func;
} Material;

Material Default_Material();

#endif
