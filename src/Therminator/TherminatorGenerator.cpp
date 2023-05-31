/********************************************************************************
 *                                                                              *
 *             THERMINATOR 2: THERampl heavy-IoN generATOR 2                     *
 *                                                                              *
 * Version:                                                                     *
 *      Release, 2.0.3, 1 February 2011                                         *
 *                                                                              *
 * Authors:                                                                     *
 *      Mikolaj Chojnacki   (Mikolaj.Chojnacki@ifj.edu.pl)                      *
 *      Adam Kisiel         (kisiel@if.pw.edu.pl)                               *
 *      Wojciech Broniowski (Wojciech.Broniowski@ifj.edu.pl)                    *
 *      Wojciech Florkowski (Wojciech.Florkowski@ifj.edu.pl)                    *
 *                                                                              *
 * Project homepage:                                                            *
 *      http://therminator2.ifj.edu.pl/                                         *
 *                                                                              *
 * For the detailed description of the program and further references           *
 * to the description of the model please refer to                              *
 * http://arxiv.org/abs/1102.0273                                               *
 *                                                                              *
 * This code can be freely used and redistributed. However if you decide to     *
 * ampke modifications to the code, please, inform the authors.                  *
 * Any publication of results obtained using this code must include the         *
 * reference to arXiv:1102.0273 and the published version of it, when           *
 * available.                                                                   *
 *                                                                              *
 ********************************************************************************/
#include "TherminatorGenerator.hpp"
#include "Model_BWA.hpp"
#include "Model_BlastWave.hpp"
#include "Model_KrakowSFO.hpp"
#include "Model_Lhyquid2DBI.hpp"
#include "Model_Lhyquid3D.hpp"
#include "Model_HadronGas.hpp"
#include "Hypersurface_Lhyquid2D.hpp"
#include "Hypersurface_Lhyquid3D.hpp"

using CAP::Event;
ClassImp(TherminatorGenerator);
//  if      (modelType == "KrakowSFO")    { sModel = 0;  tModelINI += "krakow.ini";  }
//  else if (modelType == "BlastWave")    { sModel = 1;  tModelINI += "blastwave.ini";  }
//  else if (tMomodelTypedel == "BWAVT")      { sModel = 2;  tModelINI += "bwa.ini";    }
//  else if (modelType == "BWAVTDelay")    { sModel = 3;  tModelINI += "bwa.ini";    }
//  else if (modelType == "BWAVLinear")    { sModel = 4;  tModelINI += "bwa.ini";    }
//  else if (modelType == "BWAVLinearDelay")  { sModel = 5;  tModelINI += "bwa.ini";    }
//  else if (modelType == "BWAVLinearForamption")  { sModel = 6;  tModelINI += "bwa.ini";    }
//  else if (modelType == "Lhyquid3D")    { sModel = 10; tModelINI += "lhyquid3d.ini";  }
//  else if (modelType == "Lhyquid2DBI")    { sModel = 11; tModelINI += "lhyquid2dbi.ini";  }


TherminatorGenerator::TherminatorGenerator(const TString & _name,
                                           const Configuration & _configuration)
:
EventTask::EventTask(_name, _configuration),
modelType(0),
modelSubType(0),
modelInputPath(),
modelInputFile(),
modelOutputPath(),
modelOutputFile(),
hypersurfaceInputPath(),
hypersurfaceInputFile(),
hypersurfaceOutputPath(),
hypersurfaceOutputFile(),
multiplicitiesImport(false),
multiplicitiesExport(false),
multiplicitiesCreate(false),
multiplicitiesFluctType(0),
multiplicitiesInputPath(),
multiplicitiesInputFile(),
multiplicitiesOutputPath(),
multiplicitiesOutputFile(),
multiplicitiesFractionMin(0.5),
multiplicitiesFractionMax(1.0),
multiplicitiesFractionRange(0.5),
disablePhotons(true),
nSamplesIntegration(10000),
modelOnlyBackFlow(0),
decayRescaleChannels(0),
decayDisabled(false),
decayDisable2Prong(false),
decayDisable3Prong(false),
particleDecayer(),
model(nullptr),
averageMultiplicities(),
eventMultiplicities()
{
  appendClassName("TherminatorGenerator");
}

void TherminatorGenerator::setDefaultConfiguration()
{
  EventTask::setDefaultConfiguration();
  // Therminator parameters
  addParameter( "ModelType",                    modelType);
  addParameter( "ModelSubType",                 modelSubType);
  addParameter( "ModelInputPath",               modelInputPath);
  addParameter( "ModelInputFile",               modelInputFile);
  addParameter( "ModelOutputPath",              modelOutputPath);
  addParameter( "ModelOutputFile",              modelOutputFile);
  addParameter( "HypersurfaceInputPath",        hypersurfaceInputPath);
  addParameter( "HypersurfaceInputFile",        hypersurfaceInputFile);
  addParameter( "HypersurfaceOutputPath",       hypersurfaceOutputPath);
  addParameter( "HypersurfaceOutputFile",       hypersurfaceOutputFile);
  addParameter( "MultiplicitiesImport",         multiplicitiesImport);
  addParameter( "MultiplicitiesExport",         multiplicitiesExport);
  addParameter( "MultiplicitiesCreate",         multiplicitiesCreate);
  addParameter( "MultiplicitiesFluctType",      multiplicitiesFluctType);
  addParameter( "MultiplicitiesInputPath",      multiplicitiesInputPath);
  addParameter( "MultiplicitiesInputFile",      multiplicitiesInputFile);
  addParameter( "MultiplicitiesOutputPath",     multiplicitiesOutputPath);
  addParameter( "MultiplicitiesOutputFile",     multiplicitiesOutputFile);
  addParameter( "MultiplicitiesFractionMin",    multiplicitiesFractionMin);
  addParameter( "MultiplicitiesFractionMax",    multiplicitiesFractionMax);
  addParameter( "DisablePhotons",               disablePhotons);
  addParameter( "nSamplesIntegration",          nSamplesIntegration);
  addParameter( "ModelOnlyBackFlow",            modelOnlyBackFlow);
  addParameter( "DecayRescaleChannels",         decayRescaleChannels);
  addParameter( "DecayDisabled",                decayDisabled);
  addParameter( "DecayDisable3Prong",           decayDisable3Prong);
  addParameter( "DecayDisable2Prong",           decayDisable2Prong);
  addParameter( "DecayNoWeakDecay",             decayNoWeakDecay);
  addParameter( "DecayStoreDecayedParts",       decayStoreDecayedParts);
}

void TherminatorGenerator::configure()
{
  EventTask::configure();
  modelType                   = getValueInt(    "ModelType");
  modelSubType                = getValueInt(    "ModelSubType");
  modelInputPath              = getValueString( "ModelInputPath");
  modelInputFile              = getValueString( "ModelInputFile");
  modelOutputPath             = getValueString( "ModelOutputPath");
  modelOutputFile             = getValueString( "ModelOutputFile");
  hypersurfaceInputPath       = getValueString( "HypersurfaceInputPath");
  hypersurfaceInputFile       = getValueString( "HypersurfaceInputFile");
  hypersurfaceOutputPath      = getValueString( "HypersurfaceOutputPath");
  hypersurfaceOutputFile      = getValueString( "HypersurfaceOutputFile");
  multiplicitiesImport        = getValueBool(   "MultiplicitiesImport");
  multiplicitiesExport        = getValueBool(   "MultiplicitiesExport");
  multiplicitiesCreate        = getValueBool(   "MultiplicitiesCreate");
  multiplicitiesFluctType     = getValueInt(    "MultiplicitiesFluctType");
  multiplicitiesInputPath     = getValueString( "MultiplicitiesInputPath");
  multiplicitiesInputFile     = getValueString( "MultiplicitiesInputFile");
  multiplicitiesOutputPath    = getValueString( "MultiplicitiesOutputPath");
  multiplicitiesOutputFile    = getValueString( "MultiplicitiesOutputFile");
  multiplicitiesFractionMin   = getValueDouble( "MultiplicitiesFractionMin");
  multiplicitiesFractionMax   = getValueDouble( "MultiplicitiesFractionMax");
  multiplicitiesFractionRange = multiplicitiesFractionMax - multiplicitiesFractionMin;
  disablePhotons              = getValueBool(   "DisablePhotons");
  nSamplesIntegration         = getValueInt(    "nSamplesIntegration");
  modelOnlyBackFlow           = getValueBool(   "ModelOnlyBackFlow");
  decayRescaleChannels        = getValueBool(   "DecayRescaleChannels");
  decayDisabled               = getValueBool(   "DecayDisabled");
  decayDisable3Prong          = getValueBool(   "DecayDisable3Prong");
  decayDisable2Prong          = getValueBool(   "DecayDisable2Prong");
  decayNoWeakDecay            = getValueBool(   "DecayNoWeakDecay");
  decayStoreDecayedParts      = getValueBool(   "DecayStoreDecayedParts");

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem( "ModelType",                   modelType);
    printItem( "ModelSubType",                modelSubType);
    printItem( "ModelInputPath",              modelInputPath);
    printItem( "ModelInputFile",              modelInputFile);
    printItem( "ModelOutputPath",             modelOutputPath);
    printItem( "ModelOutputFile",             modelOutputFile);
    printItem( "HypersurfaceInputPath",       hypersurfaceInputPath);
    printItem( "HypersurfaceInputFile",       hypersurfaceInputFile);
    printItem( "HypersurfaceOutputPath",      hypersurfaceOutputPath);
    printItem( "HypersurfaceOutputFile",      hypersurfaceOutputFile);
    printItem( "MultiplicitiesImport",        multiplicitiesImport);
    printItem( "MultiplicitiesExport",        multiplicitiesExport);
    printItem( "MultiplicitiesCreate",        multiplicitiesCreate);
    printItem( "MultiplicitiesFluctType",     multiplicitiesFluctType);
    printItem( "MultiplicitiesInputPath",     multiplicitiesInputPath);
    printItem( "MultiplicitiesInputFile",     multiplicitiesInputFile);
    printItem( "MultiplicitiesOutputPath",    multiplicitiesOutputPath);
    printItem( "MultiplicitiesOutputFile",    multiplicitiesOutputFile);
    printItem( "MultiplicitiesFractionMin",   multiplicitiesFractionMin);
    printItem( "MultiplicitiesFractionMax",   multiplicitiesFractionMax);
    printItem( "MultiplicitiesFractionRange", multiplicitiesFractionRange);
    printItem( "DisablePhotons",              disablePhotons);
    printItem( "nSamplesIntegration",         nSamplesIntegration);
    printItem( "ModelOnlyBackFlow",           modelOnlyBackFlow);
    printItem( "DecayRescaleChannels",        decayRescaleChannels);
    printItem( "DecayDisabled",               decayDisabled);
    printItem( "DecayDisable3Prong",          decayDisable3Prong);
    printItem( "DecayDisable2Prong",          decayDisable2Prong);
    printItem( "DecayNoWeakDecay",            decayNoWeakDecay);
    printItem( "DecayStoreDecayedParts",      decayStoreDecayedParts);
    cout << endl;
    }
}

// void TherminatorGenerator::convertEventCAPToNative()
//{
//
// }
//
//
// void TherminatorGenerator::convertEventNativeToCAP()
//{
//
// }
//
//
//
// void TherminatorGenerator::exportEventNative()
//{
//
// }

// void TherminatorGenerator::resetEventNative()
//{
//
// }
//
//
//
// void TherminatorGenerator::clearEventNative()
//{
//
// }

void TherminatorGenerator::importEvent() {}
void TherminatorGenerator::exportEvent() {}
void TherminatorGenerator::printEvent() {}

void TherminatorGenerator::createEvent()
{
  Event & event = *eventStreams[0];
  event.reset();
  particleFactory->reset();
  // generate multiplicities for this event
  unsigned int nTypes = particleDb->getParticleTypeCount();
  if (averageMultiplicities.size() < 1)
    {
    if (reportError(__FUNCTION__))
      {
      cout << " Array averageMultiplicities is not initialized." << endl;
      throw TaskException("averageMultiplicities.size() < 1","TherminatorGenerator::createEvent()");
      }
    }

  double multiplicitiesFraction = 1.0;
  if (multiplicitiesFractionRange>0 || multiplicitiesFractionMin<1)
    {
    multiplicitiesFraction = multiplicitiesFractionMin + multiplicitiesFractionRange*gRandom->Rndm();
    }

  switch (multiplicitiesFluctType)
    {
      case 0:
      // Poisson fluctuations
      for (unsigned int iType=0; iType<nTypes; iType++)
        {
        double mean  = multiplicitiesFraction * averageMultiplicities[iType].multiplicity;
        eventMultiplicities[iType] = gRandom->Poisson(mean);
        }
      break;
      case 1:
      // Negative Binomial  fluctuations
      for (unsigned int iType=0; iType<nTypes; iType++)
        {
        eventMultiplicities[iType] = 0; // HOW?
        }
      break;
      default:
      case 2:
      // Gaussian fluctuations
      for (unsigned int iType=0; iType<nTypes; iType++)
        {
        double mean  = multiplicitiesFraction * averageMultiplicities[iType].multiplicity;
        double sigma = sqrt(mean);
        eventMultiplicities[iType] = TMath::Max(0, int(gRandom->Gaus(mean,sigma)));
        }
      break;
      case 3:
      // Poisson or Gaussian fluctuations
      for (unsigned int iType=0; iType<nTypes; iType++)
        {
        double mean  = multiplicitiesFraction * averageMultiplicities[iType].multiplicity;
        if (mean>20)
          {
          double sigma = sqrt(mean);
          eventMultiplicities[iType] = TMath::Max(0, int(gRandom->Gaus(mean,sigma)));
          }
        else
          {
          eventMultiplicities[iType] = TMath::Max(0, int(gRandom->Poisson(mean)));
          }
        }
    }

  // generate "m" particles of each specicies

  int      multiplicity;
  double   maxIntegrand;
  double   value;
  double   valueTest;
  CAP::Factory<Particle> * factory = Particle::getFactory();
  for (unsigned int iType=0; iType<nTypes; iType++)
    {
    ParticleType * particleType = particleDb->getParticleType(iType);
    if (particleType->isPhoton() && disablePhotons) continue;
    maxIntegrand = averageMultiplicities[iType].integral;
    multiplicity = eventMultiplicities[iType];
    //    if (reportInfo(__FUNCTION__))
    //      cout << " iType: " << iType << " Name:" << particleType->getName() << "  multiplicity:" << multiplicity << endl;
    int iParticle = 0;
    while (iParticle < multiplicity)
      {
      value     = model->getIntegrand(*particleType);
      valueTest = gRandom->Rndm() * maxIntegrand;
      //cout << "valueTest:" << valueTest << " value:" << value << " valueTest<value:" << (valueTest < value) << endl;
      if (valueTest<value)
        {
        Particle * particle = factory->getNextObject();
        particle->setType(particleType);
        particle->setLive(true);
        model->setParticlePX(*particle);
        iParticle++;
        if (particleType->isStable() || decayDisabled)
          {
          if (accept(*particle)) event.add(particle);
          }
        else
          decayParticle(event, *particle);
        }
      }
    }
}

//!
//!Accept the particle if any of the filter accepts it or if not filters were provided.
//!
bool TherminatorGenerator::accept(Particle & particle)
{
  if (particleFilters.size()<1) return true;
  for (int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ )
    {
    if (particleFilters[iParticleFilter]->accept(particle)) return true;
    }
  return false;
}

void TherminatorGenerator::decayParticle(Event & event, Particle & parent)
{
  ParticleType      & parentType = parent.getType();

//  cout << " parent type name: " <<  parentType.getName() << endl;
//  cout << " parent mass     : " <<  parentType.getMass() << endl;
//  cout << " parent width    : " <<  parentType.getWidth() << endl;
//  cout << " parent stable   : " <<  parentType.isStable() << endl;
//  cout << " parent n modes  : " <<  parentType.getNDecayModes() << endl;

  ParticleDecayMode & decayMode  = parentType.generateDecayMode();
  int nChildren = decayMode.getNChildren();
  if (nChildren<2)  return;
  if ((nChildren==2 && decayDisable2Prong) ||
      (nChildren==3 && decayDisable3Prong))
    {
    event.add(&parent);
    return;
    }
  LorentzVector & parentMomentum  = parent.getMomentum();
  LorentzVector & parentPosition  = parent.getPosition();
  switch (nChildren)
    {
      case 1:
      if (reportInfo(__FUNCTION__)) cout << "case 1  parentType==" << parent.getName() << endl;
      break;

      case 2:
      {
      //cout << "2-body decay" << endl;
      Particle * child1 = particleFactory->getNextObject();
      Particle * child2 = particleFactory->getNextObject();
      ParticleType  & childType1 = decayMode.getChildType(0); child1->setType(&childType1); child1->setLive(true);
      ParticleType  & childType2 = decayMode.getChildType(1); child2->setType(&childType2); child2->setLive(true);
      LorentzVector & p1 = child1->getMomentum();
      LorentzVector & r1 = child1->getPosition();
      LorentzVector & p2 = child2->getMomentum();
      LorentzVector & r2 = child2->getPosition();
      particleDecayer.decay2(parentType,
                             parentMomentum,
                             parentPosition,
                             childType1,p1,r1,
                             childType2,p2,r2);
      parent.setDecayed(true);
      if (decayStoreDecayedParts) event.add(&parent);
      if (child1->isStable() || decayDisabled)
        {
        if (accept(*child1)) event.add(child1);
        }
      else
        decayParticle(event, *child1);
      if (child2->isStable() || decayDisabled)
        {
        if (accept(*child2)) event.add(child2);
        }
      else
        decayParticle(event, *child2);
      break;
      }

      case 3:
      {
      //cout << "3-body decay" << endl;
      Particle * child1 = particleFactory->getNextObject();
      Particle * child2 = particleFactory->getNextObject();
      Particle * child3 = particleFactory->getNextObject();
      ParticleType  & childType1 = decayMode.getChildType(0); child1->setType(&childType1); child1->setLive(true);
      ParticleType  & childType2 = decayMode.getChildType(1); child2->setType(&childType2); child2->setLive(true);
      ParticleType  & childType3 = decayMode.getChildType(2); child3->setType(&childType3); child3->setLive(true);
      LorentzVector & p1 = child1->getMomentum();
      LorentzVector & r1 = child1->getPosition();
      LorentzVector & p2 = child2->getMomentum();
      LorentzVector & r2 = child2->getPosition();
      LorentzVector & p3 = child3->getMomentum();
      LorentzVector & r3 = child3->getPosition();
      particleDecayer.decay3(parentType,
                             parentMomentum,
                             parentPosition,
                             childType1,p1,r1,
                             childType2,p2,r2,
                             childType3,p3,r3);
      parent.setDecayed(true);
      if (decayStoreDecayedParts) event.add(&parent);
      if (child1->isStable() || decayDisabled)
        {
        if (accept(*child1)) event.add(child1);
        }
      else
        decayParticle(event, *child1);
      if (child2->isStable() || decayDisabled)
        {
        if (accept(*child2)) event.add(child2);
        }
      else
        decayParticle(event, *child2);
      if (child3->isStable() || decayDisabled)
        {
        if (accept(*child3)) event.add(child3);
        }
      else
        decayParticle(event, *child3);
      break;
      }

      default:
      case 4:
      {
      throw TaskException("4- or more body decay should not happen","TherminatorGenerator::createEvent()");

      //        Particle * child1 = particleFactory->getNextObject();
      //        Particle * child2 = particleFactory->getNextObject();
      //        Particle * child3 = particleFactory->getNextObject();
      //        Particle * child4 = particleFactory->getNextObject();
      //        ParticleType   & childType1 = decayMode.getChildType(0); child1->setType(&childType1); child1->setLive(true);
      //        ParticleType   & childType2 = decayMode.getChildType(1); child2->setType(&childType2); child2->setLive(true);
      //        ParticleType   & childType3 = decayMode.getChildType(2); child3->setType(&childType3); child3->setLive(true);
      //        ParticleType   & childType4 = decayMode.getChildType(3); child4->setType(&childType4); child4->setLive(true);
      //        LorentzVector & p1 = child1->getMomentum();
      //        LorentzVector & r1 = child1->getPosition();
      //        LorentzVector & p2 = child2->getMomentum();
      //        LorentzVector & r2 = child2->getPosition();
      //        LorentzVector & p3 = child3->getMomentum();
      //        LorentzVector & r3 = child3->getPosition();
      //        LorentzVector & p4 = child4->getMomentum();
      //        LorentzVector & r4 = child4->getPosition();
      //        decayer.decay4(parentType,
      //                       parentMomentum,
      //                       parentPosition,
      //                       childType1,p1,r1,
      //                       childType2,p2,r2,
      //                       childType3,p3,r3,
      //                       childType4,p4,r4);
      //      parent.setDecayed(true);
      //      if (decayStoreDecayedParts) event.add(&parent);
      //      if (child1->isStable() && accept(*child1))
      //        event.add(child1);
      //      else
      //        decayParticle(event, *child1);
      //      if (child2->isStable() && accept(*child2))
      //        event.add(child2);
      //      else
      //        decayParticle(event, *child2);
      //      if (child3->isStable() && accept(*child3))
      //        event.add(child3);
      //      else
      //        decayParticle(event, *child3);
      //      if (child4->isStable() && accept(*child4))
      //        event.add(child4);
      //      else
      //        decayParticle(event, *child4);
      //      break;
      break;
      }
    }
}


void TherminatorGenerator::printIntroMessage(const TString & option __attribute__ (( unused)) )  const
{
  cout << endl << endl << endl << endl<< endl << endl ;
  cout << " ***********************************************************************" << endl;
  cout << " *\t\tTHERMINATOR 2 EVENTS version "<<_THERMINATOR2_VERSION_ << endl;
  cout << " *" << endl;
  cout << " * Authors: M.Chojnacki, A.Kisiel, W.Florkowski, W.Broniowski" << endl;
  cout << " * Cite as: arXiv:1102.0273" << endl;
  cout << " * webpage: http://therminator2.ifj.edu.pl/\t\t\t\t*"<< endl;
  cout << " ***********************************************************************" << endl;
  cout << endl << endl << endl << endl<< endl << endl ;
}

void TherminatorGenerator::printHelp(const TString & option __attribute__ (( unused)) ) const
{
  cout << endl << endl << endl << endl<< endl << endl ;
  cout << "Usage:" << endl;
  cout << "therm2_events [EVENTS_INI] [PPID] [HYPER_XML]" << endl;
  cout << "therm2_events [OPTION]" << endl;
  cout << "  [EVENTS_INI]\t\tampin settings file;\t\tdefault: events.ini" << endl;
  cout << "  [PPID]\t\tparent's system process ID;\tdefault: 0" << endl;
  cout << "  [HYPER_XML]\tlocation of the hypersurface XML file;\tdefault:" << endl;
  cout << "  [OPTION]" << endl;
  cout << "    -h | --help\t\tthis screen" << endl;
  cout << "    -v | --version\tversion inforamption" << endl;
  cout << endl << endl << endl << endl<< endl << endl ;
}

void TherminatorGenerator::printVersion(const TString & option __attribute__ (( unused)) ) const
{
  cout << endl << endl;
  cout << "version:\tTHERMINATOR 2 EVENTS version " << _THERMINATOR2_VERSION_ << endl;
  cout << "compiled with:\t"<<_CXX_VER_<<", ROOT(" <<_ROOT_VER_<<")" << endl;
  cout << endl << endl;
}


void TherminatorGenerator::initializeEventGenerator()
{
  if (reportInfo(__FUNCTION__)) printIntroMessage();
  particleDb = ParticleDb::getDefaultParticleDb();
  if (particleDb->getNumberOfTypes()<1)
    throw TaskException("Particle Database is not initialized. Waky Waky!!!!!","TherminatorGenerator::initializeEventGenerator()");
  switch (modelType)
    {
      default:
      throw TaskException("Unknown model requested","TherminatorGenerator::initializeEventGenerator()");
      case 0:  model = new Model_KrakowSFO(*requestedConfiguration);   break;
      case 1:  model = new Model_BlastWave(*requestedConfiguration);   break;
      case 5:  model = new Model_HadronGas(*requestedConfiguration);   break;
      case 6:  model = new Model_BWA(*requestedConfiguration);         break;
      case 10: model = new Model_Lhyquid3D(*requestedConfiguration);   break;
      case 11: model = new Model_Lhyquid2DBI(*requestedConfiguration); break;
    };
  model->setConfigurationPath(getFullTaskPath());
  model->initialize();
  if (multiplicitiesImport)
    {
    importMultiplicities();
    }
  else if (multiplicitiesCreate)
    {
    calculateMultiplicities();
    }
  else
    {
    throw TaskException("Not loading or creating multiplicities","TherminatorGenerator::initializeEventGenerator()");
    }
  if (multiplicitiesExport && !multiplicitiesImport)
    {
    exportMultiplicities();
    }
  eventMultiplicities.assign(averageMultiplicities.size(),0.0);
}


void TherminatorGenerator::finalizeEventGenerator()
{
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    }

  particleDb = nullptr;
  if (model) delete model;
  averageMultiplicities.clear();
  eventMultiplicities.clear();
}

void TherminatorGenerator::importMultiplicities()
{
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("multiplicitiesInputPath",multiplicitiesInputPath);
    printItem("multiplicitiesInputFile",multiplicitiesInputFile);
    }
  // initialize the multiplicity array
  averageMultiplicities.clear();
  int nPartTypes = particleDb->getParticleTypeCount();
  if (reportDebug(__FUNCTION__)) cout << " nPartTypes: " << nPartTypes << endl;
  for (int iPartType=0; iPartType<nPartTypes; iPartType++)
    {
    ParticleMultiplicity pm;
    ParticleType * particleType = particleDb->getParticleType(iPartType);
    pm.name         = particleType->getName();
    pm.integral     = 0.0;
    pm.multiplicity = 0.0;
    averageMultiplicities.push_back(pm);
    }
  if (reportDebug(__FUNCTION__)) cout <<" averageMultiplicities initialized -- now open and read the file" << endl;
  ifstream & inputFile = openInputAsciiFile(multiplicitiesInputPath,multiplicitiesInputFile,".txt");
  try {
    {
    int count = 0;
    String name;
    double integral;
    double multiplicity;
    while (!inputFile.eof())
      {
      inputFile >> name >> integral >> multiplicity;
      if (reportDebug(__FUNCTION__))
        {
        cout << endl;
        cout << "i:" << count <<  " name: " << name << " integral: " << integral << " multiplicity: " << multiplicity << endl;
        }
      int index = particleDb->findIndexForName(name);
      if (index<0)
        {
        if (reportWarning(__FUNCTION__)) cout << "Name not found (skipping):" << name << endl;
        continue;
        }
      averageMultiplicities[index].integral     = integral;
      averageMultiplicities[index].multiplicity = multiplicity;
      count++;
      }
    if (reportDebug(__FUNCTION__))
      {
      cout << endl;
      cout << "Read in " << count << " records."  << endl;
      }
    inputFile.close();
    }
  }
  catch (...)
  {
  throw FileException(multiplicitiesInputFile,"Error reading multiplicity file.","TherminatorGenerator::importMultiplicities()");
  }
}

void TherminatorGenerator::exportMultiplicities()
{
  // create the outputpath if it does not exist...
  gSystem->mkdir(multiplicitiesOutputPath,1);
  ofstream & outputFile = openOutputAsciiFile(multiplicitiesOutputPath,multiplicitiesOutputFile,".txt");
  unsigned int nTypes = averageMultiplicities.size();
  for (unsigned int iType=0; iType<nTypes; iType++)
    {
    ParticleMultiplicity & pm = averageMultiplicities[iType];
    outputFile << pm.name << "    " << pm.integral << "    " << pm.multiplicity << endl;
    }
  outputFile.close();
}

void TherminatorGenerator::calculateMultiplicities()
{
  int nPartTypes = particleDb->getParticleTypeCount();
  if (reportDebug(__FUNCTION__))
    {
    cout << endl;
    cout << " nPartTypes : " << nPartTypes << endl<< endl;
    }
  if (nPartTypes<1)
    throw TaskException("nPartTypes<1","TherminatorGenerator::calculateMultiplicities()");
  for (int iPartType = 0; iPartType<nPartTypes; iPartType++)
    {
    ParticleType & particleType = *particleDb->getParticleType(iPartType);
    double maxIntegrand  = 0.0;
    double multiplicity  = 0.0;
    double integrand     = 0.0;
    ParticleMultiplicity particleMultiplicity;
    if (particleType.isPhoton() && disablePhotons)
      {
      particleMultiplicity.name         = particleType.getName();
      particleMultiplicity.integral     = 0.0;
      particleMultiplicity.multiplicity = 0.0;
      }
    else
      {
      for (int iParticle = 0; iParticle < nSamplesIntegration; iParticle++)
        {
        integrand = model->getIntegrand(particleType);
        //if (integrand<0.0) continue;
        if (integrand>maxIntegrand) maxIntegrand = integrand;
        multiplicity += integrand;
        }
      //multiplicity *= 1.0/ double(nSamplesIntegration);
      //cout << "iPartType:" << iPartType << " maxIntegrand: " << maxIntegrand << " multiplicity:" << multiplicity << endl;
      //cout << "            volume: " << model->getHyperCubeVolume() <<  " nSamplesIntegration:" << nSamplesIntegration << endl;
      multiplicity *= model->getHyperCubeVolume() / double(nSamplesIntegration);
      //cout << "            multiplicity: "  <<  multiplicity << endl;
      particleMultiplicity.integral     = maxIntegrand;
      particleMultiplicity.multiplicity = multiplicity;
      }
    averageMultiplicities.push_back(particleMultiplicity);
    }
  if (reportDebug(__FUNCTION__)) printMultiplicities();
}

void TherminatorGenerator::printMultiplicities()
{
  cout << endl<< endl<< endl<< endl;
  cout << "ParticleDb Name.................................: " << particleDb->getName() << endl;
  cout << "Model Name......................................: " << model->getName() << endl;
  cout << "Average Multiplicities vs. Species..............: " << endl;
  cout << endl<< endl;
  cout << fixed << setw(5)  <<  "Index";
  cout << fixed << setw(12) <<  "Name";
  cout << fixed << setw(16) <<  "Integral";
  cout << fixed << setw(16) <<  "Multiplicity";
  cout << endl;
  unsigned int nTypes = averageMultiplicities.size();
  for (unsigned int iType=0; iType<nTypes; iType++)
    {
    ParticleType & type = *particleDb->getParticleType(iType);
    ParticleMultiplicity & pm = averageMultiplicities[iType];
    cout
    << fixed << setw(5) <<  iType
    << fixed << setw(12)  << type.getName()
    << scientific << setw(16) << setprecision(6) <<  pm.integral
    << scientific << setw(16) << setprecision(6) <<  pm.multiplicity << endl;
    }
  cout << endl<< endl<< endl<< endl;
}
