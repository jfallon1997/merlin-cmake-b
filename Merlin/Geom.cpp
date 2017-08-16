#include "Random.h"
#include "Geom.h"

double Geometric::operator()()
{
    int samples;
    for (samples = 1; pGenerator -> asDouble() < pMean; samples++);
    return((double) samples);
}

