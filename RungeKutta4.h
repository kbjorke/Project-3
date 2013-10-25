#ifndef RUNGEKUTTA4_H
#define RUNGEKUTTA4_H

#include <armadillo>

using namespace arma;

void RK4 ( double h, double t, mat *u,
          mat (*func)(double t, mat u) );

#endif // RUNGEKUTTA4_H
