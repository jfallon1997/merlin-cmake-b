/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 *
 * Class library version 2.0 (1999)
 *
 * file Merlin\AcceleratorModel\StdComponent\Solenoid.h
 * last modified 10/12/01 16:41:41
 */

#ifndef Solenoid_h
#define Solenoid_h 1

#include "merlin_config.h"

#include "SimpleSolenoid.h"

/**
*	A simple solenoid with field Bz.
*/
class Solenoid : public SimpleSolenoid
{
public:
	Solenoid (const std::string& id, double len, double Bz);

    /**
	*	Returns the value of the field in Tesla.
	*   @return Value of the field (T)
	*/
	double GetBz () const;

    /**
	*	Sets the value of the field in Tesla.
	*/
	void SetBz (double B);

    /**
	*	Rotates the component 180 degrees about its local Y axis.
	*/
	virtual void RotateY180 ();

    /**
	*	Return the type string for the element.
	*	@return Type string for the element
	*/
	virtual const string& GetType () const;

    /**
	*	Virtual constructor.
	*/
	virtual ModelElement* Copy () const;

    /**
	*	Returns the unique index for this class of accelerator
	*	components.
	*	@return Accelerator component class' unique index
	*/
	virtual int GetIndex () const;

    /**
	*	Primary tracking interface. Prepares the specified
	*	Tracker object for tracking this component.
	*/
	virtual void PrepareTracker (ComponentTracker& aTracker);

    /**
	* The following field access function added for
	* compatibility with other magnets
	*/
	void SetFieldStrength(double b)
	{
		SetBz(b);
	}
	double GetFieldStrength() const
	{
		return GetBz();
	}

    /**
	* Data Members for Class Attributes
	*/

	static const int ID;

protected:
private:
private:
};

/**
* Class Solenoid
*/
inline double Solenoid::GetBz () const
{
	return GetField().GetStrength();
}

inline void Solenoid::SetBz (double B)
{
	GetField().SetStrength(B);
}



#endif
