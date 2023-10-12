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

  addParameter("Analysis:RunPerformanceSim",          NO);
  addParameter("Analysis:RunPerformanceAna",          NO);

  addParameter("Analysis:RunPythiaGenerator",         NO);
  addParameter("Analysis:RunPythiaReader",            NO);
  addParameter("Analysis:RunHerwigGenerator",         NO);
  addParameter("Analysis:RunHerwigReader",            NO);
  addParameter("Analysis:RunAmptGenerator",           NO);
  addParameter("Analysis:RunAmptReader",              NO);
  addParameter("Analysis:RunEposGenerator",           NO);
  addParameter("Analysis:RunEposReader",              NO);
  addParameter("Analysis:RunUrqmdReader",             NO);
  addParameter("Analysis:RunTherminatorGenerator",    NO);
  addParameter("Analysis:RunHijingReader",            NO);
  addParameter("Analysis:RunResonanceGenerator",      NO);
  addParameter("Analysis:RunGlobalAnalysisGen",       NO);
  addParameter("Analysis:RunGlobalAnalysisReco",      NO);
  addParameter("Analysis:RunSpherocityAnalysisGen",   NO);
  addParameter("Analysis:RunSpherocityAnalysisReco",  NO);
  addParameter("Analysis:RunPartSingleAnalysisGen",   NO);
  addParameter("Analysis:RunPartSingleAnalysisReco",  NO);
  addParameter("Analysis:RunPartPairAnalysisGen",     NO);
  addParameter("Analysis:RunPartPairAnalysisReco",    NO);
  addParameter("Analysis:RunNuDynAnalysisGen",        NO);
  addParameter("Analysis:RunNuDynAnalysisReco",       NO);
  addParameter("Analysis:nBunches",                   int(10));
  addParameter("Analysis:HistogramsImportPath",       TString("DEFAULT"));
  addParameter("Analysis:HistogramsExportPath",       TString("DEFAULT"));
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

  cout << "Startin configuration w/ Task::configure()" << endl;
  Task::configure();
  cout << "setSeverity()" << endl;
  setSeverity();
  cout << "configureLabels()" << endl;
 // exit(1);
  try
  {

  configureLabels();
  if (reportInfo(__FUNCTION__)) printConfiguration(cout);

  String  histoImportPath = getValueString("HistogramsImportPath");
  String  histoExportPath = getValueString("HistogramsExportPath");
  int nBunches = getValueInt("Analysis:nBunches");

  printItem("histoExportPath",histoExportPath);
  printItem("nBunches",nBunches);
  exit(1);

  //
  // task run only once at the beginning...
  //
  if (getValueBool("RunParticleDbManager")) addSubTask(new ParticleDbManager("ParticleDb",*requestedConfiguration));
  if (getValueBool("RunFilterCreator"))     addSubTask(new FilterCreator("Filter",*requestedConfiguration));
  

  //
  // data production or analysis tasks called for each event...
  //
  if (getValueBool("RunEventAnalysis"))
    {
    if (reportInfo(__FUNCTION__)) cout << "Setting up event analysis" << std::endl;
    TaskIterator * eventAnalysis = new TaskIterator("Analysis",*requestedConfiguration);
    addSubTask(eventAnalysis);

    if (getValueBool("Analysis:RunPythiaGenerator"))         eventAnalysis->addSubTask(new PythiaEventGenerator(labelPythia,*requestedConfiguration));
    if (getValueBool("Analysis:RunAmptReader"))              eventAnalysis->addSubTask(new AmptEventReader(labelAmpt,*requestedConfiguration));
    if (getValueBool("Analysis:RunTherminatorGenerator"))    eventAnalysis->addSubTask(new TherminatorGenerator(labelTherminator,*requestedConfiguration));
    if (getValueBool("Analysis:RunResonanceGenerator"))      eventAnalysis->addSubTask(new ResonanceGenerator(labelResonance,*requestedConfiguration));
    if (getValueBool("Analysis:RunPerformanceSim"))          eventAnalysis->addSubTask(new MeasurementPerformanceSimulator(labelPerformance,*requestedConfiguration));

    if (getValueBool("RunEventAnalysisGen"))
      {
      if (getValueBool("Analysis:RunGlobalAnalysisGen"))       eventAnalysis->addSubTask(new GlobalAnalyzer(labelGlobal+labelGenerator, *requestedConfiguration));
      if (getValueBool("Analysis:RunSpherocityAnalysisGen"))   eventAnalysis->addSubTask(new TransverseSpherocityAnalyzer(labelSpherocity+labelGenerator, *requestedConfiguration));
      if (getValueBool("Analysis:RunPartSingleAnalysisGen"))   eventAnalysis->addSubTask(new ParticleSingleAnalyzer(labelSingle+labelGenerator, *requestedConfiguration));
      if (getValueBool("Analysis:RunPartPairAnalysisGen"))     eventAnalysis->addSubTask(new ParticlePairAnalyzer(labelPair+labelGenerator, *requestedConfiguration));
      if (getValueBool("Analysis:RunNuDynAnalysisGen"))        eventAnalysis->addSubTask(new NuDynAnalyzer(labelNuDyn+labelGenerator,*requestedConfiguration));
      }

    if (getValueBool("RunEventAnalysisReco"))
      {
      if (getValueBool("Analysis:RunGlobalAnalysisReco"))      eventAnalysis->addSubTask(new GlobalAnalyzer(labelGlobal+labelReconstruction,*requestedConfiguration));
      if (getValueBool("Analysis:RunSpherocityAnalysisReco"))  eventAnalysis->addSubTask(new TransverseSpherocityAnalyzer(labelSpherocity+labelReconstruction, *requestedConfiguration));
      if (getValueBool("Analysis:RunPartSingleAnalysisReco"))  eventAnalysis->addSubTask(new ParticleSingleAnalyzer(labelSingle+labelReconstruction, *requestedConfiguration));
      if (getValueBool("Analysis:RunPartPairAnalysisReco"))    eventAnalysis->addSubTask(new ParticlePairAnalyzer(labelPair+labelReconstruction, *requestedConfiguration));
      if (getValueBool("Analysis:RunNuDynAnalysisReco"))       eventAnalysis->addSubTask(new NuDynAnalyzer(labelNuDyn+labelReconstruction,*requestedConfiguration));
      if (getValueBool("Analysis:RunPerformanceAna"))          eventAnalysis->addSubTask(new ParticlePerformanceAnalyzer(labelSimAna,*requestedConfiguration));
      }

    // make sure the subtasks get the right import and export paths for histograms...
    // this way, we do not have to specify the path in the ini file for eacu sub task.
    //
    if (eventAnalysis->hasSubTasks())
      for (unsigned int  iTask=0; iTask<eventAnalysis->getNSubTasks(); iTask++)
        {
        Task * task = eventAnalysis->getSubTaskAt(iTask);
        task->configure();
        task->addParameter("HistogramsImportPath",histoImportPath);
        task->addParameter("HistogramsExportPath",histoExportPath);
        }
    if (reportInfo(__FUNCTION__)) cout << "Event Analysis Setup Completed" << std::endl;
    }

  //
  // Run tasks that compute derived histograms. Call once for each type of analysis task.
  //
  if (getValueBool("RunDerived"))
    {
    if (reportInfo(__FUNCTION__)) cout << "Setting up derived calculation" << std::endl;
    // here we need to overide the ini file based on the info provided by the user in the call to RunAnalysis.

    TString taskName;
    TString configBasePath;
    TString configPath = "Run:Analysis";
    TString subTaskName;
    TString subConfigBasePath;
    TString subConfigPath;

    if (getValueBool("RunDerivedGen"))
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
      dConfig.addParameter(configPath+"nBunches",nBunches);

      DerivedHistoIterator * derived = new DerivedHistoIterator(taskName,dConfig);
      addSubTask(derived);

      //    if (runGlobalAnalysisGen)          derived->addSubTask(new GlobalAnalyzer(labelGlobal+labelGenerator, configuration));
      //    if (runSpherocityAnalysisGen)      derived->addSubTask(new TransverseSpherocityAnalyzer(labelSpherocity+labelGenerator, configuration));

      if (getValueBool("Analysis:RunPartSingleAnalysisGen"))
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
        //subConfig.addParameter(configPath+"nBunches",nBunches);

        derived->addSubTask(new ParticleSingleAnalyzer(subTaskName, subConfig));


        }

      if (getValueBool("Analysis:RunPartPairAnalysisGen"))
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

    if (getValueBool("RunBalFct"))
      {
      if (reportInfo(__FUNCTION__)) cout << "Setting up BalFct" << std::endl;

      if (getValueBool("Analysis:RunBalFctGen") && getValueBool("Analysis:RunPartPairAnalysisGen"))
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
       if (reportInfo(__FUNCTION__)) cout << "BalFct Setup Completed" << std::endl;

      }
    if (reportInfo(__FUNCTION__)) cout << "Derived calculation Setup Completed" << std::endl;
    }

  //
  // Run tasks that compute subsample sums of  histograms.
  //
  if (getValueBool("RunSubsample"))
    {
    if (reportInfo(__FUNCTION__)) 
      {
      cout << endl;
      cout << "Setting up Subsample calculation" << std::endl;
      printItem("RunSubsample w/ histoImportPath",histoImportPath);
      printItem("RunSubsample w/ histoExportPath",histoExportPath);
      printItem("RunSubsampleBase");
      printItem("RunSubsampleDerived");
      printItem("RunSubsampleDerivedGen");
      }

    if (getValueBool("RunSubsampleBase"))
      {
      int maximumDepth = 2;
      if (getValueBool("RunSubsampleBaseGen"))
        {
        if (getValueBool("RunGlobalAnalysisGen"))     addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelGlobal+labelGenerator);
        if (getValueBool("RunSpherocityAnalysisGen")) addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSpherocity+labelGenerator);
        if (getValueBool("RunPartSingleAnalysisGen")) addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSingle+labelGenerator);
        if (getValueBool("RunPartPairAnalysisGen"))   addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelGenerator);
        if (getValueBool("RunNuDynAnalysisGen"))      addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelNuDyn+labelGenerator);
        }
      if (getValueBool("RunSubsampleBaseReco"))
        {
        if (getValueBool("RunGlobalAnalysisReco"))     addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelGlobal+labelReconstruction);
        if (getValueBool("RunSpherocityAnalysisReco")) addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSpherocity+labelReconstruction);
        if (getValueBool("RunPartSingleAnalysisReco")) addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSingle+labelReconstruction);
        if (getValueBool("RunPartPairAnalysisReco"))   addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelReconstruction);
        if (getValueBool("RunNuDynAnalysisReco"))      addBaseSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelNuDyn+labelReconstruction);
        }
      }
    if (getValueBool("RunSubsampleDerived"))
      {
      int maximumDepth = 1;
      if (getValueBool("RunSubsampleDerivedGen"))
        {
        if (getValueBool("RunGlobalAnalysisGen"))     addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelGlobal+labelGenerator);
        if (getValueBool("RunSpherocityAnalysisGen")) addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSpherocity+labelGenerator);
        if (getValueBool("RunPartSingleAnalysisGen")) addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSingle+labelGenerator);
        if (getValueBool("RunPartPairAnalysisGen"))   addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelGenerator);
        if (getValueBool("RunNuDynAnalysisGen"))      addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelNuDyn+labelGenerator);
        }
      if (getValueBool("RunSubsampleDerivedReco"))
        {
        if (getValueBool("RunGlobalAnalysisReco"))     addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelGlobal+labelReconstruction);
        if (getValueBool("RunSpherocityAnalysisReco")) addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSpherocity+labelReconstruction);
        if (getValueBool("RunPartSingleAnalysisReco")) addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelSingle+labelReconstruction);
        if (getValueBool("RunPartPairAnalysisReco"))   addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelReconstruction);
        if (getValueBool("RunNuDynAnalysisReco"))      addDerivedSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelNuDyn+labelReconstruction);
        }
      }
//    if (getValueBool("RunSubsampleBalFct"))
//      {
//      int maximumDepth = 1;
//      if (getValueBool("RunSubsampleBalFctGen"))
//        {
//        if (getValueBool("RunPartPairAnalysisGen"))   addBalFctSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelGenerator);
//        }
//      if (getValueBool("RunSubsampleBalFctReco"))
//        {
//        if (getValueBool("RunPartPairAnalysisReco"))  addBalFctSubSampleTask(histoImportPath,labelBunch,nBunches,labelSubBunch,maximumDepth,labelPair+labelReconstruction);
//        }
//      }

    if (reportInfo(__FUNCTION__)) cout << "Subsample calculation Setup Completed" << std::endl;
    }

  // He we call configure on all tasks and subtasks. We also make sure all the tasks have the same import
  // and export paths for histograms.
  //
  if (hasSubTasks())
    {
    if (reportInfo(__FUNCTION__)) cout << "Start configuration of tasks and their subtasks" << std::endl;
    for (unsigned int  iTask=0; iTask<getNSubTasks(); iTask++)
      {
      Task * task = getSubTaskAt(iTask);
      if (reportInfo(__FUNCTION__)) cout << " Task: " << iTask << " Named: " << task->getName() << endl;
      task->configure();
      task->addParameter("HistogramsImportPath",histoImportPath);
      task->addParameter("HistogramsExportPath",histoExportPath);
      for (unsigned int  kTask=0; kTask<task->getNSubTasks(); kTask++)
        {
        Task * subtask = task->getSubTaskAt(kTask);
        if (reportInfo(__FUNCTION__)) cout << " Subtask: " << kTask << " Named: " << subtask->getName() << endl;
        subtask->configure();
        subtask->addParameter("HistogramsImportPath",histoImportPath);
        subtask->addParameter("HistogramsExportPath",histoExportPath);
        }
      }
    if (reportInfo(__FUNCTION__)) cout << "Completed configuration of tasks and their subtasks" << std::endl;
    }

  }
  catch (TaskException & te)
  {
  te.print(); exit(1);
  }
  catch (ConfigurationException & ce)
  {
  ce.print(); exit(1);
  }
  catch (MathException & me)
  {
  me.print(); exit(1);
  }
  catch (FileException & fe)
  {
  fe.print(); exit(1);
  }
  catch (MemoryException & mme)
  {
  mme.print(); exit(1);
  }
  catch (HistogramException & he)
  {
  he.print(); exit(1);
  }
  catch (FactoryException & ffe)
  {
  ffe.print(); exit(1);
  }
  catch (Exception & e)
  {
  e.print(); exit(1);
  }

  if (reportInfo(__FUNCTION__)) cout << "Configuration completed.";
}

void RunAnalysis::execute()
{
  try
  {
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    cout << "==================================================================================" << std::endl;
    cout << "RunAnalysis::execute() Started" << std::endl;
    cout << "==================================================================================" << std::endl;
    }

//  int n = subTasks.size();
//  cout << "RunAnalysis::execute() Number of subtasks: " << n << endl;;
//  for (int k=0; k<n; k++ )
//    cout << "RunAnalysis::execute() Sub taskName: " << subTasks[k]->getName()<< endl;
//  exit(1);
  initializeSubTasks();
  executeSubTasks();
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    cout << "==================================================================================" << std::endl;
    cout << "RunAnalysis::execute() Completed" << std::endl;
    cout << "==================================================================================" << std::endl;
    }
  }

  catch (TaskException & te)
  {
  te.print(); exit(1);
  }
  catch (ConfigurationException & ce)
  {
  ce.print(); exit(1);
  }
  catch (MathException & me)
  {
  me.print(); exit(1);
  }
  catch (FileException & fe)
  {
  fe.print(); exit(1);
  }
  catch (MemoryException & mme)
  {
  mme.print(); exit(1);
  }
  catch (HistogramException & he)
  {
  he.print(); exit(1);
  }
  catch (FactoryException & ffe)
  {
  ffe.print(); exit(1);
  }
  catch (Exception & e)
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
  if (reportInfo(__FUNCTION__))
    {
    printItem("basePath",basePath);
    printItem("labelBunch",labelBunch);
    printItem("nBunches",nBunches);
    printItem("subPath",subPath);
    printItem("maximumDepth",maximumDepth);
    printItem("taskType",taskType);
    }

  if (nBunches>0)
    {
    for (int k=1;k<=nBunches; k++)
      {
      String inputPathName  = TString(Form("%s/%s%02d/%s",basePath.Data(),labelBunch.Data(),k,subPath.Data()));
      String outputPathName = TString(Form("%s/%s%02d/",basePath.Data(),labelBunch.Data(),k));
      Configuration & subConfig = * new Configuration(configuration);
      subConfig.addParameter(TString("Run:")+taskType+TString(":Severity"),"Info");
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),taskType);
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
    subConfig.addParameter(TString("Run:")+taskType+TString(":Severity"),"Info");
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),taskType);
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
                                           const String & labelBunch __attribute__((unused)),
                                           int   nBunches,
                                           const String & subPath __attribute__((unused)),
                                           int   maximumDepth __attribute__((unused)),
                                           const String & taskType)
{
  if (reportInfo(__FUNCTION__))
    {
    printItem("basePath",basePath);
    printItem("labelBunch",labelBunch);
    printItem("nBunches",nBunches);
    printItem("subPath",subPath);
    printItem("maximumDepth",maximumDepth);
    printItem("taskType",taskType);
    }

  if (nBunches>0)
    {
    for (int k=1;k<=nBunches; k++)
      {
      String inputPathName  = basePath;  //TString(Form("%s/%s%02d/",basePath.Data(),labelBunch.Data(),k));
      String outputPathName = basePath;  //.Data(); // TString(Form("%s/%s%02d/",,"",k));
      Configuration & subConfig = * new Configuration(configuration);
      subConfig.addParameter(TString("Run:")+taskType+TString(":Severity"),"Info");
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),taskType);
      subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern1"),TString("Derived"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern0"),TString("DerivedSum"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":AppendedString"),TString("DerivedSum"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"),1);
      // subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"),maximumDepth);
      //subConfig.printConfiguration(cout);
      addSubTask( new SubSampleStatCalculator(taskType,subConfig));
      }
    }
  else // not bunched
    {
    cout << " BUG" << endl; exit(1);

    String inputPathName  = TString(Form("%s/",basePath.Data()));
    String outputPathName = inputPathName;
    Configuration & subConfig = * new Configuration(configuration);
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
    subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),taskType);
    subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern1"),TString("Derived"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern0"),TString("Reco"));
    //subConfig.addParameter(TString("Run:")+taskType+TString(":ExcludedPattern1"),TString("BalFct"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":AppendedString"),TString("DerivedSum"));
    subConfig.addParameter(TString("Run:")+taskType+TString(":MaximumDepth"),1);
    subConfig.printConfiguration(cout);
    addSubTask( new SubSampleStatCalculator(taskType,subConfig));
    }
}

void RunAnalysis::addBalFctSubSampleTask(const String & basePath,
                                          const String & labelBunch __attribute__((unused)),
                                          int   nBunches,
                                          const String & subPath __attribute__((unused)),
                                          int   maximumDepth,
                                          const String & taskType)
{
  if (reportInfo(__FUNCTION__))
    {
    printItem("basePath",basePath);
    printItem("labelBunch",labelBunch);
    printItem("nBunches",nBunches);
    printItem("subPath",subPath);
    printItem("maximumDepth",maximumDepth);
    printItem("taskType",taskType);
    }

  if (nBunches>0)
    {
    for (int k=1;k<=nBunches; k++)
      {
      String inputPathName  = basePath;  //TString(Form("%s/%s%02d/",basePath.Data(),labelBunch.Data(),k));
      String outputPathName = basePath;  //.Data(); // TString(Form("%s/%s%02d/",,"",k));
      Configuration & subConfig = * new Configuration();
      subConfig.addParameter(TString("Run:")+taskType+TString(":Severity"),TString("Info"));
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsImportPath"),inputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":HistogramsExportPath"),outputPathName);
      subConfig.addParameter(TString("Run:")+taskType+TString(":IncludedPattern0"),TString("PairGen"));
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
