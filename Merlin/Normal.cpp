#include "Random.h"
#include "Normal.h"

//
//	See Simulation, Modelling & Analysis by Law & Kelton, pp259
//
//	This is the ``polar'' method.
//

double Normal::operator()()
{

	if (haveCachedNormal == 1)
	{
		haveCachedNormal = 0;
		return(cachedNormal * pStdDev + pMean );
	}
	else
	{

		for(;;)
		{
			double u1 = pGenerator -> asDouble();
			double u2 = pGenerator -> asDouble();
			double v1 = 2 * u1 - 1;
			double v2 = 2 * u2 - 1;
			double w = (v1 * v1) + (v2 * v2);

			//
			//	We actually generate two IID normal distribution variables.
			//	We cache the one & return the other.
			//
			if (w <= 1)
			{
				double y = sqrt( (-2 * log(w)) / w);
				double x1 = v1 * y;
				double x2 = v2 * y;

				haveCachedNormal = 1;
				cachedNormal = x2;
				return(x1 * pStdDev + pMean);
			}
		}
	}
}

