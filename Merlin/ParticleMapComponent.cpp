/*
* Merlin C++ Class Library for Charged Particle Accelerator Simulations
*
* Class library version 2.0 (1999)
*
* file Merlin\BeamDynamics\ParticleTracking\ParticleMapComponent.cpp
* last modified 26/09/02 15:18:14
*/

#include "ParticleBunch.h"
#include "ComponentTracker.h"
#include "ParticleMapComponent.h"

#include <cassert>

namespace ParticleTracking
{

// Class ParticleMapComponent

const int ParticleMapComponent::ID = UniqueIndex();

ParticleMapComponent::ParticleMapComponent (const std::string& id, ParticleMap* pmap, double intB2ds)
	: AcceleratorComponent(id),itsMap(pmap),ib2(intB2ds)
{
	assert(pmap);
}

const string& ParticleMapComponent::GetType () const
{
	_TYPESTR(ParticleMap);
}

ModelElement* ParticleMapComponent::Copy () const
{
	return new ParticleMapComponent(*this);
}

int ParticleMapComponent::GetIndex () const
{
	return ID;
}

void ParticleMapComponent::RotateY180 ()
{
	itsMap->Invert();
}

void ParticleMapComponent::PrepareTracker (ComponentTracker& aTracker)
{
	_PREPTRACK(aTracker,AcceleratorComponent)
}
} //end namespace ParticleTracking
