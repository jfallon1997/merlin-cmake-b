#ifndef _Binomial_h
#define _Binomial_h 1

#include "Random.h"

class Binomial: public Random
{
protected:
	int pN;
	double pU;
public:
	Binomial(int n, double u, RNG *gen);

	int n();
	int n(int xn);

	double u();
	double u(double xu);

	virtual double operator()();

};


inline Binomial::Binomial(int n, double u, RNG *gen)
	: Random(gen)
{
	pN = n;
	pU = u;
}

inline int Binomial::n()
{
	return pN;
}
inline int Binomial::n(int xn)
{
	int tmp = pN;
	pN = xn;
	return tmp;
}

inline double Binomial::u()
{
	return pU;
}
inline double Binomial::u(double xu)
{
	double tmp = pU;
	pU = xu;
	return tmp;
}

#endif
