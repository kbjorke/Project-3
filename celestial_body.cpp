#include <cstring>
#include <iostream>
#include "celestial_body.h"

using namespace std;

Celestial_Body::Celestial_Body(char *_ID, double _mass, int _dimension,
                               double *_position, double *_velocity)
{
    static int i;

    strcpy(ID, _ID);
    mass = _mass;
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
