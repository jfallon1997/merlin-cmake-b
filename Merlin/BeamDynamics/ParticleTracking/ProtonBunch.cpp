//#include <TH1.h>
#include <cmath>
#include <fstream>
#include "ProtonBunch.h"
#include "Collimators/CoulombScatter.h"
#include "NumericalUtils/PhysicalUnits.h"
#include "NumericalUtils/PhysicalConstants.h"
#include "Exception/MerlinException.h"
#include "AcceleratorModel/Aperture.h"
#include "AcceleratorModel/Apertures/CollimatorAperture.hpp"
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>

using namespace std;
using namespace ParticleTracking;
using namespace PhysicalConstants;
using namespace PhysicalUnits;


//extern TH1D* histt1;
//extern TH1D* histt2;

double ProtonBunch::GetParticleMass() const
{
	return ProtonMass;
}
double ProtonBunch::GetParticleMassMeV() const
{
	return ProtonMassMeV;
}

double ProtonBunch::GetParticleLifetime() const
{
	return 0;
}

bool ProtonBunch::IsStable() const
{
	//We assume protons do not decay :]
	return true;
}

void ProtonBunch::ConfigureScatter_pp_table(const char* filename)
{
        t_sigma_table.clear();// get rid of any old values
        double last_temp1;
        ifstream f;
        f.open(filename);
        if(!f)
        {
                cout << "ProtonBunch::ConfigureScatter_pp_table(): Cannot open file " << filename << endl;
                exit(1);
        }

        while(!f.eof())
        {

                double temp1, temp2;

                if(f >> temp1 >> temp2)
                {
                        //cout << "sam 2  " <<temp1<< " " <<temp2 << endl;
                        t_sigma_table.push_back(temp2);
                        if (t_sigma_table.size() == 2)
                        {
                                t_sigma_table_step = temp1 -last_temp1;
                        }
                        else if (t_sigma_table.size() > 2)
                        {
                                if (fabs(t_sigma_table_step - (temp1 -last_temp1)) > 1e-12 )
                                {
                                        cerr << "WARNING: step size changed ("
                                        << (temp1 -last_temp1) <<" -> "<<t_sigma_table_step
                                        << "), diff="<< t_sigma_table_step - (temp1 -last_temp1)
                                        <<" in ProtonBunch::ConfigureScatter_pp_table(), interpolation will be wrong\n";
                                }
                        }
                        last_temp1 =  temp1;
                }
                else
                {
                        // if can't read 2 doubles, skip line (assume its a header)
                        f.clear();
                        f.ignore(numeric_limits<streamsize>::max(), '\n');
                }
        }
        f.close();
        cout << "Read " << t_sigma_table.size() << " values from " << filename << ". step size = " << t_sigma_table_step << endl;

}


// based on parabolic() from collimatortable.h
double parabolic(const double v1, const double v2, const double v3, const double d)
{
     return v2+d*(v3-v1)/2+d*d*(v3+v1-2*v2)/2;
    // for getting the gradient do the differentiate of above expression:
    // return (v3+v1-2*v2) * d + (v3-v1)/2;

}

// based on interpolate() from collimatortable.h
double ProtonBunch::get_ft(const double t)
{
        if (t_sigma_table.size() == 0)
        {
                cerr << "WARNING: no data in t_sigma_table, call ProtonBunch::ConfigureScatter_pp_table() first\n";
                exit(1);
        }

	if(t < 0)
	{
		cerr << "WARNING: outside range of t_sigma_table" << endl;
		cerr << "t="<< t << " index=" << index << " t_sigma_table.size()" << t_sigma_table.size()
		<< " t_sigma_table_step=" << t_sigma_table_step << endl;
	}

        size_t index = size_t(0.5+t/t_sigma_table_step);

        if (index > t_sigma_table.size())
        {
                cerr << "WARNING: outside range of t_sigma_table \n";
                cerr << "t="<< t << " index=" << index << " t_sigma_table.size()" << t_sigma_table.size()
                        << " t_sigma_table_step=" << t_sigma_table_step << endl;
        }

        if(index<0) index=0;
        int i1;

        if(index==0)
        {
                i1 = 1;
        }
        else if(index == (t_sigma_table.size()-1))
        {
                i1 = t_sigma_table.size()-2;
        }
        else
        {
                i1 = index;
        }

        return (index >= t_sigma_table.size()) ? 0 : parabolic(t_sigma_table[i1-1], t_sigma_table[i1], t_sigma_table[i1+1], t/t_sigma_table_step-i1);
}


void ProtonBunch::ConfigureScatter_xi_table(const char* filename)
{
        xi_sigma_table.clear();// get rid of any old values
        double last_temp1;
        ifstream f;
        f.open(filename);
        if(!f)
        {
                cout << "ProtonBunch::ConfigureScatter_xi_table(): Cannot open file " << filename << endl;
                exit(1);
        }

        while(!f.eof())
        {

                double temp1, temp2;

                if(f >> temp1 >> temp2)
                {
                        //cout << "sam 2  " <<temp1<< " " <<temp2 << endl;
                        xi_sigma_table.push_back(temp2);
                        if (xi_sigma_table.size() == 2)
                        {
                                xi_sigma_table_step = temp1 -last_temp1;
                        }
                        else if (xi_sigma_table.size() > 2)
                        {
                                if (fabs(xi_sigma_table_step - (temp1 -last_temp1)) > 1e-5 )
                                {
                                        cerr << "WARNING: step size changed ("
                                        << (temp1 -last_temp1) <<" -> "<<xi_sigma_table_step
                                        << "), diff="<< xi_sigma_table_step - (temp1 -last_temp1)
                                        <<" in ProtonBunch::ConfigureScatter_xi_table(), interpolation will be wrong\n";
                                }
                        }
                        last_temp1 =  temp1;
                }
                else
                {
                        // if can't read 2 doubles, skip line (assume its a header)
                        f.clear();
                        f.ignore(numeric_limits<streamsize>::max(), '\n');
                }
        }
        f.close();
        //cout << "Read " << xi_sigma_table.size() << " values from " << filename << ". step size = " << xi_sigma_table_step << endl;

}


// based on parabolic() from collimatortable.h
double parabolic2(const double v1, const double v2, const double v3, const double d)
{
    return v2+d*(v3-v1)/2+d*d*(v3+v1-2*v2)/2;
    // for getting the gradient do the differentiate of above expression:
     //return (v3+v1-2*v2) * d + (v3-v1)/2;

}

// based on interpolate() from collimatortable.h
double ProtonBunch::get_fxi(const double xi)
{
        if (xi_sigma_table.size() == 0)
        {
                cerr << "WARNING: no data in xi_sigma_table, call ProtonBunch::ConfigureScatter_xi_table() first\n";
                exit(1);
        }

	if(xi < 0)
	{
		cerr << "WARNING: outside range of xi_sigma_table \n";
		cerr << "xi="<< xi << " index=" << index << " xi_sigma_table.size()" << xi_sigma_table.size()
		<< " xi_sigma_table_step=" << xi_sigma_table_step << endl;
	}

	size_t index = size_t(0.5+xi/xi_sigma_table_step);

        if (index > xi_sigma_table.size())
        {
		cerr << "WARNING: outside range of xi_sigma_table \n";
		cerr << "xi="<< xi << " index=" << index << " xi_sigma_table.size()" << xi_sigma_table.size()
		<< " xi_sigma_table_step=" << xi_sigma_table_step << endl;
        }

	if(index < 0)
	{
        	index=0;
        }
        int i1;

        if(index==0)
        {
                i1 = 1;
        }
        else if(index == xi_sigma_table.size()-1)
        {
                i1 = xi_sigma_table.size()-2;
        }
        else
        {
                i1 = index;
        }

        return (index >= xi_sigma_table.size()) ? 0 : parabolic2(xi_sigma_table[i1-1], xi_sigma_table[i1], xi_sigma_table[i1+1], xi/xi_sigma_table_step-i1);
}


void ProtonBunch::EnableSixtrackPhysics(bool state)
{
	if(state == true)
	{
		ScatteringPhysicsModel = 1;
	}
	else
	{
		ScatteringPhysicsModel = 0;
	}
}

int ProtonBunch::Scatter(PSvector& p, double x, const Aperture* ap)
{
	int returnvalue;
	if(ScatteringPhysicsModel == 1)
	{
		returnvalue = ScatterSixtrack(p,x,ap);
	}
	else	//Do updated Merlin scattering physics
	{
		returnvalue = ScatterMerlin(p,x,ap);
	}
	return returnvalue;
} //End of ScatterProton

void ProtonBunch::ConfigureScatter(const Aperture* ap)
{
	if(ScatteringPhysicsModel == 1)
	{
		ConfigureScatterSixtrack(ap);
	}
	else
	{
		ConfigureScatterMerlin(ap);
	}
	/*
	std::cout << "pp total\t" << sigma_pp_total << std::endl;
	std::cout << "pp elastic\t" << sigma_pp_elastic << std::endl;

	std::cout << "pN total\t" << sigma_pN_total << std::endl;
	std::cout << "pN inelastic\t" << sigma_pN_inelastic << std::endl;
	std::cout << "pN elastic\t" << sigma_pN_elastic << std::endl;
	std::cout << "pR elastic\t" << sigma_Rutherford << std::endl;
	std::cout << "pn SD\t" << sigma_pn_SingleDiffractive << std::endl;
	std::cout << "diff\t" << sigma_pN_total - sigma_pN_elastic - sigma_pN_inelastic << std::endl;
*/
}

void ProtonBunch::ConfigureScatterMerlin(const Aperture* ap)
{

	//Do a cast to check if we have a "CollimatorAperture"
	const CollimatorAperture* tap= dynamic_cast<const CollimatorAperture*> (ap);
	if(!tap)
	{
		throw MerlinException("ScatterProton : No Collimator Aperture");
	}

	double P0 = GetReferenceMomentum();
	E0 = sqrt(P0*P0 + pow(ProtonMassMeV*MeV,2));
	double gamma = E0/(ProtonMassMeV*MeV);
	double beta = 1 - ( 1 / (gamma*gamma));
	double T0 = (gamma-1.0) * ProtonMassMeV*MeV;	//T0: kinetic energy
/*
	cout << "E0: " << E0 << endl;
	cout << "T0: " << T0 << endl;
	cout << "P0: " << P0 << endl;
	cout << "gamma: " << gamma << endl;
	cout << "beta: " << beta << endl;
*/
	const double sigma_pN_total_reference = tap->Material->sigma_pN_total;		//Material reference proton-Nucleus total scattering cross section
	const double sigma_pN_inelastic_reference = tap->Material->sigma_pN_inelastic;	//Material reference proton-Nucleus inelastic scattering cross section
	const double sigma_Rutherford_reference = tap->Material->sigma_Rutherford;		//Material reference Rutherford scattering cross section
	//const double dEdx = tap->Material->dEdx*tap->Material->rho/10;			//dE/dx - (GeV m^-1)
	dEdx = tap->Material->dEdx;					//dE/dx - (GeV m^-1)
	rho = tap->Material->rho;					//density (g /cm^3)
	A = tap->Material->A;						//Atomic mass
	Z = tap->Material->atomic_number;				//Atomic number
	//const double X0 = (tap->Material->X0*centimeter)/tap->Material->rho;
	X0 = tap->Material->X0;
	I = tap->Material->MeanExcitationEnergy/eV;
	const double ElectronDensity = tap->Material->ElectronDensity;		//N_e / m^3
	const double PlasmaEnergy = tap->Material->PlasmaEnergy/eV;
	const double b_N_ref = tap->Material->b_N;

	//We have now read the material properties, now to scale these if required to the current energy scale etc
	//double center_of_mass_squared = 2 * ProtonMassMeV * MeV * E0;	//ecmsq in SixTrack
	center_of_mass_squared = (2 * ProtonMassMeV * MeV * E0) + (2 * ProtonMassMeV * MeV * ProtonMassMeV * MeV);
	//cout << center_of_mass_squared << "\t" << sqrt(center_of_mass_squared) << endl;

	//pp cross-sections and parameters for energy dependence scaling
	const double p_reference = 450.0 * GeV;			//Reference energy at which the scattering data is based on.	(pref)
	const double pp_total_reference = 0.04;			//Proton total cross section at reference energy		(pptref)
	const double pp_elastic_reference = 0.007;		//Proton elastic cross section at reference energy		(pperef)
	//const double single_diffractive_constant = 0.00068;	//Single Diffractive constant					(sdcoe)
	const double pp_total_constant = 0.05788;		//pp total cross section constant				(pptco)
	const double pp_elastic_constant = 0.04792;		//pp elastic scattering cross section power constant		(ppeco)
	const double free_nucleon_constant = 1.618;		//free nucleon constant						(freeco)
	//const double free_nucleon_constant = 1.0218;		//free nucleon constant						(freeco)
	t_low_cut = 0.0009982;					//Rutherford scattering cut scale (GeV^2)			(tlcut)
	//emr - material atomic size for Rutherford - see NCL thesis for correct term FIXME

	//Atom radius
	//double atomic_radius = 1.2e-15 * pow(A,(1.0/3.0);	// In m, remember elsewhere if using area, to convert to barns
	
	//First calculate the number of "free nucleons" available for scattering
	const double free_nucleon_count = free_nucleon_constant * pow(A,1.0/3.0);

	//Could put the following block within the collimator iteration loop if one is being ultra-pedantic.

	//Cross sections need scaling from the reference energy to the beam energy
	//Nucleus cross sections need scaling to the number of nucleons
	//First task is to calculate the adjusted total cross section at this energy from the reference energy
	
	//double sigma_pp_total = pp_total_reference * pow((E0 / p_reference),pp_total_constant);		//(pptot)
	
	/* 
	*                 Say "Pomeron Exchange" and enter! 22 March 2011 
	*/
	// total cross section calculation(ref. PDG) 

        const double Z_pp = 35.4548e-3;
        const double B_pp = 0.30810e-3;
        const double Y1_pp = 42.5323e-3;
        const double Y2_pp = 33.3433e-3;
        
        const double Z_pn = 35.8016e-3;
        const double B_pn = 0.30810e-3;
        const double Y1_pn = 40.15e-3;
        const double Y2_pn = 30.0e-3;
        
        const double eta1 = 0.45817;
        const double eta2 = 0.545;
        const double s0 = 28.998225*GeV*GeV;
        const double s1 =1*GeV*GeV;
        const double s = center_of_mass_squared;
        double sigma_pp_total = Z_pp + B_pp*pow(log (s/s0),2.0) + Y1_pp * pow(s1/s,eta1) -Y2_pp * pow(s1/s,eta2);               //(pptot)
        double sigma_pn_total = Z_pn + B_pn*pow(log (s/s0),2.0) + Y1_pn * pow(s1/s,eta1) -Y2_pn * pow(s1/s,eta2);

        //const double sigma_pp_elastic = 8.166e-3; //at cms = 81 GeV (ie. 3.5teV) calc by Sandy 
        const double sigma_pp_elastic = 8.938e-3; //at cms = 115 GeV (ie 7teV) calc by Sandy 

	/*

	double sigma_pp_total = 0.0;

	if(T0 < 0.75*GeV)
	{
		sigma_pp_total = 80.0;
	}
	else if(T0 >= 0.75*GeV &&  T0 < 1.5*GeV)
	{
		sigma_pp_total = 80.0;
	}
	else // > 1.5GeV -> 150GeV???
	{
		sigma_pp_total = 80.0; 
	}
	*/
	//Next we also scale the elastic proton-nucleon cross section to the current energy
	//Remember this is for a single nucleon, when applying to a nucleus
	//double sigma_pp_elastic = pp_elastic_reference * pow((E0 / p_reference),pp_elastic_constant);	// demolaize equation 1.21 / catalan 3.7
/*
	//fit to pdg pp elastic data
	double sigma_pp_elastic = 0.0;
	if(T0 < 15*GeV)
	{
		sigma_pp_elastic = (21.1125 * pow(T0,-0.665556)) + 6.12535;
		cout << "LOW T0" << endl;
	}
	else
	{
		sigma_pp_elastic = (4.5 * log(log(sqrt(T0)))) + (27 * pow(T0,-0.76)) + 2.25;
	}
*/	
	//double sigma_pp_elastic = pp_elastic_reference * pow((E0 / p_reference),pp_elastic_constant);	// demolaize equation 1.21 / catalan 3.7
	//And here the elastic cross section is adjusted to the number of nucleons in this material
	sigma_pn_elastic = free_nucleon_count * sigma_pp_elastic;

	//Single diffractive cross section
	//double sigma_pp_SingleDiffractive = single_diffractive_constant * (1 + (36/center_of_mass_squared)) * log(0.6 + (0.1 * center_of_mass_squared));
	double sigma_pp_SingleDiffractive = 0.18 * sigma_pp_elastic;
	//And again scale to the number of nucleons
	sigma_pn_SingleDiffractive = free_nucleon_count * sigma_pp_SingleDiffractive;

	//Next fix Rutherford coulomb scattering
	//FIXME
	sigma_Rutherford = sigma_Rutherford_reference;

	//Correct total without Rutherford inclusion
	sigma_pN_total = sigma_pN_total_reference + free_nucleon_count * (sigma_pp_total - pp_total_reference);
	//sigma_pN_total = sigma_pN_total_reference;	//Adina
	
	//And the inelastic
	//double sigma_pN_inelastic = sigma_pN_inelastic_reference * sigma_pN_total / sigma_pN_total_reference;
	double sigma_pN_inelastic = sigma_pN_inelastic_reference;

	//Caluclate the full nucleus elastic contribution
	sigma_pN_elastic = sigma_pN_total - sigma_pN_inelastic - sigma_pn_elastic - sigma_pn_SingleDiffractive; 

	//Work on slopes next
	b_pp = 8.5 + 1.086 * log(sqrt(center_of_mass_squared)) ; // slope given on GeV units

	b_N = b_N_ref * (sigma_pN_total/sigma_pN_total_reference);

	tmax = (2*ElectronMassMeV * beta * beta * gamma * gamma ) / (1 + (2 * gamma * (ElectronMassMeV/ProtonMassMeV)) + pow((ElectronMassMeV/ProtonMassMeV),2))*MeV;
	//cout << "Tmax: " << tmax/GeV << " GeV" << endl;

	static const double xi1 = 2.0 * pi * pow(ElectronRadius,2) * ElectronMass * pow(SpeedOfLight,2);
	xi0 = xi1 * ElectronDensity;

	C = 1 + 2*log(I/PlasmaEnergy);

	if((I/eV) < 100)
	{
		if(C <= 3.681)
		{
			C0 = 0.2;
			C1 = 2.0;
		}
		else
		{
			C0 = 0.326*C - 1.0;
			C1 = 2.0;
		}
	}
	else	//I >= 100eV
	{
		if(C <= 5.215)
		{
			C0 = 0.2;
			C1 = 3.0;
		}
		else
		{
			C0 = 0.326*C - 1.5;
			C1 = 3.0;
		}
	}

	//cout << C << "\t" << C0 << "\t" << C1 << "\t" << endl;
	//Finally calculate the mean free path
	lambda_tot = A * 1.e-6 / ((sigma_pN_total + sigma_Rutherford) * barn * rho * Avogadro);	// total mean free path (units meter)
	SetScatterConfigured(true);
}

int ProtonBunch::ScatterMerlin(PSvector& p, double x, const Aperture* ap)
{
	// p is the scattering Proton - a single particle.
	// x is the length of the collimator
	// E0 is the reference energy
	// ap is the aperture

	//We simulate many physical processes that occur in bulk materials:
	//Ionization	(-dE/dx)		TODO
	//multiple coulomb scattering		TODO

	//proton-nucleon elastic		OK
	//proton-nucleon inelastic		OK
	//proton-nucleus elastic		OK
	//proton-nucleus inelastic		OK

	//Single Diffractive			OK - CHECK 1/26 FACTOR
	//Rutherford scattering			TODO

	if(!ScatterConfigured)
	{
		ConfigureScatter(ap);
	}
	const CollimatorAperture* tap= dynamic_cast<const CollimatorAperture*> (ap);
      
	//Keep track of distance along the collimator for aperture checking (aperture could vary with z)
	double z = 0; 	// distance travelled along the collimator. Units (m)

	static const double MAXDP = 1.0 - 0.05;	// maximum allowed energy loss - 95%

	//Track back a drift
	p.x() -= x * p.xp();
	p.y() -= x * p.yp();

	//const double Mx_lo2 = pow((ProtonMassMeV * MeV + PionZeroMassMeV*MeV),2);   // SD Mx2_lo =  mp2
     	const double Mx_lo2 = ProtonMassMeV * MeV * 3;   // SD Mx2_lo =  mp2
	const double Mx_hi2 =  Mx_lo2 + 0.15 * center_of_mass_squared;  // SD: Mx2_hi = Mp2 +0.15 *center_of_mass_squared
	double TargetMass=A*AtomicMassUnit; // Nucleus mass

	while( x > 0 )
	{
		bool interacted;	//Interacted on this step or not - true/false?
		double t=0.0;		//Momentum transfer
		double delta_s = -lambda_tot * log (RandomNG::uniform (0, 1));
		double step_size;

        	interacted = ( x > delta_s );
	        step_size = interacted ? delta_s : x;
	
		//Do MCS + dE/dx
        	double zstep = step_size * sqrt( 1 - p.xp()*p.xp() - p.yp()*p.yp() );
		p.x() += step_size * p.xp();
		p.y() += step_size * p.yp();
		double E1 = E0 * (1 + p.dp());	// particle energy
		double thick = step_size / X0;	// material length in radiation lengths
		


		//Start dEdx
		double gamma = E1/(ProtonMassMeV*MeV);
		double beta = 1 - ( 1 / (gamma*gamma));
		double land = gsl_ran_landau(rnd);

		double xi = (xi0 * step_size /(beta*beta)) / ElectronCharge * (eV/MeV);

		//Density correction
		double ddx = log10(beta*gamma);
		if(ddx > C1)
		{
			delta = 4.606*ddx - C;
		}
		else if(ddx >= C0 && ddx <= C1)
		{
			double m = 3.0;
			double xa = C /4.606;
			double a = 4.606 * (xa - C0) / pow((C1-C0),m);
			delta = 4.606*ddx -C + a*pow((C1 - ddx),m);
		}
		else
		{
			//cout << "Delta is zero" << endl;
			delta = 0.0;
		}

		double tcut = 2.0*MeV;
		tcut = tmax;

		//Mott Correction
		double G = pi*FineStructureConstant*beta/2.0;
//		double q = (2*(tmax/MeV)*(ElectronMassMeV)*SpeedOfLight*SpeedOfLight )/(pow((0.843/MeV),2));
		double q = (2*(tmax/MeV)*(ElectronMassMeV) )/(pow((0.843/MeV),2));
		double S = log(1+q);

	//	double L1c = (beta*beta)/(Z*FineStructureConstant*FineStructureConstant);
		double L1 = 0.0;

		double yL2 = FineStructureConstant/beta;

/*		double L2sum = 0.0;
		for (int n=1; n<2000000; n++)
		{
			L2sum += 1/(n * ( (n*n) + (yL2*yL2) ) );
		}
*/
		double L2sum = 1.202001688211;	//Sequence limit calculated with mathematica
		double L2 = -yL2*yL2*L2sum;

		double F = G - S + 2*(L1 + L2);
		//double epsp = (pow(I/eV,2)/(2 * ElectronMassMeV * gamma*gamma*beta*beta));
		double deltaE = xi * (log(2 * ElectronMassMeV * beta*beta * gamma*gamma * (tcut/MeV)/pow(I/MeV,2)) - (beta*beta)*(1 + ((tcut/MeV)/(tmax/MeV))) - delta + F - 1.0 - euler);
		deltaE = xi * (log(2 * ElectronMassMeV * beta*beta * gamma*gamma * xi /pow(I/MeV,2)) - (beta*beta) - delta + F + 0.20);
		//double deltaE = xi * (log(2 * ElectronMassMeV * beta*beta * gamma*gamma * (tcut/MeV)/pow(I/MeV,2)) - (beta*beta)*(1 + ((tcut/MeV)/(tmax/MeV))) - delta + F);
		//xi= xi*2.0;
		//double deltaE = xi * (log(xi/epsp) - (beta*beta) - delta + F + 1.0 - euler);
		//double deltaE = xi * (log(xi/epsp) - (beta*beta) - delta + 0.2);
		//cout << xi << "\t" << (2*ElectronMassMeV * beta*beta*gamma*gamma) << endl;
		if(xi > (2*ElectronMassMeV * beta*beta*gamma*gamma))
		{
			cout << "de,xi " <<  deltaE << "\t" << xi << endl;
		}

		double dp = ((xi * land) - deltaE) * MeV;

	

		//End dEdx
		//
		double E2 = E1 - dp;
		//if(E2 <= 0.0){cout << "E2 is less than zero: " << E2 << endl;}
		if(E2 <=1.0)
		{
			p.ct() = z;
			return 1;
		}

		p.dp () =  ((E1 - dp) - E0) / E0;
		double Eav = (E1+E2) / 2.0;

		/*
		*
		*	MULTIPLE COULOMB SCATTERING
		*
		*/
		double theta0 = 13.6*MeV * sqrt (thick) * (1.0 + 0.038 * log (thick)) / Eav;	// small-angle Coulomb scattering

		pair < double, double > s = CoulombScatter (step_size, theta0);
		p.x ()  += s.first;
		p.xp () += s.second;

		s = CoulombScatter (step_size, theta0);
		p.y ()  += s.first;
		p.yp () += s.second;

		if (E2 < (E0 / 100.0))
		{
			return 4;
		}

		//Check we are still inside the collimator
		//If not, the particle leaves
		if(tap->PointInside(p.x(),p.y(),z+=zstep))
		{
			tally[0]++; 
			p.x() += p.xp()*x;
			p.y() += p.yp()*x;
			return 0;
		}


		//Point process interaction
	        if (interacted)
		{
			E1 = E0 * (1 + p.dp());
			double r = RandomNG::uniform(0,1) * (sigma_pN_total + sigma_Rutherford);

			//Choose which scattering process to do
			/*
			*
			*	Elastic scatter pN (proton - Nucleus)
			*
			*/
			if ( (r -= sigma_pN_elastic) < 0  )
			{
				tally[1]++;
				t = -log(RandomNG::uniform(0,1))/b_N;
				//histt1->Fill(t);
				dp = t/(2*TargetMass); // units of GeV
			}

			/*
			*
			*	Elastic scatter pn (proton - nucleon)
			*
			*/
			else if ( (r -= sigma_pn_elastic) < 0  )
			{
				tally[2]++; 
				t = -log(RandomNG::uniform(0,1))/b_pp;
				//histt2->Fill(t);
				double fmax=1671400.0, vfmax, v, ft;
				do{
					double u = RandomNG::uniform(0,0.012);
					t = -log(u)/80000.0; //tmax= 0.01
					ft= get_ft(t);
					v=ft*exp(80000.0*t);
					vfmax = RandomNG::uniform(0,1)*fmax;
				}
				while(v< vfmax);
				dp = t/(2*AtomicMassUnit);
			}

			/*
			*
			*	Single Diffractive
			*
			*/

			else if ( (r -= sigma_pn_SingleDiffractive) < 0 )
			{
			
				tally[3]++;
				double u = RandomNG::uniform(0,1);
				double Mx2 = pow((1+1/pow(Mx_lo2,0.08)+u*(1/pow(Mx_hi2,0.08)-1/pow(Mx_lo2,0.08))),1/0.08); //if the cross section ~ 1/(Mx2)^(1+epsilon) where epsilon = 0.08 
				//double Mx2 =1/ pow((1+1/pow(Mx_lo2,0.08)+u*(1/pow(Mx_hi2,0.08)-1/pow(Mx_lo2,0.08))),1/0.08);
				double b = 25.51 + 0.5 * log(center_of_mass_squared/Mx2); //Goulianos
				t =-log(RandomNG::uniform(0,1))/b;
				dp = (t + Mx2 - pow(ProtonMassMeV * MeV,2))/(2*ProtonMassMeV * MeV);
				
			}

			/*
			*
			*	Rutherford coulomb scattering
			*
			*/
			else if ( (r -= sigma_Rutherford) < 0)
			{
				tally[4]++;
				double tcut=t_low_cut;			
				t=tcut/(1-RandomNG::uniform(0,1)); // generates 1/t squared distribution,
				dp = t/(2*TargetMass); //units of GeV
				//ruth = 2.607e-4 * exp(-t * 0.8561e3 * emr^2 ) * (atomic_number / t) ^2
			}

			/*
			*
			*	Inelastic interaction - no more proton :(
			*
			*/
			else
			{
				tally[5]++; 
				//lose particle
				p.ct() = z;
				return 1;
			}
			double E3 = E2 - dp;

			if(E3 <=0.10)
			{
				p.ct() = z;
			//	cout << "E3 <= 1 GeV" << endl;
				return 1;
			}

			p.dp() = (E3 - E0)/E0;

			double theta = sqrt(t)/E3;
			double phi = RandomNG::uniform(-pi,pi);
			p.xp() += theta * cos(phi);
			p.yp() += theta * sin(phi);
		}

	x -= step_size;
	} // end of while loop

	if(p.dp() < -MAXDP || p.dp() < -1.0)	//dp cut should be at 95%
	{
		p.ct() = z;
		//cout << (MAXDP*100.0) << "% P loss" << endl;
		return 1;
	}

	return 0;
}

/****************************************************************
**
**
**	"Sixtrack/K2 style" scattering physics
**
**
****************************************************************/

void ProtonBunch::ConfigureScatterSixtrack(const Aperture* ap)
{
	//Do a cast to check if we have a "CollimatorAperture"
	const CollimatorAperture* tap= dynamic_cast<const CollimatorAperture*> (ap);
	if(!tap)
	{
		throw MerlinException("ScatterProton : No Collimator Aperture");
	}

	double P0 = GetReferenceMomentum();
	E0 = sqrt(P0*P0 + pow(ProtonMassMeV*MeV,2));

	const double sigma_pN_total_reference = tap->Material->sigma_pN_total;		//Material reference proton-Nucleus total scattering cross section
	const double sigma_pN_inelastic_reference = tap->Material->sigma_pN_inelastic;	//Material reference proton-Nucleus inelastic scattering cross section
	const double sigma_Rutherford_reference = tap->Material->sigma_Rutherford;		//Material reference Rutherford scattering cross section
	dEdx = tap->Material->dEdx;					//dE/dx - (GeV m^-1)
	rho = tap->Material->rho;						//density (g /cm^3)
	A = tap->Material->A;						//Atomic mass
	Z = tap->Material->atomic_number;				//Atomic number
	X0 = tap->Material->X0;
	const double b_N_ref = tap->Material->b_N;

	//We have now read the material properties, now to scale these if required to the current energy scale etc
	center_of_mass_squared = 2 * ProtonMassMeV * MeV * E0;	//ecmsq in SixTrack

	//pp cross-sections and parameters for energy dependence scaling
	const double p_reference = 450.0 * GeV;			//Reference energy at which the scattering data is based on.	(pref)
	const double pp_total_reference = 0.04;			//Proton total cross section at reference energy		(pptref)
	const double pp_elastic_reference = 0.007;		//Proton elastic cross section at reference energy		(pperef)
	const double single_diffractive_constant = 0.00068;	//Single Diffractive constant					(sdcoe)
	const double pp_total_constant = 0.05788;		//pp total cross section constant				(pptco)
	const double pp_elastic_constant = 0.04792;		//pp elastic scattering cross section power constant		(ppeco)
	const double free_nucleon_constant = 1.618;		//free nucleon constant						(freeco)
	//const double free_nucleon_constant = 1.0218;		//free nucleon constant						(freeco)
	t_low_cut = 0.0009982;					//Rutherford scattering cut scale (GeV^2)			(tlcut)
	//emr - material atomic size for Rutherford - see NCL thesis for correct term FIXME
	//ppsd = sdcoe * log(0.15d0 * ecmsq)

	//Atom radius
	double atomic_radius = 1.2e-15 * pow(A,(1.0/3.0));	// In m, remember elsewhere if using area, to convert to barns

	//First calculate the number of "free nucleons" available for scattering
	const double free_nucleon_count = free_nucleon_constant * pow(A,1.0/3.0);

	//Could put the following block within the collimator iteration loop if one is being ultra-pedantic.
	//Cross sections need scaling from the reference energy to the beam energy
	//Nucleus cross sections need scaling to the number of nucleons
	//First task is to calculate the adjusted total cross section at this energy from the reference energy

	double sigma_pp_total = pp_total_reference * pow((E0 / p_reference),pp_total_constant);		//(pptot)

	//Next we also scale the elastic proton-nucleon cross section to the current energy
	//Remember this is for a single nucleon, when applying to a nucleus
	const double sigma_pp_elastic = pp_elastic_reference * pow((E0 / p_reference),pp_elastic_constant);	// demolaize equation 1.21 / catalan 3.7

	//And here the elastic cross section is adjusted to the number of nucleons in this material
	sigma_pn_elastic = free_nucleon_count * sigma_pp_elastic;

	//Single diffractive cross section
	const double sigma_pp_SingleDiffractive = single_diffractive_constant * log(0.15*center_of_mass_squared);
	//And again scale to the number of nucleons
	sigma_pn_SingleDiffractive = free_nucleon_count * sigma_pp_SingleDiffractive;

	//Next fix Rutherford coulomb scattering
	//FIXME
	sigma_Rutherford = sigma_Rutherford_reference;

	//Correct total without Rutherford inclusion
	sigma_pN_total = sigma_pN_total_reference + free_nucleon_count * (sigma_pp_total - pp_total_reference);

	//And the inelastic
	double sigma_pN_inelastic = sigma_pN_inelastic_reference * sigma_pN_total / sigma_pN_total_reference;

	//Caluclate the full nucleus elastic contribution
	sigma_pN_elastic = sigma_pN_total - sigma_pN_inelastic - sigma_pn_elastic - sigma_pn_SingleDiffractive; 

	//Work on slopes next
	b_pp = 8.5 + 1.086 * log(sqrt(center_of_mass_squared)) ; // slope given on GeV units

	b_N = b_N_ref * (sigma_pN_total/sigma_pN_total_reference);

	//Finally calculate the mean free path
	lambda_tot = A * 1.e-6 / ((sigma_pN_total + sigma_Rutherford) * barn * rho * Avogadro);	// total mean free path (units meter)
	SetScatterConfigured(true);
}

int ProtonBunch::ScatterSixtrack(PSvector& p, double x, const Aperture* ap)
{
	// p is the scattering Proton - a single particle.
	// x is the length of the collimator
	// E0 is the reference energy
	// ap is the aperture

	//We simulate many physical processes that occur in bulk materials:
	//Ionization	(-dE/dx)		TODO
	//multiple coulomb scattering		TODO

	//proton-nucleon elastic		OK
	//proton-nucleon inelastic		OK
	//proton-nucleus elastic		OK
	//proton-nucleus inelastic		OK

	//Single Diffractive			OK - CHECK 1/26 FACTOR
	//Rutherford scattering			TODO

	if(!ScatterConfigured)
	{
		ConfigureScatter(ap);
	}
	const CollimatorAperture* tap= dynamic_cast<const CollimatorAperture*> (ap);
      
	//Keep track of distance along the collimator for aperture checking (aperture could vary with z)
	double z = 0; 	// distance travelled along the collimator. Units (m)

	static const double MAXDP = 1.0 - 0.05;	// maximum allowed energy loss - 95%

	//Track back a drift
	p.x() -= x * p.xp();
	p.y() -= x * p.yp();

	while( x > 0 )
	{
		bool interacted;	//Interacted on this step or not - true/false?
		double t=0.0;		//Momentum transfer
		double delta_s = -lambda_tot * log (RandomNG::uniform (0, 1));
		double step_size;

        	interacted = ( x > delta_s );
	        step_size = interacted ? delta_s : x;
	
		//Do MCS + dE/dx
        	double zstep = step_size * sqrt( 1 - p.xp()*p.xp() - p.yp()*p.yp() );
		p.x() += step_size * p.xp();
		p.y() += step_size * p.yp();
		double E1 = E0 * (1 + p.dp());	// particle energy
		double thick = step_size / X0;	// material length in radiation lengths
		


		//Start dEdx
		double dp = dEdx * step_size;
		//End dEdx

		double E2 = E1 - dp;

		if(E2 <=1.0)
		{
			p.ct() = z;
			return 1;
		}

		p.dp () =  ((E1 - dp) - E0) / E0;
		double Eav = (E1+E2) / 2.0;

		/*
		*
		*	MULTIPLE COULOMB SCATTERING
		*
		*/
		double theta0 = 13.6*MeV * sqrt (thick) * (1.0 + 0.038 * log (thick)) / Eav;	// small-angle Coulomb scattering

		pair < double, double > s = CoulombScatter (step_size, theta0);
		p.x ()  += s.first;
		p.xp () += s.second;

		s = CoulombScatter (step_size, theta0);
		p.y ()  += s.first;
		p.yp () += s.second;

		if (E2 < (E0 / 100.0))
		{
			return 4;
		}

		//Check we are still inside the collimator
		//If not, the particle leaves
		if(tap->PointInside(p.x(),p.y(),z+=zstep))
		{
			tally[0]++; 
			p.x() += p.xp()*x;
			p.y() += p.yp()*x;
			return 0;
		}

		//Reset this, not all interactions use it...
		dp = 0.0;
		//Point process interaction
	        if (interacted)
		{
			E1 = E0 * (1 + p.dp());
			double r = RandomNG::uniform(0,1) * (sigma_pN_total + sigma_Rutherford);

			//Choose which scattering process to do
			/*
			*
			*	Elastic scatter pN (proton - Nucleus)
			*
			*/
			if ( (r -= sigma_pN_elastic) < 0  )
			{
				tally[1]++;
				t = -log(RandomNG::uniform(0,1))/b_N;
			}

			/*
			*
			*	Elastic scatter pn (proton - nucleon)
			*
			*/
			else if ( (r -= sigma_pn_elastic) < 0  )
			{
				tally[2]++; 
				t = -log(RandomNG::uniform(0,1))/b_pp;
			}

			/*
			*
			*	Single Diffractive
			*
			*/

			else if ( (r -= sigma_pn_SingleDiffractive) < 0 )
			{
			
				tally[3]++;
				double xm2 = exp(RandomNG::uniform(0,1)*log(0.15*center_of_mass_squared));
				double b = 0.0;
				if(xm2 < 2.0)
				{
					b = 2 * b_pp;
				}
				else if(2.0 <= xm2 && xm2 <= 5.0)
				{
					b = (106.0 - 17.0 * xm2 ) * b_pp / 36.0;	//This isn't what is in the sixtrack code (/26.0 typo) but is what is listed in N. Lasheras' thesis... 
				}
				else if(xm2 > 5.0)
				{
					b = 7.0 * b_pp / 12.0;
				}
				t =-log(RandomNG::uniform(0,1))/b;
				dp = xm2/center_of_mass_squared;
				
			}

			/*
			*
			*	Rutherford coulomb scattering
			*
			*/
			else if ( (r -= sigma_Rutherford) < 0)
			{
				tally[4]++;
				double tcut=t_low_cut;			
				t=tcut/(1-RandomNG::uniform(0,1)); // generates 1/t squared distribution,
				//ruth = 2.607e-4 * exp(-t * 0.8561e3 * emr^2 ) * (atomic_number / t) ^2
			}

			/*
			*
			*	Inelastic interaction - no more proton :(
			*
			*/
			else
			{
				tally[5]++; 
				//lose particle
				p.ct() = z;
				return 1;
			}
			double E3 = E2 - dp;

			if(E3 <=0.10)
			{
				p.ct() = z;
			//	cout << "E3 <= 1 GeV" << endl;
				return 1;
			}

			p.dp() = (E3 - E0)/E0;

			double theta = sqrt(t)/E3;
			double phi = RandomNG::uniform(-pi,pi);
			p.xp() += theta * cos(phi);
			p.yp() += theta * sin(phi);
		}

	x -= step_size;
	} // end of while loop

	if(p.dp() < -MAXDP || p.dp() < -1.0)	//dp cut should be at 95%
	{
		p.ct() = z;
		//cout << (MAXDP*100.0) << "% P loss" << endl;
		return 1;
	}

	return 0;
}
