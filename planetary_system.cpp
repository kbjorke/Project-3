#include <armadillo>
#include <cmath>
#include <fstream>
#include "planetary_system.h"
#include "celestial_body.h"
#include "RungeKutta4.h"

#include <iostream>

using namespace std;
using namespace arma;


Planetary_System::Planetary_System(Celestial_Body *celest_bodies,
                                   int objects, int dimension)
{
    this->celest_bodies = celest_bodies;
    this->objects = objects;
    this->dimension = dimension;


    static int object, other_object, i;
    static double distance;
    static double pi = 3.1415926535897;

    total_energy = 0;

    total_momentum = new double[dimension];
    for( i = 0; i < dimension; i++ ){
        total_momentum[i] = 0;
    }

    for( object = 0; object < objects; object++ ){
        for( other_object = 0; other_object < objects; other_object++ ){
            if( object != other_object )
            {
                distance = 0;
                for( i = 0; i < dimension; i++ )
                {
                    distance +=
                            (celest_bodies[object].position[i] -
                             celest_bodies[other_object].position[i])*
                            (celest_bodies[object].position[i] -
                             celest_bodies[other_object].position[i]);
                }
                distance = sqrt(distance);

                celest_bodies[object].potential_energy -=
                        (4*pi*pi*celest_bodies[other_object].mass)/distance;
            }
        }
        total_energy += celest_bodies[object].potential_energy +
                celest_bodies[object].kinetic_energy;

        for( i = 0; i < dimension; i++ )
        {
            total_momentum[i] += celest_bodies[object].velocity[i]*
                    celest_bodies[object].mass;
        }
    }
}

Planetary_System::Planetary_System()
{
}

void Planetary_System::evolve(char *output_filename,
                              double end_time, double time_step)
{
    int i, j, step;
    double time, steps;
    double speed_sqr;

    fstream myfile;
    myfile.open(output_filename, ios::out);

    myfile << "Objects: " << objects << '\t'
           << "Dimensions: " << dimension << '\t'
           << "Time step: " << time_step << '\t'
           << "End time: " << end_time << '\t' << endl;

    static mat k1, k2, k3, k4;

    steps = ceil(end_time/time_step);

    mat u(objects, 2*dimension);

    myfile << "Time" << '\t';
    for (i = 0; i < objects; i++)
    {
        myfile << celest_bodies[i].ID << '\t';
        /*
        myfile << "Position," << celest_bodies[i].ID << '\t'
               << "Velocity," << celest_bodies[i].ID << '\t';
        */
    }
    myfile << "Total energy" << '\t' << "Total momentum" << endl;

    for( i = 0; i < objects; i++ ){
        for( j = 0; j < dimension; j++ )
        {
            u(i,j) = celest_bodies[i].position[j];
            u(i,j+dimension) = celest_bodies[i].velocity[j];
        }
    }

    myfile << "0" << '\t';
    myfile << scientific;
    for( i = 0; i < objects; i++ ){
        myfile << "(";
        for( j = 0; j < dimension; j++ ){
            if( j > 0 ){
                myfile << ",";
            }
            myfile << celest_bodies[i].position[j];
        }
        myfile << ")" << '\t'; // << "(";
        /*
        for( j = 0; j < dimension; j++ ){
            if (j > 0 ){
                myfile << ",";
            }
            myfile << celest_bodies[i].velocity[j];
        }
        myfile << ")" << '\t';
        */
    }
    myfile << total_energy << '\t';
    myfile << "(";
    for( j = 0; j < dimension; j++ ){
        if( j > 0 ){
            myfile << ",";
        }
        myfile << total_momentum[j];
    }
    myfile << ")" << endl;


    for( step = 1; step <= steps; step++ )
    {
        time = time_step*step;

        k1 = time_step*gravity_function(time, u);
        k2 = time_step*gravity_function(time + time_step/2, (u + k1/2));
        k3 = time_step*gravity_function(time + time_step/2, (u + k2/2));
        k4 = time_step*gravity_function(time + time_step, (u + k3));

        u = u + (1./6)*(k1 + k2*2 + k3*2 + k4);

        total_energy = 0;

        for( i = 0; i < dimension; i++ ){
            total_momentum[i] = 0;
        }

        for( i = 0; i < objects; i++ ){
            speed_sqr = 0;
            for( j = 0; j < dimension; j ++ )
            {
                celest_bodies[i].position[j] = u(i,j);
                celest_bodies[i].velocity[j] = u(i,j+dimension);

                speed_sqr += celest_bodies[i].velocity[j]*
                        celest_bodies[i].velocity[j];

                total_momentum[j] += celest_bodies[i].velocity[j]*
                        celest_bodies[i].mass;
            }
            celest_bodies[i].kinetic_energy = 0.5*celest_bodies[i].mass*
                    speed_sqr;

            total_energy += celest_bodies[i].kinetic_energy +
                   celest_bodies[i].potential_energy;
        }
        myfile << time << '\t';
        for( i = 0; i < objects; i++ ){
            myfile << "(";
            for( j = 0; j < dimension; j++ ){
                if( j > 0 ){
                    myfile << ",";
                }
                myfile << celest_bodies[i].position[j];
            }
            myfile << ")" << '\t'; // << "(";
            /*
            for( j = 0; j < dimension; j++ ){
                if (j > 0 ){
                    myfile << ",";
                }
                myfile << celest_bodies[i].velocity[j];
            }
            myfile << ")" << '\t';
            */
        }
        myfile << total_energy << '\t';
        myfile << "(";
        for( j = 0; j < dimension; j++ ){
            if( j > 0 ){
                myfile << ",";
            }
            myfile << total_momentum[j];
        }
        myfile << ")" << endl;


    }
    myfile.close();
}


mat Planetary_System::gravity_function(double t, mat u)
{
    static int object, other_object, i;
    static double distance;
    static double pi = 3.1415926535897;

    double force[dimension];
    double abs_force;
    static mat u_new(objects, dimension*2);

    for( object = 0; object < objects; object++ ){
        abs_force = 0;
        celest_bodies[object].potential_energy = 0;

        for( i = 0; i < dimension; i++ )
        {
            u_new(object, i) = u(object, dimension+i);
            force[i] = 0;
        }
        for( other_object = 0; other_object < objects; other_object++ ){
            if( object != other_object )
            {
                distance = 0;
                for( i = 0; i < dimension; i++ )
                {
                    distance += (u(object,i) - u(other_object,i))*
                            (u(object,i) - u(other_object,i));
                }
                distance = sqrt(distance);
                for( i = 0; i < dimension; i++ )
                {
                    force[i] -= (4*pi*pi*celest_bodies[other_object].mass)/
                            pow(distance,3);

                    abs_force += force[i]*force[i];
                }
                abs_force = sqrt(abs_force);

                celest_bodies[object].potential_energy -= abs_force*distance;
            }
            for( i = 0; i < dimension; i++ )
            {
                u_new(object, dimension+i) = force[i]*
                        (u(object,i) - u(other_object,i));
            }
        }
    }

    return u_new;
}

