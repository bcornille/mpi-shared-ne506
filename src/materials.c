/***************************************************************************//*!
 * \file
 * \brief File responsible for materials stuffs.
 *
 *
 ******************************************************************************/

#include <math.h>
#include "rngsets.h"
#include "geoms.h"

Vector Cross(Vector a, Vector b)
{
	Vector c;

	c.u = a.v*b.w - b.v*a.w;
	c.v = a.w*b.u - b.w*a.u;
	c.w = a.u*b.v - b.u*a.v;

	return c;
}

Vector Rotation(Vector e1, Vector e2, Vector e3, double theta, double phi)
{
	Vector n;

	n.u = cos(phi)*sin(theta)*e1.u + sin(phi)*sin(theta)*e2.u + cos(theta)*e3.u;
	n.v = cos(phi)*sin(theta)*e1.v + sin(phi)*sin(theta)*e2.v + cos(theta)*e3.v;
	n.w = cos(phi)*sin(theta)*e1.w + sin(phi)*sin(theta)*e2.w + cos(theta)*e3.w;

	return n;
}

Vector Hard_Sphere(Vector v_hat)
{
	Vector e1;
	Vector e2;
	double theta = 2*acos(sprng());
	double phi = 2*M_PI*sprng();
	Vector v_prime;

	if(fabs(v_hat.w) > 0.5) {
		e1.u = sqrt(v_hat.w*v_hat.w/(v_hat.u*v_hat.u + v_hat.w*v_hat.w));
		e1.w = e1.u*v_hat.u/v_hat.w;
		e1.v = 0;
		e2 = Cross(v_hat, e1);
		v_prime = Rotation(e1, e2, v_hat, theta, phi);
	} else if(fabs(v_hat.v) > 0.5) {
		e1.w = sqrt(v_hat.v*v_hat.v/(v_hat.w*v_hat.w + v_hat.v*v_hat.v));
		e1.v = e1.w*v_hat.w/v_hat.v;
		e1.u = 0;
		e2 = Cross(v_hat, e1);
		v_prime = Rotation(e1, e2, v_hat, theta, phi);
	} else {
		e1.v = sqrt(v_hat.u*v_hat.u/(v_hat.v*v_hat.v + v_hat.u*v_hat.u));
		e1.u = e1.v*v_hat.v/v_hat.u;
		e1.w = 0;
		e2 = Cross(v_hat, e1);
		v_prime = Rotation(e1, e2, v_hat, theta, phi);
	}

	return v_prime;
}

Material Default_Material()
{
	return (Material){10, Hard_Sphere};
}
