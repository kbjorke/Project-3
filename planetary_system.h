#ifndef PLANETARY_SYSTEM_H
#define PLANETARY_SYSTEM_H

#include <armadillo>
#include "celestial_body.h"

using namespace arma;


/* Class for planetary system.
 *
 * Contains Celestial_Body array containing instances of
 * Celestial_Body for the objects in the planetary system.
 * Also contains total energy and total momentum of the
 * system.
 *
 * Use method evolve to evolve the planetary system based
 * on the forces between the different object in the
 * system.
 * */

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
