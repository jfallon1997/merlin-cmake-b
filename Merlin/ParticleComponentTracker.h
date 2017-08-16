/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 *
 * Class library version 2.0 (1999)
 *
 * file Merlin\BeamDynamics\ParticleTracking\ParticleBunchTracker.h
 * last modified 09/11/01 04:10:33 PM
 */

#ifndef ParticleBunchTracker_h
#define ParticleBunchTracker_h 1

#include "merlin_config.h"
#include "ParticleBunch.h"
#include "ComponentTracker.h"

namespace ParticleTracking
{
typedef TBunchCMPTracker<ParticleBunch> ParticleComponentTracker;
}


#endif
