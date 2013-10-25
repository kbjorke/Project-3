#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "unittest++/UnitTest++.h"
#include "celestial_body.h"
#include "read_file.h"

using namespace std;

int main(int argc, char* argv[])
{
    Celestial_Body *celest_bodies;

    read_file(argv[1], &celest_bodies);

    cout << celest_bodies[1].ID << endl;

    /*
    char ID[20], dummy[20], pos[20], vel[20];
    char *p_value, *v_value;
    int dimension, objects , planet_nr, i;
    double mass;

    fstream input_file;
    input_file.open(argv[1], ios::in);

    input_file >> dummy >> dimension >> dummy >> objects;

    double position[dimension], velocity[dimension];

    Celestial_Body *celest_bodies = new Celestial_Body[objects];

    input_file >> dummy >> dummy >> dummy >> dummy;

    planet_nr = 0;
    while( true )
    {
        input_file >> ID >> mass >> pos >> vel;

        if( input_file.eof() ) break;

        p_value = strtok( pos, "(,)" );
        position[0] = atof(p_value);

        for ( i = 1; i < dimension; i++ )
        {
            p_value = strtok( NULL, "(,)" );
            position[i] = atof(p_value);
        }
        v_value = strtok( vel, "(,)" );
        velocity[0] = atof(v_value);
        for ( i = 1; i < dimension; i++ )
        {
            v_value = strtok( NULL, "(,)" );
            velocity[i] = atof(v_value);
        }

        celest_bodies[planet_nr] = Celestial_Body(ID, mass, dimension,
                                                  position, velocity);
        planet_nr++;
    }

    input_file.close();

    return 0;
    */
}

