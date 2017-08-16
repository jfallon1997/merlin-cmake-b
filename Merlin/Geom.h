#ifndef _Geometric_h
#define _Geometric_h

#include "Random.h"

class Geometric: public Random
{
protected:
	double pMean;
public:
	Geometric(double mean, RNG *gen);

	double mean();
	double mean(double x);

	virtual double operator()();

};


inline Geometric::Geometric(double mean, RNG *gen) : Random(gen)
{
	pMean = mean;
}


inline double Geometric::mean()
{
	return pMean;
}
inline double Geometric::mean(double x)
{
	double tmp = pMean;
	pMean = x;
	return tmp;
}


#endif
