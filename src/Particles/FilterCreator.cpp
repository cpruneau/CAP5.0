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
  if (partFilterModelOption.EqualTo("All"))                   FilterCreator::addParticleFiltersModel(createOpenParticleFilter());
  else if (partFilterModelOption.EqualTo("AliceV0"))          FilterCreator::addParticleFiltersModel(createAliceV0Filter());
  else if (partFilterModelOption.EqualTo("Neutral"))          FilterCreator::addParticleFiltersModel(createNeutralParticleFilter(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Charged"))          FilterCreator::addParticleFiltersModel(createChargedParticleFilter(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Negative"))         FilterCreator::addParticleFiltersModel(createNegativeParticleFilter(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Positive"))         FilterCreator::addParticleFiltersModel(createPositiveParticleFilter(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("ChargedHadrons"))   FilterCreator::addParticleFiltersModel(createChargedHadronFilters(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("PlusMinusHadrons")) FilterCreator::addParticleFiltersModel(createPlusMinusHadronFilters(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("StrangeHadrons"))   FilterCreator::addParticleFiltersModel(createStrangeHadronFilters(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Baryons"))          FilterCreator::addParticleFiltersModel(createBaryonFilters(partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else if (partFilterModelOption.EqualTo("Index"))            FilterCreator::addParticleFiltersModel(createIndexFilters(0,381,partFilterModelPt,partFilterModelMinPt,partFilterModelMaxPt,partFilterModelEta,partFilterModelMinEta,partFilterModelMaxEta,partFilterModelY,partFilterModelMinY,partFilterModelMaxY));
  else
    if (reportWarning(__FUNCTION__)) cout << "PartFilterModelOption is unknown:" << partFilterModelOption  << endl;

  if (reportInfo(__FUNCTION__)) cout << "PartFilterModelOption" << partFilterModelOption  << endl;
  if (partFilterAnaOption.EqualTo("All"))                     FilterCreator::addParticleFiltersAnalysis(createOpenParticleFilter());
  else if (partFilterAnaOption.EqualTo("AliceV0"))            FilterCreator::addParticleFiltersAnalysis(createAliceV0Filter());
  else if (partFilterAnaOption.EqualTo("Neutral"))            FilterCreator::addParticleFiltersAnalysis(createNeutralParticleFilter(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Charged"))            FilterCreator::addParticleFiltersAnalysis(createChargedParticleFilter(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Negative"))           FilterCreator::addParticleFiltersAnalysis(createNegativeParticleFilter(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Positive"))           FilterCreator::addParticleFiltersAnalysis(createPositiveParticleFilter(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("ChargedHadrons"))     FilterCreator::addParticleFiltersAnalysis(createChargedHadronFilters(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("PlusMinusHadrons"))   FilterCreator::addParticleFiltersAnalysis(createPlusMinusHadronFilters(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("StrangeHadrons"))     FilterCreator::addParticleFiltersAnalysis(createStrangeHadronFilters(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Baryons"))            FilterCreator::addParticleFiltersAnalysis(createBaryonFilters(partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
  else if (partFilterAnaOption.EqualTo("Index"))              FilterCreator::addParticleFiltersAnalysis(createIndexFilters(0,381,partFilterAnaFilterPt,partFilterAnaMinPt,partFilterAnaMaxPt,partFilterAnaEta,partFilterAnaMinEta,partFilterAnaMaxEta,partFilterAnaY,partFilterAnaMinY,partFilterAnaMaxY));
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



vector<ParticleFilter*> FilterCreator::createOpenParticleFilter()
{
  vector<ParticleFilter*> filters;
  ParticleFilter * filter = new ParticleFilter();
  filter->setName("All");
  filter->setLongName("All");
  filter->setTitle("All");
  filter->setLongTitle("All");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filters.push_back(filter);
  return filters;
}

vector<ParticleFilter*> FilterCreator::createAliceV0Filter()
{
  vector<ParticleFilter*> filters;
  ParticleFilter* filter  = new ParticleFilter();
  filter->setName("V0M");
  filter->setLongName("V0M");
  filter->setTitle("V0M");
  filter->setLongTitle("V0M");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(4, 1102, 0.0, 0.0);   // low mass charged hadron
  filter->addCondition(5, 1, 0.05,  1000.0);  // pT
  filter->addCondition(5, 7, -3.7, -1.7, 2.8, 5.1); // pseudorapidity in V0A and V0C
  filters.push_back(filter);
  return filters;
}

vector<ParticleFilter*> FilterCreator::createNeutralParticleFilter(bool filteringOnPt,  double minPt,  double maxPt,
                                                                    bool filteringOnEta, double minEta, double maxEta,
                                                                    bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;
  ParticleFilter* filter  = new ParticleFilter();
  filter->setName("Neutral");
  filter->setLongName("Meutral");
  filter->setTitle("Q=0");
  filter->setLongTitle("Q=0");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(1, 0,  0.0, 0.0);   // neutral particles only
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);  return filters;
}

vector<ParticleFilter*> FilterCreator::createChargedParticleFilter(bool filteringOnPt,  double minPt,  double maxPt,
                                                                    bool filteringOnEta, double minEta, double maxEta,
                                                                    bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;
  ParticleFilter* filter  = new ParticleFilter();
  filter->setName("Charged");
  filter->setLongName("Charged");
  filter->setTitle("Q!=0");
  filter->setLongTitle("Q!=0");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(1, 1,  0.0, 0.0);   // charged particles only
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);  return filters;
}

vector<ParticleFilter*> FilterCreator::createNegativeParticleFilter(bool filteringOnPt,  double minPt,  double maxPt,
                                                                     bool filteringOnEta, double minEta, double maxEta,
                                                                     bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;
  ParticleFilter* filter  = new ParticleFilter();
  filter->setName("Negative");
  filter->setLongName("Negative");
  filter->setTitle("Q<0");
  filter->setLongTitle("Q<0");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(1, 2,  0.0, 0.0);   // negative particles only
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);  return filters;
}

vector<ParticleFilter*> FilterCreator::createPositiveParticleFilter(bool filteringOnPt,  double minPt,  double maxPt,
                                                                     bool filteringOnEta, double minEta, double maxEta,
                                                                     bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;
  ParticleFilter* filter  = new ParticleFilter();
  filter->setName("Positive");
  filter->setLongName("Positive");
  filter->setTitle("Q>0");
  filter->setLongTitle("Q>0");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(1, 3,  0.0, 0.0);   // negative particles only
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);  return filters;
}

vector<ParticleFilter*> FilterCreator::createPlusMinusHadronFilters(bool filteringOnPt,  double minPt,  double maxPt,
                                                                     bool filteringOnEta, double minEta, double maxEta,
                                                                     bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;

  ParticleFilter * filter;

  filter = new ParticleFilter();
  filter->setName("PiP");
  filter->setLongName("PiP");
  filter->setTitle("#pi^{+}");
  filter->setLongTitle("#pi^{+}");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(2, 211, 0.0, 0.0);  // pi+
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);

  filter = new ParticleFilter();
  filter->setName("PiM");
  filter->setLongName("PiM");
  filter->setTitle("#pi^{-}");
  filter->setLongTitle("#pi^{-}");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(2, -211, 0.0, 0.0);  // pi-
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);

  filter = new ParticleFilter();
  filter->setName("KP");
  filter->setLongName("KP");
  filter->setTitle("K^{+}");
  filter->setLongTitle("K^{+}");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(2, 321, 0.0, 0.0);  // K+
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);

  filter = new ParticleFilter();
  filter->setName("KM");
  filter->setLongName("KM");
  filter->setTitle("K^{-}");
  filter->setLongTitle("K^{-}");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(2, -321, 0.0, 0.0);  // K-
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);

  filter = new ParticleFilter();
  filter->setName("PP");
  filter->setLongName("PP");
  filter->setTitle("p");
  filter->setLongTitle("p");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(2, 2212, 0.0, 0.0);  // p+
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);

  filter = new ParticleFilter();
  filter->setName("PM");
  filter->setLongName("PM");
  filter->setTitle("#bar{p}");
  filter->setLongTitle("#bar{p}");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(2, -2212, 0.0, 0.0);  // pi+
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);
  return filters;
}

vector<ParticleFilter*> FilterCreator::createChargedHadronFilters(bool filteringOnPt,  double minPt,  double maxPt,
                                                                   bool filteringOnEta, double minEta, double maxEta,
                                                                   bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;

  ParticleFilter * filter;

  filter = new ParticleFilter();
  filter->setName("HP");
  filter->setLongName("HP");
  filter->setTitle("h^{+}");
  filter->setLongTitle("h^{+}");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(4, 1103, 0.0, 0.0);   // positive low mass hadron
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);

  filter = new ParticleFilter();
  filter->setName("HM");
  filter->setLongName("HM");
  filter->setTitle("h^{-}");
  filter->setLongTitle("h^{+}");
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(4, 1104, 0.0, 0.0);   // negative low mass hadron
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  filters.push_back(filter);
  return filters;
}



ParticleFilter *  FilterCreator::createHadronFilter(int pdg, const String & name, const String  & title,
                                                     bool filteringOnPt,  double minPt,  double maxPt,
                                                     bool filteringOnEta, double minEta, double maxEta,
                                                     bool filteringOnY,   double minY,   double maxY)
{
  ParticleFilter * filter = new ParticleFilter();
  filter->setName(name);
  filter->setLongName(name);
  filter->setTitle(title);
  filter->setLongTitle(title);
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(2, pdg,  double(pdg), double(pdg));
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  return filter;
}

ParticleFilter *  FilterCreator::createIndexFilter(int index, const String & name, const String  & title,
                                                    bool filteringOnPt,  double minPt,  double maxPt,
                                                    bool filteringOnEta, double minEta, double maxEta,
                                                    bool filteringOnY,   double minY,   double maxY)
{
  ParticleFilter * filter = new ParticleFilter();
  filter->setName(name);
  filter->setLongName(name);
  filter->setTitle(title);
  filter->setLongTitle(title);
  filter->addCondition(0, 1,  0.0, 0.0);  // live particles only
  filter->addCondition(3, index,  double(index), double(index));   // accept particles w/ given index
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  return filter;
}

vector<ParticleFilter*> FilterCreator::createIndexFilters(int minIndex,
                                                           int maxIndex,
                                                           bool filteringOnPt,  double minPt,  double maxPt,
                                                           bool filteringOnEta, double minEta, double maxEta,
                                                           bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;
  String name;
  for (int index=minIndex; index<=maxIndex; index++)
    {
    name = "Part";
    name += index;
    filters.push_back(createIndexFilter(index,name,name,
                                        filteringOnPt,minPt,maxPt,
                                        filteringOnEta,minEta,maxEta,
                                        filteringOnY,minY,maxY));
    }
  return filters;
}




vector<ParticleFilter*> FilterCreator::createBaryonFilters(bool filteringOnPt,  double minPt,  double maxPt,
                                                            bool filteringOnEta, double minEta, double maxEta,
                                                            bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;

  // proton  : 2212
  // neutron : 2112
  // lambda  : 3122
  // Sigma+  : 3222
  // Sigma0  : 3212
  // Sigma-  : 3112
  // Xi0     : 3322
  // XiM     : 3312
  // Omega-  : 3334
  // ===========================

  filters.push_back(createHadronFilter(2212,"P",       "p",          filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(2112,"N",       "n",          filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3122,"Lambda0", "#Lambda^{0}",filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3222,"SigmaP",  "#Sigma^{+}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3212,"Sigma0",  "#Sigma^{0}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3112,"SigmaM",  "#Sigma^{-}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3322,"Xi0",     "#Xi^{0}",    filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3312,"XiM",     "#Xi^{-}",    filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3334,"OmegaM",  "#Omega^{-}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));

  filters.push_back(createHadronFilter(-2212,"Pbar",       "#bar{p}",          filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-2112,"Nbar",       "#bar{n}",          filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3122,"Lambda0bar", "#bar{#Lambda}^{0}",filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3222,"SigmaPbar",  "#bar{#Sigma}^{-}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3212,"Sigma0bar",  "#bar{#Sigma}^{0}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3112,"SigmaMbar",  "#bar{#Sigma}^{+}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3322,"Xi0bar",     "#bar{#Xi}^{0}",    filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3312,"XiMbar",     "#bar{#Xi}^{+}",    filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3334,"OmegaMbar",  "#bar{#Omega}^{+}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));

  return filters;
}



vector<ParticleFilter*> FilterCreator::createStrangeHadronFilters(bool filteringOnPt,  double minPt,  double maxPt,
                                                                   bool filteringOnEta, double minEta, double maxEta,
                                                                   bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;

  // lambda  : 3122
  // Sigma+  : 3222
  // Sigma0  : 3212
  // Sigma-  : 3112
  // Xi0     : 3322
  // XiM     : 3312
  // Omega-  : 3334
  // ===========================

  filters.push_back(createHadronFilter(321, "KP",      "K^{+}",      filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3122,"Lambda0", "#Lambda^{0}",filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3222,"SigmaP",  "#Sigma^{+}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3212,"Sigma0",  "#Sigma^{0}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3112,"SigmaM",  "#Sigma^{-}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3322,"Xi0",     "#Xi^{0}",    filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3312,"XiM",     "#Xi^{-}",    filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(3334,"OmegaM",  "#Omega^{-}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));

  filters.push_back(createHadronFilter(-321, "KM",         "K^{-}",            filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3122,"Lambda0bar", "#bar{#Lambda}^{0}",filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3222,"SigmaPbar",  "#bar{#Sigma}^{-}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3212,"Sigma0bar",  "#bar{#Sigma}^{0}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3112,"SigmaMbar",  "#bar{#Sigma}^{+}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3322,"Xi0bar",     "#bar{#Xi}^{0}",    filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3312,"XiMbar",     "#bar{#Xi}^{+}",    filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));
  filters.push_back(createHadronFilter(-3334,"OmegaMbar",  "#bar{#Omega}^{+}", filteringOnPt,minPt,maxPt,filteringOnEta,minEta,maxEta,filteringOnY,minY,maxY));

  return filters;
}





} // namespace CAP
