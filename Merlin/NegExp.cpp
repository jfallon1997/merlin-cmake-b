#include "Random.h"
#include "NegExp.h"

double NegativeExpntl::operator()()
{
    return(-pMean * log(pGenerator -> asDouble()));
}

