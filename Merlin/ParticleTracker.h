/*
* Merlin C++ Class Library for Charged Particle Accelerator Simulations
*
* Class library version 2.0 (1999)
*
* file Merlin\BeamDynamics\ParticleTracking\ParticleTracker.h
* last modified 09/06/01 02:15:18 PM
*/


#ifndef ParticleTracker_h
#define ParticleTracker_h 1

#include "merlin_config.h"

// TrackingSimulation
#include "TTrackSim.h"
// ParticleBunch
#include "ParticleComponentTracker.h"

/**
*	A Particle Tracking simulation. ParticleTracker is a
*	TrackingSimulation whose primary Transport process is
*	particle tracking.
*/
namespace ParticleTracking
{
typedef TTrackSim<ParticleComponentTracker> ParticleTracker;
}

#endif
