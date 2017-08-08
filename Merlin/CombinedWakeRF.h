// DK 3.12.08

#ifndef _H_CombinedWakeRF
#define _H_CombinedWakeRF

#include "WakePotentials.h"
#include "Complex.h"
#include "Transform2D.h"
#include "PhysicalConstants.h"

using namespace PhysicalConstants;
using namespace std;

// Wxy            - Sum (up+downstream) of coupler wakefield
// CouplerRFKick  - Sum        "        of coupler RF kicks

/**
* Interface class for e.g. coupler wakefields
* i.e wakefields and RF kicks that depends on x,y
* where wakefields depend on bunch charge
* and RF kicks do not
*
* @see "../MerlinExamples/Wakefields" example 3
* @see "../Merlin/CouplerWakeFieldProcess.cpp"
*/
class CombinedWakeRF : public WakePotentials
{
public:

	CombinedWakeRF() {};

    /**
	* Coupler wake fields -- we need x,y since this is not just a transverse
	* (dipole) wake field sum of upstream + downstream coupler
	*/
	virtual Vector2D Wxy(double x, double y) const = 0; // kV/nC

    /**
	* Coupler RF kicks scaled kick equals
	* \f[
	*    \Re\left( V_t/V_z \times e^{i\phi} \right)
	* \f]
	* for particle at 
	* \f[
	*    V_z=V_{cavity}, \quad \phi=\phi_0 + 2\pi f\times (t-t_0)
	* \f]
	* a larger \f$\phi\f$ means later than \f$t_0\f$ -- opposite sign to Merlin 
	* TWRFStructure::GetPhase
	*/
	virtual Vector2D CouplerRFKick(double x, double y,double phi)  const = 0;
};

#endif
