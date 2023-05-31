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
#include "RunAnalysis.hpp"
#include "ParticleDbManager.hpp"
#include "FilterCreator.hpp"
#include "TaskIterator.hpp"
#include "DerivedHistoIterator.hpp"
#include "BalanceFunctionCalculator.hpp"
#include "SubSampleStatCalculator.hpp"
#include "ClosureIterator.hpp"
#include "PythiaEventGenerator.hpp"
#include "AmptEventReader.hpp"
#include "TherminatorGenerator.hpp"
#include "ResonanceGenerator.hpp"
#include "MeasurementPerformanceSimulator.hpp"
#include "ParticlePerformanceAnalyzer.hpp"
#include "GlobalAnalyzer.hpp"
#include "TransverseSpherocityAnalyzer.hpp"
#include "ParticleSingleAnalyzer.hpp"
#include "ParticlePairAnalyzer.hpp"
#include "NuDynAnalyzer.hpp"
//#include "PythiaEventReader.hpp"
//#include "HerwigEventReader.hpp"
//#include "EposEventReader.hpp"
//#include "UrqmdEventReader.hpp"
//#include "HijingEventReader.hpp"


ClassImp(CAP::RunAnalysis);

namespace CAP
{
RunAnalysis::RunAnalysis(const String & _name,
                         const Configuration & _configuration)
:
Task(_name, _configuration),
labelParticleDb("ParticleDb"),
labelFilterCreator("Filter"),
labelBunch("Bunch"),
labelSubBunch(""),
labelGlobal("Global"),
labelSpherocity("Spherocity"),
labelSingle("Single"),
labelPair("Pair"),
labelNuDyn("NuDyn"),
labelSimAna("SimAna"),
labelDerived("Derived"),
labelSum("Sum"),
labelBalFct("BalFct"),
labelClosure("Closure"),
labelGenerator("Gen"),
labelReconstruction("Reco"),
labelPythia("Pythia"),
labelHerwig("Herwig"),
labelHijing("Hijing"),
labelAmpt("Ampt"),
labelEpos("Epos"),
labelUrqmd("Urqmd"),
labelTherminator("Therminator"),
labelResonance("Resonance"),
labelPerformance("Performance")
{
  appendClassName("RunAnalysis");
}


void RunAnalysis::setDefaultConfiguration()
{
  Task::setDefaultConfiguration();
  bool YES = true;
  bool NO  = false;
  addParameter("labelParticleDb",     labelParticleDb);
  addParameter("labelFilterCreator",  labelFilterCreator);
  addParameter("labelBunch",          labelBunch);
  addParameter("labelSubBunch",       labelSubBunch);
  addParameter("labelGlobal",         labelGlobal);
  addParameter("labelSpherocity",     labelSpherocity);
  addParameter("labelSingle",         labelSingle);
  addParameter("labelPair",           labelPair);
  addParameter("labelNuDyn",          labelNuDyn);
  addParameter("labelSimAna",         labelSimAna);
  addParameter("labelDerived",        labelDerived);
  addParameter("labelSum",            labelSum);
  addParameter("labelBalFct",         labelBalFct);
  addParameter("labelClosure",        labelClosure);
  addParameter("labelGenerator",      labelGenerator);
  addParameter("labelReconstruction", labelReconstruction);
  addParameter("labelPythia",         labelPythia);
  addParameter("labelHerwig",         labelHerwig);
  addParameter("labelHijing",         labelHijing);
  addParameter("labelAmpt",           labelAmpt);
  addParameter("labelEpos",           labelEpos);
  addParameter("labelUrqmd",          labelUrqmd);
  addParameter("labelTherminator",    labelTherminator);
  addParameter("labelResonance",      labelResonance);
  addParameter("labelPerformance",    labelPerformance);

  addParameter("Severity",                   TString("Info"));
  addParameter("RunParticleDbManager",       YES);
  addParameter("RunFilterCreator",           YES);

  addParameter("RunEventAnalysis",           YES);
  addParameter("RunEventAnalysisGen",        YES);
  addParameter("RunEventAnalysisReco",       NO);

  addParameter("RunDerived",                 NO);
  addParameter("RunDerivedGen",              NO);
  addParameter("RunDerivedReco",             NO);

  addParameter("RunBalFct",                  NO);
  addParameter("RunBalFctGen",               NO);
  addParameter("RunBalFctReco",              NO);

  addParameter("RunSubsample",               NO);
  addParameter("RunSubsampleBase",           NO);
  addParameter("RunSubsampleBaseGen",        NO);
  addParameter("RunSubsampleBaseReco",       NO);
  addParameter("RunSubsampleDerived",        NO);
  addParameter("RunSubsampleDerivedGen",     NO);
  addParameter("RunSubsampleDerivedReco",    NO);
  addParameter("RunSubsampleBalFct",         NO);
  addParameter("RunSubsampleBalFctGen",      NO);
  addParameter("RunSubsampleBalFctReco",     NO);

  addParameter("RunPerformanceSim",          NO);
  addParameter("RunPerformanceAna",          NO);
  addParameter("RunClosure",                 NO);

  addParameter("RunPythiaGenerator",         NO);
  addParameter("RunPythiaReader",            NO);
  addParameter("RunHerwigGenerator",         NO);
  addParameter("RunHerwigReader",            NO);
  addParameter("RunAmptGenerator",           NO);
  addParameter("RunAmptReader",              NO);
  addParameter("RunEposGenerator",           NO);
  addParameter("RunEposReader",              NO);
  addParameter("RunUrqmdReader",             NO);
  addParameter("RunTherminatorGenerator",    NO);
  addParameter("RunHijingReader",            NO);
  addParameter("RunResonanceGenerator",      NO);
  addParameter("RunGlobalAnalysisGen",       NO);
  addParameter("RunGlobalAnalysisReco",      NO);
  addParameter("RunSpherocityAnalysisGen",   NO);
  addParameter("RunSpherocityAnalysisReco",  NO);
  addParameter("RunPartSingleAnalysisGen",   NO);
  addParameter("RunPartSingleAnalysisReco",  NO);
  addParameter("RunPartPairAnalysisGen",     NO);
  addParameter("RunPartPairAnalysisReco",    NO);
  addParameter("RunNuDynAnalysisGen",        NO);
  addParameter("RunNuDynAnalysisReco",       NO);

//  addParameter("nEventsPerSubbunch",         long(100));
//  addParameter("nSubbunchesPerBunch",        int(10));
  addParameter("nBunches",                   int(10));
//
//  addParameter("EventsUseStream0",           true);
//  addParameter("EventsUseStream1",           false);
//  addParameter("EventsUseStream2",           false);
//  addParameter("EventsUseStream3",           false);

//  addParameter("SetSeed",                    true);
//  addParameter("SeedValue",                  long(121212121));
}


void RunAnalysis::configureLabels()
{
  labelParticleDb     = getValueString("labelParticleDb");
  labelFilterCreator  = getValueString("labelFilterCreator");
  labelBunch          = getValueString("labelBunch");
  labelSubBunch       = getValueString("labelSubBunch");
  labelGlobal         = getValueString("labelGlobal");
  labelSpherocity     = getValueString("labelSpherocity");
  labelSingle         = getValueString("labelSingle");
  labelPair           = getValueString("labelPair");
  labelNuDyn          = getValueString("labelNuDyn");
  labelSimAna         = getValueString("labelSimAna");
  labelDerived        = getValueString("labelDerived");
  labelSum            = getValueString("labelSum");
  labelBalFct         = getValueString("labelBalFct");
  labelClosure        = getValueString("labelClosure");
  labelGenerator      = getValueString("labelGenerator");
  labelReconstruction = getValueString("labelReconstruction");
  labelPythia         = getValueString("labelPythia");
  labelHerwig         = getValueString("labelHerwig");
  labelHijing         = getValueString("labelHijing");
  labelAmpt           = getValueString("labelAmpt");
  labelEpos           = getValueString("labelEpos");
  labelUrqmd          = getValueString("labelUrqmd");
  labelTherminator    = getValueString("labelTherminator");
  labelResonance      = getValueString("labelResonance");
  labelPerformance    = getValueString("labelPerformance");

  if (reportDebug(__FUNCTION__))
    {
    cout << endl;
    printItem("labelParticleDb",    labelParticleDb);
    printItem("labelFilterCreator", labelFilterCreator);
    printItem("labelBunch",         labelBunch);
    printItem("labelSubBunch",      labelSubBunch);
    printItem("labelGlobal",        labelGlobal);
    printItem("labelSpherocity",    labelSpherocity);
    printItem("labelSingle",        labelSingle);
    printItem("labelPair",          labelPair);
    printItem("labelNuDyn",         labelNuDyn);
    printItem("labelSimAna",        labelSimAna);
    printItem("labelDerived",       labelDerived);
    printItem("labelSum",           labelSum);
    printItem("labelBalFct",        labelBalFct);
    printItem("labelClosure",       labelClosure);
    printItem("labelGenerator",     labelGenerator);
    printItem("labelReconstruction",labelReconstruction);
    printItem("labelPythia",        labelPythia);
    printItem("labelHerwig",        labelHerwig);
    printItem("labelHijing",        labelHijing);
    printItem("labelAmpt",          labelAmpt);
    printItem("labelEpos",          labelEpos);
    printItem("labelUrqmd",         labelUrqmd);
    printItem("labelTherminator",   labelTherminator);
    printItem("labelResonance",     labelResonance);
    printItem("labelPerformance",   labelPerformance);
    }
}

void RunAnalysis::configure()
{
  if (reportStart(__FUNCTION__))
    ;
  Task::configure();
  setSeverity();

  try
  {

  configureLabels();
 // configuration.printConfiguration(cout); ex it(1);
  bool    runParticleDbManager            = getValueBool("RunParticleDbManager");
  bool    runFilterCreator                = getValueBool("RunFilterCreator");
  bool    runEventAnalysis                = getValueBool("RunEventAnalysis");
  bool    runEventAnalysisGen             = getValueBool("RunEventAnalysisGen");
  bool    runEventAnalysisReco            = getValueBool("RunEventAnalysisReco");

  bool    runDerived                      = getValueBool("RunDerived");
  bool    runDerivedGen                   = getValueBool("RunDerivedGen");
  bool    runDerivedReco                  = getValueBool("RunDerivedReco");

  bool    runBalFct                       = getValueBool("RunBalFct");
  bool    runBalFctGen                    = getValueBool("RunBalFctGen");
  bool    runBalFctReco                   = getValueBool("RunBalFctReco");

  bool    runSubsample                    = getValueBool("RunSubsample");
  bool    runSubsampleBase                = getValueBool("RunSubsampleBase");
  bool    runSubsampleBaseGen             = getValueBool("RunSubsampleBaseGen");
  bool    runSubsampleBaseReco            = getValueBool("RunSubsampleBaseReco");
  bool    runSubsampleDerived             = getValueBool("RunSubsampleDerived");
  bool    runSubsampleDerivedGen          = getValueBool("RunSubsampleDerivedGen");
  bool    runSubsampleDerivedReco         = getValueBool("RunSubsampleDerivedReco");
  bool    runSubsampleBalFct              = getValueBool("RunSubsampleBalFct");
  bool    runSubsampleBalFctGen           = getValueBool("RunSubsampleBalFctGen");
  bool    runSubsampleBalFctReco          = getValueBool("RunSubsampleBalFctReco");

  bool    runPerformanceSim               = getValueBool("RunPerformanceSim");
  bool    runPerformanceAna               = getValueBool("RunPerformanceAna");
  bool    runClosure                      = getValueBool("RunClosure");
  bool    runPythiaGenerator              = getValueBool("RunPythiaGenerator");
  bool    runPythiaReader                 = getValueBool("RunPythiaReader");
  bool    runHerwigGenerator              = getValueBool("RunHerwigGenerator");
  bool    runHerwigReader                 = getValueBool("RunHerwigReader");
  bool    runAmptGenerator                = getValueBool("RunAmptGenerator");
  bool    runAmptReader                   = getValueBool("RunAmptReader");
  bool    runEposGenerator                = getValueBool("RunEposGenerator");
  bool    runEposReader                   = getValueBool("RunEposReader");
  bool    runUrqmdReader                  = getValueBool("RunUrqmdReader");
  bool    runTherminatorGenerator         = getValueBool("RunTherminatorGenerator");
  bool    runHijingReader                 = getValueBool("RunHijingReader");
  bool    runResonanceGenerator           = getValueBool("RunResonanceGenerator");
  bool    runGlobalAnalysisGen            = getValueBool("RunGlobalAnalysisGen");
  bool    runGlobalAnalysisReco           = getValueBool("RunGlobalAnalysisReco");
  bool    runSpherocityAnalysisGen        = getValueBool("RunSpherocityAnalysisGen");
  bool    runSpherocityAnalysisReco       = getValueBool("RunSpherocityAnalysisReco");
  bool    runPartSingleAnalysisGen        = getValueBool("RunPartSingleAnalysisGen");
  bool    runPartSingleAnalysisReco       = getValueBool("RunPartSingleAnalysisReco");
  bool    runPartPairAnalysisGen          = getValueBool("RunPartPairAnalysisGen");
  bool    runPartPairAnalysisReco         = getValueBool("RunPartPairAnalysisReco");
  bool    runNuDynAnalysisGen             = getValueBool("RunNuDynAnalysisGen");
  bool    runNuDynAnalysisReco            = getValueBool("RunNuDynAnalysisReco");
  int     nBunches                        = getValueInt ("nBunches");
  String importPathName                   = getValueString("HistogramsImportPath");
  String exportPathName                   = getValueString("HistogramsExportPath");
//  bool   setSeed                          = getValueBool(  "SetSeed");
//  long   seedValue                        = getValueLong(  "SeedValue");

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;

    printItem("RunParticleDbManager",  runParticleDbManager);
    printItem("RunFilterCreator",      runFilterCreator);

    printItem("RunEventAnalysis",      runEventAnalysis);
    printItem("RunEventAnalysisGen",   runEventAnalysisGen);
    printItem("RunEventAnalysisReco",  runEventAnalysisReco);

    printItem("RunDerived",            runDerived);
    printItem("RunDerivedGen",         runDerivedGen);
    printItem("RunDerivedReco",        runDerivedReco);
    printItem("RunDerivedGen",         runDerivedGen);
    printItem("RunDerivedReco",        runDerivedReco);

    printItem("RunBalFct",             runBalFct);
    printItem("RunBalFctGen",          runBalFctGen);
    printItem("RunBalFctReco",         runBalFctReco);

    printItem("RunSubsample",            runSubsample);
    printItem("RunSubsampleBase",        runSubsampleBase);
    printItem("RunSubsampleBaseGen",     runSubsampleBaseGen);
    printItem("RunSubsampleBaseReco",    runSubsampleBaseReco);
    printItem("RunSubsampleDerived",     runSubsampleDerived);
    printItem("RunSubsampleDerivedGen",  runSubsampleDerivedGen);
    printItem("RunSubsampleDerivedReco", runSubsampleDerivedReco);
    printItem("RunSubsampleBalFct",      runSubsampleBalFct);
    printItem("RunSubsampleBalFctGen",   runSubsampleBalFctGen);
    printItem("RunSubsampleBalFctReco",  runSubsampleBalFctReco);


    printItem("RunPerformanceSim",        runPerformanceSim);
    printItem("RunPerformanceAna",        runPerformanceAna);
    printItem("RunClosure",               runClosure);
    printItem("RunPythiaGenerator",       runPythiaGenerator);
    printItem("RunPythiaReader",          runPythiaReader);
    printItem("RunHerwigGenerator",       runHerwigGenerator);
    printItem("RunHerwigReader",          runHerwigReader);
    printItem("RunAmptGenerator",         runAmptGenerator);
    printItem("RunAmptReader",            runAmptReader);
    printItem("RunEposGenerator",         runEposGenerator);
    printItem("RunEposReader",            runEposReader);
    printItem("RunUrqmdReader",           runUrqmdReader);
    printItem("RunTherminatorGenerator",  runTherminatorGenerator);
    printItem("RunHijingReader",          runHijingReader);
    printItem("RunResonanceGenerator",    runResonanceGenerator);
    printItem("RunGlobalAnalysisGen",     runGlobalAnalysisGen);
    printItem("RunGlobalAnalysisReco",    runGlobalAnalysisReco);
    printItem("RunSpherocityAnalysisGen", runSpherocityAnalysisGen);
    printItem("RunSpherocityAnalysisReco",runSpherocityAnalysisReco);
    printItem("RunPartSingleAnalysisGen", runPartSingleAnalysisGen);
    printItem("RunPartSingleAnalysisReco",runPartSingleAnalysisReco);
    printItem("RunPartPairAnalysisGen",   runPartPairAnalysisGen);
    printItem("RunPartPairAnalysisReco",  runPartPairAnalysisReco);
    printItem("RunNuDynAnalysisGen",      runNuDynAnalysisGen);
    printItem("RunNuDynAnalysisReco",     runNuDynAnalysisReco);
    printItem("HistogramsImportPath",     importPathName);
    printItem("HistogramsExportPath",     exportPathName);
    printItem("nBunches",                 nBunches);
//    printItem("SetSeed",                  setSeed);
//    printItem("SeedValue",                seedValue);
    cout << endl;
    }

  if (runParticleDbManager)
    {
    if (reportInfo(__FUNCTION__)) cout << "Setting up ParticleDb" << std::endl;
    ParticleDbManager * particleDbManager = new ParticleDbManager("ParticleDb",*requestedConfiguration);
    addSubTask(particleDbManager);
    }

  if (runFilterCreator)
    {
    if (reportInfo(__FUNCTION__)) cout << "Setting up Filters" << std::endl;
    FilterCreator * filterCreator = new FilterCreator("Filter",*requestedConfiguration);
    addSubTask(filterCreator);
    }

  if (runEventAnalysis)
    {
    if (reportInfo(__FUNCTION__)) cout << "Setting up event analysis" << std::endl;
    TaskIterator * eventAnalysis = new TaskIterator("Analysis",*requestedConfiguration);
    addSubTask(eventAnalysis);

    //if (runPythiaReader)         eventAnalysis->addSubTask(new PythiaEventReader(labelPythia,*requestedConfiguration));
    //if (runHerwigReader)         eventAnalysis->addSubTask(new HerwigEventReader(labelHerwig,*requestedConfiguration));
    //if (runEposReader)           eventAnalysis->addSubTask(new EposEventReader(labelEpos,*requestedConfiguration));
    //if (runUrqmdReader)          eventAnalysis->addSubTask(new UrqmdEventReader(labelUrqmd,*requestedConfiguration));
    //if (runHijingReader)         eventAnalysis->addSubTask(new HijingEventReader(labelHijing,*requestedConfiguration));
    if (runPythiaGenerator)         eventAnalysis->addSubTask(new PythiaEventGenerator(labelPythia,*requestedConfiguration));
    if (runAmptReader)              eventAnalysis->addSubTask(new AmptEventReader(labelAmpt,*requestedConfiguration));
    if (runTherminatorGenerator)    eventAnalysis->addSubTask(new TherminatorGenerator(labelTherminator,*requestedConfiguration));
    if (runResonanceGenerator)      eventAnalysis->addSubTask(new ResonanceGenerator(labelResonance,*requestedConfiguration));
    if (runPerformanceSim)          eventAnalysis->addSubTask(new MeasurementPerformanceSimulator(labelPerformance,*requestedConfiguration));

    if (runEventAnalysisGen)
      {
      if (runGlobalAnalysisGen)       eventAnalysis->addSubTask(new GlobalAnalyzer(labelGlobal+labelGenerator, *requestedConfiguration));
      if (runSpherocityAnalysisGen)   eventAnalysis->addSubTask(new TransverseSpherocityAnalyzer(labelSpherocity+labelGenerator, *requestedConfiguration));
      if (runPartSingleAnalysisGen)   eventAnalysis->addSubTask(new ParticleSingleAnalyzer(labelSingle+labelGenerator, *requestedConfiguration));
      if (runPartPairAnalysisGen)     eventAnalysis->addSubTask(new ParticlePairAnalyzer(labelPair+labelGenerator, *requestedConfiguration));
      if (runNuDynAnalysisGen)        eventAnalysis->addSubTask(new NuDynAnalyzer(labelNuDyn+labelGenerator,*requestedConfiguration));
      }

    if (runEventAnalysisReco)
      {
      if (runGlobalAnalysisReco)      eventAnalysis->addSubTask(new GlobalAnalyzer(labelGlobal+labelReconstruction,*requestedConfiguration));
      if (runSpherocityAnalysisReco)  eventAnalysis->addSubTask(new TransverseSpherocityAnalyzer(labelSpherocity+labelReconstruction, *requestedConfiguration));
      if (runPartSingleAnalysisReco)  eventAnalysis->addSubTask(new ParticleSingleAnalyzer(labelSingle+labelReconstruction, *requestedConfiguration));
      if (runPartPairAnalysisReco)    eventAnalysis->addSubTask(new ParticlePairAnalyzer(labelPair+labelReconstruction, *requestedConfiguration));
      if (runNuDynAnalysisReco)       eventAnalysis->addSubTask(new NuDynAnalyzer(labelNuDyn+labelReconstruction,*requestedConfiguration));
      if (runPerformanceAna)          eventAnalysis->addSubTask(new ParticlePerformanceAnalyzer(labelSimAna,*requestedConfiguration));
      }

    if (reportInfo(__FUNCTION__)) cout << "Event Analysis Setup Completed" << std::endl;
    }

  if (runDerived)
    {
    if (reportInfo(__FUNCTION__)) cout << "Setting up derived calculation" << std::endl;
    TString taskName;
    TString configBasePath;
    TString configPath = "Run:Analysis";
    TString subTaskName;
    TString subConfigBasePath;
    TString subConfigPath;

    if (runDerivedGen)
      {
      if (reportInfo(__FUNCTION__)) cout << "Setting up DerivedGen" << std::endl;
      Configuration & dConfig = * new Configuration(configuration);
      taskName       = "Analysis";
      configBasePath = "Run:";
      configPath     = configBasePath + taskName;  configPath += ":";
      dConfig.addParameter(configPath+"HistogramsImportPath",histosImportPath);
      dConfig.addParameter(configPath+"HistogramsExportPath",histosExportPath);
      dConfig.addParameter(configPath+"IncludedPattern0",TString("Sum"));
      dConfig.addParameter(configPath+"ExcludedPattern0",TString("Reco"));
      dConfig.addParameter(configPath+"ExcludedPattern1",TString("BalFct"));
      dConfig.addParameter(configPath+"ExcludedPattern2",TString("Derived"));
      DerivedHistoIterator * derived = new DerivedHistoIterator(taskName,dConfig);
      addSubTask(derived);

      //    if (runGlobalAnalysisGen)          derived->addSubTask(new GlobalAnalyzer(labelGlobal+labelGenerator, configuration));
      //    if (runSpherocityAnalysisGen)      derived->addSubTask(new TransverseSpherocityAnalyzer(labelSpherocity+labelGenerator, configuration));

      if (runPartSingleAnalysisGen)
        {
        Configuration & subConfig = * new Configuration(configuration);
        subTaskName       = labelSingle+labelGenerator;
        subConfigBasePath = configPath;
        subConfigPath     = subConfigBasePath + subTaskName;  subConfigPath += ":";

        subConfig.addParameter(subConfigPath+"HistogramsCreate",         false);
        subConfig.addParameter(subConfigPath+"HistogramsCreateDerived",  true);
        subConfig.addParameter(subConfigPath+"HistogramsReset",          false);
        subConfig.addParameter(subConfigPath+"HistogramsClear",          true);
        subConfig.addParameter(subConfigPath+"HistogramsScale",          false);
        subConfig.addParameter(subConfigPath+"HistogramsForceRewrite",   true);
        subConfig.addParameter(subConfigPath+"HistogramsImportPath",histosImportPath);
        subConfig.addParameter(subConfigPath+"HistogramsExportPath",histosExportPath);
        subConfig.addParameter(subConfigPath+"IncludedPattern0",TString(subTaskName));
        subConfig.addParameter(subConfigPath+"IncludedPattern1",TString("Sum"));
        subConfig.addParameter(subConfigPath+"ExcludedPattern0",TString("Reco"));
        subConfig.addParameter(subConfigPath+"ExcludedPattern2",TString("Derived"));
        subConfig.addParameter(subConfigPath+"ExcludedPattern1",TString("BalFct"));
        derived->addSubTask(new ParticleSingleAnalyzer(subTaskName, subConfig));
        }

      if (runPartPairAnalysisGen)
        {
        Configuration & subConfig = * new Configuration(dConfig);
        subTaskName       = labelPair+labelGenerator;
        subConfigBasePath = configPath;
        subConfigPath     = subConfigBasePath + subTaskName;  subConfigBasePath += ":";
        subConfig.addParameter(subConfigPath+"HistogramsImportPath",histosImportPath);
        subConfig.addParameter(subConfigPath+"HistogramsExportPath",histosExportPath);
        subConfig.addParameter(subConfigPath+"IncludedPattern0",TString("Sum"));
        subConfig.addParameter(subConfigPath+"ExcludedPattern0",TString("Reco"));
        subConfig.addParameter(subConfigPath+"ExcludedPattern1",TString("BalFct"));
        subConfig.addParameter(subConfigPath+"ExcludedPattern2",TString("Derived"));
        derived->addSubTask(new ParticlePairAnalyzer(subTaskName, subConfig));
        }

      //    if (runNuDynAnalysisGen)           derived->addSubTask(new NuDynAnalyzer(labelNuDyn+labelGenerator,configuration));
      //    if (runGlobalAnalysisReco)         derived->addSubTask(new GlobalAnalyzer(labelGlobal+labelReconstruction, configuration));
      //    if (runSpherocityAnalysisReco)     derived->addSubTask(new TransverseSpherocityAnalyzer(labelSpherocity+labelReconstruction, configuration));
      //    if (runPartSingleAnalysisReco)     derived->addSubTask(new ParticleSingleAnalyzer(labelSingle+labelReconstruction, configuration));
      //    if (runPartPairAnalysisReco)       derived->addSubTask(new ParticlePairAnalyzer(labelPair+labelReconstruction, configuration));
      //    if (runNuDynAnalysisReco)          derived->addSubTask(new NuDynAnalyzer(labelNuDyn+labelReconstruction,configuration));
      if (reportInfo(__FUNCTION__)) cout << "DerivedGen Setup Completed" << std::endl;
      }

    if (runDerivedReco)
      {
      // to be implemented
      }

    if (runBalFct)
      {
      if (reportInfo(__FUNCTION__)) cout << "Setting up BalFct" << std::endl;

      if (runBalFctGen && runPartPairAnalysisGen)
        {
        Configuration & dConfig = * new Configuration(configuration);
        taskName       = "PairGen";
        configBasePath = "Run:";
        configPath     = configBasePath + taskName;  configPath += ":";
        dConfig.addParameter(configPath+"HistogramsImportPath",histosImportPath);
        dConfig.addParameter(configPath+"HistogramsExportPath",histosExportPath);
        dConfig.addParameter(configPath+"IncludedPattern0",TString("Sum"));
        dConfig.addParameter(configPath+"IncludedPattern1",TString("Derived"));
        dConfig.addParameter(configPath+"IncludedPattern2",TString("Gen"));
        dConfig.addParameter(configPath+"ExcludedPattern0",TString("Reco"));
        dConfig.addParameter(configPath+"ExcludedPattern1",TString("BalFct"));
        dConfig.addParameter(configPath+"ExcludedPattern2",TString("Single"));
        dConfig.addParameter(configPath+"AppendedString",  TString("BalFct"));
        dConfig.printConfiguration(cout);
        addSubTask(new BalanceFunctionCalculator(taskName,dConfig));
        }
      if (runBalFctReco && runPartPairAnalysisReco)
        {
        // to be implmented
        }
      if (reportInfo(__FUNCTION__)) cout << "BalFct Setup Completed" << std::endl;

      }
    if (reportInfo(__FUNCTION__)) cout << "Derived calculation Setup Completed" << std::endl;
    }

  int maximumDepth= 1;

  if (runSubsample)
    {
    if (reportInfo(__FUNCTION__)) cout << "Setting up Subsample calculation" << std::endl;
    if (runSubsampleBase)
      {
      maximumDepth = 2;
      if (runSubsampleBaseGen)
        {
        if (runGlobalAnalysisGen)     addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelGlobal+labelGenerator);
        if (runSpherocityAnalysisGen) addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSpherocity+labelGenerator);
        if (runPartSingleAnalysisGen) addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSingle+labelGenerator);
        if (runPartPairAnalysisGen)   addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelGenerator);
        if (runNuDynAnalysisGen)      addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelNuDyn+labelGenerator);
        }
      if (runSubsampleBaseReco)
        {
        if (runGlobalAnalysisReco)     addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelGlobal+labelReconstruction);
        if (runSpherocityAnalysisReco) addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSpherocity+labelReconstruction);
        if (runPartSingleAnalysisReco) addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSingle+labelReconstruction);
        if (runPartPairAnalysisReco)   addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelReconstruction);
        if (runNuDynAnalysisReco)      addBaseSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelNuDyn+labelReconstruction);
        }
      }
    if (runSubsampleDerived)
      {
      maximumDepth = 1;
      if (runSubsampleDerivedGen)
        {
        if (runGlobalAnalysisGen)     addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelGlobal+labelGenerator);
        if (runSpherocityAnalysisGen) addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSpherocity+labelGenerator);
        if (runPartSingleAnalysisGen) addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSingle+labelGenerator);
        if (runPartPairAnalysisGen)   addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelGenerator);
        if (runNuDynAnalysisGen)      addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelNuDyn+labelGenerator);
        }
      if (runSubsampleDerivedReco)
        {
        if (runGlobalAnalysisReco)     addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelGlobal+labelReconstruction);
        if (runSpherocityAnalysisReco) addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSpherocity+labelReconstruction);
        if (runPartSingleAnalysisReco) addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSingle+labelReconstruction);
        if (runPartPairAnalysisReco)   addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelReconstruction);
        if (runNuDynAnalysisReco)      addDerivedSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelNuDyn+labelReconstruction);
        }
      }
    if (runSubsampleBalFct)
      {
      maximumDepth = 1;
      if (runSubsampleBalFctGen)
        {
        if (runPartPairAnalysisGen)   addBalFctSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelGenerator);
        }
      if (runSubsampleBalFctReco)
        {
        if (runPartPairAnalysisReco)  addBalFctSubSampleTask(importPathName,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelReconstruction);
        }
      }
    if (reportInfo(__FUNCTION__)) cout << "Subsample calculation Setup Completed" << std::endl;
    }

  gSystem->mkdir(exportPathName,1);
  if (hasSubTasks())
    for (unsigned int  iTask=0; iTask<subTasks.size(); iTask++)
      {
      subTasks[iTask]->configure();
      }
  }
  catch (TaskException te)
  {
  te.print(); exit(1);
  }
  catch (ConfigurationException ce)
  {
  ce.print(); exit(1);
  }
  catch (MathException me)
  {
  me.print(); exit(1);
  }
  catch (FileException fe)
  {
  fe.print(); exit(1);
  }
  catch (MemoryException mme)
  {
  mme.print(); exit(1);
  }
  catch (HistogramException he)
  {
  he.print(); exit(1);
  }
  catch (FactoryException ffe)
  {
  ffe.print(); exit(1);
  }
  catch (Exception e)
  {
  e.print(); exit(1);
  }

  if (reportEnd(__FUNCTION__))
    ;
}

void RunAnalysis::execute()
{
  try
  {
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    cout << "==================================================================================" << std::endl;
    cout << "Analysis Started" << std::endl;
    cout << "==================================================================================" << std::endl;
    }

//  int n = subTasks.size();
//  cout << "Number of subtasks: " << n << endl;;
//  for (int k=0; k<n; k++ )
//    cout << " sub taskName: " << subTasks[k]->getName()<< endl;
//  exit(1);
  initializeSubTasks();
  executeSubTasks();
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    cout << "==================================================================================" << std::endl;
    cout << "Analysis Completed" << std::endl;
    cout << "==================================================================================" << std::endl;
    }
  }

  catch (TaskException te)
  {
  te.print(); exit(1);
  }
  catch (ConfigurationException ce)
  {
  ce.print(); exit(1);
  }
  catch (MathException me)
  {
  me.print(); exit(1);
  }
  catch (FileException fe)
  {
  fe.print(); exit(1);
  }
  catch (MemoryException mme)
  {
  mme.print(); exit(1);
  }
  catch (HistogramException he)
  {
  he.print(); exit(1);
  }
  catch (FactoryException ffe)
  {
  ffe.print(); exit(1);
  }
  catch (Exception e)
  {
  e.print(); exit(1);
  }



}

void RunAnalysis::addBaseSubSampleTask(const String & basePath,
                                        const String & labelBunch,
                                        int   nBunches,
                                        const String & subPath,
                                        int   maximumDepth,
                                        const String & taskType)
{


  if (nBunches>0)
    {
    for (int k=1;k<=nBunches; k++)
      {
      String inputPathName  = TString(Form("%s/%s%02d/%s",basePath.Data(),labelBunch.Data(),k,subPath.Data()));
      String outputPathName = TString(Form("%s/%s%02d/",basePath.Data(),labelBunch.Data(),k));
      Configuration & subConfig = * new Configuration(configuration);
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),TString("Gen"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern0"),TString("Reco"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern1"),TString("Derived"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern2"),TString("BalFct"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern3"),TString("Sum"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":AppendedString"),TString("Sum"));
      // subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"), maximumDepth);
      //subConfig.printConfiguration(cout);
      addSubTask( new SubSampleStatCalculator(taskType,subConfig));
      }
    }
  else // not bunched
    {
    String inputPathName  = TString(Form("%s/",basePath.Data()));
    String outputPathName = inputPathName;
    Configuration & subConfig = * new Configuration(configuration);
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),TString("Gen"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern0"),TString("Reco"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern1"),TString("Derived"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern2"),TString("BalFct"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern3"),TString("Sum"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":AppendedString"),TString("Sum"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"),maximumDepth);
    subConfig.printConfiguration(cout);
    addSubTask( new SubSampleStatCalculator(taskType,subConfig));
    }
}

void RunAnalysis::addDerivedSubSampleTask(const String & basePath,
                                           const String & labelBunch,
                                           int   nBunches,
                                           const String & subPath __attribute__((unused)),
                                           int   maximumDepth,
                                           const String & taskType)
{
  if (nBunches>0)
    {
    for (int k=1;k<=nBunches; k++)
      {
      String inputPathName  = basePath;  //TString(Form("%s/%s%02d/",basePath.Data(),labelBunch.Data(),k));
      String outputPathName = basePath;  //.Data(); // TString(Form("%s/%s%02d/",,"",k));
      Configuration & subConfig = * new Configuration(configuration);
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),TString("Gen"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern1"),TString("Derived"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern0"),TString("Reco"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern1"),TString("BalFct"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":AppendedString"),TString("DerivedSum"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"),1);
      // subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"),maximumDepth);
      //subConfig.printConfiguration(cout);
      addSubTask( new SubSampleStatCalculator(taskType,subConfig));
      }
    }
  else // not bunched
    {
    String inputPathName  = TString(Form("%s/",basePath.Data()));
    String outputPathName = inputPathName;
    Configuration & subConfig = * new Configuration(configuration);
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),TString("Gen"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern1"),TString("Derived"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern0"),TString("Reco"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern1"),TString("BalFct"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":AppendedString"),TString("DerivedSum"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"),1);
    subConfig.printConfiguration(cout);
    addSubTask( new SubSampleStatCalculator(taskType,subConfig));
    }
}

void RunAnalysis::addBalFctSubSampleTask(const String & basePath,
                                          const String & labelBunch,
                                          int   nBunches,
                                          const String & subPath __attribute__((unused)),
                                          int   maximumDepth,
                                          const String & taskType)
{
  if (nBunches>0)
    {
    for (int k=1;k<=nBunches; k++)
      {
      String inputPathName  = TString(Form("%s/%s%02d/",basePath.Data(),labelBunch.Data(),k));
      String outputPathName = TString(Form("%s/%s%02d/",basePath.Data(),labelBunch.Data(),k));
      Configuration & subConfig = * new Configuration();
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),TString("RunPartPairAnalysisReco"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern1"),TString("BalFct"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern0"),TString("Derived"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern1"),TString("Reco"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":AppendedString"),TString("BalFctSum"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"),maximumDepth);
      subConfig.printConfiguration(cout);
      addSubTask( new SubSampleStatCalculator(taskType,subConfig));
      }
    }
  else // not bunched
    {
    String inputPathName  = TString(Form("%s/",basePath.Data()));
    String outputPathName = inputPathName;
    Configuration & subConfig = * new Configuration();
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),TString("RunPartPairAnalysisReco"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern1"),TString("BalFct"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern0"),TString("Derived"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern1"),TString("Reco"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":AppendedString"),TString("BalFctSum"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"),maximumDepth);
    subConfig.printConfiguration(cout);
    addSubTask( new SubSampleStatCalculator(taskType,subConfig));
    }
}

} // namespace CAP
