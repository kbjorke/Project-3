#ifndef CELESTIAL_BODY_H
#define CELESTIAL_BODY_H

class Celestial_Body
{
public:
    char ID[20];
    int dimension;
    double mass;
    double *position, *velocity;

    Celestial_Body(char *_ID, double _mass, int _dimension,
                   double *_position, double *_velocity);
    Celestial_Body();
};

#endif // CELESTIAL_BODY_H
