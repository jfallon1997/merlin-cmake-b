/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 *
 * Class library version 2.0 (1999)
 *
 * file Merlin\AcceleratorModel\StdComponent\Solenoid.cpp
 * last modified 10/12/01 16:41:41
 */

#include "ComponentTracker.h"
#include "Solenoid.h"

// Class Solenoid
const int Solenoid::ID = UniqueIndex();

Solenoid::Solenoid (const std::string& id, double len, double Bz)
    : SimpleSolenoid(id,new RectangularGeometry(len),new BzField(Bz))
{
}


void Solenoid::RotateY180 ()
{
    BzField& field = GetField();
    field.SetStrength(-field.GetStrength());
}

const string& Solenoid::GetType () const
{
    _TYPESTR(Solenoid);
}

ModelElement* Solenoid::Copy () const
{
    return new Solenoid(*this);
}

int Solenoid::GetIndex () const
{
    return Solenoid::ID;
}

void Solenoid::PrepareTracker (ComponentTracker& aTracker)
{
    _PREPTRACK(aTracker,AcceleratorComponent);
}

