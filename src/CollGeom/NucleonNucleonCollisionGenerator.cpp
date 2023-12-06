/* **********************************************************************
 * Copyright (C) 2019-2022, Claude Pruneau, Victor Gonzalez, Sumit Basu
 * All rights reserved.
 *
 * Based on the ROOT package and environment
 *
 * For the licensing terms see LICENSE.
 *
 * Author: Claude Pruneau,   04/01/2022
 *
 * *********************************************************************/
#include "NucleonNucleonCollisionGenerator.hpp"

ClassImp(CAP::NucleonNucleonCollisionGenerator);

namespace CAP
{


NucleonNucleonCollisionGenerator::NucleonNucleonCollisionGenerator(const String & _name,
                                                                   const Configuration & _configuration)
:
EventTask(_name, _configuration)
{
  appendClassName("NucleonNucleonCollisionGenerator");
}

void NucleonNucleonCollisionGenerator::generate(Particle * parent)
{
}

}  // namespace CAP
