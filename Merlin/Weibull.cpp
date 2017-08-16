#include "Random.h"
#include "Weibull.h"

/**
*	See Simulation, Modelling & Analysis by Law & Kelton, pp259
*
*	This is the ``polar'' method.
*//

double Weibull::operator()()
{
	return( pow(pBeta * ( - log(1 - pGenerator -> asDouble()) ), pInvAlpha) );
}
