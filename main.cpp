#include <iostream>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unittest++/UnitTest++.h>

using namespace std;

int main(int argc, char* argv[])
{
    char ID, dummy[20], pos[20], vel[20];
    int dimension;
    double mass;


    fstream input_file;
    input_file.open(argv[1], ios::in);

    input_file >> dummy >> dimension;

    double position[dimension], velocity[dimension];

    input_file >> dummy >> dummy >> dummy >> dummy;

    while( !input_file.eof())
    {
        input_file >> ID >> mass >> pos >> vel;

        cout << ID << mass << pos << vel << endl;
    }
    input_file.close();

    return 0;
}

