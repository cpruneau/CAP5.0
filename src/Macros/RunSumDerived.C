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
#include <iostream>
#include <fstream>
#include <TStyle.h>
#include <TROOT.h>

void loadBase(const TString & includeBasePath);
void loadParticles(const TString & includeBasePath);
void loadPythia(const TString & includeBasePath);
void loadPerformance(const TString & includeBasePath);
void loadAmpt(const TString & includeBasePath);
void loadEpos(const TString & includeBasePath);
void loadHijing(const TString & includeBasePath);
void loadHerwig(const TString & includeBasePath);
void loadUrqmd(const TString & includeBasePath);
void loadBasicGen(const TString & includeBasePath);
void loadGlobal(const TString & includeBasePath);
void loadSingle(const TString & includeBasePath);
void loadPair(const TString & includeBasePath);
void loadNuDyn(const TString & includeBasePath);
void loadSubSample(const TString & includeBasePath);
void loadExec(const TString & includeBasePath);



int RunSumDerived(TString configFile="AnalysisPythia_pp13TeV_CH_Y2_inclusive",
                  TString pathName="/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Y2/")
{
  TString includeBasePath = getenv("CAP_SRC");
  loadBase(includeBasePath);
  loadParticles(includeBasePath);
  loadPythia(includeBasePath);
  loadPerformance(includeBasePath);
  loadAmpt(includeBasePath);
  //loadEpos(includeBasePath);
  //loadHijing(includeBasePath);
  //loadHerwig(includeBasePath);
  //loadUrqmd(includeBasePath);
  loadBasicGen(includeBasePath);
  loadGlobal(includeBasePath);
  loadSingle(includeBasePath);
  loadPair(includeBasePath);
  loadNuDyn(includeBasePath);
  loadSubSample(includeBasePath);
  loadExec(includeBasePath);

  //outputPath = "/Volumes/ClaudeDisc4/OutputFiles/Reso/";

  std::cout << "==================================================================================" << std::endl;
  std::cout << "Executing RunSumDerived" << endl;
  std::cout << "configFile......: " << configFile << endl;
  std::cout << "pathName........: " << pathName   << endl;
  std::cout << "==================================================================================" << std::endl;
  CAP::Configuration configuration;

  try
  {
  configuration.readFromFile("",configFile);
  }
  catch (CAP::ConfigurationException ce)
  {
  ce.print();
  }
  catch (...)
  {
  cout << "Unknown exception while reading configuration file." << endl;
  return 1;
  }
  configuration.addParameter("Run:HistogramInputPath",  pathName);
  configuration.addParameter("Run:HistogramOutputPath", pathName);
  configuration.addParameter("Run:HistogramsExportPath",      pathName);
  configuration.addParameter("Run:HistogramsImportPath",      pathName);
  configuration.addParameter("Run:HistogramsForceRewrite",    true);
  configuration.addParameter("Run:RunParticleDbManager",      false);
  configuration.addParameter("Run:RunFilterCreator",          false);
  configuration.addParameter("Run:RunEventAnalysis",          false);
  configuration.addParameter("Run:RunEventAnalysisGen",       false);
  configuration.addParameter("Run:RunEventAnalysisReco",      false);
  configuration.addParameter("Run:RunDerived",                false);
  configuration.addParameter("Run:RunDerivedGen",             false);
  configuration.addParameter("Run:RunDerivedReco",            false);
  configuration.addParameter("Run:RunBalFct",                 false);
  configuration.addParameter("Run:RunBalFctGen",              false);
  configuration.addParameter("Run:RunBalFctReco",             false);
  configuration.addParameter("Run:RunPartSingleAnalysisGen",  false);
  configuration.addParameter("Run:RunPartSingleAnalysisReco", false);
  configuration.addParameter("Run:RunPartPairAnalysisGen",    false);
  configuration.addParameter("Run:RunPartPairAnalysisReco",   false);

  configuration.addParameter("Run:RunSubsample",              true);
  configuration.addParameter("Run:RunSubsampleBase",          false);
  configuration.addParameter("Run:RunSubsampleBaseGen",       false);
  configuration.addParameter("Run:RunSubsampleBaseReco",      false);
  configuration.addParameter("Run:RunSubsampleDerived",       true);
  configuration.addParameter("Run:RunSubsampleDerivedGen",    true);
  configuration.addParameter("Run:RunSubsampleDerivedReco",   false);
  configuration.addParameter("Run:RunSubsampleBalFct",        false);
  configuration.addParameter("Run:RunSubsampleBalFctGen",     false);
  configuration.addParameter("Run:RunSubsampleBalFctReco",    false);
  configuration.addParameter("Run:Bunched",                   true);
  configuration.addParameter("Run:nBunches",                  1);
  configuration.addParameter("Run:Analysis:nBunches",         1);
  configuration.addParameter("Run:MaximumDepth",              1);
  configuration.addParameter("Run:Analysis:RunPartSingleAnalysisGen",      true);
  configuration.addParameter("Run:Analysis:RunPartSingleAnalysisReco",     false);
  configuration.addParameter("Run:Analysis:RunPartPairAnalysisGen",        true);
  configuration.addParameter("Run:Analysis:RunPartPairAnalysisReco",       false);

  configuration.addParameter("Run:Analysis:RunGlobalAnalysisGen",          false);
  configuration.addParameter("Run:Analysis:RunGlobalAnalysisReco",         false);
  configuration.addParameter("Run:Analysis:RunSpherocityAnalysisGen",      false);
  configuration.addParameter("Run:Analysis:RunSpherocityAnalysisReco",     false);
  configuration.addParameter("Run:Analysis:RunNuDynAnalysisGen",           false);
  configuration.addParameter("Run:Analysis:RunNuDynAnalysisReco",          false);



//  CAP::RunAnalysis * analysisD = new CAP::RunAnalysis("Run", configuration);
//  analysisD->configure();
//  analysisD->execute();

  configuration.addParameter("Run:RunSubsampleBalFct",     true);
  configuration.addParameter("Run:RunSubsampleBalFctGen",  true);
  configuration.addParameter("Run:RunSubsampleDerivedGen", true);
  CAP::RunAnalysis * analysisB = new CAP::RunAnalysis("Run", configuration);
  analysisB->configure();
  analysisB->execute();


  //if (selectedLevel==MessageLogger::Debug) analysis->getConfiguration().writeToFile("DebugConfig.txt");
  return 0;
}

void loadBase(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Base/";
  gSystem->Load(includePath+"Configuration.hpp");
  gSystem->Load(includePath+"Timer.hpp");
  gSystem->Load(includePath+"MessageLogger.hpp");
  gSystem->Load(includePath+"Task.hpp");
  gSystem->Load(includePath+"TaskIterator.hpp");
  gSystem->Load(includePath+"Collection.hpp");
  gSystem->Load(includePath+"DerivedHistoIterator.hpp");
  gSystem->Load("libBase.dylib");
}

void loadParticles(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Particles/";
  gSystem->Load(includePath+"Particle.hpp");
  gSystem->Load(includePath+"ParticleType.hpp");
  gSystem->Load(includePath+"ParticleDecayMode.hpp");
  gSystem->Load("libParticles.dylib");
}

void loadSingle(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/ParticleSingle/";
  gSystem->Load(includePath+"ParticleSingleHistos.hpp");
  gSystem->Load(includePath+"ParticleSingleDerivedHistos.hpp");
  gSystem->Load(includePath+"ParticleSingleAnalyzer.hpp");
  gSystem->Load("libParticleSingle.dylib");
}

void loadPair(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/ParticlePair/";
  gSystem->Load(includePath+"ParticlePairAnalyzer.hpp");
  gSystem->Load(includePath+"ParticlePairHistos.hpp");
  gSystem->Load(includePath+"ParticlePairDerivedHistos.hpp");
  gSystem->Load(includePath+"BalanceFunctionCalculator.hpp");
  gSystem->Load("libParticlePair.dylib");
}

void loadPythia(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/CAPPythia/";
  gSystem->Load(includePath+"PythiaEventGenerator.hpp");
  gSystem->Load(includePath+"PythiaEventReader.hpp");
  gSystem->Load("libCAPPythia.dylib");
}

void loadPerformance(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Performance/";
  gSystem->Load(includePath+"ClosureCalculator.hpp");
  gSystem->Load(includePath+"ClosureIterator.hpp");
  gSystem->Load(includePath+"MeasurementPerformanceSimulator.hpp");
  gSystem->Load(includePath+"ParticlePerformanceSimulator.hpp");
  gSystem->Load(includePath+"ParticlePerformanceAnalyzer.hpp");
  gSystem->Load(includePath+"ParticlePerformanceHistos.hpp");
  gSystem->Load("libPerformance.dylib");
}

void loadAmpt(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Ampt/";
  gSystem->Load(includePath+"AmptEventReader.hpp");
  gSystem->Load("libAmpt.dylib");
}

void loadEpos(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Epos/";
  gSystem->Load(includePath+"EposEventReader.hpp");
  gSystem->Load("libEpos.dylib");
}

void loadHijing(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Hijing/";
  gSystem->Load(includePath+"HijingEventReader.hpp");
  gSystem->Load("libHijing.dylib");
}

void loadHerwig(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Herwig/";
  gSystem->Load(includePath+"HerwigEventReader.hpp");
  gSystem->Load("libHerwig.dylib");
}

void loadUrqmd(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Urqmd/";
  gSystem->Load(includePath+"UrqmdEventReader.hpp");
  gSystem->Load("libUrqmd.dylib");
}


void loadBasicGen(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/BasicGen/";
  gSystem->Load(includePath+"GaussianGeneratorTask.hpp");
  gSystem->Load(includePath+"RadialBoostHistos.hpp");
  gSystem->Load(includePath+"RadialBoostTask.hpp");
  gSystem->Load(includePath+"RapidityGenerator.hpp");
  gSystem->Load("libBasicGen.dylib");
}

void loadGlobal(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Global/";
  gSystem->Load(includePath+"GlobalAnalyzer.hpp");
  gSystem->Load(includePath+"GlobalHistos.hpp");
  gSystem->Load(includePath+"TransverseSpherocityHistos.hpp");
  gSystem->Load(includePath+"TransverseSpherocityAnalyzer.hpp");
  gSystem->Load("libBasicGen.dylib");
}



void loadNuDyn(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/NuDyn/";
  gSystem->Load(includePath+"NuDynAnalyzer.hpp");
  gSystem->Load(includePath+"NuDynDerivedHistos.hpp");
  gSystem->Load(includePath+"NuDynHistos.hpp");
  gSystem->Load("libNuDyn.dylib");
}

void loadSubSample(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/SubSample/";
  gSystem->Load(includePath+"SubSampleStatCalculator.hpp");
  gSystem->Load("libSubSample.dylib");
}

void loadExec(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Exec/";
  //gSystem->Load(includePath+"RunAnalysis.hpp");
  gSystem->Load(includePath+"RunSubsample.hpp");
  gSystem->Load("libExec.dylib");
}

