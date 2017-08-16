#ifndef _Random_h
#define _Random_h 1

#include <cmath>
#include "RNG.h"

class Random
{
protected:
	RNG *pGenerator;

public:
	virtual ~Random() {};
	Random(RNG *generator);
	virtual double operator()() = 0;

	RNG *generator();
	void generator(RNG *p);

private:
	//Copy protection
	Random(const Random& rhs);
	Random& operator=(const Random& rhs);
};


inline Random::Random(RNG *gen)
{
	pGenerator = gen;
}

inline RNG *Random::generator()
{
	return(pGenerator);
}

inline void Random::generator(RNG *p)
{
	pGenerator = p;
}

#endif
