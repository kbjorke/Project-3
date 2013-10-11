#include <armadillo>


using namespace std;
using namespace arma;

int RK4 ( double h, double t, mat *u,
          mat (*func)(double t, mat *u) )
{
        static mat *k1, *k2, *k3, *k4;
        static mat temp1, temp2, temp3;

        *k1 = h*func(t, u);
        temp1 = (*u + *k1/2);
        *k2 = h*func(t + h/2, &temp1);
        temp2 = (*u + *k2/2);
        *k3 = h*func(t + h/2, &temp2);
        temp3 = (*u + *k3);
        *k4 = h*func(t + h, &temp3);

        return 0;
}
