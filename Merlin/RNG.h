#ifndef _RNG_h
#define _RNG_h 1

#include <cassert>
#include <cmath>
//#include <_G_config.h>

// 32 bit integer types
typedef unsigned int _G_uint32_t;
typedef int _G_int32_t;

union PrivateRNGSingleType  		   	/// used to access floats as unsigned
{
	float s;
	unsigned int u;
};

union PrivateRNGDoubleType  		   	/// used to access doubles as unsigned
{
	double d;
	unsigned int u[2];
};

/**
* Base class for Random Number Generators. See ACG and MLCG for instances.
* @see ACG
* @see MLCG
*/
class RNG
{
	static PrivateRNGSingleType singleMantissa;	/// mantissa bit vector
	static PrivateRNGDoubleType doubleMantissa;	/// mantissa bit vector
public:
	RNG();
	virtual ~RNG() {};

    /**
	* Return a long-words word of random bits
	* @return A long-words  word of random bits
	*/
	virtual _G_uint32_t asLong() = 0;
	virtual void reset() = 0;

    /**
	* Return random bits converted to either a float or a double
	* @return Random bits converted to either a float or a double
	*/
	float asFloat();
	double asDouble();
};

#endif
