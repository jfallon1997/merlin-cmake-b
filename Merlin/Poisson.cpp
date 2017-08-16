#include "Random.h"
#include "Poisson.h"

double Poisson::operator()()
{
    double bound = exp(-1.0 * pMean);
    int count = 0;

    for (double product = 1.0;
            product >= bound;
            product *= pGenerator -> asDouble())
    {
        count++;
    }
    return(count - 1);
}
