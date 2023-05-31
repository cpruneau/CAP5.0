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
#include "FilterCreator.hpp"
#include "EventFilter.hpp"
#include "ParticleFilter.hpp"

// using CAP::FilterCreator;

ClassImp(CAP::FilterCreator);


namespace CAP
{


FilterCreator::FilterCreator(const String & _name,
                             const Configuration & _configuration)
:
EventTask(_name, _configuration)
{
  appendClassName("FilterCreator");
}


void FilterCreator::setDefaultConfiguration()
{
  EventTask::setDefaultConfiguration();
//  bool YES = true;
//  bool NO  = false;

  addParameter("EventFilterModelOption",     TString("All"));
  addParameter("EventFilterModelNValues",    0);
  addParameter("EventFilterModelValue0",     0.0);
  addParameter("EventFilterModelValue1",     0.0);
  addParameter("EventFilterModelValue2",     0.0);
  addParameter("EventFilterModelValue3",     0.0);
  addParameter("EventFilterModelValue4",     0.0);
  addParameter("EventFilterModelValue5",     0.0);
  addParameter("EventFilterModelValue6",     0.0);
  addParameter("EventFilterModelValue7",     0.0);
  addParameter("EventFilterModelValue8",     0.0);
  addParameter("EventFilterModelValue9",     0.0);
  addParameter("EventFilterModelValue10",    0.0);
  addParameter("EventFilterModelValue11",    0.0);
  addParameter("EventFilterModelValue12",    0.0);

  addParameter("EventFilterAnaOption",      TString("All"));
  addParameter("EventFilterAnaNValues",     0);
  addParameter("EventFilterAnaValue0",      0.0);
  addParameter("EventFilterAnaValue1",      0.0);
  addParameter("EventFilterAnaValue2",      0.0);
  addParameter("EventFilterAnaValue3",      0.0);
  addParameter("EventFilterAnaValue4",      0.0);
  addParameter("EventFilterAnaValue5",      0.0);
  addParameter("EventFilterAnaValue6",      0.0);
  addParameter("EventFilterAnaValue7",      0.0);
  addParameter("EventFilterAnaValue8",      0.0);
  addParameter("EventFilterAnaValue9",      0.0);
  addParameter("EventFilterAnaValue10",     0.0);
  addParameter("EventFilterAnaValue11",     0.0);
  addParameter("EventFilterAnaValue12",     0.0);

  addParameter("PartFilterModelOption",     TString("All"));
  addParameter("PartFilterModelPt",         false);
  addParameter("PartFilterModelMinPt",      0.2);
  addParameter("PartFilterModelMaxPt",      2.0);
  addParameter("PartFilterModelEta",        false);
  addParameter("PartFilterModelMinEta",     -4.0);
  addParameter("PartFilterModelMaxEta",     4.0);
  addParameter("PartFilterModelY",          false);
  addParameter("PartFilterModelMinY",       -4.0);
  addParameter("PartFilterModelMaxY",       4.0);

  addParameter("PartFilterAnaOption",       TString("All"));
  addParameter("PartFilterAnaFilterPt",     false);
  addParameter("PartFilterAnaMinPt",        0.0);
  addParameter("PartFilterAnaMaxPt",        2.0);
  addParameter("PartFilterAnaEta",          false);
  addParameter("PartFilterAnaMinEta",       -4.0);
  addParameter("PartFilterAnaMaxEta",       4.0);
  addParameter("PartFilterAnaY",            false);
  addParameter("PartFilterAnaMinY",         -4.0);
  addParameter("PartFilterAnaMaxY",         4.0);
}


void FilterCreator::configure()
{
  if (reportStart(__FUNCTION__))
    ;
  EventTask::configure();
  setSeverity();
  }


void FilterCreator::execute()
{  }


void FilterCreator::initialize()
{
  if (reportInfo(__FUNCTION__)) cout << "Building filters" << endl;

  String eventFilterModelOption           = getValueString("EventFilterModelOption");
  int    eventFilterModelNValues          = getValueInt("EventFilterModelNValues");
  String eventFilterAnaOption             = getValueString("EventFilterAnaOption");
  int    eventFilterAnaNValues            = getValueInt("EventFilterAnaNValues");

  String partFilterModelOption            = getValueString("PartFilterModelOption");
  double partFilterModelPt                = getValueBool(  "PartFilterModelPt");
  double partFilterModelMinPt             = getValueDouble("PartFilterModelMinPt");
  double partFilterModelMaxPt             = getValueDouble("PartFilterModelMaxPt");
  bool   partFilterModelEta               = getValueBool(  "PartFilterModelEta");
  double partFilterModelMinEta            = getValueDouble("PartFilterModelMinEta");
  double partFilterModelMaxEta            = getValueDouble("PartFilterModelMaxEta");
  bool   partFilterModelY                 = getValueBool(  "PartFilterModelY");
  double partFilterModelMinY              = getValueDouble("PartFilterModelMinY");
  double partFilterModelMaxY              = getValueDouble("PartFilterModelMaxY");

  String partFilterAnaOption              = getValueString("PartFilterAnaOption");
  double partFilterAnaFilterPt            = getValueBool(  "PartFilterAnaFilterPt");
  double partFilterAnaMinPt               = getValueDouble("PartFilterAnaMinPt");
  double partFilterAnaMaxPt               = getValueDouble("PartFilterAnaMaxPt");
  bool   partFilterAnaEta                 = getValueBool(  "PartFilterAnaEta");
  double partFilterAnaMinEta              = getValueDouble("PartFilterAnaMinEta");
  double partFilterAnaMaxEta              = getValueDouble("PartFilterAnaMaxEta");
  bool   partFilterAnaY                   = getValueBool(  "PartFilterAnaY");
  double partFilterAnaMinY                = getValueDouble("PartFilterAnaMinY");
  double partFilterAnaMaxY                = getValueDouble("PartFilterAnaMaxY");

//  if (reportDebug(__FUNCTION__)) printConfiguration(cout);

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;

    printItem("EventFilterModelOption",  eventFilterModelOption);
    printItem("EventFilterModelNValues", eventFilterModelNValues);
    printItem("EventFilterAnaOption",    eventFilterAnaOption);
    printItem("EventFilterAnaNValues",   eventFilterAnaNValues);

    printItem("PartFilterModelOption",   partFilterModelOption);
    printItem("PartFilterModelPt",       partFilterModelPt);
    printItem("PartFilterModelMinPt",    partFilterModelMinPt);
    printItem("PartFilterModelMaxPt",    partFilterModelMaxPt);
    printItem("PartFilterModelEta",      partFilterModelEta);
    printItem("PartFilterModelMinEta",   partFilterModelMinEta);
    printItem("PartFilterModelMaxEta",   partFilterModelMaxEta);
    printItem("PartFilterModelY",        partFilterModelY);
    printItem("PartFilterModelMinY",     partFilterModelMinY);
    printItem("PartFilterModelMaxY",     partFilterModelMaxY);

    printItem("PartFilterAnaOption",     partFilterAnaOption);
    printItem("PartFilterAnaFilterPt",   partFilterAnaFilterPt);
    printItem("PartFilterAnaMinPt",      partFilterAnaMinPt);
    printItem("PartFilterAnaMaxPt",      partFilterAnaMaxPt);
    printItem("PartFilterAnaEta",        partFilterAnaEta);
    printItem("PartFilterAnaMinEta",     partFilterAnaMinEta);
    printItem("PartFilterAnaMaxEta",     partFilterAnaMaxEta);
    printItem("PartFilterAnaY",          partFilterAnaY);
    printItem("PartFilterAnaMinY",       partFilterAnaMinY);
    printItem("PartFilterAnaMaxY",       partFilterAnaMaxY);
     cout << endl;
    }

  // =========================================
  // Setup all event filters
  // =========================================
  createEventFiltersModel();
  createEventFiltersAnalysis();
  createParticleFiltersModel();
  createParticleFiltersAnalysis();

  if (reportInfo(__FUNCTION__)) cout << "Event filter model option selected: " << eventFilterModelOption  << endl;

  if (eventFilterModelOption.EqualTo("none"))
    {
    if (reportWarning(__FUNCTION__)) cout << "No event filter selected for model" << endl;
    }
  else
    {
    if (eventFilterModelOption.EqualTo("All"))          FilterCreator::addEventFiltersModel(EventFilter::createOpenEventFilter());
    else if (eventFilterModelOption.EqualTo("AliceMB")) FilterCreator::addEventFiltersModel(EventFilter::createAliceMBEventFilter());
    else
      {

      vector<double> bounds;
      for (int k=0; k<eventFilterModelNValues; k++)
        {
        String key = "EventFilterModelValue";  key += k;
        bounds.push_back( getValueBool(key));
        }
      if (eventFilterModelOption.EqualTo("ImpactParameter"))  FilterCreator::addEventFiltersModel(EventFilter::createImpactParameterFilters(bounds));
      else if (eventFilterModelOption.EqualTo("V0Mult"))      FilterCreator::addEventFiltersModel(EventFilter::createV0MultiplicityFilters(bounds));
      else if (eventFilterModelOption.EqualTo("TpcMult"))     FilterCreator::addEventFiltersModel(EventFilter::createTpcMultiplicityFilters(bounds));
      else
        {
        if (reportWarning(__FUNCTION__)) cout << "Unknown filter option selected for model: " <<  eventFilterModelOption << endl;
        }
      }
    }

  if (reportInfo(__FUNCTION__)) cout << "Event filter analysis option selected: " << eventFilterAnaOption  << endl;
  if (eventFilterAnaOption.EqualTo("none"))
    {
    if (reportWarning(__FUNCTION__)) cout << "No event filter selected for model" << endl;
    }
  else
    {
    if (eventFilterAnaOption.EqualTo("All"))          FilterCreator::addEventFiltersAnalysis(EventFilter::createOpenEventFilter());
    else if (eventFilterAnaOption.EqualTo("AliceMB")) FilterCreator::addEventFiltersAnalysis(EventFilter::createAliceMBEventFilter());
    else
      {
      vector<double> bounds;
      for (int k=0; k<eventFilterAnaNValues; k++)
        {
        String key = "EventFilterAnaValue";  key += k;
        bounds.push_back( getValueBool(key));
        }
      if (eventFilterAnaOption.EqualTo("ImpactParameter"))  FilterCreator::addEventFiltersAnalysis(EventFilter::createImpactParameterFilters(bounds));
      else if (eventFilterAnaOption.EqualTo("V0Mult"))      FilterCreator::addEventFiltersAnalysis(EventFilter::createV0MultiplicityFilters(bounds));
      else if (eventFilterAnaOption.EqualTo("TpcMult"))     FilterCreator::addEventFiltersAnalysis(EventFilter::createTpcMultiplicityFilters(bounds));
      else
        {
        if (reportWarning(__FUNCTION__)) cout << "Unknown filter option selected for analysis: " <<  eventFilterAnaOption << endl;
        }
      }
    }


  // =========================================
  // Setup all particle filters
  // =========================================
  if (reportInfo(__FUNCTION__)) cout << "PartFilterModelOption" << partFilterModelOption  << endl;
  if (partFilterModelOption.EqualTo("All"))                   FilterCreator::addParticleFiltersModel(ParticleFilter::createOpenParticleFilter());
  else if (partFilterModelOption.EqualTo("AliceV0"))          FilterCreator::addParticleFiltersModel(ParticleFilter::createAliceV0Filter());
  else if (partFilterModelOption.EqualTo("Neutral"))          FilterCreator::addParticleFiltersModel(ParticleFilter::createNeutralParticleFilter(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Charged"))          FilterCreator::addParticleFiltersModel(ParticleFilter::createChargedParticleFilter(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Negative"))         FilterCreator::addParticleFiltersModel(ParticleFilter::createNegativeParticleFilter(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Positive"))         FilterCreator::addParticleFiltersModel(ParticleFilter::createPositiveParticleFilter(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("ChargedHadrons"))   FilterCreator::addParticleFiltersModel(ParticleFilter::createChargedHadronFilters(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("PlusMinusHadrons")) FilterCreator::addParticleFiltersModel(ParticleFilter::createPlusMinusHadronFilters(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("StrangeHadrons"))   FilterCreator::addParticleFiltersModel(ParticleFilter::createStrangeHadronFilters(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Baryons"))          FilterCreator::addParticleFiltersModel(ParticleFilter::createBaryonFilters(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Index"))            FilterCreator::addParticleFiltersModel(ParticleFilter::createIndexFilters(0,381,partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else
    if (reportWarning(__FUNCTION__)) cout << "PartFilterModelOption is unknown:" << partFilterModelOption  << endl;

  if (reportInfo(__FUNCTION__)) cout << "PartFilterModelOption" << partFilterModelOption  << endl;
  if (partFilterAnaOption.EqualTo("All"))                     FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createOpenParticleFilter());
  else if (partFilterAnaOption.EqualTo("AliceV0"))            FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createAliceV0Filter());
  else if (partFilterAnaOption.EqualTo("Neutral"))            FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createNeutralParticleFilter(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Charged"))            FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createChargedParticleFilter(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Negative"))           FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createNegativeParticleFilter(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Positive"))           FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createPositiveParticleFilter(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("ChargedHadrons"))     FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createChargedHadronFilters(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("PlusMinusHadrons"))   FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createPlusMinusHadronFilters(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("StrangeHadrons"))     FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createStrangeHadronFilters(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Baryons"))            FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createBaryonFilters(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Index"))              FilterCreator::addParticleFiltersAnalysis(ParticleFilter::createIndexFilters(0,381,partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else
    if (reportWarning(__FUNCTION__)) cout << "PartFilterAnaOption is unknown:" << partFilterAnaOption  << endl;

  if (particleFiltersAnalysis->size()<1)
    {
    if (reportFatal(__FUNCTION__))
      {
      cout << endl;
      cout << "==================================================================================" << std::endl;
      cout << "No Analysis Particle Filter" << std::endl;
      cout << "==================================================================================" << std::endl;
      }
    throw TaskException("particleFiltersAnalysis->size()<1","FilterCreator::execute()");
    }
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    cout << "==================================================================================" << std::endl;
    cout << "Filter Created" << std::endl;
    cout << "==================================================================================" << std::endl;
    cout << "  eventFiltersModel.size().............: " << eventFiltersModel->size() << endl;
    for (unsigned int k=0; k<eventFiltersModel->size(); k++)
      cout << "    " << k << "   " << (*eventFiltersModel)[k]->getName() << endl;
    cout << "  particleFiltersModel.size()..........: " << particleFiltersModel->size() << endl;
    for (unsigned int k=0; k<particleFiltersModel->size(); k++)
      cout << "    " << k << "   " << (*particleFiltersModel)[k]->getName() << endl;
    cout << "  eventFiltersAnalysis.size()..........: " << eventFiltersAnalysis->size() << endl;
    for (unsigned int k=0; k<eventFiltersAnalysis->size(); k++)
      cout << "    " << k << "   " << (*eventFiltersAnalysis)[k]->getName() << endl;
    cout << "  particleFiltersAnalysis.size().......: " << particleFiltersAnalysis->size() << endl;
    for (unsigned int k=0; k<particleFiltersAnalysis->size(); k++)
      cout << "    " << k << "   " << (*particleFiltersAnalysis)[k]->getName() << endl;
    cout << "==================================================================================" << std::endl;
    }
}

// static members

vector<EventFilter*>    * FilterCreator::eventFiltersModel = nullptr;
vector<ParticleFilter*> * FilterCreator::particleFiltersModel = nullptr;
vector<EventFilter*>    * FilterCreator::eventFiltersAnalysis = nullptr;
vector<ParticleFilter*> * FilterCreator::particleFiltersAnalysis = nullptr;

void FilterCreator::createEventFiltersModel()
{
  if (eventFiltersModel!=nullptr) throw TaskException("eventFiltersModel already created","FilterCreator::createEventFiltersModel()");
  eventFiltersModel = new vector<EventFilter*>();
}

void FilterCreator::createEventFiltersAnalysis()
{
  if (eventFiltersAnalysis!=nullptr) throw TaskException("eventFiltersAnalysis already created","FilterCreator::createEventFiltersAnalysis()");
  eventFiltersAnalysis = new vector<EventFilter*>();
}

void FilterCreator::createParticleFiltersModel()
{
  if (particleFiltersModel!=nullptr) throw TaskException("particleFiltersModel already created","FilterCreator::createParticleFiltersModel()");
  particleFiltersModel = new vector<ParticleFilter*>();
}

void FilterCreator::createParticleFiltersAnalysis()
{
  if (particleFiltersAnalysis!=nullptr) throw TaskException("particleFiltersAnalysis already created","FilterCreator::createParticleFiltersAnalysis()");
  particleFiltersAnalysis = new vector<ParticleFilter*>();
}

void FilterCreator::addEventFilterModel(EventFilter* filter)
{
  if (eventFiltersModel==nullptr) throw TaskException("eventFiltersModel==nullptr","FilterCreator::addEventFilterModel(EventFilter* filter)");
  eventFiltersModel->push_back(filter);
}

void FilterCreator::addEventFilterAnalysis(EventFilter* filter)
{
  if (eventFiltersAnalysis==nullptr) throw TaskException("eventFiltersAnalysis==nullptr","FilterCreator::addEventFilterAnalysis(EventFilter* filter)");
  eventFiltersAnalysis->push_back(filter);
}

void FilterCreator::addParticleFilterModel(ParticleFilter* filter)
{
  if (particleFiltersModel==nullptr) throw TaskException("particleFiltersModel==nullptr","FilterCreator::addParticleFilterModel(ParticleFilter* filter)");
  particleFiltersModel->push_back(filter);
}


void FilterCreator::addParticleFilterAnalysis(ParticleFilter* filter)
{
  if (particleFiltersAnalysis==nullptr) throw TaskException("particleFiltersAnalysis==nullptr","FilterCreator::addParticleFilterAnalysis(ParticleFilter* filter)");
  particleFiltersAnalysis->push_back(filter);
}

void FilterCreator::addEventFiltersModel(vector<EventFilter*>  filters)
{
  if (eventFiltersModel==nullptr) throw TaskException("eventFiltersModel==nullptr","FilterCreator::addEventFiltersModel(vector<EventFilter*> & filters)");
  int n = filters.size();
  if (n<1)  throw TaskException("filters.size()<1","FilterCreator::addEventFiltersModel(vector<EventFilter*> & filters)");
  for (int k=0; k<n; k++)
    {
    eventFiltersModel->push_back(filters[k]);
    }
}

void FilterCreator::addEventFiltersAnalysis(vector<EventFilter*>  filters)
{
  if (eventFiltersAnalysis==nullptr) throw TaskException("eventFiltersAnalysis==nullptr","FilterCreator::addEventFiltersAnalysis(vector<EventFilter*> & filters)");
  int n = filters.size();
  if (n<1)  throw TaskException("filters.size()<1","FilterCreator::addEventFiltersAnalysis(vector<EventFilter*> & filters)");
  for (int k=0; k<n; k++)
    {
    eventFiltersAnalysis->push_back(filters[k]);
    }
}

void FilterCreator::addParticleFiltersModel(vector<ParticleFilter*> filters)
{
  if (particleFiltersModel==nullptr) throw TaskException("particleFiltersModel==nullptr","FilterCreator::addParticleFiltersModel(vector<ParticleFilter*>  filters)");
  int n = filters.size();
  if (n<1)  throw TaskException("filters.size()<1","FilterCreator::addParticleFiltersModel(vector<ParticleFilter*>  filters)");
  for (int k=0; k<n; k++)
    {
    particleFiltersModel->push_back(filters[k]);
    }
}

void FilterCreator::addParticleFiltersAnalysis(vector<ParticleFilter*>  filters)
{
  if (particleFiltersAnalysis==nullptr) throw TaskException("particleFiltersAnalysis==nullptr","FilterCreator::addParticleFiltersAnalysis(vector<ParticleFilter*>  filters)");
  int n = filters.size();
  if (n<1)  throw TaskException("filters.size()<1","FilterCreator::addParticleFiltersAnalysis(vector<ParticleFilter*>  filters)");
  for (int k=0; k<n; k++)
    {
    particleFiltersAnalysis->push_back(filters[k]);
    }
}


vector<EventFilter*> & FilterCreator::getEventFiltersModel()
{
  if (eventFiltersModel==nullptr) throw TaskException("eventFiltersModel==nullptr","FilterCreator::getEventFiltersModel()");
  return *eventFiltersModel;
}

vector<EventFilter*> & FilterCreator::getEventFiltersAnalysis()
{
  if (eventFiltersAnalysis==nullptr) throw TaskException("eventFiltersAnalysis==nullptr","FilterCreator::getEventFiltersAnalysis()");
  return *eventFiltersModel;
}

vector<ParticleFilter*> & FilterCreator::getParticleFiltersModel()
{
  if (particleFiltersModel==nullptr) throw TaskException("particleFiltersModel==nullptr","FilterCreator::getParticleFiltersModel()");
  return *particleFiltersModel;
}

vector<ParticleFilter*> & FilterCreator::getParticleFiltersAnalysis()
{
  if (particleFiltersAnalysis==nullptr) throw TaskException("particleFiltersAnalysis==nullptr","FilterCreator::getParticleFiltersAnalysis()");
  return *particleFiltersAnalysis;
}



} // namespace CAP
