#include "Random.h"
#include "HypGeom.h"

double HyperGeometric::operator()()
{
	double d = (pGenerator -> asDouble() > pP) ? (1.0 - pP) :  (pP);
	return(-pMean * log(pGenerator -> asDouble()) / (2.0 * d) );
}

