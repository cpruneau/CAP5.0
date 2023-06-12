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
#include "EventTask.hpp"
ClassImp(CAP::EventTask);
#include "FilterCreator.hpp"

namespace CAP
{

//!
//! Default constructor.
//!
EventTask::EventTask()
:
Task(),
eventsCreate             (false),
eventsRequested          (false),
eventsConvertToCAP       (false),
eventsImport             (false),
eventsImportTree         (""),
eventsImportPath         (""),
eventsImportFile         (""),
eventsImportFileMinIndex (0),
eventsImportFileMaxIndex (1),
eventsExport             (false),
eventsExportPath         (""),
eventsExportFile         (""),
eventsExportTree         (""),
eventsExportNative       (false),
eventsExportCAP          (false),
eventsExportMaxPerFile   (false),
eventsUseStream0         (false),
eventsUseStream1         (false),
eventsUseStream2         (false),
eventsUseStream3         (false),
eventsAnalyze            (false),
filtersUseModel          (false),
filtersUseGlobal         (false),
filtersUseAnalysis       (false),
calibsCreate             (false),
calibsReset              (false),
calibsClear              (false),
calibsForceRewrite       (false),
calibsImport             (false),
calibsImportPath         (""),
calibsImportFile         (""),
calibsExport             (false),
calibsExportAsRoot       (false),
calibsExportAsText       (false),
calibsExportPath         (""),
calibsExportFile         (""),
particleDb(nullptr),
particleFactory(nullptr),
eventStreams(),
nEventFilters(0),
nParticleFilters(0),
eventFilters(),
particleFilters(),
nEventsAccepted(),
nEventsAcceptedTotal(),
nParticlesAcceptedEvent(),
nParticlesAccepted(),
nParticlesAcceptedTotal()
{
  appendClassName("EventTask");
}

//!
//! Long constructor. 
//!
EventTask::EventTask(const String & _name,
                     const Configuration & _configuration)
:
Task(_name,_configuration),
eventsCreate             (false),
eventsRequested          (false),
eventsConvertToCAP       (false),
eventsImport             (false),
eventsImportTree         (""),
eventsImportPath         (""),
eventsImportFile         (""), 
eventsImportFileMinIndex (0),
eventsImportFileMaxIndex (1),
eventsExport             (false),
eventsExportPath         (""),
eventsExportFile         (""),
eventsExportTree         (""),
eventsExportNative       (false),
eventsExportCAP          (false),
eventsExportMaxPerFile   (false),
eventsUseStream0         (false),
eventsUseStream1         (false),
eventsUseStream2         (false),
eventsUseStream3         (false),
eventsAnalyze            (false),
filtersUseModel          (false),
filtersUseGlobal         (false),
filtersUseAnalysis       (true),
calibsCreate             (false),
calibsReset              (false),
calibsClear              (false),
calibsForceRewrite       (false),
calibsImport             (false),
calibsImportPath         (""),
calibsImportFile         (""),
calibsExport             (false),
calibsExportAsRoot       (false),
calibsExportAsText       (false),
calibsExportPath         (""),
calibsExportFile         (""),
particleDb(nullptr),
particleFactory(nullptr),
eventStreams(),
nEventFilters(0),
nParticleFilters(0),
eventFilters(),
particleFilters(),
nEventsAccepted(),
nEventsAcceptedTotal(),
nParticlesAcceptedEvent(),
nParticlesAccepted(),
nParticlesAcceptedTotal()
{
  appendClassName("EventTask");
}


//!
//! Initialize the configuration parameter of the EventTask to their default value;
//!
void EventTask::setDefaultConfiguration()
{
  Task::setDefaultConfiguration();
  addParameter("EventsCreate",                eventsCreate);
  addParameter("EventsRequested",             eventsRequested);
  addParameter("EventsConvertToCAP",          eventsConvertToCAP);
  addParameter("EventsImport",                eventsImport);
  addParameter("EventsImportTree",            eventsImportTree);
  addParameter("EventsImportPath",            eventsImportPath);
  addParameter("EventsImportFile",            eventsImportFile);
  addParameter("EventsImportFileMinIndex",    eventsImportFileMinIndex);
  addParameter("EventsImportFileMaxIndex",    eventsImportFileMaxIndex);
  addParameter("EventsExport",                eventsExport);
  addParameter("EventsExportPath",            eventsExportPath);
  addParameter("EventsExportFile",            eventsExportFile);
  addParameter("EventsExportTree",            eventsExportTree);
  addParameter("EventsExportNative",          eventsExportNative);
  addParameter("EventsExportCAP",             eventsExportCAP);
  addParameter("EventsExportMaxPerFile",      eventsExportMaxPerFile);
  addParameter("EventsUseStream0",            eventsUseStream0);
  addParameter("EventsUseStream1",            eventsUseStream1);
  addParameter("EventsUseStream2",            eventsUseStream2);
  addParameter("EventsUseStream3",            eventsUseStream3);
  addParameter("EventsAnalyze",               eventsAnalyze);
  addParameter("FiltersUseModel",             filtersUseModel);
  addParameter("FiltersUseGlobal",            filtersUseGlobal);
  addParameter("FiltersUseAnalysis",          filtersUseAnalysis);
  addParameter("CalibrationsCreate",          calibsCreate);
  addParameter("CalibrationsReset",           calibsReset);
  addParameter("CalibrationsClear",           calibsClear);
  addParameter("CalibrationsForceRewrite",    calibsForceRewrite);
  addParameter("CalibrationsImport",          calibsImport);
  addParameter("CalibrationsImportPath",      calibsImportPath);
  addParameter("CalibrationsImportFile",      calibsImportFile);
  addParameter("CalibrationsExport",          calibsExport);
  addParameter("CalibrationsExportAsRoot",    calibsExportAsRoot);
  addParameter("CalibrationsExportAsText",    calibsExportAsText);
  addParameter("CalibrationsExportPath",      calibsExportPath);
  addParameter("CalibrationsExportFile",      calibsExportFile);

}

//!
//! Set configuration parameters of this EventTask to values in the given config;
//!
void EventTask::configure()
{
  Task::configure();
  eventsCreate             = getValueBool(  "EventsCreate");
  eventsRequested          = getValueBool(  "EventsRequested");
  eventsConvertToCAP       = getValueBool(  "EventsConvertToCAP");
  eventsImport             = getValueBool(  "EventsImport");
  eventsImportTree         = getValueString("EventsImportTree");
  eventsImportPath         = getValueString("EventsImportPath");
  eventsImportFile         = getValueString("EventsImportFile");
  eventsImportFileMinIndex = getValueInt(   "EventsImportFileMinIndex");
  eventsImportFileMaxIndex = getValueInt(   "EventsImportFileMaxIndex");
  eventsExport             = getValueBool(  "EventsExport");
  eventsExportPath         = getValueString("EventsExportPath");
  eventsExportFile         = getValueString("EventsExportFile");
  eventsExportTree         = getValueString("EventsExportTree");
  eventsExportNative       = getValueBool(  "EventsExportNative");
  eventsExportCAP          = getValueBool(  "EventsExportCAP");
  eventsExportMaxPerFile   = getValueLong(  "EventsExportMaxPerFile");
  eventsUseStream0         = getValueBool(  "EventsUseStream0");
  eventsUseStream1         = getValueBool(  "EventsUseStream1");
  eventsUseStream2         = getValueBool(  "EventsUseStream2");
  eventsUseStream3         = getValueBool(  "EventsUseStream3");
  eventsAnalyze            = getValueBool(  "EventsAnalyze");
  filtersUseModel          = getValueBool(  "FiltersUseModel");
  filtersUseGlobal         = getValueBool(  "FiltersUseGlobal");
  filtersUseAnalysis       = getValueBool(  "FiltersUseAnalysis");

  calibsCreate       = getValueBool("CalibrationsCreate");
  calibsReset        = getValueBool("CalibrationsReset");
  calibsClear        = getValueBool("CalibrationsClear");
  calibsForceRewrite = getValueBool("CalibrationsForceRewrite");
  calibsImport       = getValueBool("CalibrationsImport");
  calibsImportPath   = getValueString("CalibrationsImportPath");
  calibsImportFile   = getValueString("CalibrationsImportFile");
  calibsExport       = getValueBool("CalibrationsExport");
  calibsExportAsRoot = getValueBool("CalibrationsExportAsRoot");
  calibsExportAsText = getValueBool("CalibrationsExportAsText");
  calibsExportPath   = getValueString("CalibrationsExportPath");
  calibsExportFile   = getValueString("CalibrationsExportFile");

  if (reportDebug(__FUNCTION__))
    {
    cout << endl;
    printItem("EventsCreate",            eventsCreate);
    printItem("EventsRequested",         eventsRequested);
    printItem("EventsConvertToCAP",      eventsConvertToCAP);
    printItem("EventsImport",            eventsImport);
    printItem("EventsImportTree",        eventsImportTree);
    printItem("EventsImportPath",        eventsImportPath);
    printItem("EventsImportFile",        eventsImportFile);
    printItem("EventsImportFileMinIndex",eventsImportFileMinIndex);
    printItem("EventsImportFileMaxIndex",eventsImportFileMaxIndex);
    printItem("EventsExport",            eventsExport);
    printItem("EventsExportPath",        eventsExportPath);
    printItem("EventsExportFile",        eventsExportFile);
    printItem("EventsExportTree",        eventsExportTree);
    printItem("EventsExportNative",      eventsExportNative);
    printItem("EventsExportCAP",         eventsExportCAP);
    printItem("EventsExportMaxPerFile",  eventsExportMaxPerFile);
    printItem("EventsUseStream0",        eventsUseStream0);
    printItem("EventsUseStream1",        eventsUseStream1);
    printItem("EventsUseStream2",        eventsUseStream2);
    printItem("EventsUseStream3",        eventsUseStream3);
    printItem("EventsAnalyze",           eventsAnalyze);
    printItem("FiltersUseModel",         filtersUseModel);
    printItem("FiltersUseGlobal",        filtersUseGlobal);
    printItem("FiltersUseAnalysis",      filtersUseAnalysis);
    }
}

void EventTask::initializeEventStreams()
{
  if (eventsUseStream0)  addEventStream(Event::getEventStream(0));
  if (eventsUseStream1)  addEventStream(Event::getEventStream(1));
  if (eventsUseStream2)  addEventStream(Event::getEventStream(2));
  if (eventsUseStream3)  addEventStream(Event::getEventStream(3));
}

void EventTask::initializeHistogramManager()
{
  // analyzer modules must implement this method
}

void EventTask::initializeFilters()
{
  if (reportInfo(__FUNCTION__)) cout << "Loading filters." << endl;
  if (filtersUseModel)
    {
    if (reportInfo(__FUNCTION__)) cout << "Using model filters." << endl;
    eventFilters = FilterCreator::getEventFiltersModel();
    particleFilters  = FilterCreator::getParticleFiltersModel();
    }
  if (filtersUseGlobal)
    {
    if (reportInfo(__FUNCTION__)) cout << "Using global filters." << endl;
    eventFilters = FilterCreator::getEventFiltersGlobal();
    particleFilters  = FilterCreator::getParticleFiltersGlobal();
    }
  if (filtersUseAnalysis)
    {
    if (reportInfo(__FUNCTION__)) cout << "Using analysis filters." << endl;
    eventFilters = FilterCreator::getEventFiltersAnalysis();
    particleFilters  = FilterCreator::getParticleFiltersAnalysis();
    }
  nEventFilters    = eventFilters.size();
  nParticleFilters = particleFilters.size();
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("nEventFilters",nEventFilters);
    printItem("nParticleFilters",nParticleFilters);
    }

}

//void initializeEvent();
//virtual void initializeEventCAP();
//virtual void initializeEventNative();

void EventTask::initializeEventGenerator() {}
void EventTask::initializeEventReader() {}
void EventTask::initializeEventWriter() {}

void EventTask::initializeParticleFactory()
{
  particleFactory = Particle::getFactory();
}

void EventTask::initializeParticleDbLink()
{
  particleDb = ParticleDb::getDefaultParticleDb();
}


void EventTask::importCalibrations()
{

}

void EventTask::createCalibrations()
{

}

void EventTask::exportCalibrations()
{

}


//!
//! Initialize this EventTask instance. Implement this method in a derived class if the functionality provided in this base class is insufficient.
//!
void EventTask::initialize()
{
  if (reportStart(__FUNCTION__))
    ;
  initializeTaskExecuted();
  initializeParticleDbLink();
  initializeFilters();
  initializeNEventsAccepted();
  initializeNParticlesAccepted();
  initializeEventStreams();
  initializeParticleFactory();
  initializeHistogramManager();
  if (eventsCreate)         initializeEventGenerator();
  if (eventsImport)         initializeEventReader();
  if (eventsExport)         initializeEventWriter();
  if (histosImport)         importHistograms();
  if (histosImportDerived)  importDerivedHistograms();
  if (histosCreate)         createHistograms();
  if (histosCreateDerived)  createDerivedHistograms();
  if (calibsImport)         importCalibrations();
  if (calibsCreate)         createCalibrations();
  if (hasSubTasks())        initializeSubTasks();
  if (reportEnd(__FUNCTION__))
    ;
}

void EventTask::finalizeEventStreams()
{
  Event::clearEventStreams();
}

void EventTask::finalizeEventGenerator()
{

}

void EventTask::finalizeEventReader()
{

}

void EventTask::finalizeEventWriter()
{

}

void EventTask::partial(const String & outputPathBase)
{
  if (reportInfo(__FUNCTION__))
    ;
  printEventStatistics();
  histosExportPath = outputPathBase;
  if (histosScale)          scaleHistograms();
  if (histosExport)         exportHistograms();
  //if (histosExportDerived)  exportHistograms();

  if (histosReset)   resetHistograms();
  if (hasSubTasks()) for (unsigned int  iTask=0; iTask<getNSubTasks(); iTask++)  subTasks[iTask]->partial(outputPathBase);
  if (reportEnd(__FUNCTION__))
    ;
}



//!
//! Finalize this Task instance. Implement this method in a derived class if the functionality provided in this base class is insufficient.
//!
void EventTask::finalize()
{
  if (reportInfo(__FUNCTION__))
    ;
  cout << endl;
  if (eventsImport || eventsCreate)  printEventStatistics();
  if (eventsCreate)  finalizeEventGenerator();
  if (eventsImport)  finalizeEventReader();
  if (eventsExport)  finalizeEventWriter();
  if (histosScale && !histosExportPartial)  scaleHistograms();
  if (histosExport&& !histosExportPartial)  exportHistograms();
  if (calibsExport)  exportCalibrations();
  if (hasSubTasks()) finalizeSubTasks();
  if (reportEnd(__FUNCTION__))
    ;
}

void EventTask::importEvent()
{
  if (eventsImportCAP)
    {
    importEventCAP();
    }
  if (eventsImportNative)
    {
    importEventNative();
    }
}

void EventTask::createEvent()
{
  cout << "EventTask::createEvent() Base==NoAction" << endl;
}

void EventTask::analyzeEvent()
{
  cout << "EventTask::analyzeEvent() Base==NoAction" << endl;

}

void EventTask::exportEvent()
{
  if (eventsCreateCAP || eventsConvertToCAP || eventsExportCAP)
    {
    exportEventCAP();
    }
  if (eventsCreateNative || eventsConvertToNative || eventsExportNative)
    {
    exportEventNative();
    }
}

void EventTask::execute()
{
//  if (reportInfo(__FUNCTION__))
//    {
//    cout << endl;
//    cout <<  left << setw(50) << setfill('.')<< "eventsImport" ,eventsImport << endl;
//    cout <<  left << setw(50) << setfill('.')<< "eventsCreate" ,eventsCreate << endl;
//    cout <<  left << setw(50) << setfill('.')<< "eventsAnalyze" ,eventsAnalyze << endl;
//    cout <<  left << setw(50) << setfill('.')<< "eventsExport" ,eventsExport << endl;
//    }

  incrementTaskExecuted();
  if (eventsImport)  importEvent();
  if (eventsCreate)  createEvent();
  if (eventsAnalyze) analyzeEvent();
  if (eventsExport)  exportEvent();
  if (hasSubTasks()) executeSubTasks();
}


//!
//! Reset this Task instance. Implement this method in a derived class if the functionality provided in this base class is insufficient.
//!
void EventTask::reset()
{
  if (reportStart(__FUNCTION__))
    ;
  resetTaskExecuted();
  resetNEventsAccepted();
  resetNParticlesAccepted();
  if (histosCreate)  resetHistograms();
  if (hasSubTasks()) resetSubTasks();
  if (reportEnd(__FUNCTION__))
    ;
}

//!
//! Clear this Task instance. Implement this method in a derived class if the functionality provided in this base class is insufficient.
//!
void EventTask::clear()
{
  if (reportStart(__FUNCTION__))
    ;
  clearNEventsAccepted();
  clearNParticlesAccepted();
  clearHistograms();
  if (hasSubTasks()) clearSubTasks();
  if (reportEnd(__FUNCTION__))
    ;
}


void EventTask::initializeNParticlesAccepted()
{
  int n = nEventFilters*nParticleFilters;
  nParticlesAcceptedTotal.assign(n,0);
  nParticlesAccepted.assign(n,0);
}

void EventTask::incrementNParticlesAccepted(int iEventFilter, int iParticleFilter)
{
  int index = iEventFilter*nParticleFilters+iParticleFilter;
  nParticlesAcceptedTotal[index]++;
  nParticlesAccepted[index]++;
}

void EventTask::resetNParticlesAcceptedEvent()
{
  int n = nEventFilters*nParticleFilters;
  nParticlesAccepted.assign(n,0);
}

void EventTask::resetNParticlesAccepted()
{
  int n = nEventFilters*nParticleFilters;
  nParticlesAcceptedTotal.assign(n,0);
  nParticlesAccepted.assign(n,0);
}

void EventTask::clearNParticlesAccepted()
{
  int n = nEventFilters*nParticleFilters;
  nParticlesAcceptedTotal.assign(n,0);
  nParticlesAccepted.assign(n,0);
}

int EventTask::getNParticlesAccepted(int iEventFilter, int iParticleFilter)  const
{
  if (iEventFilter<0 || iEventFilter>=nEventFilters)
    return -1;
  else
    {
    if (iParticleFilter<0 || iParticleFilter>=nParticleFilters)
      return -1;
    else
      return nParticlesAccepted[iEventFilter*nParticleFilters+iParticleFilter];
    }
}

int EventTask::getNParticlesAcceptedTotal(int iEventFilter, int iParticleFilter) const
{
  if (iEventFilter<0 || iEventFilter>=nEventFilters)
    return -1;
  else
    {
    if (iParticleFilter<0 || iParticleFilter>=nParticleFilters)
      return -1;
    else
      return nParticlesAcceptedTotal[iEventFilter*nParticleFilters+iParticleFilter];
    }
}



//!
//! Add the given event as a stream used by this Task instance.
//! @param event stream to be added to this Task.
//!
void EventTask::addEventStream(Event * event)
{
  eventStreams.push_back(event);
}

void EventTask::writeNEventsAccepted(TFile & outputFile)
{
  if (reportStart(__FUNCTION__))
    ;
  String parameterName = "nEventFilters";
  writeParameter(outputFile,parameterName,nEventFilters);

  for (int iFilter=0; iFilter<nEventFilters; iFilter++)
    {
    parameterName = "EventFilter";
    parameterName += iFilter;
    writeParameter(outputFile,parameterName,nEventsAccepted[iFilter]);
    }
  if (reportEnd(__FUNCTION__))
    ;
}

void EventTask::loadNEventsAccepted(TFile & inputFile)
{
  if (reportStart(__FUNCTION__))
    ;
  String parameterName = "nEventFilters";
  nEventFilters = readParameter(inputFile,parameterName);
  if (nEventsAccepted.size()<1) nEventsAccepted.assign(nEventFilters,0);
  for (int iFilter=0; iFilter<nEventFilters; iFilter++)
    {
    parameterName = "EventFilter";
    parameterName += iFilter;
    nEventsAccepted[iFilter] = readParameter(inputFile,parameterName);
    }
  if (reportEnd(__FUNCTION__))
    ;
}


void EventTask::printEventStatistics() const
{
  if (reportInfo(__FUNCTION__))
    ;
  cout << endl;
  printItem("TaskExecuted after reset",taskExecuted);
  printItem("TaskExecuted total",      taskExecutedTotal);
  printItem("n EventFilters",          nEventFilters);
  printItem("n ParticleFilters",       nParticleFilters);
  for (int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++)
    {
    cout << "Event filter:" << iEventFilter << " " << eventFilters[iEventFilter]->getName() << " #events : " << getAcceptedEventCount(iEventFilter) << endl;
    for (int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++)
      {
      cout
      << "Particle filter: "  << iParticleFilter
      << " " << particleFilters[iParticleFilter]->getName()
      << " (event): " << getNParticlesAccepted(iEventFilter,iParticleFilter)
      << " (total): " << getNParticlesAcceptedTotal(iEventFilter,iParticleFilter) << endl;
      }
    }
  if (reportEnd(__FUNCTION__))
    ;
}

//!
//! Clear the event filters used by this Task instance.
//!
void EventTask::clearEventFilters()
{
  eventFilters.clear();
  nEventFilters = eventFilters.size();
}

//!
//! Set the event filters used by this Task instance.
//!
void EventTask::setEventFilters(vector<EventFilter*> _eventFilters)
{
  eventFilters = _eventFilters;
  nEventFilters = eventFilters.size();
}

//!
//! Add an event filter to the event filters used by this Task instance.
//!
void EventTask::addEventFilter(EventFilter* _eventFilter)
{
  eventFilters.push_back(_eventFilter);
  nEventFilters = eventFilters.size();
}

//!
//! Return event filters used by this Task instance.
//!
vector<EventFilter*> & EventTask::getEventFilters()
{
  return eventFilters;
}

//!
//! Return event filters used by this Task instance.
//!
const vector<EventFilter*> & EventTask::getEventFilters() const
{
  return eventFilters;
}

//!
//! Clear the particle filters used by this Task instance.
//!
void EventTask::clearParticleFilters()
{
  particleFilters.clear();
  nParticleFilters = particleFilters.size();
}

//!
//! Set particle filters  used by this Task instance.
//!
void EventTask::setParticleFilters(vector<ParticleFilter*> _particleFilters)
{
  particleFilters = _particleFilters;
  nParticleFilters = particleFilters.size();
}

//!
//! Add a particle filter to the particle filters used by this Task instance.
//!
void EventTask::addParticleFilter(ParticleFilter* _particleFilter)
{
  particleFilters.push_back(_particleFilter);
  nParticleFilters = particleFilters.size();
}

//!
//! Return particle filters used by this Task instance.
//!
vector<ParticleFilter*> & EventTask::getParticleFilters()
{
  return particleFilters;
}

//!
//! Return particle filters used by this Task instance.
//!
const vector<ParticleFilter*> & EventTask::getParticleFilters() const
{
  return particleFilters;
}

void EventTask::resetEvent()
{
  if (eventsCreateCAP || eventsConvertToCAP || eventsImportCAP || eventsExportCAP)
    {
    resetEventCAP();
    }
  if (eventsCreateNative || eventsConvertToNative || eventsImportNative || eventsExportNative)
    {
    resetEventNative();
    }
}

void EventTask::resetEventCAP()
{

}

void EventTask::resetEventNative()
{

}

void EventTask::clearEvent()
{
  if (eventsCreateCAP || eventsConvertToCAP || eventsImportCAP || eventsExportCAP)
    {
    clearEventCAP();
    }
  if (eventsCreateNative || eventsConvertToNative || eventsImportNative || eventsExportNative)
    {
    clearEventNative();
    }
}


void EventTask::clearEventCAP()
{

}


void EventTask::clearEventNative()
{

}

void EventTask::importEventCAP() {}
void EventTask::importEventNative() {}
void EventTask::convertEventCAPToNative() {}
void EventTask::convertEventNativeToCAP() {}
void EventTask::exportEventCAP() {}
void EventTask::exportEventNative() {}


} // namespace CAP



