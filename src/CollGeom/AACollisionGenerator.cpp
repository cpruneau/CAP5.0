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
#include "AACollisionGenerator.hpp"
#include "TDatabasePDG.h"
using CAP::AACollisionGenerator;

ClassImp(AACollisionGenerator);

AACollisionGenerator::AACollisionGenerator(const String * _name,
                                           const Configuration & _configuration)
:
EventTask(_name, _configuration),
nnCollisionGenerator(NucleonNucleonCollisionGenerator::getDefaultNNCollisionGenerator() )
{
  nnCollisionGenerator = new NucleonNucleonCollisionGenerator("NN",_configuration);
  appendClassName("AACollisionGenerator");
}

void AACollisionGenerator::configure()
{
  EventTask::configure();
}

void AACollisionGenerator::setDefaultConfiguration()
{
  addParameter("UseParticles",    true);
  addParameter("EventsUseStream0", true);
}

void AACollisionGenerator::initialize()
{
  
  if (reportStart(__FUNCTION__))
    ;
  Task::initialize();
  nnCollisionGenerator->initialize();
}

void AACollisionGenerator::createEvent()
{
  
  if (reportStart(__FUNCTION__))
    ;
  incrementTaskExecuted();
  unsigned int nParticles = eventStreams[0]->getNParticles()
  for (unsigned int iParticle = 0; iParticle < nParticles; iParticle++)
  {
  Particle * particle = event->getParticleAt(iParticle)
  if (particle->isInteraction() && particle->isLive() )
    {
    nnCollisionGenerator->generate(particle);
    particle->setLive(false); // the interaction has been generated
    }
  }
}

void AACollisionGenerator::finalize()
{
  
  if (reportStart(__FUNCTION__))
    ;
  Task::finalize();
  nnCollisionGenerator->printStatistics();
}

void AACollisionGenerator::setNucleonNucleonCollisionGenerator(NucleonNucleonCollisionGenerator  * _nnCollisionGenerator)
{
  if (!_nnCollisionGenerator)
    {
    if (reportFatal()) cout << "No nnCollisionGenerator available (nnCollisionGenerator==nullptr)" <<endl;
    throw TaskException("!_nnCollisionGenerator","AACollisionGenerator::setNucleonNucleonCollisionGenerator(NucleonNucleonCollisionGenerator  *)");
    }
  nnCollisionGenerator = _nnCollisionGenerator;
}
