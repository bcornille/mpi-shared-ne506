/***************************************************************************//*!
 * \file
 * \brief This file handles particle transport.
 *
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "rngsets.h"
#include "source.h"
#include "trans.h"

Particle *curr_part = NULL;

double Sample_Collision(double mu)
{
	return -log(sprng())/mu;
}

double Intersection(Point r, Vector v, Surface *surf)
{
	double A = surf->a*v.u*v.u + surf->b*v.v*v.v + surf->c*v.w*v.w
		     + surf->d*v.u*v.v + surf->e*v.v*v.w + surf->f*v.w*v.u;
	double B = surf->a*r.x*v.u + surf->b*r.y*v.v + surf->c*r.z*v.w
		+ surf->d*(r.x*v.v + r.y*v.u)/2
		+ surf->e*(r.y*v.w + r.z*v.v)/2
		+ surf->f*(r.z*v.u + r.x*v.w)/2
		+ (surf->g*v.u + surf->h*v.v + surf->i*v.w)/2;
	double C = surf->a*r.x*r.x + surf->b*r.y*r.y + surf->c*r.z*r.z
		     + surf->d*r.x*r.y + surf->e*r.y*r.z + surf->f*r.z*r.x
		     + surf->g*r.x     + surf->h*r.y     + surf->i*r.z     + surf->j;
	double D = B*B - A*C;
	double s;

	if(A == 0) {
		if(B*C < 0) {
			s = -C/(2*B);
		} else {
			s = INFINITY;
		}
	} else if(D > 0) {
		if(C > 0) {
			s = (-B - sqrt(D))/A;
		} else {
			s = (-B + sqrt(D))/A;
		}
	} else {
		s = INFINITY;
	}

	return s;
}

double Boundary_Crossing(Point r_p, Vector v_hat, Cell *cell, Surface *surf)
{
	int i;
	double s_b = INFINITY;

	for(i = 0; i < cell->nfaces; i++) {
		if(cell->faces[i].surf != surf) {
			s_b = fmin(s_b, Intersection(r_p, v_hat, cell->faces[i].surf));
		}
	}

	return s_b;
}

Point Jump(Point r_i, double s, Vector v_hat)
{
	Point r_f;

	r_f.x = r_i.x + s*v_hat.u;
	r_f.y = r_i.y + s*v_hat.v;
	r_f.z = r_i.z + s*v_hat.w;

	return r_f;
}

Particle *Propagate(Particle *part)
{
	double s_c;
	double s_b;

	while(part->in_cell != NULL) {
		s_c = Sample_Collision(part->in_cell->mat.lac);
		s_b = Boundary_Crossing(part->r,part->v_hat,part->in_cell,part->on_surf);
		if(s_c < s_b) {
			part->r = Jump(part->r,s_c,part->v_hat);
			part->v_hat = part->in_cell->mat.scat_func(part->v_hat);
			//printf("Particle position (%f, %f, %f)\n", part->r.x, part->r.y, part->r.z);
		} else {
			part->r = Jump(part->r,s_b,part->v_hat);
			part->in_cell = NULL;	/* WARNING: This is a major fault in this
									 * program.  Here it is assumed that there
									 * is only one cell in the entire geometry!
									 * In general this will not be the case, but
									 * this was a rush job to get something for
									 * my class project. */
		}
	}

	return part;
}

Particle *Destroy(Particle *part)
{
	Particle *next_part;

	if(part->next != NULL) {
		next_part = part->next;
		free(part);
		return next_part;
	} else {
		free(part);
		return NULL;
	}
}

void ShMemMC_Transport(int nparts_gen)
{
	int nparts;

	for(nparts = 1; nparts <= nparts_gen; nparts++) {
		curr_part = Source_Particle();
		while(curr_part != NULL) {
			curr_part = Propagate(curr_part);
			curr_part = Destroy(curr_part);
		}
	}

	return;
}
