#ifndef _Poisson_h
#define _Poisson_h

#include "Random.h"

class Poisson: public Random
{
protected:
	double pMean;
public:
	Poisson(double mean, RNG *gen);

	double mean();
	double mean(double x);

	virtual double operator()();
};


inline Poisson::Poisson(double mean, RNG *gen)
	: Random(gen)
{
	pMean = mean;
}

inline double Poisson::mean()
{
	return pMean;
}
inline double Poisson::mean(double x)
{
	double t = pMean;
	pMean = x;
	return t;
}

#endif
