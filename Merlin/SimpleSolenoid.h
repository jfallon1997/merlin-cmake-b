/*
 * Merlin C++ Class Library for Charged Particle Accelerator Simulations
 *
 * Class library version 2.0 (1999)
 *
 * file Merlin\AcceleratorModel\StdComponent\SimpleSolenoid.h
 * last modified 10/12/01 14:23:49
 */

#ifndef SimpleSolenoid_h
#define SimpleSolenoid_h 1

#include "merlin_config.h"

#include "TemplateComponents.h"
#include "RectangularGeometry.h"
#include "BzField.h"


typedef TAccCompGF< RectangularGeometry , BzField  > SimpleSolenoid;

#endif
