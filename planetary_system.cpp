#include <armadillo>
#include <cmath>
#include <fstream>
#include <cstring>
#include "planetary_system.h"
#include "celestial_body.h"

#include <iostream>

using namespace std;
using namespace arma;

/* Constructor for Planetary_System class.
 *
 * Initialze a planetary system based on a
 * array of Celestial_Body containing the objects in the
 * system.
 * Also calculates
 *
 * Input:
 *
 *			*celest_bodies  : Celestial objects that make up the system.
 *
 *			object          : Number of objects in the system.
 *
 * 			dimension       : Dimensionality of the system.
 *
 * */
Planetary_System::Planetary_System(Celestial_Body *celest_bodies,
                                   int objects, int dimension)
{
    this->celest_bodies = celest_bodies;
    this->objects = objects;
    this->dimension = dimension;


    static int object, other_object, i;
    static double distance;
    static double pi = 3.1415926535897;

    // Initial stationary boolean array, to be used for the
    // functionality of the -statio option in the main program.
    // Starts with none of the objects set as stationary.
    for( object = 0; object < objects; object++ ){
        stationary[object] = false;
    }

    total_energy = 0;

    total_momentum = new double[dimension];
    for( i = 0; i < dimension; i++ ){
        total_momentum[i] = 0;
    }

    for( object = 0; object < objects; object++ ){
        // Loop to calculate potential energy for all the objects.
        // Updates the celest_bodies array with the computed values.
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
                            (4*pi*pi*celest_bodies[other_object].mass*
                             celest_bodies[object].mass)/distance;
            }
        }

        // Sets the total energy of the system equal to the sum of the
        // potential energy and the kinetic energy of all the objects.
        total_energy += celest_bodies[object].potential_energy +
                celest_bodies[object].kinetic_energy;

        // Loop to set the total momentum of the system, based on the
        // velocity and mass of the objects.
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

/* Method to preforme a time evolution of the system over a period of
 * time. Bases its evolution on Runge_Kutta 4th order and a time step.
 * During the time evolution the method writed the updated values for
 * position and velocity to a output file.
 *
 * Input:
 * 			- *output_filename: filename of the file where the output
 *								data is to be written.
 *
 *			- end_time: how long time we want our evolution to go, in unit yr.
 *
 * 			- time_step: time step for the solution, in unit yr.
 *
 * */
void Planetary_System::evolve(char *output_filename,
                              double end_time, double time_step)
{
    int i, j, step;
    double steps;
    double speed_sqr;

    fstream myfile;
    myfile.open(output_filename, ios::out);

    // Writes first line of output file, which contains
    // Information about how many objects, the dimensionality
    // of the problem, the time step and the end time of the
    // simulation:
    myfile << "Objects: " << objects << '\t'
           << "Dimensions: " << dimension << '\t'
           << "Time step: " << time_step << '\t'
           << "End time: " << end_time << '\t' << endl;

    static mat k1, k2, k3, k4;

    steps = ceil(end_time/time_step);

    // Generate matrix to be used for the Runge Kutta solver:
    mat u(objects, 2*dimension);

    // Matrix contains in the position and velocity of all the objects
    // in the system.
    for( i = 0; i < objects; i++ ){
        for( j = 0; j < dimension; j++ )
        {
            u(i,j) = celest_bodies[i].position[j];
            u(i,j+dimension) = celest_bodies[i].velocity[j];
        }
    }

    // Start to write second line, information of what the columns in
    // the output file contains.
    myfile << "Time" << '\t';
    for (i = 0; i < objects; i++)
    {
        myfile << celest_bodies[i].ID << '\t';
    }
    myfile << "Total energy" << '\t' << "Total momentum" << endl;

    // Start to write first line of output form the system, this is
    // the inital condition at time t = 0:
    myfile.precision(10);
    myfile << scientific;
    myfile << "0" << '\t' << '\t' << '\t' << '\t' << '\t';
    for( i = 0; i < objects; i++ ){
        // Loop that writes the position and the kinetic and
        // potential energy for each object.
        // ([pos],kinetic_energy, potential_energy)
        myfile << "(";
        for( j = 0; j < dimension; j++ ){
            if( j > 0 ){
                myfile << ",";
            }
            myfile << celest_bodies[i].position[j];
        }
        myfile << "," << celest_bodies[i].kinetic_energy;
        myfile << "," << celest_bodies[i].potential_energy;
        myfile << ")" << '\t';

    }
    // Last two columns contains total energy and total momentum of system:
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
        // Loop for the time evolution:

        time = time_step*step;

        // Impementation of Runge-Kutta 4th order, uses
        // gravitation_fucntion method:
        k1 = time_step*gravity_function(time, u);
        k2 = time_step*gravity_function(time + time_step/2, (u + k1/2));
        k3 = time_step*gravity_function(time + time_step/2, (u + k2/2));
        k4 = time_step*gravity_function(time + time_step, (u + k3));

        u = u + (1./6)*(k1 + k2*2 + k3*2 + k4);

        // Set total energy and momentum to zero, so they are ready to
        // be updated.
        total_energy = 0;

        for( i = 0; i < dimension; i++ ){
            total_momentum[i] = 0;
        }

        for( i = 0; i < objects; i++ ){
            speed_sqr = 0;
            for( j = 0; j < dimension; j ++ )
            {
                // We update the celest_bodies array with the new values
                // obtained with the Runge-Kutta solution:
                celest_bodies[i].position[j] = u(i,j);
                celest_bodies[i].velocity[j] = u(i,j+dimension);

                speed_sqr += celest_bodies[i].velocity[j]*
                        celest_bodies[i].velocity[j];

                // Update total momentum:
                total_momentum[j] += celest_bodies[i].velocity[j]*
                        celest_bodies[i].mass;
            }
            // Update kinetic energy:
            celest_bodies[i].kinetic_energy = 0.5*celest_bodies[i].mass*
                    speed_sqr;

            // Update total energy:
            total_energy += celest_bodies[i].kinetic_energy +
                   celest_bodies[i].potential_energy;
        }

        // Writes to outputfile results form current itteration:
        myfile << time << '\t';
        for( i = 0; i < objects; i++ ){
            myfile << "(";
            for( j = 0; j < dimension; j++ ){
                if( j > 0 ){
                    myfile << ",";
                }
                myfile << celest_bodies[i].position[j];
            }
            myfile << "," << celest_bodies[i].kinetic_energy;
            myfile << "," << celest_bodies[i].potential_energy;
            myfile << ")" << '\t';

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


/* Method used as right hand side in the Runge-Kutta algorithm in evolve method.
 * Based on the celestial mechanical forces we derive from Newton's laws.
 *
 * Also as a part of the method it  updates the potential energy of the
 * system.
 *
 *
 * Input:
 *			- u: Matrix containing input data for the right hand side function.
 * 				 For our problem the matrix u consist of the number of objects
 *				 rows and the position and the velocity in the rows.
 *
 *           Example, dim=2, obj=3:
 *										u = |x_1, y_1, v_x1, v_y1|
 *										    |x_2, y_2, v_x2, v_y2|
 *										    |x_3, y_3, v_x3, v_y3|
 *
 *
 * 			- t: Time of current itteration.
 *
 * Return:
 *	 	u_new	: matrix wich contain values return by the
 *  				  respective rhs function.
 *
 * */
mat Planetary_System::gravity_function(double t, mat u)
{
    static int object, other_object, i;
    static double distance;
    static double pi = 3.1415926535897;

    double force;
    double potential;
    static mat u_new(objects, dimension*2);

    for( object = 0; object < objects; object++ ){
        if( t == time ){
        celest_bodies[object].potential_energy = 0;
        }

        for( i = 0; i < dimension; i++ )
        {
            // Answer to first rhs function:
            // dx/dt = v_x
            u_new(object, i) = u(object, dimension+i);

            u_new(object, dimension+i) = 0;
        }

        for( other_object = 0; other_object < objects; other_object++ ){
            // Loop to calculate force on a object and the potential on the same
            // object.
            potential = 0;

            force = 0;

            if( object != other_object )
            {
                distance = 0;
                for( i = 0; i < dimension; i++ )
                {
                    // Loop to calculate distance between two objects
                    distance += (u(object,i) - u(other_object,i))*
                            (u(object,i) - u(other_object,i));
                }
                distance = sqrt(distance);

                // Adds force from other object
                force = -(4*pi*pi*celest_bodies[other_object].mass)/
                            pow(distance,3);

                // If the object is set as stationary it does not update its
                // potential energy.
                if( stationary[object] == false ){
                    potential = -(4*pi*pi*celest_bodies[object].mass*
                                  celest_bodies[other_object].mass)/distance;
                }

                // Since this method is called four time each time step,
                // then this loop ensures that the potential energy is
                // just updated once every time step.
                if( t == time ){
                        celest_bodies[object].potential_energy +=
                                potential;
                }
                for( i = 0; i < dimension; i++ )
                {
                    // Sets the rhs function if not stationary.
                    // dv/dt = a
                    if( stationary[object] == false ){
                        u_new(object, dimension+i) += force*
                                (u(object,i) - u(other_object,i));
                    }
                }
            }
        }
    }

    return u_new;
}


/* Method used to set object stationary, meaning that it will not
 * be affected by the gravitational pull of the other objects.
 *
 * Removes the objects energy from the systems total energy,
 * and sets the objects potential energy to zero, since it
 * is not affected by forces.
 *
 * Input:
 * 			- *stationary_object : ID of the object to be
 *								   set as stationary.
 *
 * */
void Planetary_System::set_stationary(char *stationary_object)
{
    static int object;

    for( object = 0; object < objects; object++ )
    {
        if( string(celest_bodies[object].ID).find(stationary_object) !=
                string::npos)
        {
            stationary[object] = true;
            total_energy -= celest_bodies[object].potential_energy;
            celest_bodies[object].potential_energy = 0;
        }
    }
}

/* Method used to adjust the coordinate system so that
 * the center of mass of the system is in the origin.
 * */
void Planetary_System::adjust_to_CM()
{
    static int object, i;

    double total_mass;
    double CM[dimension];

    for( i = 0; i < dimension; i++ ){
        CM[i] = 0;
    }
    total_mass = 0;

    for( object = 0; object < objects; object++ )
    {
        // Loop to calculate center of mass position in
        // current coordinates.
        for( i = 0; i < dimension; i++ )
        {
            CM[i] += celest_bodies[object].position[i]*
                    celest_bodies[object].mass;
        }

        total_mass += celest_bodies[object].mass;
    }

    for( i = 0; i < dimension; i++ ){
        CM[i] = CM[i]/total_mass;
    }


    for( object = 0; object < objects; object++ )
    {
        // Loop to adjust all the positions of the objects
        // so that the center of mass position is in the
        // origin.
        for( i = 0; i < dimension; i++ )
        {
            celest_bodies[object].position[i] -=
                    CM[i];
        }
    }
}

/* Method used to fix the the system, such that the total
 * momentum of the system i zero. It does this by giving
 * a choosen object a velocity which cencel out the
 * total momentum of the system.
 *
 * Input:
 * 			- *fix_object : ID of object to be given the
 *							cenceling momentum.
 * */
void Planetary_System::fix_momentum(char *fix_object)
{
    static int object, i;

    for( object = 0; object < objects; object++ )
    {
        // Loop over all objects to fine the fix_object
        if( string(celest_bodies[object].ID).find(fix_object) !=
                string::npos)
        {
            for( i = 0; i < dimension; i++ )
            {
                // We change the velocity of the object so
                // that the momentum it gets from the
                // change in momentum cancels out the total
                // momentum.
                celest_bodies[object].velocity[i] -=
                        total_momentum[i]/celest_bodies[object].mass;
            }
        }
    }

    for( i = 0; i < dimension; i++ ){
        total_momentum[i] = 0;
    }
    for( object = 0; object < objects; object++ )
    {
        //Loop where total momentum of system is updated
        for( i = 0; i < dimension; i++ )
        {
            total_momentum[i] += celest_bodies[object].velocity[i]*
                    celest_bodies[object].mass;
        }
    }
}
