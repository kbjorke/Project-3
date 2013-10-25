#ifndef PLANETARY_SYSTEM_H
#define PLANETARY_SYSTEM_H

#include <armadillo>
#include "celestial_body.h"

using namespace arma;

class Planetary_System
{
    int objects;
    int dimension;

public:
    Celestial_Body *celest_bodies;

    Planetary_System(Celestial_Body *celest_bodies, int objects);
    void evolve(double end_time, double time_step);
    static mat gravity_function(double t, mat u);
};

#endif // PLANETARY_SYSTEM_H
