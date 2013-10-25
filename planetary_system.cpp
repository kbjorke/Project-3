#include <armadillo>
#include <cmath>
#include "planetary_system.h"
#include "celestial_body.h"
#include "RungeKutta4.h"

#include <iostream>

using namespace std;
using namespace arma;



Planetary_System::Planetary_System(Celestial_Body *celest_bodies, int objects)
{
    this->celest_bodies = celest_bodies;
    this->objects = objects;
}

void Planetary_System::evolve(double end_time, double time_step)
{
    int steps, i, j;
    double time;

    dimension = 2;

    //steps = ceil(end_time/time_step);

    mat u(objects, 2*dimension);

    for( i = 0; i < objects; i++ ){
        for( j = 0; j < dimension; j ++ )
        {
            u(i,j) = celest_bodies[i].position[j];
            u(i,j+dimension) = celest_bodies[i].velocity[j];
        }
    }

    cout << u.n_rows << "  " << u.n_cols << endl;

    for( time = time_step; time < end_time; time+=time_step )
    {
        RK4(time_step, time, &u, &gravity_function);
    }

}


mat Planetary_System::gravity_function(double t, mat u)
{
    static int objects, dimension, object, other_object, i;
    static double distance, force;

    objects = u.n_rows;
    dimension = u.n_cols/2;

    static mat u_new(objects, dimension*2);

    for( object = 0; object < objects; object++ )
    {
        for( i = 0; i < dimension; i++ )
        {
            u_new(object, i) = u(object, dimension+i);
        }
        force = 0;
    }

    return u_new;
}
