#ifndef _Erlang_h
#define _Erlang_h 1

#include "Random.h"

class Erlang: public Random
{
protected:
	double pMean;
	double pVariance;
	int k;
	double a;
	void setState();
public:
	Erlang(double mean, double variance, RNG *gen);
	virtual ~Erlang();
	double mean();
	double mean(double x);
	double variance();
	double variance(double x);

	virtual double operator()();

};


inline void Erlang::setState()
{
	k = int( (pMean * pMean ) / pVariance + 0.5 );
	k = (k > 0) ? k : 1;
	a = k / pMean;
}

inline Erlang::Erlang(double mean, double variance, RNG *gen) : Random(gen)
{
	pMean = mean;
	pVariance = variance;
	setState();
}

inline double Erlang::mean()
{
	return pMean;
}
inline double Erlang::mean(double x)
{
	double tmp = pMean;
	pMean = x;
	setState();
	return tmp;
}

inline double Erlang::variance()
{
	return pVariance;
}
inline double Erlang::variance(double x)
{
	double tmp = pVariance;
	pVariance = x;
	setState();
	return tmp;
}

#endif
