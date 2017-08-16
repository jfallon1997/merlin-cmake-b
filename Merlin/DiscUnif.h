#ifndef _DiscreteUniform_h
#define _DiscreteUniform_h 1

#include "Random.h"

//
//	The interval [lo..hi)
//

class DiscreteUniform: public Random
{
	long pLow;
	long pHigh;
	double delta;
public:
	DiscreteUniform(long low, long high, RNG *gen);

	long low();
	long low(long x);
	long high();
	long high(long x);

	virtual double operator()();
};


inline DiscreteUniform::DiscreteUniform(long low, long high, RNG *gen)
	: Random(gen)
{
	pLow = (low < high) ? low : high;
	pHigh = (low < high) ? high : low;
	delta = (pHigh - pLow) + 1;
}

inline long DiscreteUniform::low()
{
	return pLow;
}

inline long DiscreteUniform::low(long x)
{
	long tmp = pLow;
	pLow = x;
	delta = (pHigh - pLow) + 1;
	return tmp;
}

inline long DiscreteUniform::high()
{
	return pHigh;
}

inline long DiscreteUniform::high(long x)
{
	long tmp = pHigh;
	pHigh = x;
	delta = (pHigh - pLow) + 1;
	return tmp;
}

#endif
