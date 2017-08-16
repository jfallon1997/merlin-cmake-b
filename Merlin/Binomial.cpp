#include "Random.h"
#include "Binomial.h"

double Binomial::operator()()
{
	int s = 0;
	for (int i = 0; i < pN; i++)
	{
		if (pGenerator -> asDouble() < pU)
		{
			s++;
		}
	}
	return(double(s));
}

