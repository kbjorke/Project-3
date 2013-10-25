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
    int objects;

    Celestial_Body *celest_bodies;

    read_file(argv[1], &celest_bodies, &objects);

    Planetary_System planetary_system(celest_bodies, objects);

    planetary_system.evolve(10,3);
}

