#include "Random.h"
#include "Uniform.h"

double Uniform::operator()()
{
    return( pLow + delta * pGenerator -> asDouble() );
}
