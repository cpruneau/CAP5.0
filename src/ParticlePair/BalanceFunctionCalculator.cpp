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
#include "TString.h"
#include "TRandom.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include <string>
#include <stdio.h>
#include "BalanceFunctionCalculator.hpp"
using CAP::createName;
using CAP::BalanceFunctionCalculator;

ClassImp(BalanceFunctionCalculator)


BalanceFunctionCalculator::BalanceFunctionCalculator(const TString & _name,
                                                     const Configuration & _configuration)
:
EventTask(_name,_configuration),
sObservableNames(),
pObservableNames(),
allFilesToAnalyze(),
appendedString("BalFct"),
calculateCI(1),
calculateCD(1),
calculateBF(1),
calculateDiffs(0)
{
  appendClassName("BalanceFunctionCalculator");
}

void BalanceFunctionCalculator::setDefaultConfiguration()
{
  EventTask::setDefaultConfiguration();
  String null("null");
  addParameter("HistogramsCreate",       true);
  addParameter("HistogramsImport",       true);
  addParameter("HistogramsExport",       true);
  addParameter("HistogramsForceRewrite", true);
  addParameter("AppendedString",         TString("BalFct"));
  addParameter("calculateCI",            true);
  addParameter("calculateCD",            true);
  addParameter("calculateBF",          true);
  addParameter("calculateDiffs",         false);
  addParameter("FillEta",                true);
  addParameter("FillY",                  false);
  addParameter("FillP2",                 false);
  addParameter("nBins_n2",     100);
  addParameter("Min_n2",       0.0);
  addParameter("Max_n2",       100.0);
  addParameter("nBins_eTot",   100);
  addParameter("Min_eTot",     0.0);
  addParameter("Max_eTot",     100.0);
  addParameter("nBins_pt",     18);
  addParameter("Min_pt",       0.20);
  addParameter("Max_pt",       2.00);
  addParameter("nBins_phi",    72);
  addParameter("Min_phi",      0.0);
  addParameter("Max_phi",      CAP::Math::twoPi());
  addParameter("nBins_eta",    20);
  addParameter("Min_eta",      -1.0);
  addParameter("Max_eta",      1.0);
  addParameter("nBins_y",      20);
  addParameter("Min_y",        -1.0);
  addParameter("Max_y",        1.0);
  addParameter("nBins_phiEta",      720);
  addParameter("nBins_phiEtaPt",    7200);
  addParameter("nBins_phiY",        720);
  addParameter("nBins_phiYPt",      7200);
  addParameter("nBins_n2",          100);
  addParameter("Min_n2",            0.0);
  addParameter("Max_n2",            1000.0);
  addParameter("nBins_DeltaPlong",  10);
  addParameter("Min_DeltaPlong",    -1.0);
  addParameter("Max_DeltaPlong",    1.0);
  addParameter("nBins_DeltaPside",  10);
  addParameter("Min_DeltaPside",    -1.0);
  addParameter("Max_DeltaPside",    1.0);
  addParameter("range_DeltaPside",  2.0);
  addParameter("nBins_DeltaPout",   10);
  addParameter("Min_DeltaPout",     -1.0);
  addParameter("Max_DeltaPout",     1.0);
  addParameter("range_DeltaPout",   2.0);
  addParameter("nBins_Dphi",        36);
  addParameter("Min_Dphi",          0.0);
  addParameter("Max_Dphi",          CAP::Math::twoPi());
  addParameter("Width_Dphi",        CAP::Math::twoPi());
  addParameter("nBins_Dphi_shft",   36);
  addParameter("Min_Dphi_shft",     0.0);
  addParameter("Max_Dphi_shft",     0.0);
  addParameter("nBins_Deta",        39);
  addParameter("Min_Deta",          -2.0);
  addParameter("Max_Deta",          2.0);
  addParameter("Width_Deta",        4.0/39.0);
  addParameter("nBins_Dy",          39);
  addParameter("Min_Dy",            -2.0);
  addParameter("Max_Dy",            2.0);
  addParameter("Width_Dy",          4.0/39.0);
}


TH2* BalanceFunctionCalculator::calculate_CI(const TString & histoBaseName,
                                             const TString & eventClassName,
                                             const TString & particleName1,
                                             const TString & particleName2,
                                             const TString & obsName,
                                             TH2* obs_1_2,
                                             TH2* obs_1Bar_2,
                                             TH2* obs_1_2Bar,
                                             TH2* obs_1Bar_2Bar,
                                             HistogramGroup * histogramGroup)
{
  TString name = CAP::createName(getName(),eventClassName,particleName1,particleName2,obsName, "CI" );
  TH2 * obs;
  TH1 * obs_x;
  TH1 * obs_y;
  obs = (TH2*) obs_1Bar_2->Clone();
  obs->SetName(name);
  obs->SetTitle(name);
  obs->Add(obs_1_2Bar);
  obs->Add(obs_1_2);
  obs->Add(obs_1Bar_2Bar);
  obs->Scale(0.25);
  histogramGroup->push_back(obs);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,"CI_x");
  obs_x = obs->ProjectionX();
  obs_x->SetName(name);
  obs_x->SetTitle(name);
  histogramGroup->push_back(obs_x);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,"CI_y");
  obs_y = obs->ProjectionY();
  obs_y->SetName(name);
  obs_y->SetTitle(name);
  histogramGroup->push_back(obs_y);

  return obs;
}

TH2* BalanceFunctionCalculator::calculate_CD(const TString & histoBaseName,
                                             const TString & eventClassName,
                                             const TString & particleName1,
                                             const TString & particleName2,
                                             const TString & obsName,
                                             TH2* obs_1_2,
                                             TH2* obs_1Bar_2,
                                             TH2* obs_1_2Bar,
                                             TH2* obs_1Bar_2Bar,
                                             HistogramGroup * histogramGroup)
{
  TString name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName, "CD" );
  TH2 * obs;
  TH1 * obs_x;
  TH1 * obs_y;
  obs = (TH2*) obs_1Bar_2->Clone();
  obs->SetName(name);
  obs->SetTitle(name);
  obs->Add(obs_1_2Bar);
  obs->Add(obs_1_2, -1.0);
  obs->Add(obs_1Bar_2Bar, -1.0);
  obs->Scale(0.5);
  histogramGroup->push_back(obs);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,"CD_x");
  obs_x = obs->ProjectionX();
  obs_x->SetName(name);
  obs_x->SetTitle(name);
  histogramGroup->push_back(obs_x);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,"CD_y");
  obs_y = obs->ProjectionY();
  obs_y->SetName(name);
  obs_y->SetTitle(name);
  histogramGroup->push_back(obs_y);

  return obs;
}

TH2* BalanceFunctionCalculator::calculate_BalFct(const TString & histoBaseName,
                                                 const TString & eventClassName,
                                                 const TString & particleName1,
                                                 const TString & particleName2,
                                                 const TString & obsName,
                                                 const TString & comboName,
                                                 TH1* rho1_2,
                                                 TH2* obs_US,
                                                 TH2* obs_LS,
                                                 HistogramGroup * histogramGroup)
{
  TString name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName);
  TH2 * obs;
  TH1 * obs_x;
  TH1 * obs_y;
  obs = (TH2*) obs_US->Clone();
  obs->SetName(name);
  obs->SetTitle(name);
  obs->Add(obs_LS, -1.0);

  double wx = obs->GetXaxis()->GetBinWidth(1);
  //double wy = obs->GetYaxis()->GetBinWidth(1);
  obs->Scale(1.0/wx); // make this a function of delta y
  //double rho1Integral = rho1_2->Integral();
  //obs->Scale(1.0/rho1Integral);
  histogramGroup->push_back(obs);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_x");
  obs_x = obs->ProjectionX();
  obs_x->SetName(name);
  obs_x->SetTitle(name);
  histogramGroup->push_back(obs_x);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_y");
  obs_y = obs->ProjectionY();
  obs_y->SetName(name);
  obs_y->SetTitle(name);
  histogramGroup->push_back(obs_y);

  return obs;
}

TH2* BalanceFunctionCalculator::calculate_BalFctSum(const TString & histoBaseName,
                                                    const TString & eventClassName,
                                                    const TString & particleName1,
                                                    const TString & particleName2,
                                                    const TString & obsName,
                                                    const TString & comboName,
                                                    TH2* obs_12Bar,
                                                    TH2* obs_1Bar2,
                                                    HistogramGroup * histogramGroup)
{
  TString name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName);
  TH2 * obs;
  TH1 * obs_x;
  TH1 * obs_y;
  obs = (TH2*) obs_12Bar->Clone();
  obs->SetName(name);
  obs->SetTitle(name);
  obs->Add(obs_1Bar2, 1.0);

  //double rho1Integral = rho1_2->Integral();
  //obs->Scale(0.5/wx);
  obs->Scale(0.5);
  histogramGroup->push_back(obs);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_x");
  obs_x = obs->ProjectionX();
  obs_x->SetName(name);
  obs_x->SetTitle(name);
  histogramGroup->push_back(obs_x);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_y");
  obs_y = obs->ProjectionY();
  obs_y->SetName(name);
  obs_y->SetTitle(name);
  histogramGroup->push_back(obs_y);

  return obs;
}

//TH2* BalanceFunctionCalculator::calculate_BalFct2(const TString & histoBaseName,
//                                                  const TString & eventClassName,
//                                                  const TString & particleName1,
//                                                  const TString & particleName2,
//                                                  const TString & obsName,
//                                                  const TString & comboName,
//                                                  TH1* rho1_1,
//                                                  TH1* rho1_2,
//                                                  TH2* obs_US,
//                                                  TH2* obs_LS,
//                                                  HistogramGroup * histogramGroup)
//{
//  TString name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName);
//  TH2 * obs;
//  TH1 * obs_x;
//  TH1 * obs_y;
//  double rho1_1_Integral = rho1_1->Integral();
//  //double rho1_2_Integral = rho1_2->Integral();
//
////  double low  = rho1_1->GetXaxis()->GetXmin();
////  double high = rho1_1->GetXaxis()->GetXmax();
////  double yieldA = yieldA/(high-low)/CAP::Math::twoPi();
////  double yieldB = yieldB/(high-low)/CAP::Math::twoPi();
//
//
//  obs = (TH2*) obs_US->Clone();
//  obs->SetName(name);
//  obs->SetTitle(name);
//  obs->Add(obs_LS, -1.0);
//  obs->Scale(rho1_1_Integral);
//  histogramGroup->push_back(obs);
//
//  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_x");
//  obs_x = obs->ProjectionX();
//  obs_x->SetName(name);
//  obs_x->SetTitle(name);
//  histogramGroup->push_back(obs_x);
//
//  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_y");
//  obs_y = obs->ProjectionY();
//  obs_y->SetName(name);
//  obs_y->SetTitle(name);
//  histogramGroup->push_back(obs_y);
//
//  return obs;
//}

//TH2* BalanceFunctionCalculator::calculate_BalFct3(const TString & histoBaseName,
//                                                  const TString & eventClassName,
//                                                  const TString & particleName1,
//                                                  const TString & particleName2,
//                                                  const TString & obsName,
//                                                  const TString & comboName,
//                                                  TH1* rho1_2 __attribute__((unused)),
//                                                  TH2* obs_US,
//                                                  TH2* obs_LS,
//                                                  HistogramGroup * histogramGroup)
//{
//  TString name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName);
//  TH2 * obs;
//  TH1 * obs_x;
//  TH1 * obs_y;
//  obs = (TH2*) obs_US->Clone();
//  obs->SetName(name);
//  obs->SetTitle(name);
//  obs->Add(obs_LS, -1.0);
////  double rho1Integral = rho1_2->Integral("Width");
////  obs->Scale(rho1Integral);
//  histogramGroup->push_back(obs);
//
//  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_x");
//  obs_x = obs->ProjectionX();
//  obs_x->SetName(name);
//  obs_x->SetTitle(name);
//  histogramGroup->push_back(obs_x);
//
//  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_y");
//  obs_y = obs->ProjectionY();
//  obs_y->SetName(name);
//  obs_y->SetTitle(name);
//  histogramGroup->push_back(obs_y);
//
//  return obs;
//}



TH2* BalanceFunctionCalculator::calculate_Diff(const TString & histoBaseName,
                                                 const TString & eventClassName,
                                                 const TString & particleName1,
                                                 const TString & particleName2,
                                                 const TString & obsName,
                                                 const TString & comboName,
                                                 TH2* obs_first,
                                               TH2* obs_second,
                                               HistogramGroup * histogramGroup)
{
  TString name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName);
  TH2 * obs;
  TH1 * obs_x;
  TH1 * obs_y;
  obs = (TH2*) obs_first->Clone();
  obs->SetName(name);
  obs->SetTitle(name);
  obs->Add(obs_second, -1.0);
  histogramGroup->push_back(obs);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_x");
  obs_x = obs->ProjectionX();
  obs_x->SetName(name);
  obs_x->SetTitle(name);
  histogramGroup->push_back(obs_x);

  name = CAP::createName(histoBaseName,eventClassName,particleName1,particleName2,obsName,comboName+"_y");
  obs_y = obs->ProjectionY();
  obs_y->SetName(name);
  obs_y->SetTitle(name);
  histogramGroup->push_back(obs_y);

  return obs;
}

void BalanceFunctionCalculator::configure()
{
  EventTask::configure();

  histosImport        = getValueString("HistogramsImport");
  histosImportPath    = getValueString("HistogramsImportPath");
  histosImportFile    = getValueString("HistogramsImportFile");
  histosExport        = getValueString("HistogramsExport");
  histosExportPath    = getValueString("HistogramsExportPath");
  histosExportFile    = getValueString("HistogramsExportFile");
  histosForceRewrite  = getValueBool(  "HistogramsForceRewrite");
  appendedString      = getValueString("AppendedString");
  calculateCI         = getValueBool("calculateCI" );
  calculateCD         = getValueBool("calculateCD" );
  calculateBF         = getValueBool("calculateBF" );
  calculateDiffs      = getValueBool("calculateDiffs" );

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("Task name",             getName());
    printItem("HistogramsImportPath",  histosImportPath);
    printItem("HistogramsImportFile",  histosImportFile);
    printItem("HistogramsExportPath",  histosExportPath);
    printItem("HistogramsExportFile",  histosExportFile);
    printItem("HistogramsForceRewrite",histosForceRewrite);
    printItem("AppendedString",        appendedString);
    printItem("calculateCI",           calculateCI);
    printItem("calculateCD",           calculateCD);
    printItem("calculateBF",           calculateBF);
    printItem("calculateDiffs",        calculateDiffs);
    cout << endl;
    }
}

void BalanceFunctionCalculator::initialize()
{
  initializeTaskExecuted();
  initializeNEventsAccepted();
  initializeNParticlesAccepted();
  initializeFilters();
  initializeParticleDbLink();
}



void BalanceFunctionCalculator::execute()
{
  if (reportStart(__FUNCTION__))
    ;

//  cout << "histosImportPath : " << histosImportPath << endl;
//  cout << "histosImportFile : " << histosImportFile << endl;
//  cout << "histosExportPath : " << histosExportPath << endl;
//  cout << "histosExportFile : " << histosExportFile << endl;
//  exit(1);

  if (histosImportFile.Contains("DEFAULT") ||
      histosImportFile.Contains("none") ||
      histosImportFile.Contains("null") ||
      histosImportFile.Contains("nil") ||
      histosImportFile.IsNull() )
    {
    if (reportInfo(__FUNCTION__))
      {
      cout << endl;
      cout << "Generating a list of files!" << endl;
      }
    vector<TString> includePatterns = getSelectedValues("IncludedPattern", "none");
    vector<TString> excludePatterns = getSelectedValues("ExcludedPattern", "none");
    for (unsigned int k=0;k<includePatterns.size();k++) cout << " k:" << k << "  Include: " << includePatterns[k] << endl;
    for (unsigned int k=0;k<excludePatterns.size();k++) cout << " k:" << k << "  Exclude: " << excludePatterns[k] << endl;
    cout << " ===========================================================" << endl;
    bool prependPath = true;
    bool verbose     = true;
    int  maximumDepth = 2;
    allFilesToAnalyze = listFilesInDir(histosImportPath,includePatterns,excludePatterns,prependPath, verbose, maximumDepth);
    }
  else
    {
    if (reportInfo(__FUNCTION__))
      {
      cout << endl;
      cout << "Using a fixed file!" << endl;
      printItem("HistogramsImportPath",histosImportPath);
      printItem("HistogramsImportFile",histosImportFile);
      }
    allFilesToAnalyze.push_back(histosImportPath+histosImportFile);
    }

  int nFilesToAnalyze = allFilesToAnalyze.size();
  if (reportInfo(__FUNCTION__)) cout << "nFilesToAnalyze : " << nFilesToAnalyze << endl;
  if (nFilesToAnalyze<1)
    {
    if (reportFatal(__FUNCTION__))
      {
      cout << endl;
      cout << "========================================================================"  << endl;
      cout << "========================================================================"  << endl;
      cout << "  Attempting to execute BalFct analysis with no selected files." << endl;
      cout << "                         Check your code!!!!!!! " <<  endl;
      cout << "========================================================================"  << endl;
      cout << "========================================================================"  << endl;
      }
    throw TaskException("Check input file","BalanceFunctionCalculator::execute()");
    }
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("Task name",             getName());
    printItem("HistogramsImportPath",  histosImportPath);
    printItem("HistogramsImportFile",  histosImportFile);
    printItem("HistogramsExportPath",  histosExportPath);
    printItem("HistogramsExportFile",  histosExportFile);
    printItem("HistogramsForceRewrite",histosForceRewrite);
    printItem("AppendedString",        appendedString);
    printItem("calculateCI",           calculateCI);
    printItem("calculateCD",           calculateCD);
    printItem("calculateBF",           calculateBF);
    printItem("calculateDiffs",        calculateDiffs);
    cout << endl;
    }

  for (int iFile =0; iFile<nFilesToAnalyze; iFile++)
    {
    histosImportFile  = allFilesToAnalyze[iFile];
    histosExportFile  = removeRootExtension(histosImportFile);
    histosExportFile.ReplaceAll(TString("Derived"),appendedString);
    TFile & inputFile = *openRootFile("",histosImportFile,"OLD");
    String option = "NEW";
    if (histosForceRewrite) option = "RECREATE";
    TFile & outputFile = *openRootFile("",histosExportFile,option);
    if (reportInfo(__FUNCTION__))
      {
      cout << endl;
      printItem("From",histosImportFile);
      printItem("Saved to",histosExportFile);
      }

    // Use histogramGroup  as helper to load and calculate histograms, etc.
    HistogramGroup * histogramGroup  = new HistogramGroup(this,getName(), configuration);
    histogramGroup ->setOwnership(false);
    loadNEexecutedTask(inputFile);
    loadNEventsAccepted(inputFile);

    unsigned int nSpecies = particleFilters.size()/2;
    vector<TString>  sObservableNames;
    vector<TString>  pObservableNames;
    int observableSelection = 5;
    switch (observableSelection)
      {
        default:
        case 0: // eta based observables, full complement
        sObservableNames.push_back("n1_eta");
        sObservableNames.push_back("n1_phi");
        pObservableNames.push_back("R2_ptpt");
        pObservableNames.push_back("R2_phiPhi");
        pObservableNames.push_back("R2_etaEta");
        pObservableNames.push_back("R2_DetaDphi_shft");
        break;

        case 1: // eta based observables, only DeltaEta vs DeltaPhi
        sObservableNames.push_back("n1_eta");
        sObservableNames.push_back("n1_phi");
        pObservableNames.push_back("rho2_DetaDphi_shft");
        break;

        case 2: // y based observables, full complement
        sObservableNames.push_back("n1_y");
        sObservableNames.push_back("n1_phi");
        pObservableNames.push_back("R2_ptpt");
        pObservableNames.push_back("R2_phiPhi");
        pObservableNames.push_back("R2_yY");
        pObservableNames.push_back("R2_DyDphi_shft");
        break;

        case 3: // y based observables, only DeltaY vs DeltaPhi
        sObservableNames.push_back("n1_y");
        sObservableNames.push_back("n1_phi");
        pObservableNames.push_back("R2_DyDphi_shft");
        break;

        case 4: // eta based observables, only DeltaEta vs DeltaPhi
        sObservableNames.push_back("n1_eta");
        sObservableNames.push_back("n1_phi");
        pObservableNames.push_back("rho2_DetaDphi_shft");
        pObservableNames.push_back("R2_DetaDphi_shft");
        //pObservableNames.push_back("B2AB_DetaDphi_shft");
        //pObservableNames.push_back("B2BA_DetaDphi_shft");
        //        pObservableNames.push_back("n2_phiPhi");
        break;

        case 5: // y based observables
        sObservableNames.push_back("n1_y");
        sObservableNames.push_back("n1_phi");
        pObservableNames.push_back("A2_DyDphi_shft");
        pObservableNames.push_back("B2_DyDphi_shft");
        pObservableNames.push_back("C2_DyDphi_shft");
        pObservableNames.push_back("D2_DyDphi_shft");
        pObservableNames.push_back("R2_DyDphi_shft");
        pObservableNames.push_back("B2_yY");
        //pObservableNames.push_back("B2_phiPhi");
        break;
      }


    if (reportInfo(__FUNCTION__))
      {
      cout << endl;
      printItem("nSpecies",nSpecies);
      for (unsigned int iPart1=0; iPart1<nSpecies; iPart1++)
        {
        cout << "iPart1:" <<  iPart1 << "  named: "<< particleFilters[iPart1]->getName() << endl;
        }
      printItem("sObservableNames.size()",int(sObservableNames.size()));
      for (unsigned int k=0; k<sObservableNames.size(); k++)
        printItem("   ",sObservableNames[k]);
      printItem("pObservableNames.size()",int(pObservableNames.size()));
      for (unsigned int k=0; k<pObservableNames.size(); k++)
        printItem("   ",pObservableNames[k]);
      }
     for (unsigned int iObservable = 0; iObservable<pObservableNames.size();iObservable++)
      {
      for (unsigned int iPart1=0; iPart1<nSpecies; iPart1++)
        {
        for (unsigned int iPart2=0; iPart2<nSpecies; iPart2++)
          {
          for (unsigned int iEventClass = 0; iEventClass<eventFilters.size();iEventClass++)
            {
            // load histogram and compute derived files.
            TString eventClassName   = eventFilters[iEventClass]->getName();
            TString particleName1    = particleFilters[iPart1]->getName();
            TString particleName1Bar = particleFilters[iPart1+nSpecies]->getName();
            TString particleName2    = particleFilters[iPart2]->getName();
            TString particleName2Bar = particleFilters[iPart2+nSpecies]->getName();
            TH1 * rho1_1             = histogramGroup ->loadH1(inputFile,createName(getName(),eventClassName,particleName1,   sObservableNames[0]));
            TH1 * rho1_1Bar          = histogramGroup ->loadH1(inputFile,createName(getName(),eventClassName,particleName1Bar,sObservableNames[0]));
            TH1 * rho1_2             = histogramGroup ->loadH1(inputFile,createName(getName(),eventClassName,particleName2,   sObservableNames[0]));
            TH1 * rho1_2Bar          = histogramGroup ->loadH1(inputFile,createName(getName(),eventClassName,particleName2Bar,sObservableNames[0]));
            TH2 * obs_1_2            = histogramGroup ->loadH2(inputFile,createName(getName(),eventClassName,particleName1,    particleName2,    pObservableNames[iObservable]));
            TH2 * obs_1Bar_2         = histogramGroup ->loadH2(inputFile,createName(getName(),eventClassName,particleName1Bar, particleName2,    pObservableNames[iObservable]));
            TH2 * obs_1_2Bar         = histogramGroup ->loadH2(inputFile,createName(getName(),eventClassName,particleName1,    particleName2Bar, pObservableNames[iObservable]));
            TH2 * obs_1Bar_2Bar      = histogramGroup ->loadH2(inputFile,createName(getName(),eventClassName,particleName1Bar, particleName2Bar, pObservableNames[iObservable]));

            if (calculateCI)
              calculate_CI(getName(),eventClassName,particleName1,particleName2, pObservableNames[iObservable],obs_1_2,obs_1Bar_2,obs_1_2Bar,obs_1Bar_2Bar,histogramGroup );

            if (calculateCD)
              calculate_CD(getName(),eventClassName,particleName1,particleName2, pObservableNames[iObservable],obs_1_2,obs_1Bar_2,obs_1_2Bar,obs_1Bar_2Bar,histogramGroup );

            if (calculateBF)
              {
              TH2* bfa = calculate_BalFct(getName(),eventClassName,particleName1,particleName2, pObservableNames[iObservable], "B2_1_2Bar",rho1_2Bar, obs_1_2Bar, obs_1Bar_2Bar,histogramGroup );
              TH2* bfb = calculate_BalFct(getName(),eventClassName,particleName1,particleName2, pObservableNames[iObservable], "B2_1Bar_2",rho1_2,    obs_1Bar_2, obs_1_2,histogramGroup );
              calculate_BalFctSum(getName(),eventClassName,particleName1,particleName2, pObservableNames[iObservable], "B2_12Sum",bfa,bfb,histogramGroup );
              }
            if (calculateDiffs)
              {
              calculate_Diff(getName(),eventClassName,particleName1,particleName2, pObservableNames[iObservable], "Diff_US",   obs_1Bar_2,    obs_1_2Bar,histogramGroup );
              calculate_Diff(getName(),eventClassName,particleName1,particleName2, pObservableNames[iObservable], "Diff_LS",   obs_1Bar_2Bar, obs_1_2,histogramGroup );
              }
            }
          }
        }
      }
    outputFile.cd();
    histogramGroup->exportHistograms(outputFile);
    writeNEventsAccepted(outputFile);
    writeNEexecutedTask(outputFile);

    inputFile.Close();
    outputFile.Close();
    histogramGroup->clear();
    delete histogramGroup ;
    }
  if (reportEnd(__FUNCTION__))
    ;
}
