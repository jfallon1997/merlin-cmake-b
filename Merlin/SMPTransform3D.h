/*
* Merlin C++ Class Library for Charged Particle Accelerator Simulations
*
* Class library version 2.0 (2000)
*
* file Merlin\BasicTransport\PSvectorTransform3D.h
* last modified 04/04/01 14:41:34
*
*/

#ifndef SMPTransform3D_h
#define SMPTransform3D_h 1

#include "merlin_config.h"
#include "Transform3D.h"
#include "SliceMacroParticle.h"
#include "RMap.h"

namespace SMPTracking
{

class SMPTransform3D
{
public:

	SMPTransform3D(const Transform3D& tfrm);

    /**
	* Apply (approximate) transformation
	*/
	SliceMacroParticle& Apply (SliceMacroParticle& p) const;
	SliceMacroParticle& operator () (SliceMacroParticle& p) const
	{
		return Apply(p);
	}

private:

	R2Map R;
	double delta_x,delta_y,theta_x,theta_y;
	bool bNoRot;
	bool nullRotation;
};

} // end namespace SMPTracking

#endif // SMPTransform3D_h
