#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "read_file.h"
#include "celestial_body.h"

using namespace std;

/* Function that reads a file containing the ID, mass and initial
 * conditions for a set of celestial objects. Generates a
 * Celestial_Body instance for each of the objects, which
 * it stores in a Celestial_Body array.
 *
 * Input:
 * 			- *filename: filename of the file cotaining the data
 *
 * 			- **celest_bodies: a pointer to an uninitialized
 *							   array of Celestial_Body instances.
 *
 *			- *object: pointer to value containing number of objects
 *					   in the input file.
 *
 * 			- *dimension: pinter to the value containing the
 * 						  dimensionality of the problem.
 *
 * */

void read_file(char* filename, Celestial_Body **celest_bodies,
               int *objects, int *dimension)
{
    char ID[40], dummy[40], pos[40], vel[40];
    char *p_value, *v_value;
    int dim, objec, planet_nr, i;
    double mass;

    fstream input_file;
    input_file.open(filename, ios::in);

    // Reads out first line of the input file, which contains
    // number of objects and dimensionality:
    input_file >> dummy >> dim >> dummy >> objec;
    *objects = objec;
    *dimension = dim;


    double position[*dimension], velocity[*dimension];

    // Initialize the array of Celestial_body wich the pointer
    // *celest_bodies is pointing at.
    *celest_bodies = new Celestial_Body[objec];

    // Reads out second line of input file, contains nothing of
    // importans.
    input_file >> dummy >> dummy >> dummy >> dummy;

    // Loop which reads the rest of the lines, which contains
    // ID, mass and initial position and velocity for each
    // object. Then creates a instance of Celestial_Body in the
    // *celest_bodies array.
    planet_nr = 0;
    while( true )
    {
        input_file >> ID >> mass >> pos >> vel;

        if( input_file.eof() ) break;


        p_value = strtok( pos, "(,)" );
        position[0] = atof(p_value);

        for ( i = 1; i < *dimension; i++ )
        {
            p_value = strtok( NULL, "(,)" );
            position[i] = atof(p_value);
        }
        v_value = strtok( vel, "(,)" );
        velocity[0] = atof(v_value);
        for ( i = 1; i < *dimension; i++ )
        {
            v_value = strtok( NULL, "(,)" );
            velocity[i] = atof(v_value);
        }

        celest_bodies[0][planet_nr] = Celestial_Body(ID, mass, *dimension,
                                                     position, velocity);
        planet_nr++;
    }

    input_file.close();

}
