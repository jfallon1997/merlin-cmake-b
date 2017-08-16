#ifndef _Normal_h
#define _Normal_h

#include "Random.h"

/**
*
*  See Simulation, Modelling & Analysis by Law & Kelton, pp259
* 
*  This is the ``polar'' method.
*
*/

class Normal: public Random
{
	char haveCachedNormal;
	double cachedNormal;

protected:
	double pMean;
	double pVariance;
	double pStdDev;

public:
	Normal(double xmean, double xvariance, RNG *gen);
	double mean();
	double mean(double x);
	double variance();
	double variance(double x);
	virtual double operator()();
};


inline Normal::Normal(double xmean, double xvariance, RNG *gen)
	: Random(gen)
{
	pMean = xmean;
	pVariance = xvariance;
	pStdDev = sqrt(pVariance);
	haveCachedNormal = 0;
}

inline double Normal::mean()
{
	return pMean;
}
inline double Normal::mean(double x)
{
	double t=pMean;
	pMean = x;
	return t;
}

inline double Normal::variance()
{
	return pVariance;
}
inline double Normal::variance(double x)
{
	double t=pVariance;
	pVariance = x;
	pStdDev = sqrt(pVariance);
	return t;
}

#endif
