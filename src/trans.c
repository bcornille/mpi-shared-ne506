/***************************************************************************//*!
 * \file
 * \brief This file handles particle transport.
 *
 *
 ******************************************************************************/

#include <math.h>
#include "trans.h"

Particle *curr_part = NULL;

double Sample_Collision(double mu)
{
	return -log(sprng())/mu;
}

double Intersection(Point r_p, Vector v_hat, Cell *cell, Surface *surf)
{
	int i;

	for(i = 0; i < cell->nfaces; i++) {


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
	while(part->in_cell != NULL) {
		s_c = Sample_Collision(part->in_cell->mat.lac);
		s_b = Intersection(part->r,part->v_hat,part->in_cell,part->on_surf);
		if(s_c < s_b) {
			part->r = Jump(part->r,s_c,part->v_hat);
			part->v_hat = part->in_cell->mat.scat_func(part->v_hat);
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
}

void ShMemMC_Transport(int nparts_gen)
{
	int nparts;

	for(nparts = 1; nparts <= npart_gen, nparts++) {
		curr_part = Source_Particle();
		while(curr_part != NULL) {
			curr_part = Propagate(curr_part);
			curr_part = Destroy(curr_part);
		}
	}

	return;
}
