#ifndef READ_FILE_H
#define READ_FILE_H

#include "celestial_body.h"

void read_file(char* filename, Celestial_Body **celest_bodies,
               int *objects, int *dimension);

#endif // READ_FILE_H
