/*
* Merlin C++ Class Library for Charged Particle Accelerator Simulations
*
* Class library version 2.0 (2000)
*
* file Merlin\BeamDynamics\ParticleTracking\ParticleBunchUtilities.h
* last modified 30/04/01 12:28:48
*/

#ifndef _h_ParticleBunchUtilities
#define _h_ParticleBunchUtilities 1

#include "merlin_config.h"
#include "ParticleBunch.h"

#include <vector>

namespace ParticleTracking
{

/**
* Sort the bunch in ascending z (ct) order, and return
* a vector of iterators which point to the equal-spaced
* bin boundaries defines by zmin to zmax in steps of dz
*
* Returns the number of particles removed from tails
* i.e. z<zmin || z>=zmax
*/
size_t ParticleBinList(ParticleBunch& bunch, double zmin, double zmax, size_t nbins,
                       std::vector<ParticleBunch::iterator>& pbins,
                       vector<double>& hd, vector<double>& hdp, vector<double>* c = nullptr);

/**
* Return the distribution of particles for the coordinate u.
* The distribution is returned as a binned histogram, with
* bin boundaries defined by umin to umax in steps of du.
* If truncate is true, then particles outside the range (umin,umax)
* are removed from bunch. If normalise is true, the histogram
* values are scaled to give a probability distribution with the
* property Sum{h_i*du} = 1.
*/
size_t ParticleBunchDistribution(ParticleBunch& bunch, PScoord u,
                                 double umin, double umax, double du, std::vector<double>& bins,
                                 bool normalise, bool truncate);

}

#endif
