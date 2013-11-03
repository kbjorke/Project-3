/* Program for Project 3, FYS3150.
 *
 * Solves a celestial problem using Runge-Kutta 4th order.
 *
 * Made by: Kristian Bjørke
 * */
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>

// Import of header files for the project.
#include "celestial_body.h"
#include "read_file.h"
#include "planetary_system.h"

using namespace std;

int main(int argc, char* argv[])
{
    /* Main program.
     * Serves as the overlaying interface for the program, processes
     * the commandline input and runs the right functions.
     *
     * Takes input from command line:
     *
     * input-file : A text file containing the objects of the problem
     * 				and their initial positions and velocities for a
     * 				chosen dimensionality. Is to be given as the last
     *				command line argument.
     *
     *
     * Parameters:
     * 			-time   :Set the end time of the simulation.
     *
     *          -h 		:Sets the time step of the simulation
     *
     * Options:
     *			-fix	 <object>    :Fixes the system so that the total
     *							  momentum of the system is zero.
     *							  This is done by giving <object> a
     *							  velocity which cancel out the total
     *							  momentum.
     *
     *      		-statio <object> :Sets the object <object> as stationary.
     *							  Meaning that it is not affected by
     *							  the gravitation from the other objects.
     *
     *			-CM				 :Changes the coordinates so that the
     *							  center of mass of the system is in the
     *							  origin.
     *
     * Output:	output_<input-filename>.txt
     *
     *
     * Use: $~ ./Project3 -time <end_time> -h <time_step> [options] input-file.txt
     * */

    int objects, dimension, i;
    double end_time, time_step;
    char *input_file, *fix_object, *stationary_object;
    char output_file[40], buffer[40];

    // Boolean values to check for the use of options:
    bool fix_momentum = false;
    bool adjust_to_CM = false;
    bool set_stationary = false;

    // Read filename of input file from last commandline argument:
    input_file = argv[argc-1];

    // Loop over commandline arguments to find parameters and options:
    for( i = 0; i < argc-1; i++ ){
        if((string(argv[i]).find("-")) == 0 &&
                (string(argv[i]).find("time")!=string::npos)){
            end_time = atof(argv[i+1]);
        }
        if((string(argv[i]).find("-") == 0) &&
                (string(argv[i]).find("h")!=string::npos)){
            time_step = atof(argv[i+1]);
        }
        if( string(argv[i]).find("-statio") == 0 ){
            stationary_object = argv[i+1];
            set_stationary = true;
        }
        if((string(argv[i]).find("-") == 0) &&
                (string(argv[i]).find("fix")!=string::npos)){
            fix_object = argv[i+1];
            fix_momentum = true;
        }
        if( string(argv[i]).find("-CM") == 0 ){
            adjust_to_CM = true;
        }
    }


    // Generating the name of the output file based on the
    // input file:
    output_file[0] = '\0';
    strcpy(buffer, input_file);
    strcat(output_file, "output_");
    strcat(output_file, strtok(buffer, "."));
    strcat(output_file, ".txt");


    Celestial_Body *celest_bodies;

    read_file(input_file, &celest_bodies, &objects, &dimension);

    Planetary_System planetary_system(celest_bodies, objects, dimension);


    // Runs eventual options as methods of planetary_system:
    if( set_stationary ){
        planetary_system.set_stationary(stationary_object);
    }
    if( adjust_to_CM ){
        planetary_system.adjust_to_CM();
    }
    if( fix_momentum && set_stationary == false){
        planetary_system.fix_momentum(fix_object);
    }

    // Run simulation:
    planetary_system.evolve(output_file, end_time, time_step);
}
