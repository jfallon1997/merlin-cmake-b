#include "Random.h"
#include "Erlang.h"

double Erlang::operator()()
{
	double prod = 1.0;

	for (int i = 0; i < k; i++)
	{
		prod *= pGenerator -> asDouble();
	}
	return(-log(prod)/a);
}
