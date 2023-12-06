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
#include "EventPlaneRandomizerTask.hpp"
using CAP::EventPlaneRandomizerTask;

ClassImp(EventPlaneRandomizerTask);

EventPlaneRandomizerTask::EventPlaneRandomizerTask(const String & _name,
                                                   const Configuration & _configuration)
:
EventTask(_name,_configuration)
{
  appendClassName("EventPlaneRandomizerTask");
}

void EventPlaneRandomizerTask::setDefaultConfiguration()
{
  EventTask::setDefaultConfiguration();
  addParameter("EventsUseStream0", true);
}

void EventPlaneRandomizerTask::createEvent()
{
  double eventAngle= CAP::Math::twoPi() * gRandom->Rndm();
  Event * event = eventStreams[0];
  unsigned int nParticles = event->getNParticles();
  for (unsigned int iParticle = 0; iParticle < nParticles; iParticle++)
    {
    Particle * particle = event->getParticleAt(iParticle);
    particle->getPosition().RotateZ(eventAngle);
    particle->getMomentum().RotateZ(eventAngle);
    }
}

