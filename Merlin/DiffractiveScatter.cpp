/////////////////////////////////////////////////////////////////////////
//
// Merlin C++ Class Library for Charged Particle Accelerator Simulations
//
// Class library version 5.02 (2017)
//
// Copyright: see Merlin/copyright.txt
//
// Created:
// Modified:    2017-08-03 James Fallon
//
/////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <iostream>
#include <fstream>

// Include for the Elastic scattering class
#include "DiffractiveScatter.h"

// Include for the max() algorithm
#include <algorithm>

// Include for make_pair
#include <utility>

#include "NumericalConstants.h"
#include "PhysicalConstants.h"
#include "PhysicalUnits.h"
#include "RandomNG.h"

using namespace PhysicalUnits;
using namespace PhysicalConstants;

namespace ParticleTracking
{

/**
* Sets the minimum t value for generation
*/
void ppDiffractiveScatter::SetTMin(double tmin){
    t_min = tmin;
}

/**
* Sets the maximum t value for generation
*/

void ppDiffractiveScatter::SetTMax(double tmax){
    t_max = tmax;
}

/**
* Sets the step size in t for the differential cross section generation
*/
void ppDiffractiveScatter::SetTStepSize(double StepSize){
    t_step = StepSize;
}

/**
* Sets the minimum t value for generation
*/
void ppDiffractiveScatter::SetXiMin(double min){
    xi_min = min;
}

/**
* Sets the maximum t value for generation
*/
void ppDiffractiveScatter::SetXiMax(double max){
    xi_max = max;
}

/**
* Sets the step size in xi for the differential cross section generation
*/
void ppDiffractiveScatter::SetXiStepSize(double StepSize){
    xi_step = StepSize;
}


/**
* Gets the currently set minimum t value
* @return t_min Currently set minimum t value
*/
double ppDiffractiveScatter::GetTMin() const {
    return t_min;
}

/**
* Gets the currently set maximum t value
* @return t_min Currently set maximum t value
*/
double ppDiffractiveScatter::GetTMax() const {
    return t_max;
}

/**
* Gets the currently set t step size
* @return t_min Currently set t step size
*/
double ppDiffractiveScatter::GetTStepSize() const {
    return t_step;
}

/**
* Gets the currently set minimum xi value
* @return t_min Currently set minimum xi value
*/
double ppDiffractiveScatter::GetXiMin() const {
    return xi_min;
}

/**
* Gets the currently set maximum xi value
* @return t_min Currently set maximum xi value
*/
double ppDiffractiveScatter::GetXiMax() const {
    return xi_max;
}

/**
* Gets the currently set xi step size
* @return t_min Currently set xi step size
*/
double ppDiffractiveScatter::GetXiStepSize() const {
    return xi_step;
}

/**
* Gets the Integrated elastic cross section
* @return Integrated elastic cross section
*/
double ppDiffractiveScatter::GetDiffractiveCrossSection() const {
    return SigDiffractive;
}


/**
* Debug toggle - set to true or false to enable/disable debugging output
*/
void ppDiffractiveScatter::EnableDebug(bool flag){
    Debug = flag;
}


/**
* Generates the required differential cross sections and integrates for the specified energy
*/
void ppDiffractiveScatter::GenerateDistribution(double energy)
{
    if(!Configured)
    {
        /// Generating pp Diffractive differential cross section
        GenerateDsigDtDxi(energy);

        /// Integrating differential cross section
        //IntegrateDsigDtDxi();

        /// Diffractive Configuration generation done
        Configured = true;
    }
}

ppDiffractiveScatter::~ppDiffractiveScatter(){}


/**
* Generates the elastic differential cross section Places the results into the
* vectors t and DSig @param energy sqrt s
*/
void  __attribute__((optimize("O3,unsafe-math-optimizations"))) ppDiffractiveScatter::GenerateDsigDtDxi(const double energy)
{
    std::cout << "Call generateDsigDtDxi " << std::endl;
    const double s = (2 * PhysicalConstants::ProtonMassMeV * PhysicalUnits::MeV * energy) + (2 * pow(PhysicalConstants::ProtonMassMeV * PhysicalUnits::MeV,2));
    ss = s;
    std::cout << "s =" << s << std::endl;
    const int NN=10*N;
    t_step=(t_max-t_min)/NN;

    xi_step=(xi_max-xi_min)/NN;
    std::cout << "t_max" << "\t" << t_max << "\t" << "t_min" << "\t" << t_min << std::endl;
    std::cout << "xi_max" << "\t" << xi_max << "\t" << "xi_min" << "\t" << xi_min << std::endl;
    std::cout << "xi_step" << "\t" << xi_step << "\t" << "t_step" << "\t" << t_step << std::endl;

    double xdist[NN] = {0};
    double tdist[NN] = {0};

    double sum=0;

    for(int i=0; i<NN; i++)
    {
        const double t=t_min + i * t_step;
        for(int j=0; j<NN; j++)
        {
            const double x=xi_min + j*xi_step;
            const double ds=PomeronScatter(t,x,s);
            sum=sum+ds;
            tdist[i]+=ds;
            xdist[j]+=ds;
        }
    }

    /// convert mbarn to barn
    SigDiffractive= 0.001*sum * xi_step * t_step;

    /// convert histograms to normalised cumulants
    /// Running total
    for(int i=1; i<NN; i++)
    {
        xdist[i]+=xdist[i-1];
        tdist[i]+=tdist[i-1];
    }

    /// Normalised
    for(int i=0; i<NN; i++)
    {
        xdist[i]/=xdist[NN-1];
        tdist[i]/=tdist[NN-1];
    }

    /// convert to lookup tables
    int iseekt=0, iseekx=0;
    xarray[0]=tarray[0]=0;

    for(int i=1; i<N; i++)
    {
        double target=double(i)/N;

        /// Increment up to the first value of iseekx that satisfies (xdist[iseekx+1] < target)
        while(xdist[iseekx+1] < target)
        {
            iseekx++;
        }

        double leftover = target - xdist[iseekx];
        xarray[i] = (iseekx + std::min(1.0E0,leftover/(xdist[iseekx+1]-xdist[iseekx])))/NN;

        /// Increment up to the first value of iseekt that satisfies (tdist[iseekt+1] < target)
        while(tdist[iseekt+1] < target)
        {
            iseekt++;
        }

        leftover = target - tdist[iseekt];
        tarray[i] = (static_cast<double>(iseekt) + std::min(1.0E0,leftover/(tdist[iseekt+1]-tdist[iseekt])))/static_cast<double>(NN);
    }

    std::cout << "Nucleon Diffractive total cross section total "  << SigDiffractive * 1000.0 <<" mb" << std::endl;
    std::cout << "Sixtrack Diffractive total cross section total " << 0.00068*log(0.15*s) * 1000.0 <<" mb" << std::endl;
}

/*
void ppDiffractiveScatter::IntegrateDsigDtDxi()
{
    unsigned int nTSteps = UniformT.size();
    unsigned int nXiSteps = UniformXi.size();
    Sig.reserve(nTSteps*nXiSteps);
//  unsigned int seekt = 0;
    IntSig[0] = 0.0;
    std::cout << "INTEGRATE\t" << nTSteps << "\t" << nXiSteps << std::endl;
//  std::cout << Uniformt.size() << "\t" << DSig.size() << "\t" << IntSig.size() << std::endl;

    for(unsigned int n = 1; n < nTSteps*nXiSteps; n++)
    {
        double CurrentStepIntegral = (DSig[n] * nTSteps);//fix this
        SigDiffractive += CurrentStepIntegral;
        IntSig.push_back(SigDiffractive);
    }

    std::cout << "Diffractive Cross section (with peak): " << SigDiffractive * 1000 << std::endl;
    //Switch to normalized values to make our life easier
    for(unsigned int n = 1; n < nTSteps; n++)
    {
        for(unsigned int m = 1; m < nXiSteps; m++)
        {
            IntSig[n][m] /= SigDiffractive;
            //(*ofile) << UniformT[n] << "\t" << IntSig[n] << std::endl;
        }
    }

    InversionInterpolation = new Interpolation(IntSig, UniformT);

    for(unsigned int n=1; n <nSteps; n++)
    {
        double target = (static_cast<double>(n) / nSteps);

        try
        {
            sig_gen = (*InversionInterpolation)(target);
        }
        catch(Interpolation::BadRange& error)
        {
            std::cerr << "Bad Range in interpolation - requested: " << error.value << " but valid range is from " << error.valid_range.lower << " to "  << error.valid_range.upper << std::endl;
            std::cerr << "error in entry: " << n << " with total " << nSteps << std::endl;
            throw;
        }
        Sig.push_back(sig_gen);
    }

    LinearInterpolation = new Interpolation(Sig, 0, (1.0/nSteps));    // Interpolation of equally spaced data points
}
*/

/// Picks a t value from the generated distribution (including interpolation)
double ppDiffractiveScatter::SelectT()
{

    double SigValue = RandomNG::uniform (0, 1.0);
    double t = (*LinearInterpolation)(SigValue);
    return t;
}

/// Picks an Xi value from the generated distribution (including interpolation)
double ppDiffractiveScatter::SelectXi()
{
    double SigValue = RandomNG::uniform (0, 1.0);
    double xi = (*LinearInterpolation)(SigValue);
    return xi;
}

std::pair<double,double> ppDiffractiveScatter::Select()
{
    double xx,tt;

retry:
    double rt = N*RandomNG::uniform(0,1);
    int it = int(rt);
    double extra = rt-it;
    double deltat = 0.0;

    /// set value of deltat depending on evaluation of (it<(N-1))
    deltat = it<(N-1) ? tarray[it+1]-tarray[it] : 1-tarray[it];

    tt = tarray[it] + extra * deltat;
    tt = t_min + tt *(t_max-t_min);

    if(tt < 0 || deltat < 0)
    {
        goto retry;
    }

    double rx = N*RandomNG::uniform(0,1);
    int ix = int(rx);
    extra = rx-ix;
    double deltax=0.0;

    /// set value of deltax depending on evaluation of (ix<(N-1))
    deltax = ix<(N-1) ? xarray[ix+1]-xarray[ix] : 1-xarray[ix];

    xx=xarray[ix]+extra*deltax;
    xx=xi_min+xx*(xi_max-xi_min);

    double ds=PomeronScatter(tt,xx,ss)*0.001;
    double ds2=SigDiffractive/(N*N*deltax*(xi_max-xi_min)*deltat*(t_max-t_min));

    if(RandomNG::uniform(0,1)>ds/ds2)
    {
        goto retry;
    }

    double mrec=sqrt(ss*xx);
    return std::make_pair(tt,mrec);
}

/// This is the high mass regge diffraction
double ppDiffractiveScatter::PomeronScatter2(double tt, double x, double s)
{
    double sigma_xi = 0.1;
    double sigma_t = 0.1;
    double gausx = exp(-x*x/(2*sigma_xi));
    double gaust = exp(-tt*tt/(2*sigma_t));
    return x*x;
}

inline double  __attribute__((optimize("O3,unsafe-math-optimisations"))) __attribute__ ((hot)) ppDiffractiveScatter::PomeronScatter(const double tt, const double x, const double s)   const
{
    /// Call PomeronScatter SD
    const double t= - tt;

    /// Parameters for the resonance term in the background
    const double Mproton = 0.938272013;
    const double Mpion = 0.1349766;
    const double Mmin2 = pow(Mproton+Mpion,2);

    /// mass of the resonance P11 D13 G15 F17
    const double ml01 = 1.44;
    const double ml02 = 1.52;
    const double ml03 = 1.68;
    const double ml04 = 2.19;

    /// width of the resonance
    const double GammaL1 = 0.325;
    const double GammaL2 = 0.13;
    const double GammaL3 = 0.14;
    const double GammaL4 = 0.45;

    /// coupling coefficient from the data fit
    const double cl01 = 3.07;
    const double cl02 = 0.4149;
    const double cl03 = 1.108  ;
    const double cl04 = 0.9515;

    /// this is chosen from the fit on the cross section data
    double Mcut = 3;

    /// Adjust matching point for high s
    if(ss > 4000)
    {
        Mcut = 3 + 0.6 * log(s/4000);
    }

    const double xi_c = Mcut*Mcut/s;
    const double xi_th = Mmin2/s;
    const double Mmin2bar = pow(Mproton-Mpion,2);

    if(x <= xi_th)
    {
        return 0;
    }

    double cc[4][3];

    cc[0][0] = 0.624529; //A
    cc[0][1] = 2.5835;   //B
    cc[0][2] = 0;        //C

    //ppr
    cc[1][0] = 3.09088;
    cc[1][1] = 4.51487;
    cc[1][2] = 0.186211;

    //rrp
    cc[2][0] = 4.0;
    cc[2][1] = 3.03392;
    cc[2][2] = 10.0;

    //rrr
    cc[3][0] = 177.217;
    cc[3][1] = 5.86474;
    cc[3][2] = 21.0029;

    const double q   = sqrt( (x*s-Mmin2) * (x*s-Mmin2bar) / (4*x*s) );

    const double ql1 = sqrt( (pow(ml01,2) - Mmin2) * (pow(ml01,2) - Mmin2bar) / (4*pow(ml01,2)) );
    const double ql2 = sqrt( (pow(ml02,2) - Mmin2) * (pow(ml02,2) - Mmin2bar) / (4*pow(ml02,2)) );
    const double ql3 = sqrt( (pow(ml03,2) - Mmin2) * (pow(ml03,2) - Mmin2bar) / (4*pow(ml03,2)) );
    const double ql4 = sqrt( (pow(ml04,2) - Mmin2) * (pow(ml04,2) - Mmin2bar) / (4*pow(ml04,2)) );

    const double gammaL01 = GammaL1*pow(q/ql1,3)*((1 + 5*ql1)/(1 + 5*q));
    const double gammaL02 = GammaL2*pow(q/ql2,5)*pow(((1 + 5*ql2)/(1 + 5*q)),2);
    const double gammaL03 = GammaL3*pow(q/ql3,7)*pow(((1 + 5*ql3)/(1 + 5*q)),3);
    const double gammaL04 = GammaL4*pow(q/ql4,9)*pow(((1 + 5*ql4)/(1 + 5*q)),4);

    const double R = ( (cl01/x) * (ml01*gammaL01) / ( pow( (x*s - pow(ml01,2) ),2) + pow(ml01*gammaL01,2))
                      +(cl02/x) * (ml02*gammaL02) / ( pow( (x*s - pow(ml02,2) ),2) + pow(ml02*gammaL02,2))
                      +(cl03/x) * (ml03*gammaL03) / ( pow( (x*s - pow(ml03,2) ),2) + pow(ml03*gammaL03,2))
                      +(cl04/x) * (ml04*gammaL04) / ( pow( (x*s - pow(ml04,2) ),2) + pow(ml04*gammaL04,2)) )
                     *exp(13.5*(t + 0.05));// Normalization factors Sandy's note
    //* sqrt(565/s)*exp(13.5*(t + 0.05));// Normalization factors Sandy's note
//  double BRMatch = - 588.20982975 *exp(13.5*(t + 0.05))*(x - xi_th)/(xi_c - xi_th);
    const double BRMatch = -  ( (cl01/xi_c) * (ml01*gammaL01) / ( pow( (xi_c*s - pow(ml01,2) ),2) + pow(ml01*gammaL01,2))
                               +(cl02/xi_c) * (ml02*gammaL02) / ( pow( (xi_c*s - pow(ml02,2) ),2) + pow(ml02*gammaL02,2))
                               +(cl03/xi_c) * (ml03*gammaL03) / ( pow( (xi_c*s - pow(ml03,2) ),2) + pow(ml03*gammaL03,2))
                               +(cl04/xi_c) * (ml04*gammaL04) / ( pow( (xi_c*s - pow(ml04,2) ),2) + pow(ml04*gammaL04,2)) )
                           *exp(13.5*(t + 0.05)) *(x - xi_th)/(xi_c - xi_th);

    if(t > -0.25)
    {
        if(x > xi_th && x <= xi_c)
        {
            const double Axi_c = (0.4+0.5*t)*pow(s,0.08) * pow(xi_c,-1.08 -0.5*t)   //ppp
                                +(cc[1][0]*exp(cc[1][1]*t) + cc[1][2]) * pow(s,-0.4525) * pow(xi_c,-1.6125 -0.5*t)  //ppr
                                +(cc[2][0]*exp(cc[2][1]*t) + cc[2][2]) * pow(s,0.08) * pow(xi_c,-0.015 - 1.86*t)    //rrp
                                +(cc[3][0]*exp(cc[3][1]*t) + cc[3][2]) * pow(s,-0.4525) * pow(xi_c,-0.5475 - 1.86*t)    //rrr
                                +1.14591559 * pow(3.52142 - 2.79*t,2) * pow(xi_c,1 - 1.86 * (-0.0182185 + t)) * (31.79*pow(s*xi_c,-0.4525) + 13.63 *pow(s*xi_c,0.0808)) //pion
                                * fabs(t) * pow(1 - 1.40845*t,-4) * pow(3.52142 -t,-2) * pow(-0.0182185 + t,-2);    //form factor


            const double Aprimexi_c = (0.4+0.5*t)*pow(s,0.08) * (-1.08 - 0.5*t) *pow(xi_c,-2.08 - 0.5*t)    //ppp
                                     +(cc[1][0]*exp(cc[1][1]*t) + cc[1][2]) * pow(s,-0.4525) * (-1.6125 - 0.5*t) *pow(xi_c,-2.6125 -0.5*t)  //ppr
                                     +(cc[2][0]*exp(cc[2][1]*t) + cc[2][2]) * pow(s,0.08) * (-0.015 - 1.86*t) *pow(xi_c,-1.015 - 1.86*t)    //rrp
                                     +(cc[3][0]*exp(cc[3][1]*t) + cc[3][2]) * pow(s,-0.4525) * (-0.5475 - 1.86*t) * pow(xi_c,-1.5475 - 1.86*t)  //rrr
                                     +1.14591559 * pow(3.52142 - 2.79*t,2) * fabs(t) * pow(1 - 1.40845*t,-4) * pow(3.52142 -t,-2) * pow(-0.0182185 + t,-2)
                                     * ((1 - 1.86 * (-0.0182185 + t)) *pow(xi_c,-1.86 * (-0.0182185 + t)) * (31.79*pow(s*xi_c,-0.4525) + 13.63 *pow(s*xi_c,0.0808))
                                        + (pow(xi_c,1 - 1.86 * (-0.0182185 + t)) * (31.79*(-0.4525)*pow(s*xi_c,-1.4525)+13.63*0.0808*pow(s*xi_c,0.0808-1))));   //form factor

            const double d = ((xi_c-xi_th)*Aprimexi_c-Axi_c)/pow(xi_c-xi_th,2);
            const double e = Aprimexi_c -2*((xi_c-xi_th)*Aprimexi_c-Axi_c)/(xi_c-xi_th);

            const double B = d * pow(x - xi_th,2) + e * (x - xi_th);
            return B + R + BRMatch;
        }
        else
        {
            return (0.4+0.5*t)*pow(s,0.08) * pow(x,-1.08 -0.5*t)    //ppp
                   +(cc[1][0]*exp(cc[1][1]*t) + cc[1][2]) * pow(s,-0.4525) * pow(x,-1.6125 -0.5*t)  //ppr
                   +(cc[2][0]*exp(cc[2][1]*t) + cc[2][2]) * pow(s,0.08)     * pow(x,-0.015 - 1.86*t)    //rrp
                   +(cc[3][0]*exp(cc[3][1]*t) + cc[3][2]) * pow(s,-0.4525) * pow(x,-0.5475 - 1.86*t)    //rrr
                   +1.14591559 * pow(3.52142 - 2.79*t,2) * pow(x,1 - 1.86 * (-0.0182185 + t)) * (31.79*pow(s*x,-0.4525) + 13.63 *pow(s*x,0.0808))   //pion
                   * fabs(t) * pow(1 - 1.40845*t,-4) * pow(3.52142 -t,-2) * pow(-0.0182185 + t,-2); //form factor
        }

    }
    else if(t > -1.15)
    {
        if(x > xi_th && x <= xi_c)
        {
            const double Axi_c =  (cc[0][0]*exp(cc[0][1]*t) + cc[0][2]) * pow(s,0.08) * pow(xi_c,-1.08 - 0.5*t) * (t/(t - 0.05))    //ppp
                                 +(cc[1][0]*exp(cc[1][1]*t) + cc[1][2]) * pow(s,-0.4525) * pow(xi_c,-1.6125 -0.5*t) //ppr
                                 +(cc[2][0]*exp(cc[2][1]*t) + cc[2][2]) * pow(s,0.08) * pow(xi_c,-0.015 - 1.86*t)   //rrp
                                 +(cc[3][0]*exp(cc[3][1]*t) + cc[3][2]) * pow(s,-0.4525) * pow(xi_c,-0.5475 - 1.86*t)   //rrr
                                 +1.14591559 * pow(3.52142 - 2.79*t,2) * pow(xi_c,1 - 1.86 * (-0.0182185 + t)) * (31.79*pow(s*xi_c,-0.4525) + 13.63 *pow(s*xi_c,0.0808))    //pion
                                 * (-t) * pow(1 - 1.40845*t,-4) * pow(3.52142 -t,-2) * pow(-0.0182185 + t,-2);  //form factor


            const double Aprimexi_c =  (cc[0][0]*exp(cc[0][1]*t) + cc[0][2]) * pow(s,0.08) * (-1.08 - 0.5*t) *pow(xi_c,-2.08 - 0.5*t) * (t/(t - 0.05))  //ppp
                                      +(cc[1][0]*exp(cc[1][1]*t) + cc[1][2]) * pow(s,-0.4525) * (-1.6125 - 0.5*t) *pow(xi_c,-2.6125 -0.5*t) //ppr
                                      +(cc[2][0]*exp(cc[2][1]*t) + cc[2][2]) * pow(s,0.08) * (-0.015 - 1.86*t) *pow(xi_c,-1.015 - 1.86*t)   //rrp
                                      +(cc[3][0]*exp(cc[3][1]*t) + cc[3][2]) * pow(s,-0.4525) * (-0.5475 - 1.86*t) * pow(xi_c,-1.5475 - 1.86*t) //rrr
                                      +1.14591559 * pow(3.52142 - 2.79*t,2) * (-t) * pow(1 - 1.40845*t,-4) * pow(3.52142 -t,-2) * pow(-0.0182185 + t,-2)
                                      * ((1 - 1.86 * (-0.0182185 + t)) *pow(xi_c,-1.86 * (-0.0182185 + t)) * (31.79*pow(s*xi_c,-0.4525) + 13.63 *pow(s*xi_c,0.0808))
                                         + (pow(xi_c,1 - 1.86 * (-0.0182185 + t)) * (31.79*(-0.4525)*pow(s*xi_c,-1.4525)+13.63*0.0808*pow(s*xi_c,0.0808-1))));  //form factor

            const double d = ((xi_c-xi_th)*Aprimexi_c-Axi_c)/pow(xi_c-xi_th,2);
            const double e = Aprimexi_c -2*((xi_c-xi_th)*Aprimexi_c-Axi_c)/(xi_c-xi_th);

            const double B = d * pow(x - xi_th,2) + e * (x - xi_th);
            return B + R + BRMatch;
        }
        else
        {
            return  (cc[0][0]*exp(cc[0][1]*t) + cc[0][2]) * pow(s,0.08) * pow(x,-1.08 - 0.5*t) * (t/(t - 0.05)) //ppp
                   +(cc[1][0]*exp(cc[1][1]*t) + cc[1][2]) * pow(s,-0.4525) * pow(x,-1.6125 -0.5*t)  //ppr
                   +(cc[2][0]*exp(cc[2][1]*t) + cc[2][2]) * pow(s,0.08)     * pow(x,-0.015 - 1.86*t)    //rrp
                   +(cc[3][0]*exp(cc[3][1]*t) + cc[3][2]) * pow(s,-0.4525) * pow(x,-0.5475 - 1.86*t)    //rrr
                   +1.14591559 * pow(3.52142 - 2.79*t,2) * pow(x,1 - 1.86 * (-0.0182185 + t)) * (31.79*pow(s*x,-0.4525) + 13.63 *pow(s*x,0.0808))   //pion
                   * (-t) * pow(1 - 1.40845*t,-4) * pow(3.52142 -t,-2) * pow(-0.0182185 + t,-2);    //form factor
        }

    }
    else
    {
        // t less than or equal to -1.15
        if(x > xi_th && x <= xi_c)
        {
            const double Axi_c = (cc[0][0]*exp(cc[0][1]*t) + cc[0][2]) * pow(s,0.08) * pow(xi_c,-1.08 - 0.5*t) * (t/(t - 0.05)) //ppp
                                 *(1 + 0.4597*(-t-1.15) + 5.7575 * pow((-t-1.15),2))
                                 +(cc[1][0]*exp(cc[1][1]*t) + cc[1][2]) * pow(s,-0.4525) * pow(xi_c,-1.6125 -0.5*t) //ppr
                                 +(cc[2][0]*exp(cc[2][1]*t) + cc[2][2]) * pow(s,0.08) * pow(xi_c,-0.015 - 1.86*t)   //rrp
                                 +(cc[3][0]*exp(cc[3][1]*t) + cc[3][2]) * pow(s,-0.4525) * pow(xi_c,-0.5475 - 1.86*t)   //rrr
                                 +1.14591559 * pow(3.52142 - 2.79*t,2) * pow(xi_c,1 - 1.86 * (-0.0182185 + t)) * (31.79*pow(s*xi_c,-0.4525) + 13.63 *pow(s*xi_c,0.0808))    //pion
                                 * (-t) * pow(1 - 1.40845*t,-4) * pow(3.52142 -t,-2) * pow(-0.0182185 + t,-2);  //form factor


            const double Aprimexi_c = (cc[0][0]*exp(cc[0][1]*t) + cc[0][2]) * pow(s,0.08) * (-1.08 - 0.5*t) *pow(xi_c,-2.08 - 0.5*t) * (t/(t - 0.05))   //ppp
                                      *(1 + 0.4597*(-t-1.15) + 5.7575 * pow((-t-1.15),2))
                                      +(cc[1][0]*exp(cc[1][1]*t) + cc[1][2]) * pow(s,-0.4525) * (-1.6125 - 0.5*t) *pow(xi_c,-2.6125 -0.5*t) //ppr
                                      +(cc[2][0]*exp(cc[2][1]*t) + cc[2][2]) * pow(s,0.08) * (-0.015 - 1.86*t) *pow(xi_c,-1.015 - 1.86*t)   //rrp
                                      +(cc[3][0]*exp(cc[3][1]*t) + cc[3][2]) * pow(s,-0.4525) * (-0.5475 - 1.86*t) * pow(xi_c,-1.5475 - 1.86*t) //rrr
                                      +1.14591559 * pow(3.52142 - 2.79*t,2) * fabs(t) * pow(1 - 1.40845*t,-4) * pow(3.52142 -t,-2) * pow(-0.0182185 + t,-2)
                                      * ((1 - 1.86 * (-0.0182185 + t)) *pow(xi_c,-1.86 * (-0.0182185 + t)) * (31.79*pow(s*xi_c,-0.4525) + 13.63 *pow(s*xi_c,0.0808))
                                         + (pow(xi_c,1 - 1.86 * (-0.0182185 + t)) * (31.79*(-0.4525)*pow(s*xi_c,-1.4525)+13.63*0.0808*pow(s*xi_c,0.0808-1))));  //form factor

            const double d = ((xi_c-xi_th)*Aprimexi_c-Axi_c)/pow(xi_c-xi_th,2);
            const double e = Aprimexi_c -2*((xi_c-xi_th)*Aprimexi_c-Axi_c)/(xi_c-xi_th);

            const double B = d * pow(x - xi_th,2) + e * (x - xi_th);
            return B + R + BRMatch;
        }
        else
        {
            return (cc[0][0]*exp(cc[0][1]*t) + cc[0][2]) * pow(s,0.08) * pow(x,-1.08 - 0.5*t) * (t/(t - 0.05))  //ppp
                   *(1 + 0.4597*(-t-1.15) + 5.7575 * pow((-t-1.15),2))
                   +(cc[1][0]*exp(cc[1][1]*t) + cc[1][2]) * pow(s,-0.4525) * pow(x,-1.6125 -0.5*t)  //ppr
                   +(cc[2][0]*exp(cc[2][1]*t) + cc[2][2]) * pow(s,0.08)     * pow(x,-0.015 - 1.86*t)    //rrp
                   +(cc[3][0]*exp(cc[3][1]*t) + cc[3][2]) * pow(s,-0.4525) * pow(x,-0.5475 - 1.86*t)    //rrr
                   +1.14591559 * pow(3.52142 - 2.79*t,2) * pow(x,1 - 1.86 * (-0.0182185 + t)) * (31.79*pow(s*x,-0.4525) + 13.63 *pow(s*x,0.0808))   //pion
                   * (-t) * pow(1 - 1.40845*t,-4) * pow(3.52142 -t,-2) * pow(-0.0182185 + t,-2);    //form factor
        }

    }
}
}//End namespace ParticleTracking
