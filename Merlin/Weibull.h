#ifndef _Weibull_h
#define _Weibull_h

#include "Random.h"

class Weibull: public Random
{
protected:
	double pAlpha;
	double pInvAlpha;
	double pBeta;

	void setState();

public:
	Weibull(double alpha, double beta, RNG *gen);

	double alpha();
	double alpha(double x);

	double beta();
	double beta(double x);

	virtual double operator()();
};


inline void Weibull::setState()
{
	pInvAlpha = 1.0 / pAlpha;
}

inline Weibull::Weibull(double alpha, double beta,  RNG *gen) : Random(gen)
{
	pAlpha = alpha;
	pBeta = beta;
	setState();
}

inline double Weibull::alpha()
{
	return pAlpha;
}

inline double Weibull::alpha(double x)
{
	double tmp = pAlpha;
	pAlpha = x;
	setState();
	return tmp;
}

inline double Weibull::beta()
{
	return pBeta;
}
inline double Weibull::beta(double x)
{
	double tmp = pBeta;
	pBeta = x;
	return tmp;
}

#endif
