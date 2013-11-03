#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

/* Class for celestial objects.
 *
 * Contains Identification (ID), mass, position, velocity,
 * kinetic energy and potential energy of a celestial body.
 * */

class Celestial_Body
{
public:
    char ID[30];
    int dimension;
    double mass; //[1/M_sun]
    double *position, *velocity; //[AU], [AU/yr]
    double potential_energy, kinetic_energy;

    Celestial_Body(char *_ID, double _mass, int _dimension,
                   double *_position, double *_velocity);
    Celestial_Body();
};

#endif // CELESTIAL_BODY_H
