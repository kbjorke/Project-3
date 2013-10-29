#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

class Celestial_Body
{
public:
    char ID[20];
    int dimension;
    double mass; //[1/M_sun]
    double *position, *velocity; //[AU], [AU/yr]
    double potential_energy, kinetic_energy;

    Celestial_Body(char *_ID, double _mass, int _dimension,
                   double *_position, double *_velocity);
    Celestial_Body();
};

#endif // CELESTIAL_BODY_H
