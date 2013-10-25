#include <armadillo>


using namespace std;
using namespace arma;

void RK4 ( double h, double t, mat *u,
         mat (*func)(double t, mat u) )
{
        static mat *k1, *k2, *k3, *k4;

        *k1 = h*func(t, *u);
        *k2 = h*func(t + h/2, (*u + *k1/2));
        *k3 = h*func(t + h/2, (*u + *k2/2));
        *k4 = h*func(t + h, (*u + *k3));

        *u = *u + (1./6)*(*k1 + *k2*2 + *k3*2 + *k4);
}
