#include "Random.h"
#include "Normal.h"

#include "LogNorm.h"

//
//	See Simulation, Modelling & Analysis by Law & Kelton, pp260
//
//

double LogNormal::operator()()
{
	return exp (this->Normal::operator()() );
}


