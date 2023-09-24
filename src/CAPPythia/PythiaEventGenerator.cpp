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

#include "PythiaEventGenerator.hpp"
using CAP::PythiaEventGenerator;

ClassImp(PythiaEventGenerator);

PythiaEventGenerator::PythiaEventGenerator(const String & _name,
                                           const Configuration & _configuration)
:
EventTask(_name, _configuration),
pythia(nullptr)
{
  appendClassName("PythiaEventGenerator");
}


void PythiaEventGenerator::setDefaultConfiguration()
{
  EventTask::setDefaultConfiguration();
  addParameter("EventsUseStream0",true);
  addParameter("EventsUseStream1",false);
  addParameter("EventsUseStream2",false);
  addParameter("EventsUseStream3",false);
  addParameter("EventsCreate",     true);
  addParameter("Print:Banner",     false);
  addParameter("Print:Statistics", false);
  addParameter("Print:NEvents",    0);
  addParameter("Beams:idA",        2212);
  addParameter("Beams:idB",        2212);
  addParameter("Beams:frameType",  2);
  addParameter("Beams:eCM",        2700.0);
  addParameter("Beams:eA",         1350.0);
  addParameter("Beams:eB",         1350.0);
  addParameter("SetSeed",          true);
  addParameter("SeedValue",        121211);
  addParameter("UseQCDCR",         true);
  addParameter("UseRopes",         false);
  addParameter("UseShoving",       false);
  addParameter("xmlInputPath",     TString(""));

  for (int k=0; k<30; k++)
    {
    String key = "Option"; key += k;
    addParameter(key, TString("none"));
    }
  // printConfiguration(cout);
}

void PythiaEventGenerator::configure()
{
  EventTask::configure();
  if (reportDebug(__FUNCTION__)) printConfiguration(cout);
}



//!
//! Initialize generator
//! pythia->Initialize(2212 /* p */, 2212 /* p */, 14000. /* GeV */);
//!
void PythiaEventGenerator::initialize()
{
  //;
  //EventTask::configure();
  EventTask::initialize();
  pythia = new Pythia8::Pythia(getValueString("xmlInputPath").Data(), getValueBool("Print:Banner"));
  pythia->settings.mode("Beams:idA",       getValueInt(   "Beams:idA"));
  pythia->settings.mode("Beams:idB",       getValueInt(   "Beams:idB"));
  pythia->settings.mode("Beams:frameType", getValueInt(   "Beams:frameType"));
  switch (getValueInt("Beams:frameType"))
    {
      default:
      case 1:
      pythia->settings.parm("Beams:eCM",     getValueDouble("Beams:eCM"));
      break;
      case 2:
      pythia->settings.parm("Beams:eA",      getValueDouble("Beams:eA"));
      pythia->settings.parm("Beams:eB",      getValueDouble("Beams:eB"));
      break;
    }


  if (getValueDouble("SetSeed"))
    {
    String  seedValueString = "Random:seed = ";
    seedValueString += getValueLong("SeedValue");
    pythia->readString("Random:setSeed = on");
    pythia->readString(seedValueString.Data());
    printItem("Pythia:Random:setSeed","ON");
    printItem("Pythia:Random:SeedValue",seedValueString);
    }
  for (int k=0; k<30; k++)
    {
    String key = "Option"; key += k;
    String  value = getValueString(key);
    if (!value.Contains("none") )
      {
      TString s = "Pythia:"; s+=key;
      printItem(s,value);
      pythia->readString(value.Data());
      }
    }
  if(getValueBool(  "UseQCDCR"))
    {
    printItem("Pythia:UseQCDCR","ON");
    pythia->readString("MultiPartonInteractions:pT0Ref = 2.15");
    pythia->readString("BeamRemnants:remnantMode = 1");
    pythia->readString("BeamRemnants:saturation = 5");
    pythia->readString("ColourReconnection:mode = 1");
    pythia->readString("ColourReconnection:allowDoubleJunRem = off");
    pythia->readString("ColourReconnection:m0 = 0.3");
    pythia->readString("ColourReconnection:allowJunctions = on");
    pythia->readString("ColourReconnection:junctionCorrection = 1.2");
    pythia->readString("ColourReconnection:timeDilationMode = 2");
    pythia->readString("ColourReconnection:timeDilationPar = 0.18");
    if(!getValueBool("UseRopes")) pythia->readString("Ropewalk:RopeHadronization = off");
    }
  if(getValueBool("UseQCDCR") && getValueBool(  "UseRopes"))
    {
    printItem("Pythia:UseQCDCR","ON");
    printItem("Pythia:UseRopes","ON");
    pythia->readString("Ropewalk:RopeHadronization = on");
    pythia->readString("Ropewalk:doShoving = on");
    pythia->readString("Ropewalk:doFlavour = on");
    pythia->readString("Ropewalk:tInit = 1.5");
    pythia->readString("Ropewalk:deltat = 0.05");
    pythia->readString("Ropewalk:tShove = 0.1");
    pythia->readString("Ropewalk:gAmplitude = 0.");// # Set shoving strength to 0 explicitly
    pythia->readString("Ropewalk:r0 = 0.5");
    pythia->readString("Ropewalk:m0 = 0.2");
    pythia->readString("Ropewalk:beta = 0.1");
    pythia->readString("PartonVertex:setVertex = on");
    pythia->readString("PartonVertex:protonRadius = 0.7");
    pythia->readString("PartonVertex:emissionWidth = 0.1");
  }
  if(!getValueBool("UseQCDCR") && getValueBool(  "UseRopes"))
    {
    throw TaskException("ropes w/o the necessary junctions! Flip kQCDCR=kTRUE","PythiaEventGenerator::initialize()");
    }

  if(getValueBool("UseShoving"))
    {
    printItem("Pythia:UseShoving","ON");

    pythia->readString("Ropewalk:RopeHadronization = on");
    pythia->readString("Ropewalk:doShoving = on");
    pythia->readString("Ropewalk:doFlavour = off");
    pythia->readString("Ropewalk:tInit = 1.5");
    pythia->readString("Ropewalk:rCutOff = 10.0");
    pythia->readString("Ropewalk:limitMom =  on");
    pythia->readString("Ropewalk:pTcut = 2.0");
    pythia->readString("Ropewalk:deltat = 0.1");
    pythia->readString("Ropewalk:deltay = 0.1");
    pythia->readString("Ropewalk:tShove = 1.");
    pythia->readString("Ropewalk:deltat = 0.1");
    pythia->readString("Ropewalk:gAmplitude = 10.0");
    pythia->readString("Ropewalk:gExponent = 1.0");
    pythia->readString("Ropewalk:r0 = 0.41");
    pythia->readString("Ropewalk:m0 = 0.2");
    pythia->readString("PartonVertex:setVertex = on");
    pythia->readString("PartonVertex:protonRadius = 0.7");
    pythia->readString("PartonVertex:emissionWidth = 0.1");
    }
  pythia->init();
//  if (reportDebug(__FUNCTION__))
//    {
//    pythia->settings.listAll();
//    pythia->settings.listChanged();
//    }
  if (reportEnd(__FUNCTION__))
    ;
}

void PythiaEventGenerator::createEvent()
{

  incrementTaskExecuted();
  Event & event = *eventStreams[0];
  EventProperties & eventProperties = * event.getEventProperties();
  Particle * interaction;
  event.reset();
  particleFactory->reset();
  interaction = particleFactory->getNextObject();
  interaction->reset();
  interaction->setType( ParticleType::getInteractionType());
  interaction->setXYZT(0.0, 0.0, 0.0, 0.0);
  event.add(interaction);
  event.setNucleusA(1.0,1.0);
  event.setNucleusB(1.0,1.0);
  pythia->next();

//  int ioff = 0;
  int nParticleToCopy   = pythia->event.size();
  //printItem("nParticleToCopy",nParticleToCopy);

  if (pythia->event[0].id() == 90)
    {
    nParticleToCopy--;
//     ioff = -1;
    }

//  if (reportDebug(__FUNCTION__)) cout << "nParticleToCopy : " << nParticleToCopy << endl;

  for (int i = 1; i <= nParticleToCopy; i++)
    {

//    int ist = tracks_fStatusCode[iParticle];
//    if (ist <= 0) continue;
    int pdg = pythia->event[i].id();
    if (abs(pdg)<40  || pdg==2101) continue; // skip quarks,  leptons, and photons
    if (!pythia->event[i].isFinal()) continue;
    //if (reportDebug(__FUNCTION__))   cout << "     pdg:" << pdg << endl;
    ParticleType * particleType = ParticleDb::getDefaultParticleDb()->findPdgCode(pdg);
    if (particleType==nullptr)
      {
      if (reportDebug(__FUNCTION__)) cout << "     is an unknown code" << endl;
      continue;
      }
    //if (particleType->isPhoton()) continue;

    Particle & particle = *particleFactory->getNextObject();
    particle.setType(particleType);
    particle.setLive(1);
//    particle.setParents(pythia->event[i].mother1()   + ioff,
//                        pythia->event[i].mother2()   + ioff);
//
////    setParents(Particle * parent1, Particle * parent2);
//
//    particle.setChildren(pythia->event[i].daughter1() + ioff,
//                         pythia->event[i].daughter2() + ioff)
    // momentum-energy units are  [GeV/c]
    // positions are in [mm], time in [mm/c]
    particle.setPxPyPzE(pythia->event[i].px(),pythia->event[i].py(),pythia->event[i].pz(),pythia->event[i].e());
    particle.setXYZT(pythia->event[i].xProd(),pythia->event[i].yProd(),pythia->event[i].zProd(),pythia->event[i].tProd());
    //incrementParticlesAccepted();
    //if (reportDebug(__FUNCTION__)) cout << "   Add Particle to the event" << endl;
    event.add(&particle);
    }
  int multiplicity = event.getParticleCount();
//  if (reportDebug(__FUNCTION__)) cout << "multiplicity " << multiplicity << endl;

  eventProperties.zProjectile        = 1;     // atomic number projectile
  eventProperties.aProjectile        = 1;     // mass number projectile
  eventProperties.nPartProjectile    = 1;     // number of participants  projectile
  eventProperties.zTarget            = 1;     // atomic number target
  eventProperties.aTarget            = 1;     // mass number target
  eventProperties.nPartTarget        = 1;     // number of participants  target
  eventProperties.nParticipantsTotal = 2;     // total number of participants
  eventProperties.nBinaryTotal       = 1;     // total number of binary collisions
  eventProperties.impactParameter    = -99999; // nucleus-nucleus center distance in fm
  eventProperties.fractionalXSection = -99999; // fraction cross section value
  eventProperties.refMultiplicity    = multiplicity;
  eventProperties.particlesCounted   = -1;
  eventProperties.particlesAccepted  = multiplicity;
  incrementNEventsAccepted(0);
  //if (reportInfo(__FUNCTION__)) eventProperties.printProperties(cout);
  //if (reportInfo(__FUNCTION__)) cout << "Pythia Execute Completed" << endl;
}

void PythiaEventGenerator::finalize()
{
  if (reportInfo(__FUNCTION__) && getValueBool("Print:Statistics"))
    {
    cout << endl;
    pythia->stat();
    cout << endl;
    }
  delete pythia;
  if (reportEnd(__FUNCTION__))
    ;
}
