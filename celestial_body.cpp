#include <cstring>
#include <iostream>
#include "celestial_body.h"

using namespace std;

Celestial_Body::Celestial_Body(char *_ID, double _mass, int _dimension,
                               double *_position, double *_velocity)
{
    double speed_sqr;
    double M_sun = 2e30; // [kg]
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
