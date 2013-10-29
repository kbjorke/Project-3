#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "read_file.h"
#include "celestial_body.h"

using namespace std;

void read_file(char* filename, Celestial_Body **celest_bodies, int *objects, int *dimension)
{
    char ID[20], dummy[20], pos[20], vel[20];
    char *p_value, *v_value;
    int dim, objec, planet_nr, i;
    double mass;


    fstream input_file;
    input_file.open(filename, ios::in);

    input_file >> dummy >> dim >> dummy >> objec;
    *objects = objec;
    *dimension = dim;

    double position[*dimension], velocity[*dimension];

    *celest_bodies = new Celestial_Body[objec];

    input_file >> dummy >> dummy >> dummy >> dummy;

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
