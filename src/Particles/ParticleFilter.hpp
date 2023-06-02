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
#ifndef CAP__ParticleFilter
#define CAP__ParticleFilter
#include "Particle.hpp"
#include "Filter.hpp"

namespace CAP
{

class ParticleFilter : public Filter<Particle>
{
public:

  ParticleFilter();
  ParticleFilter(const ParticleFilter & otherFilter);
  ParticleFilter & operator=(const ParticleFilter & otherFilter);
  virtual ~ParticleFilter() {}
  virtual bool accept(const Particle & particle);


 
  ClassDef(ParticleFilter,0)
};

}

#endif /* CAP__ParticleFilter */

