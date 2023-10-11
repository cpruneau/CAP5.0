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
#include "RunDerivedCalculation.hpp"
#include "TaskIterator.hpp"
#include "DerivedHistoIterator.hpp"
#include "BalanceFunctionCalculator.hpp"
#include "SubSampleStatCalculator.hpp"
#include "ClosureIterator.hpp"
#include "ParticleDbManager.hpp"
//#include "HerwigEventReader.hpp"
#include "AmptEventReader.hpp"
//#include "EposEventReader.hpp"
//#include "UrqmdEventReader.hpp"
//#include "HijingEventReader.hpp"
#include "ResonanceGenerator.hpp"
#include "MeasurementPerformanceSimulator.hpp"
#include "ParticlePerformanceAnalyzer.hpp"
#include "GlobalAnalyzer.hpp"
#include "TransverseSpherocityAnalyzer.hpp"
#include "ParticleSingleAnalyzer.hpp"
#include "ParticlePairAnalyzer.hpp"
#include "NuDynAnalyzer.hpp"
#include "FilterCreator.hpp"
using CAP::RunDerivedCalculation;

ClassImp(RunDerivedCalculation);

RunDerivedCalculation::RunDerivedCalculation(const String & _name,
                                             const Configuration & _configuration)
:
EventTask(_name, _configuration)
{
  appendClassName("RunDerivedCalculation");
  setInstanceName(_name);
}


void RunDerivedCalculation::setDefaultConfiguration()
{
  EventTask::setDefaultConfiguration();
  bool YES = true;
  bool NO  = false;
  addParameter("GlobalLabel",     TString("G"));
  addParameter("SpherocityLabel", TString("S"));
  addParameter("SingleLabel",     TString("Single"));
  addParameter("PairLabel",       TString("Pair"));
  addParameter("NuDynLabel",      TString("NuDyn"));
  addParameter("SimAnaLabel",     TString("SimAna"));
  addParameter("RootExt",         TString(".root"));
  addParameter("DerivedLabel",    TString("Derived"));
  addParameter("SumLabel",        TString("Sum"));
  addParameter("BalFctLabel",     TString("BalFct"));
  addParameter("ClosureLabel",    TString("Closure"));
  addParameter("GenLabel",        TString("Gen"));
  addParameter("RecoLabel",       TString("Reco"));
  addParameter("PythiaLabel",     TString("PYTHIA"));
  addParameter("HerwigLabel",     TString("HERWIG"));
  addParameter("HijingLabel",     TString("HIJING"));
  addParameter("AmptLabel",       TString("AMPT"));
  addParameter("EposLabel",       TString("EPOST"));
  addParameter("UrqmdLabel",      TString("URQMD"));
  addParameter("TherminatorLabel",TString("Therminator"));
  addParameter("ResoLabel",       TString("RESO"));
  addParameter("PerformLabel",    TString("Perform"));

  //  addParameter("histoModelDataName",      TString("none"));
  //  addParameter("histoAnalyzerName",       TString("none"));
  //  addParameter("histoBaseName",           TString("none"));
  addParameter("Severity",                   TString("Info"));
  addParameter("RunParticleDbManager",       YES);
  addParameter("RunEventAnalysis",           YES);
  addParameter("RunEventAnalysisGen",        YES);
  addParameter("RunEventAnalysisReco",       NO);
  addParameter("RunDerivedGen",              YES);
  addParameter("RunDerivedReco",             NO);
  addParameter("RunBalFctGen",               NO);
  addParameter("RunBalFctReco",              NO);
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
  addParameter("RunPartSingleAnalysisGen",   YES);
  addParameter("RunPartSingleAnalysisReco",  NO);
  addParameter("RunPartPairAnalysisGen",     YES);
  addParameter("RunPartPairAnalysisReco",    NO);
  addParameter("RunNuDynAnalysisGen",        NO);
  addParameter("RunNuDynAnalysisReco",       NO);
  addParameter("RunFillEta",                 NO);
  addParameter("RunFillY",                   YES);
  addParameter("nEventsPerSubbunch",      long(100));
  addParameter("nSubbunchesPerBunch",     int(10));
  addParameter("nBunches",                int(10));
  addParameter("BunchLabel",              "Bunch");
  addParameter("SubbunchLabel",           "");
  addParameter("EventsUseStream0",         true);
  addParameter("EventsUseStream1",         false);
  addParameter("SetSeed",                 true);
  addParameter("SeedValue",               long(121212121));

  addParameter("Analysis:EventFilterModelOption",     TString("All"));
  addParameter("Analysis:EventFilterModelNValues",    0);
  addParameter("Analysis:EventFilterModelValue0",     0.0);
  addParameter("Analysis:EventFilterModelValue1",     0.0);
  addParameter("Analysis:EventFilterModelValue2",     0.0);
  addParameter("Analysis:EventFilterModelValue3",     0.0);
  addParameter("Analysis:EventFilterModelValue4",     0.0);
  addParameter("Analysis:EventFilterModelValue5",     0.0);
  addParameter("Analysis:EventFilterModelValue6",     0.0);
  addParameter("Analysis:EventFilterModelValue7",     0.0);
  addParameter("Analysis:EventFilterModelValue8",     0.0);
  addParameter("Analysis:EventFilterModelValue9",     0.0);
  addParameter("Analysis:EventFilterModelValue10",    0.0);
  addParameter("Analysis:EventFilterModelValue11",    0.0);
  addParameter("Analysis:EventFilterModelValue12",    0.0);

  addParameter("Analysis:EventFilterAnaOption",      TString("All"));
  addParameter("Analysis:EventFilterAnaNValues",     0);
  addParameter("Analysis:EventFilterAnaValue0",      0.0);
  addParameter("Analysis:EventFilterAnaValue1",      0.0);
  addParameter("Analysis:EventFilterAnaValue2",      0.0);
  addParameter("Analysis:EventFilterAnaValue3",      0.0);
  addParameter("Analysis:EventFilterAnaValue4",      0.0);
  addParameter("Analysis:EventFilterAnaValue5",      0.0);
  addParameter("Analysis:EventFilterAnaValue6",      0.0);
  addParameter("Analysis:EventFilterAnaValue7",      0.0);
  addParameter("Analysis:EventFilterAnaValue8",      0.0);
  addParameter("Analysis:EventFilterAnaValue9",      0.0);
  addParameter("Analysis:EventFilterAnaValue10",     0.0);
  addParameter("Analysis:EventFilterAnaValue11",     0.0);
  addParameter("Analysis:EventFilterAnaValue12",     0.0);

  addParameter("Analysis:PartFilterModelOption",     TString("All"));
  addParameter("Analysis:PartFilterModelPt",         false);
  addParameter("Analysis:PartFilterModelMinPt",      0.2);
  addParameter("Analysis:PartFilterModelMaxPt",      2.0);
  addParameter("Analysis:PartFilterModelEta",        false);
  addParameter("Analysis:PartFilterModelMinEta",     -4.0);
  addParameter("Analysis:PartFilterModelMaxEta",     4.0);
  addParameter("Analysis:PartFilterModelY",          false);
  addParameter("Analysis:PartFilterModelMinY",       -4.0);
  addParameter("Analysis:PartFilterModelMaxY",       4.0);

  addParameter("Analysis:PartFilterAnaOption",       TString("All"));
  addParameter("Analysis:PartFilterAnaFilterPt",     false);
  addParameter("Analysis:PartFilterAnaMinPt",        0.0);
  addParameter("Analysis:PartFilterAnaMaxPt",        2.0);
  addParameter("Analysis:PartFilterAnaEta",          false);
  addParameter("Analysis:PartFilterAnaMinEta",       -4.0);
  addParameter("Analysis:PartFilterAnaMaxEta",       4.0);
  addParameter("Analysis:PartFilterAnaY",            false);
  addParameter("Analysis:PartFilterAnaMinY",         -4.0);
  addParameter("Analysis:PartFilterAnaMaxY",         4.0);
}


void RunDerivedCalculation::configure()
{
  if (reportEnd(__FUNCTION__))
    ;
  EventTask::configure();
  DerivedHistoIterator      * derived   = nullptr;
  String GlobalLabel      = getValueString("GlobalLabel");
  String SpherocityLabel  = getValueString("SpherocityLabel");
  String SingleLabel      = getValueString("SingleLabel");
  String PairLabel        = getValueString("PairLabel");
  String NuDynLabel       = getValueString("NuDynLabel");
  String SimAnaLabel      = getValueString("SimAnaLabel");
  String RootExt          = getValueString("RootExt");
  String DerivedLabel     = getValueString("DerivedLabel");
  String SumLabel         = getValueString("SumLabel");
  String BalFctLabel      = getValueString("BalFctLabel");
  String ClosureLabel     = getValueString("ClosureLabel");
  String GenLabel         = getValueString("GenLabel");
  String RecoLabel        = getValueString("RecoLabel");
  String PythiaLabel      = getValueString("PythiaLabel");
  String HerwigLabel      = getValueString("HerwigLabel");
  String HijingLabel      = getValueString("HijingLabel");
  String AmptLabel        = getValueString("AmptLabel");
  String EposLabel        = getValueString("EposLabel");
  String UrqmdLabel       = getValueString("UrqmdLabel");
  String TherminatorLabel = getValueString("TherminatorLabel");
  String ResoLabel        = getValueString("ResoLabel");
  String PerformLabel     = getValueString("PerformLabel");
  bool    runParticleDbManager            = getValueBool("RunParticleDbManager");
  bool    runEventAnalysis                = getValueBool("RunEventAnalysis");
  bool    runEventAnalysisGen             = getValueBool("RunEventAnalysisGen");
  bool    runEventAnalysisReco            = getValueBool("RunEventAnalysisReco");
  bool    runDerivedGen                   = getValueBool("RunDerivedGen");
  bool    runDerivedReco                  = getValueBool("RunDerivedReco");
  bool    runBalFctGen                    = getValueBool("RunBalFctGen");
  bool    runBalFctReco                   = getValueBool("RunBalFctReco");
  bool    runSubsample                    = getValueBool("RunSubsample");
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
  bool    runFillEta                      = getValueBool("RunFillEta");
  bool    runFillY                        = getValueBool("RunFillY");
  String histosImportPath                 = getValueString("HistogramsImportPath");
  String histosExportPath                 = getValueString("HistogramsExportPath");



  if (reportInfo(__FUNCTION__))
    {
    cout << endl;

    printItem("RunParticleDbManager",runParticleDbManager);
    printItem("RunEventAnalysis",runEventAnalysis);
    printItem("RunEventAnalysisGen",runEventAnalysisGen);
    printItem("RunEventAnalysisReco",runEventAnalysisReco);
    printItem("RunDerivedGen",runDerivedGen);
    printItem("RunDerivedReco",runDerivedReco);
    printItem("RunBalFctGen",runBalFctGen);
    printItem("RunBalFctReco",runBalFctReco);
    printItem("RunSubsample",runSubsample);
    printItem("RunPerformanceSim",runPerformanceSim);
    printItem("RunPerformanceAna",runPerformanceAna);
    printItem("RunClosure",runClosure);
    printItem("RunPythiaGenerator",runPythiaGenerator);
    printItem("RunPythiaReader",runPythiaReader);
    printItem("RunHerwigGenerator",runHerwigGenerator);
    printItem("RunHerwigReader",runHerwigReader);
    printItem("RunAmptGenerator",runAmptGenerator);
    printItem("RunAmptReader",runAmptReader);
    printItem("RunEposGenerator",runEposGenerator);
    printItem("RunEposReader",runEposReader);
    printItem("RunUrqmdReader",runUrqmdReader);
    printItem("RunTherminatorGenerator",runTherminatorGenerator);
    printItem("RunHijingReader",runHijingReader);
    printItem("RunResonanceGenerator",runResonanceGenerator);
    printItem("RunGlobalAnalysisGen",runGlobalAnalysisGen);
    printItem("RunGlobalAnalysisReco",runGlobalAnalysisReco);
    printItem("RunSpherocityAnalysisGen",runSpherocityAnalysisGen);
    printItem("RunSpherocityAnalysisReco",runSpherocityAnalysisReco);
    printItem("RunPartSingleAnalysisGen",runPartSingleAnalysisGen);
    printItem("RunPartSingleAnalysisReco",runPartSingleAnalysisReco);
    printItem("RunPartPairAnalysisGen",runPartPairAnalysisGen);
    printItem("RunPartPairAnalysisReco",runPartPairAnalysisReco);
    printItem("RunNuDynAnalysisGen",runNuDynAnalysisGen);
    printItem("RunNuDynAnalysisReco",runNuDynAnalysisReco);
    printItem("RunFillEta",runFillEta);
    printItem("RunFillY",runFillY);
    printItem("HistogramsImportPath",histosImportPath);
    printItem("HistogramsExportPath",histosExportPath);
    printItem("EventFilterModelOption",eventFilterModelOption);
    printItem("EventFilterAnaOption",eventFilterAnaOption);
    printItem("SetSeed",setSeed);
    printItem("SeedValue",seedValue);
    cout << endl;
    }

 

  TString taskName;
  TString configBasePath;
  TString configPath;
  TString subTaskName;
  TString subConfigBasePath;
  TString subConfigPath;

  if (runDerivedGen)
    {
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
    derived = new DerivedHistoIterator(taskName,dConfig);
    addSubTask(derived);

//    if (runGlobalAnalysisGen)          derived->addSubTask(new GlobalAnalyzer(GlobalLabel+GenLabel, configuration));
//    if (runSpherocityAnalysisGen)      derived->addSubTask(new TransverseSpherocityAnalyzer(SpherocityLabel+GenLabel, configuration));

    if (runPartSingleAnalysisGen)
      {
      Configuration & subConfig = * new Configuration(configuration);
      subTaskName       = SingleLabel+GenLabel;
      subConfigBasePath = configPath;
      subConfigPath     = subConfigBasePath + subTaskName;  subConfigBasePath += ":";
      subConfig.addParameter(subConfigPath+"HistogramsImportPath",histosImportPath);
      subConfig.addParameter(subConfigPath+"HistogramsExportPath",histosExportPath);
      subConfig.addParameter(subConfigPath+"IncludedPattern0",TString("Sum"));
      subConfig.addParameter(subConfigPath+"ExcludedPattern0",TString("Reco"));
      subConfig.addParameter(subConfigPath+"ExcludedPattern1",TString("BalFct"));
      subConfig.addParameter(subConfigPath+"ExcludedPattern2",TString("Derived"));
      derived->addSubTask(new ParticleSingleAnalyzer(subTaskName, subConfig));
      }

    if (runPartPairAnalysisGen)
      {
      Configuration & subConfig = * new Configuration(dConfig);
      subTaskName       = PairLabel+GenLabel;
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


//    if (runNuDynAnalysisGen)           derived->addSubTask(new NuDynAnalyzer(NuDynLabel+GenLabel,configuration,eventFilterAnalysis,particleFiltersAnalysis));
//    if (runGlobalAnalysisReco)         derived->addSubTask(new GlobalAnalyzer(GlobalLabel+RecoLabel, configuration));
//    if (runSpherocityAnalysisReco)     derived->addSubTask(new TransverseSpherocityAnalyzer(SpherocityLabel+RecoLabel, configuration));
//    if (runPartSingleAnalysisReco)     derived->addSubTask(new ParticleSingleAnalyzer(SingleLabel+RecoLabel, configuration));
//    if (runPartPairAnalysisReco)       derived->addSubTask(new ParticlePairAnalyzer(PairLabel+RecoLabel, configuration));
//    if (runNuDynAnalysisReco)          derived->addSubTask(new NuDynAnalyzer(NuDynLabel+RecoLabel,configuration,eventFilterAnalysis,particleFiltersAnalysis));
    }

  if (runBalFctGen && runPartPairAnalysisGen)
    {
    Configuration & dConfig = * new Configuration(configuration);
    taskName       = PairLabel+GenLabel;
    configBasePath = configPath;

    configPath     = configBasePath + taskName;  configPath += ":";
    dConfig.addParameter(configPath+"HistogramsImportPath",histosImportPath);
    dConfig.addParameter(configPath+"HistogramsExportPath",histosExportPath);
    dConfig.addParameter(configPath+"IncludedPattern0",TString("Sum"));
    dConfig.addParameter(configPath+"IncludedPattern1",TString("Derived"));
    dConfig.addParameter(configPath+"ExcludedPattern0",TString("Reco"));
    dConfig.addParameter(configPath+"ExcludedPattern1",TString("BalFct"));
    dConfig.addParameter(configPath+"ExcludedPattern2",TString("Single"));
    dConfig.addParameter(configPath+"AppendedString",  TString("BalFct"));
    dConfig.printConfiguration(cout);

    addSubTask(new BalanceFunctionCalculator(taskName,dConfig));
    }

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    cout << "==================================================================================" << std::endl;
    cout << "Configuration Completed; RunDerivedCalculation" << std::endl;
    cout << "==================================================================================" << std::endl;
    cout << endl;
    cout << endl;
    }
  gSystem->mkdir(histosExportPath,1);

  for (unsigned int  iTask=0; iTask<subTasks.size(); iTask++)
    {
    //cout << subTasks[iTask]->getName() << endl;
    subTasks[iTask]->configure();
    }
  if (reportEnd(__FUNCTION__))
    ;
}

void RunDerivedCalculation::execute()
{
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    cout << "==================================================================================" << std::endl;
    cout << "Analysis Started" << std::endl;
    cout << "==================================================================================" << std::endl;
    }

  try
  {
    executeSubTasks();
  }
  catch (HistogramException hException)
  {
  hException.print();
  }
  catch (MathException mException)
  {
  mException.print();
  }
  catch (Exception exception)
  {
  exception.print();
  }

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    cout << "==================================================================================" << std::endl;
    cout << "Analysis Completed" << std::endl;
    cout << "==================================================================================" << std::endl;
    }
}

