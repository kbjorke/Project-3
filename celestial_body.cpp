#include <cstring>
#include <iostream>
#include "celestial_body.h"

using namespace std;

Celestial_Body::Celestial_Body(char *_ID, double _mass, int _dimension,
                               double *_position, double *_velocity)
{
    double M_sun = 2e30; // [kg]
    double pi = 3.1415926535897;
    int i;

    strcpy(ID, _ID);
    mass = _mass/M_sun;
    dimension = _dimension;

    position = new double[dimension];
    velocity = new double[dimension];

    for( i = 0; i < dimension; i++ )
    {
        position[i] = _position[i];
        velocity[i] = _velocity[i];
    }
}

Celestial_Body::Celestial_Body()
{
}
