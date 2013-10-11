#include <armadillo>


using namespace std;
using namespace arma;

int RK4 ( int i, double h, double t, mat *u, mat *du,
          vec (*func)(double t, mat *u, mat *du) )
{
        static vec k1, k2, k3, k4;

        /*
        k1 = h*func(t, &u[i], &du[i]);
        k2 = h*func(t + h/2, u[i] + k1/2, du[i] + k1/2);
        k3 = h*func(t + h/2, u[i] + k2/2, du[i] + k2/2);
        k4 = h*func(t + h, u[i] + k3, du[i] + k3);

        du[i+1] = du[i] + (k1 + k2 + k3 + k4)/6;
        u[i+1] = 2;
        */

        return 0;
}
