#ifndef PLANETARY_SYSTEM_H
#define PLANETARY_SYSTEM_H

#include <armadillo>
#include "celestial_body.h"

using namespace arma;

class Planetary_System
{
    int objects;
    int dimension;
    double total_energy, *total_momentum;
    double time;
    bool *stationary;

public:
    Celestial_Body *celest_bodies;

    Planetary_System(Celestial_Body *celest_bodies,
                     int objects, int dimension);
    Planetary_System();
    void evolve(char *output_filename,
                double end_time, double time_step);
    mat gravity_function(double t, mat u);
    void adjust_to_CM();
    void fix_momentum(char *fix_object);
    void set_stationary(char *stationary_object);
};

#endif // PLANETARY_SYSTEM_H
