#ifndef _NegativeExpntl_h
#define _NegativeExpntl_h 1

/**
*	Negative Exponential Random Numbers
*/

#include "Random.h"

class NegativeExpntl: public Random
{
protected:
	double pMean;
public:
	NegativeExpntl(double xmean, RNG *gen);
	double mean();
	double mean(double x);

	virtual double operator()();
};


inline NegativeExpntl::NegativeExpntl(double xmean, RNG *gen)
	: Random(gen)
{
	pMean = xmean;
}

inline double NegativeExpntl::mean()
{
	return pMean;
}
inline double NegativeExpntl::mean(double x)
{
	double t = pMean;
	pMean = x;
	return t;
}

#endif
