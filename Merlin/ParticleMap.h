/*
* Merlin C++ Class Library for Charged Particle Accelerator Simulations
*
* Class library version 2.0 (1999)
*
* file Merlin\BeamDynamics\ParticleTracking\ParticleMap.h
* last modified 08/10/01 02:14:16 PM
*/

#ifndef ParticleMap_h
#define ParticleMap_h 1

#include "merlin_config.h"


namespace ParticleTracking
{

class ParticleBunch;

/**
*	An arbitrary map that can be applied to a ParticleBunch.
*/
class ParticleMap
{
public:

	virtual ~ParticleMap ();

    /**
	*	Applies the map to the specified ParticleBunch.
	*/
	virtual ParticleBunch& Apply (ParticleBunch& bunch) const = 0;


	virtual void Invert () = 0;

protected:
private:
private:
};

/**
* Class ParticleMap
*/
inline ParticleMap::~ParticleMap ()
{


}

} //end namespace ParticleTracking



#endif
