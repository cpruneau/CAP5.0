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

  addParameter("EventFilterGlobalOption",      TString("All"));
  addParameter("EventFilterGlobalNValues",     0);
  addParameter("EventFilterGlobalValue0",      0.0);
  addParameter("EventFilterGlobalValue1",      0.0);
  addParameter("EventFilterGlobalValue2",      0.0);
  addParameter("EventFilterGlobalValue3",      0.0);
  addParameter("EventFilterGlobalValue4",      0.0);
  addParameter("EventFilterGlobalValue5",      0.0);
  addParameter("EventFilterGlobalValue6",      0.0);
  addParameter("EventFilterGlobalValue7",      0.0);
  addParameter("EventFilterGlobalValue8",      0.0);
  addParameter("EventFilterGlobalValue9",      0.0);
  addParameter("EventFilterGlobalValue10",     0.0);
  addParameter("EventFilterGlobalValue11",     0.0);
  addParameter("EventFilterGlobalValue12",     0.0);

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
  addParameter("PartFilterModelFilterPt",   false);
  addParameter("PartFilterModelMinPt",      0.2);
  addParameter("PartFilterModelMaxPt",      2.0);
  addParameter("PartFilterModelFilterEta",  false);
  addParameter("PartFilterModelMinEta",     -4.0);
  addParameter("PartFilterModelMaxEta",     4.0);
  addParameter("PartFilterModelFilterY",    false);
  addParameter("PartFilterModelMinY",       -4.0);
  addParameter("PartFilterModelMaxY",       4.0);

  addParameter("PartFilterGlobalOption",       TString("All"));
  addParameter("PartFilterGlobalFilterPt",     false);
  addParameter("PartFilterGlobalMinPt",        0.0);
  addParameter("PartFilterGlobalMaxPt",        2.0);
  addParameter("PartFilterGlobalFilterEta",    false);
  addParameter("PartFilterGlobalMinEta",       -4.0);
  addParameter("PartFilterGlobalMaxEta",       4.0);
  addParameter("PartFilterGlobalFilterY",      false);
  addParameter("PartFilterGlobalMinY",         -4.0);
  addParameter("PartFilterGlobalMaxY",         4.0);

  addParameter("PartFilterAnaOption",       TString("All"));
  addParameter("PartFilterAnaFilterPt",     false);
  addParameter("PartFilterAnaMinPt",        0.0);
  addParameter("PartFilterAnaMaxPt",        2.0);
  addParameter("PartFilterAnaFilterEta",    false);
  addParameter("PartFilterAnaMinEta",       -4.0);
  addParameter("PartFilterAnaMaxEta",       4.0);
  addParameter("PartFilterAnaFilterY",      false);
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
  initializeParticleDbLink();
  createEventFilterContainers();
  createEventFilters(0);
  createEventFilters(1);
  createEventFilters(2);
  createParticleFilterContainers();
  createParticleFilters(0);
  createParticleFilters(1);
  createParticleFilters(2);

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

    cout << "  eventFiltersGlobal.size()..........: " << eventFiltersGlobal->size() << endl;
    for (unsigned int k=0; k<eventFiltersGlobal->size(); k++)
      cout << "    " << k << "   " << (*eventFiltersGlobal)[k]->getName() << endl;
    cout << "  particleFiltersGlobal.size().......: " << particleFiltersGlobal->size() << endl;
    for (unsigned int k=0; k<particleFiltersGlobal->size(); k++)
      cout << "    " << k << "   " << (*particleFiltersGlobal)[k]->getName() << endl;


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
vector<EventFilter*>    * FilterCreator::eventFiltersGlobal = nullptr;
vector<ParticleFilter*> * FilterCreator::particleFiltersGlobal = nullptr;
vector<EventFilter*>    * FilterCreator::eventFiltersAnalysis = nullptr;
vector<ParticleFilter*> * FilterCreator::particleFiltersAnalysis = nullptr;

void FilterCreator::createEventFilterContainers()
{
  if (eventFiltersModel!=nullptr)    throw TaskException("eventFiltersModel already created","FilterCreator::createEventFiltersModel()");
  if (eventFiltersGlobal!=nullptr)   throw TaskException("eventFiltersGlobal already created","FilterCreator::createEventFiltersGlobal()");
  if (eventFiltersAnalysis!=nullptr) throw TaskException("eventFiltersAnalysis already created","FilterCreator::createEventFiltersAnalysis()");

  eventFiltersModel     = new vector<EventFilter*>();
  eventFiltersGlobal    = new vector<EventFilter*>();
  eventFiltersAnalysis  = new vector<EventFilter*>();

}

void FilterCreator::createParticleFilterContainers()
{
  if (particleFiltersModel!=nullptr) throw TaskException("particleFiltersModel already created","FilterCreator::createParticleFiltersModel()");
  if (particleFiltersGlobal!=nullptr) throw TaskException("particleFiltersGlobal already created","FilterCreator::createParticleFiltersGlobal()");
  if (particleFiltersAnalysis!=nullptr) throw TaskException("particleFiltersAnalysis already created","FilterCreator::createParticleFiltersAnalysis()");
  particleFiltersModel    = new vector<ParticleFilter*>();
  particleFiltersGlobal   = new vector<ParticleFilter*>();
  particleFiltersAnalysis = new vector<ParticleFilter*>();

}

void FilterCreator::createEventFilters(unsigned int type)
{
  String selection;
  String keyBase;
  int    nBounds;
  switch (type)
    {
      case 0:
      selection = getValueString("EventFilterModelOption");
      keyBase   = "EventFilterModelValue";
      nBounds   = getValueInt(   "EventFilterModelNValues");
      break;
      case 1:
      selection = getValueString("EventFilterGlobalOption");
      keyBase   = "EventFilterGlobalValue";
      nBounds   = getValueInt(   "EventFilterGlobalNValues");
      break;
      case 2:
      selection = getValueString("EventFilterAnaOption");
      keyBase   = "EventFilterAnaValue";
      nBounds   = getValueInt(   "EventFilterAnaNValues");
      break;
    }
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("Event Filter Type",type);
    printItem("Selection",selection);
    printItem("nBounds",nBounds);
    }

  vector<double> bounds;
  for (int k=0; k<nBounds; k++)
    {
    String key = keyBase;  key += k;
    bounds.push_back( getValueDouble(key));
    }

  if (selection.EqualTo("All"))                   addEventFilters(type,createOpenEventFilter());
  else if (selection.EqualTo("AliceMB"))          addEventFilters(type,createAliceMBEventFilter());
  else if (selection.EqualTo("ImpactParameter"))  addEventFilters(type,createImpactParameterFilters(bounds));
  else if (selection.EqualTo("V0Mult"))           addEventFilters(type,createV0MultiplicityFilters(bounds));
  else if (selection.EqualTo("TpcMult"))          addEventFilters(type,createTpcMultiplicityFilters(bounds));
  else
    {
    throw TaskException("No valid option supplied","FilterCreator::createEventFilters(unsigned int type,  const String selection, vector<double> bounds)");
    }
}

void FilterCreator::createParticleFilters(unsigned int type)
{
  String selection;
  bool   filterPt;
  bool   filterEta;
  bool   filterY;
  double minPt,  maxPt;
  double minEta, maxEta;
  double minY,   maxY;

  switch (type)
    {
      case 0:
      selection = getValueString("PartFilterModelOption");
      filterPt  = getValueBool(  "PartFilterModelFilterPt");
      filterEta = getValueBool(  "PartFilterModelFilterEta");
      filterY   = getValueBool(  "PartFilterModelFilterY");
      minPt     = getValueDouble("PartFilterModelMinPt");
      maxPt     = getValueDouble("PartFilterModelMaxPt");
      minEta    = getValueDouble("PartFilterModelMinEta");
      maxEta    = getValueDouble("PartFilterModelMaxEta");
      minY      = getValueDouble("PartFilterModelMinY");
      maxY      = getValueDouble("PartFilterModelMaxY");
      break;
      case 1:
      selection = getValueString("PartFilterGlobalOption");
      filterPt  = getValueBool(  "PartFilterGlobalFilterPt");
      filterEta = getValueBool(  "PartFilterGlobalFilterEta");
      filterY   = getValueBool(  "PartFilterGlobalFilterY");
      minPt     = getValueDouble("PartFilterGlobalMinPt");
      maxPt     = getValueDouble("PartFilterGlobalMaxPt");
      minEta    = getValueDouble("PartFilterGlobalMinEta");
      maxEta    = getValueDouble("PartFilterGlobalMaxEta");
      minY      = getValueDouble("PartFilterGlobalMinY");
      maxY      = getValueDouble("PartFilterGlobalMaxY");
      break;
      case 2:
      selection = getValueString("PartFilterAnaOption");
      filterPt  = getValueBool(  "PartFilterAnaFilterPt");
      filterEta = getValueBool(  "PartFilterAnaFilterEta");
      filterY   = getValueBool(  "PartFilterAnaFilterY");
      minPt     = getValueDouble("PartFilterAnaMinPt");
      maxPt     = getValueDouble("PartFilterAnaMaxPt");
      minEta    = getValueDouble("PartFilterAnaMinEta");
      maxEta    = getValueDouble("PartFilterAnaMaxEta");
      minY      = getValueDouble("PartFilterAnaMinY");
      maxY      = getValueDouble("PartFilterAnaMaxY");
      break;
    }
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("Particle Filter Type",type);
    printItem("Selection",selection);
    printItem("filterPt", filterPt);
    printItem("filterEta",filterEta);
    printItem("filterY",  filterY);
    printItem("minPt",    minPt);
    printItem("maxPt",    maxPt);
    printItem("minEta",   minEta);
    printItem("maxEta",   maxEta);
    printItem("minY",     minY);
    printItem("maxY",     maxY);
    }

  // =========================================
  // Setup all particle filters
  // =========================================
  if (selection.EqualTo("All"))                   addParticleFilters(type,createOpenParticleFilter());
  else if (selection.EqualTo("AliceV0"))          addParticleFilters(type,createAliceV0Filter());
  else if (selection.EqualTo("Neutral"))          addParticleFilters(type,createNeutralParticleFilter(filterPt,minPt,maxPt,filterEta,minEta,maxEta,filterY,minY,maxY));
  else if (selection.EqualTo("Charged"))          addParticleFilters(type,createChargedParticleFilter(filterPt,minPt,maxPt,filterEta,minEta,maxEta,filterY,minY,maxY));
  else if (selection.EqualTo("Negative"))         addParticleFilters(type,createNegativeParticleFilter(filterPt,minPt,maxPt,filterEta,minEta,maxEta,filterY,minY,maxY));
  else if (selection.EqualTo("Positive"))         addParticleFilters(type,createPositiveParticleFilter(filterPt,minPt,maxPt,filterEta,minEta,maxEta,filterY,minY,maxY));
  else if (selection.EqualTo("ChargedHadrons"))   addParticleFilters(type,createChargedHadronFilters(filterPt,minPt,maxPt,filterEta,minEta,maxEta,filterY,minY,maxY));
  else if (selection.EqualTo("PlusMinusHadrons")) addParticleFilters(type,createPlusMinusHadronFilters(filterPt,minPt,maxPt,filterEta,minEta,maxEta,filterY,minY,maxY));
  else if (selection.EqualTo("StrangeHadrons"))   addParticleFilters(type,createStrangeHadronFilters(filterPt,minPt,maxPt,filterEta,minEta,maxEta,filterY,minY,maxY));
  else if (selection.EqualTo("Baryons"))          addParticleFilters(type,createBaryonFilters(filterPt,minPt,maxPt,filterEta,minEta,maxEta,filterY,minY,maxY));
  else if (selection.EqualTo("Index"))
    {
    if (!particleDb)
      throw TaskException("particleDb==nullptr","FilterCreator::initialize()");
    addParticleFilters(type,createIndexFilters(*particleDb,filterPt,minPt,maxPt,filterEta,minEta,maxEta,filterY,minY,maxY));
    }
  else
    throw TaskException("No valid option supplied","FilterCreator::createParticleFilters(unsigned int type)");
}



void FilterCreator::addEventFilter(unsigned int type, EventFilter* filter)
{
  switch (type)
    {
      case 0:
      if (eventFiltersModel==nullptr) throw TaskException("eventFiltersModel==nullptr","FilterCreator::addEventFilter(unsigned int type, EventFilter* filter)");
      eventFiltersModel->push_back(filter);
      break;
      case 1:
      if (eventFiltersGlobal==nullptr) throw TaskException("eventFiltersGlobal==nullptr","FilterCreator::addEventFilter(unsigned int type, EventFilter* filter)");
      eventFiltersGlobal->push_back(filter);
      break;
      case 2:
      if (eventFiltersAnalysis==nullptr) throw TaskException("eventFiltersAnalysis==nullptr","FilterCreator::addEventFilter(unsigned int type, EventFilter* filter)");
      eventFiltersAnalysis->push_back(filter);
      break;
    }
}

void FilterCreator::addParticleFilter(unsigned int type, ParticleFilter* filter)
{
  switch (type)
    {
      case 0:
      if (particleFiltersModel==nullptr) throw TaskException("particleFiltersModel==nullptr","FilterCreator::addParticleFilterModel(unsigned int type, ParticleFilter* filter)");
      particleFiltersModel->push_back(filter);
      break;
      case 1:
      if (particleFiltersGlobal==nullptr) throw TaskException("eventFiltersGlobal==nullptr","FilterCreator::addEventFilter(unsigned int type, EventFilter* filter)");
      particleFiltersGlobal->push_back(filter);
      break;
      case 2:
      if (particleFiltersAnalysis==nullptr) throw TaskException("eventFiltersAnalysis==nullptr","FilterCreator::addEventFilter(unsigned int type, EventFilter* filter)");
      particleFiltersAnalysis->push_back(filter);
      break;
    }
}



void FilterCreator::addEventFilters(unsigned int type, vector<EventFilter*>  filters)
{
  if (eventFiltersModel==nullptr) throw TaskException("eventFiltersModel==nullptr","FilterCreator::addEventFilters(unsigned int type, EventFilter* filter)");
  if (eventFiltersGlobal==nullptr) throw TaskException("eventFiltersGlobal==nullptr","FilterCreator::addEventFilters(unsigned int type, EventFilter* filter)");
  if (eventFiltersAnalysis==nullptr) throw TaskException("eventFiltersAnalysis==nullptr","FilterCreator::addEventFilters(vector<EventFilter*> & filters)");
  int n = filters.size();
  if (n<1)  throw TaskException("filters.size()<1","FilterCreator::addEventFiltersModel(vector<EventFilter*> & filters)");
  for (int k=0; k<n; k++)
    {
    switch (type)
      {
        case 0: eventFiltersModel->push_back(filters[k]);
        break;
        case 1: eventFiltersGlobal->push_back(filters[k]);
        break;
        case 2: eventFiltersAnalysis->push_back(filters[k]);
        break;
      }
    }
}

void FilterCreator::addParticleFilters(unsigned int type, vector<ParticleFilter*> filters)
{
  if (particleFiltersModel==nullptr)    throw TaskException("particleFiltersModel==nullptr","FilterCreator::addParticleFilters(unsigned int type, vector<ParticleFilter*>  filters)");
  if (particleFiltersGlobal==nullptr)   throw TaskException("particleFiltersGlobal==nullptr","FilterCreator::addParticleFilters(unsigned int type, vector<ParticleFilter*>  filters)");
  if (particleFiltersAnalysis==nullptr) throw TaskException("particleFiltersAnalysis==nullptr","FilterCreator::addParticleFilters(unsigned int type, vector<ParticleFilter*>  filters)");
  int n = filters.size();
  if (n<1)  throw TaskException("filters.size()<1","FilterCreator::addParticleFilters(vector<ParticleFilter*>  filters)");
  for (int k=0; k<n; k++)
    {
    switch (type)
      {
        case 0: particleFiltersModel->push_back(filters[k]);
        break;
        case 1: particleFiltersGlobal->push_back(filters[k]);
        break;
        case 2: particleFiltersAnalysis->push_back(filters[k]);
        break;
      }
    }
}

vector<EventFilter*> & FilterCreator::getEventFiltersModel()
{
  if (eventFiltersModel==nullptr) throw TaskException("eventFiltersModel==nullptr","FilterCreator::getEventFiltersModel()");
  return *eventFiltersModel;
}

vector<EventFilter*> & FilterCreator::getEventFiltersGlobal()
{
  if (eventFiltersGlobal==nullptr) throw TaskException("eventFiltersGlobal==nullptr","FilterCreator::getEventFiltersGlobal()");
  return *eventFiltersGlobal;
}

vector<EventFilter*> & FilterCreator::getEventFiltersAnalysis()
{
  if (eventFiltersAnalysis==nullptr) throw TaskException("eventFiltersAnalysis==nullptr","FilterCreator::getEventFiltersAnalysis()");
  return *eventFiltersAnalysis;
}

vector<ParticleFilter*> & FilterCreator::getParticleFiltersModel()
{
  if (particleFiltersModel==nullptr) throw TaskException("particleFiltersModel==nullptr","FilterCreator::getParticleFiltersModel()");
  return *particleFiltersModel;
}

vector<ParticleFilter*> & FilterCreator::getParticleFiltersGlobal()
{
  if (particleFiltersGlobal==nullptr) throw TaskException("particleFiltersGlobal==nullptr","FilterCreator::getParticleFiltersGlobal()");
  return *particleFiltersGlobal;
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

ParticleFilter *  FilterCreator::createIndexFilter(int pdgCode, const String & name, const String  & title,
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
  filter->addCondition(2, pdgCode,  double(pdgCode), double(pdgCode));   // accept particles w/ given pdg code
  if (filteringOnPt)   filter->addCondition(5, 1, minPt,  maxPt);
  if (filteringOnEta)  filter->addCondition(5, 7, minEta, maxEta);
  if (filteringOnY)    filter->addCondition(5, 8, minY,   maxY);
  return filter;
}

vector<ParticleFilter*> FilterCreator::createIndexFilters(ParticleDb & particleDb,
                                                          bool filteringOnPt,  double minPt,  double maxPt,
                                                          bool filteringOnEta, double minEta, double maxEta,
                                                          bool filteringOnY,   double minY,   double maxY)
{
  vector<ParticleFilter*> filters;
  int    pdgCode;
  String name;
  String title;
  int nTypes = particleDb.getNumberOfTypes();
  if (reportDebug(__FUNCTION__)) printItem("particleDb::nTypes",nTypes);
  for (int k=0; k<nTypes; k++)
    {
    ParticleType * particleType = particleDb.getParticleType(k);
    if (!particleType) throw TaskException("particleType==nullptr","FilterCreator::createIndexFilters(...)");
    pdgCode = particleType->getPdgCode();
    name    = particleType->getName();
    title   = particleType->getTitle();
    ParticleFilter * filter = createIndexFilter(pdgCode,name,title,
                                                filteringOnPt,minPt,maxPt,
                                                filteringOnEta,minEta,maxEta,
                                                filteringOnY,minY,maxY);
    if (reportDebug(__FUNCTION__)) printItem("Created index filter named",filter->getName());
    filters.push_back(filter);
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

// EventFilter
//  filterType  filterSubtype  Observable/Variable
//     10          any            ImpactParameter
//     11          0              AliceMBEvent  v0 multiplicity
//     11          1              AliceMBEvent  TPC multiplicity
//     12          0              V0Multiplicity
//     13          1              TpcMultiplicity

vector<EventFilter*> FilterCreator::createOpenEventFilter()
{
  vector<EventFilter*> filters;
  EventFilter * filter = new EventFilter();
  filter->setName("All");
  filter->setLongName("All");
  filter->setTitle("All");
  filter->setLongTitle("All");
  filters.push_back(filter);
  return filters;
}


vector<EventFilter*> FilterCreator::createImpactParameterFilters(vector<double> & bounds)
{
  vector<EventFilter*> filters;
  EventFilter* filter;
  int n = bounds.size();
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("bounds.size()",n);
    }
  for (int k=0; k<n-1; k++)
    {
    double low  = bounds[k];
    double high = bounds[k+1];
    String name = "b";
    name += int(1000*low);
    name +="To";
    name += int(1000*high);
    String title;
    title = low;
    title += "#LT b <";
    title += high;
    filter = new EventFilter();
    filter->setName(name);
    filter->setLongName(name);
    filter->setTitle(title);
    filter->setLongTitle(title);
    filter->addCondition(10, 0, low, high); // meant to cut on b
    filters.push_back(filter);
    }
  return filters;
}


vector<EventFilter*> FilterCreator::createAliceMBEventFilter()
{
  vector<EventFilter*> filters;
  EventFilter* filter  = new EventFilter();
  filter->setName("AliceMB");
  filter->setLongName("AliceMB");
  filter->setTitle("AliceMB");
  filter->setLongTitle("AliceMB");
  filter->addCondition(11, 0, 1.0, 1.0E10); // v0 multiplicity
  filter->addCondition(11, 1, 1.0, 1.0E10); // TPC multiplicity
  filters.push_back(filter);
  return filters;
}


vector<EventFilter*> FilterCreator::createV0MultiplicityFilters(vector<double> & bounds)
{
  int n = bounds.size();
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("bounds.size()",n);
    }
  vector<EventFilter*> filters;
  EventFilter* filter;
  for (int k=0; k<n-1; k++)
    {
    double low  = bounds[k];
    double high = bounds[k+1];
    String name = "V0M";
    name += int(1000*low);
    name +="To";
    name += int(1000*high);
    String title;
    title = low;
    title += "#LT V0M <";
    title += high;
    filter = new EventFilter();
    filter->setName(name);
    filter->setLongName(name);
    filter->setTitle(title);
    filter->setLongTitle(title);
    filter->addCondition(11, 0, low, high); // meant to cut on V0M
    filters.push_back(filter);
    }
  return filters;
}


vector<EventFilter*> FilterCreator::createTpcMultiplicityFilters(vector<double> & bounds)
{
  vector<EventFilter*> filters;
  EventFilter* filter;
  int n = bounds.size();
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("bounds.size()",n);
    }
  for (int k=0; k<n-1; k++)
    {
    double low  = bounds[k];
    double high = bounds[k+1];
    String name = "TPCMult";
    name += int(1000*low);
    name +="To";
    name += int(1000*high);
    String title;
    title = low;
    title += "#LT TPCMult <";
    title += high;
    filter = new EventFilter();
    filter->setName(name);
    filter->setLongName(name);
    filter->setTitle(title);
    filter->setLongTitle(title);
    filter->addCondition(11, 1, low, high); // meant to cut on V0M
    filters.push_back(filter);
    }
  return filters;
}


} // namespace CAP
