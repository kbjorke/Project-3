#include <cstring>
#include <iostream>
#include "celestial_body.h"

using namespace std;

/* Constructor for Celestial_Body class.
 *
 * Takes ID, mass, dimensionality, position and velocity for
 * a celestial object. Caculates the Kinetic energy by the mass
 * and the speed. Sets the Potential energy to zero, since an
 * singel celestial object is not affected by any force and
 * therfore have zero potential energy.
 *
 * Input:
 *
 *			*_ID  :ID of object.
 *
 *			_mass :Mass of object, in units of kg.
 *
 * 			_dimension :Dimension of the object.
 *
 *			*_position :Array containing position of object, same
 *						dimensionality as _dimension, in unit AU.
 *
 *			*_velocity :Array containing velocity of object, same
 *						dimensionality as _dimension in unit AU/yr.
 * */
Celestial_Body::Celestial_Body(char *_ID, double _mass, int _dimension,
                               double *_position, double *_velocity)
{
    double speed_sqr;
    double M_sun = 2e30; // [kg] Used to get the mass in
    int i;

    strcpy(ID, _ID);
    mass = _mass/M_sun;
    dimension = _dimension;

    position = new double[dimension];
    velocity = new double[dimension];

    speed_sqr = 0;

    for( i = 0; i < dimension; i++ )
    {
        position[i] = _position[i];
        velocity[i] = _velocity[i];

        speed_sqr += velocity[i]*velocity[i];
    }

    kinetic_energy = 0.5*mass*speed_sqr;
    potential_energy = 0;
}

Celestial_Body::Celestial_Body()
{
}
