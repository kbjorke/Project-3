#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "unittest++/UnitTest++.h"
#include "celestial_body.h"
#include "read_file.h"
#include "planetary_system.h"

using namespace std;

int main(int argc, char* argv[])
{
    int objects, dimension, i;
    double end_time, time_step;
    char *input_file, output_file[40], buffer[40];

    input_file = argv[argc-1];

    for( i = 0; i < argc-1; i++ ){
        if((string(argv[i]).find("-")) == 0 &&
                (string(argv[i]).find("time")!=string::npos)){
            end_time = atof(argv[i+1]);
        }
        if((string(argv[i]).find("-") == 0) &&
                (string(argv[i]).find("h")!=string::npos)){
            time_step = atof(argv[i+1]);
        }
    }

    strcpy(buffer, input_file);
    strcat(output_file, "output_");
    strcat(output_file, strtok(buffer, "."));
    strcat(output_file, ".txt");

    Celestial_Body *celest_bodies;

    read_file(input_file, &celest_bodies, &objects, &dimension);

    Planetary_System planetary_system(celest_bodies, objects, dimension);

    planetary_system.evolve(output_file, end_time, time_step);
}

