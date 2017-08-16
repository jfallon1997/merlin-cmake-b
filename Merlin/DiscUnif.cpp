#include "Random.h"
#include "DiscUnif.h"

double DiscreteUniform::operator()()
{
	long tmp = long(floor(delta * pGenerator -> asDouble()));
	return( double(pLow + tmp) );
}

