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
#include "BalFctMasterPlotter.hpp"
using CAP::BalFctMasterPlotter;
using CAP::Configuration;

ClassImp(BalFctMasterPlotter);

BalFctMasterPlotter::BalFctMasterPlotter(const String & _name,
                             const Configuration & _configuration)
:
Plotter(_name, _configuration),
groupName("group"),
outputPath("./"),
canvasBaseName("baseName"),
bf_Files(),
bf_rebin2Ds(),
bf_rebinFactorsX(),
bf_rebinFactorsY(),
bf_DeltaYDeltaPhi_HistoNames(),
bf_DeltaY_HistoNames(),
bf_DeltaPhi_HistoNames(),
bf_DeltaY_rmsWidth_Name("SigmaVsDeltaY"),
bf_DeltaY_rmsWidth_Title("#sigma_{#Delta y}"),
bf_Title("B_{2}"),
bf_Integral_Title("I_{2}"),
bf_IntegralSum_Title("#sum I_{2}"),
bf_Width_DeltaY_Title("#sigma_{#Delta y}"),
bf_Width_DeltaPhi_Title("#sigma_{#Delta #varphi}"),
deltaY_Title("#Delta y"),
deltaPhi_Title("#Delta #varphi"),
bf_DeltaYDeltaPhi_CanvasNames(),
bf_DeltaY_CanvasName(),
bf_DeltaPhi_CanvasName(),
bf_Integral_DeltaY_CanvasName(),
bf_IntegralSum_DeltaY_CanvasName(),
bf_Width_DeltaY_CanvasName(),
bf_Width_DeltaPhi_CanvasName(),
bf_DeltaYDeltaPhi_Minima(),
bf_DeltaYDeltaPhi_Maxima(),
bf_DeltaY_Minima(),
bf_DeltaY_Maxima(),
bf_DeltaPhi_Minima(),
bf_DeltaPhi_Maxima(),
bf_Integral_DeltaY_Minima(),
bf_Integral_DeltaY_Maxima(),
deltaY_Minimum(-10.0),
deltaY_Maximum( 10.0),
deltaPhi_Minimum(-CAP::Math::pi()/4.0),
deltaPhi_Maximum(7.0*CAP::Math::pi()/4.0),
bf_Width_DeltaY_Minima(0.0),
bf_Width_DeltaY_Maxima(1.0),
bf_DeltaYDeltaPhi_Histos(),
bf_DeltaY_Histos(),
bf_DeltaPhi_Histos(),
bf_Integral_DeltaY_Graphs(),
bf_IntegralSum_DeltaY_Graphs(),
bf_DeltaY_rmsWidth(),
bf_DeltaPhi_rmsWidth(),
bf_means_DeltaY(),
bf_meanErrors_DeltaY(),
bf_rmsWidths_DeltaY(),
bf_rmsWidthErrors_DeltaY(),
bf_means_DeltaPhi(),
bf_meanErrors_DeltaPhi(),
bf_rmsWidths_DeltaPhi(),
bf_rmsWidthErrors_DeltaPhi(),
bf_DeltaPhi_rmsWidth_Name("DeltahiRmsWidth"),
bf_DeltaPhi_rmsWidth_Title("#sigma_{#Delta#varphi}"),
bf_DeltaYDeltaPhi_CanvasConfig(CAP::CanvasConfiguration::LandscapeTight, CAP::CanvasConfiguration::Linear),
bf_DeltaY_CanvasConfig(CAP::CanvasConfiguration::LandscapeTight, CAP::CanvasConfiguration::Linear),
bf_DeltaPhi_CanvasConfig(CAP::CanvasConfiguration::LandscapeTight, CAP::CanvasConfiguration::Linear),
bf_Integral_DeltaY_CanvasConfig(CAP::CanvasConfiguration::LandscapeTight, CAP::CanvasConfiguration::Linear),
bf_IntegralSum_DeltaY_CanvasConfig(CAP::CanvasConfiguration::LandscapeTight, CAP::CanvasConfiguration::Linear),
bf_Width_DeltaY_CanvasConfig(CAP::CanvasConfiguration::LandscapeTight, CAP::CanvasConfiguration::Linear),
bf_Width_DeltaPhi_CanvasConfig(CAP::CanvasConfiguration::LandscapeTight, CAP::CanvasConfiguration::Linear),
bf_DeltaYDeltaPhi_GraphConfig(2),
bf_DeltaY_GraphConfigs(),
bf_DeltaPhi_GraphConfigs(),
bf_Integral_DeltaY_GraphConfigs(),
bf_IntegralSum_DeltaY_GraphConfigs(),
bf_Width_DeltaY_GraphConfig(1,0),
bf_Width_DeltaPhi_GraphConfig(1,0),
bf_DeltaYDeltaPhi_LegendConfig(),
bf_DeltaY_LegendConfig(),
bf_DeltaPhi_LegendConfig(),
bf_Integral_DeltaY_LegendConfig(),
bf_IntegralSum_DeltaY_LegendConfig(),
bf_Width_DeltaY_LegendConfig(),
bf_Width_DeltaPhi_LegendConfig(),
doPlotsBfVsDeltaYDeltaPhi(false),
doPlotsBfVsDeltaY(false),
doPlotsBfVsDeltaPhi(false),
doPlotsBfIntegralVsDeltaY(false),
doPlotsBfWidthDeltaY(false),
doPlotsBfWidthDeltaPhi(false),
doPrint(false),
doPrintGif(false),
doPrintPdf(false),
doPrintSvg(false),
doPrintPng(false),
doPrintC(false),
rapidityLowEdge(-4.0),
rapidityHighEdge(4.0),
phiLowEdge(-CAP::Math::pi()/4.0),
phiHighEdge(7*CAP::Math::pi()/4.0),
rapidityLowEdgeIntegral(0.01),
rapidityHighEdgeIntegral(20.0)
{}

void BalFctMasterPlotter::setSpeciesOption(int option)
{
  speciesOption = option;
}

void BalFctMasterPlotter::setOutputBase(const String & pathNameBase, const String & fileNameBase)
{
  outputPathBase  = pathNameBase;
  outFileNameBase = fileNameBase;
}

void BalFctMasterPlotter::addSystem(const String & inputPathName,
                                    const String & inputFileName,
                                    const String & histoTitleBase,
                                    const String & histoNameBase,
                                    const String & canvasNameBase,
                                    int    bfType,
                                    double bf_DeltaYDeltPhiMin,
                                    double bf_DeltaYDeltPhiMax,
                                    double bf_DeltaYMin,
                                    double bf_DeltaYMax,
                                    double bf_DeltPhiMin,
                                    double bf_DeltPhiMax,
                                    double bf_Integral_DeltaYMin,
                                    double bf_Integral_DeltaYMax,
                                    double bf_IntegralSum_DeltaYMin,
                                    double bf_IntegralSum_DeltaYMax,
                                    double bf_Width_DeltaYMin,
                                    double bf_Width_DeltaYMax)
{
  inputPathNames.push_back(inputPathName);
  inputFileNames.push_back(inputFileName);
  histoTitleBases.push_back(histoTitleBase);
  histoNameBases.push_back(histoNameBase);
  canvasNameBase.push_back(canvasNameBase);
  bfTypes.push_back(bfType);
  bf_DeltaYDeltaPhi_Minima.push_back(bf_DeltaYDeltPhiMin);
  bf_DeltaYDeltaPhi_Maxima.push_back(bf_DeltaYDeltPhiMax);
  bf_DeltaY_Minima.push_back(bf_DeltaYMin);
  bf_DeltaY_Maxima.push_back(bf_DeltaYMax);
  bf_DeltaPhi_Minima.push_back(bf_DeltPhiMin);
  bf_DeltaPhi_Maxima.push_back(bf_DeltPhiMax);
  bf_Integral_DeltaY_Minima.push_back(bf_Integral_DeltaYMin);
  bf_Integral_DeltaY_Maxima.push_back(bf_Integral_DeltaYMax);
  bf_IntegralSum_DeltaY_Minima.push_back(bf_IntegralSum_DeltaYMin);
  bf_IntegralSum_DeltaY_Maxima.push_back(bf_IntegralSum_DeltaYMax);
  bf_Width_DeltaY_Minima.push_back(bf_Width_DeltaYMin);
  bf_Width_DeltaY_Maxima.push_back(bf_Width_DeltaYMax);
}

void BalFctMasterPlotter::setRapidityType(int _rapidityType)
{
  rapidityType = _rapidityType;
}

void BalFctMasterPlotter::execute()
{
  int nSystems = inputPathNames.size();
  if (reportInfo(__FUNCTION__))
    {
    printItem("BF Type", bfType);
    printItem("Rapidity Type", rapidityType);
    printItem("Number of systems", nSystems);
    printItem("Number of systems", nSystems);
    }
    createNames(rapidityType,bfType);


  for (int k=0; k<nSystems; k++)
    {
    String importPath = pathNameBase;   importPath += inputPathNames[k];
    String importFile = inputFileNames[k];
    TFile * f =  openRootFile(importPath,importFile,"READ");
    BalFctPlotter * system = new BalFctPlotter();
    systems.push_back(system);
    system->addPlot(f,0,1,1,
                    bf_DeltaYDeltaPhi_HistoName,
                    bf_DeltaY_HistoName,
                    bf_DeltaPhi_HistoName);
    }
}



void BalFctMasterPlotter::createNames(int rapidityType, int balFctType)
{

  deltaPhi_Name  = "DeltaPhi";
  deltaPhi_Title = "#Delta #varphi";
  switch (rapidityType)
    {
      default:
      case 0: deltaY_Title   = "#Delta y";    deltaY_Name    = "DeltaY";    break;
      case 1: deltaY_Title   = "#Delta #eta"; deltaY_Name    = "DeltaEta";  break;
    }

  switch (bfType)
    {
      case 0:
      bf_Title              = "B^{#bar{#alpha}#beta}";
      bf_Integral_Title     = "I^{#bar{#alpha}#beta}";
      bf_IntegralSum_Title  = "#sum I^{#bar{#alpha}#beta}";
      bf_Name               = "B1Bar2";
      bf_Integral_Name      = "I1Bar2";
      bf_IntegralSum_Name   = "I1Bar2Sum";
      bf_Width_Name         = "Width_B1Bar2";
      bf_Width_Title        = "#sigma_{B^{#bar{#alpha}#beta}}";
      break;

      case 1:
      bf_Title              = "B^{#alpha#bar#beta}";
      bf_Integral_Title     = "I^{#alpha#bar#beta}";
      bf_IntegralSum_Title  = "#sum I^{#alpha#bar#beta}";
      bf_Name               = "B12Bar";
      bf_Integral_Name      = "I12Bar";
      bf_IntegralSum_Name   = "I12BarSum";
      bf_Width_Name         = "Width_B12Bar";
      bf_Width_Title        = "#sigma_{B^{#alpha#bar#beta}}";
      break;

      case 2:
      bf_Title              = "B^{s}";
      bf_Integral_Title     = "I^{s}";
      bf_IntegralSum_Title  = "#sum I^{s}";
      bf_Name               = "B12s";
      bf_Integral_Name      = "I12s";
      bf_IntegralSum_Name   = "I12sSum";
      bf_Width_Name         = "Width_B12s";
      bf_Width_Title        = "#sigma_{B^{s}}";
      break;

    }

  String vsPairName = "VsPairName";
  String baseHistoName;
  String baseCanvasName;
  String baseHistoTitle;
  String pairName;
  String bf_DeltaYDeltaPhi_InputName;
  String bf_DeltaY_InputName;
  String bf_DeltaPhi_InputName;
  String title;
  String underscore = "_";
  for (int iFile=0; iFile<bf_InputFiles.size(); iFile++)
    {
    baseHistoName  = bf_HistoNameBases[iFile];
    baseHistoTitle = bf_HistoTitleBases[iFile];
    baseCanvasName = bf_CanvasNameBases[iFile];
    for (int iPair=0; iPair<pairNames.size(); iPair++)
      {
      pairName  = pairNames[iPair];

      bf_DeltaYDeltaPhi_InputName     = baseHistoName+pairName+correlatorSourceNames[2];
      bf_DeltaY_InputName             = baseHistoName+pairName+correlatorSourceNames[2]+"_x";
      bf_DeltaPhi_InputName           = baseHistoName+pairName+correlatorSourceNames[2]+"_y";
      bf_DeltaYDeltaPhi_Histo_InputNames.push_back( bf_DeltaYDeltaPhi_InputName);
      bf_DeltaY_Histo_InputNames.push_back(         bf_DeltaY_InputName);
      bf_DeltaPhi_Histo_InputNames.push_back(       bf_DeltaPhi_InputName);

      title = baseHistoTitle;
      title += " ";
      title += pairName;
      bf_DeltaYDeltaPhi_Titles.push_back(    title  );
      bf_DeltaY_Titles.push_back(            title  );
      bf_DeltaPhi_Titles.push_back(          title  );
      bf_Integral_DeltaY_Titles.push_back(   title  );
      bf_IntegralSum_DeltaY_Titles.push_back(title  );
      }

    for (int iTrigger=0; iTrigger<speciesNames.size(); iTrigger++)
      {
      bf_DeltaYDeltaPhi_CanvasNames.push_back(    makeName(baseCanvasName,bf_Name, speciesNames[iTrigger],  deltaY_Name,DeltaPhi_Name));
      bf_DeltaY_CanvasNames.push_back(            makeName(baseCanvasName,bf_Name, speciesNames[iTrigger],  deltaY_Name  ));

      bf_DeltaPhi_CanvasNames.push_back(          makeName(baseCanvasName,bf_Name, speciesNames[iTrigger],  DeltaPhi_Name));
      bf_Integral_DeltaY_CanvasNames.push_back(   makeName(baseCanvasName,bf_Integral_Name, speciesNames[iTrigger],  deltaY_Name  ));
      bf_IntegralSum_DeltaY_CanvasNames.push_back(makeName(baseCanvasName,bf_IntegralSum_Name, speciesNames[iTrigger],  deltaY_Name  ));
      bf_IntegralVsPair_CanvasNames.push_back(    makeName(baseCanvasName,bf_Integral_Name, speciesNames[iTrigger],  vsPairName  ));
      bf_IntegralSumVsName_Titles.push_back(      baseHistoTitle+String(" ")+ speciesTitles[iTrigger] );
      bf_Width_VsPair_CanvasNames.push_back(      makeName(baseCanvasName,bf_Width_Name, speciesNames[iTrigger],  vsPairName  ));
      }
    }
  for (int iPair=0; iPair<pairNames.size(); iPair++)
    {
    bf_DeltaY_VsPair_CanvasNames.push_back(  makeName(baseCanvasName,bf_Name, pairNames[iPair],  deltaY_Name  ));
    }

}

void BalFctPlotter::setSpeciesArrays(int option)
{
  if (reportInfo(__FUNCTION__)) cout << "SpeciesOption:" << option << endl;
  speciesNames.clear();
  speciesTitles.clear();
  speciesPath = "";

  switch (option)
    {
      case 0:
      speciesNames.push_back(String("HP"));
      speciesTitles.push_back(String("h^{+}"));
      speciesPath = "PM/";
      break;

      case 1:
      speciesNames.push_back(String("PiP"));
      speciesNames.push_back(String("KP"));
      speciesNames.push_back(String("PP"));

      speciesTitles.push_back(String("#pi"));
      speciesTitles.push_back(String("K"));
      speciesTitles.push_back(String("P"));
      speciesPath = "PiKP/";
      break;

      case 2:
      speciesNames.push_back(String("P"));
      speciesNames.push_back(String("N"));
      speciesNames.push_back(String("Lambda0"));
      speciesNames.push_back(String("SigmaP"));
      speciesNames.push_back(String("Sigma0"));
      speciesNames.push_back(String("SigmaM"));
      speciesNames.push_back(String("Xi0"));
      speciesNames.push_back(String("XiM"));
      speciesNames.push_back(String("OmegaM"));

      speciesTitles.push_back(String("p"));
      speciesTitles.push_back(String("n"));
      speciesTitles.push_back(String("#Lambda^{0}"));
      speciesTitles.push_back(String("#Sigma^{+}"));
      speciesTitles.push_back(String("#Sigma^{0}"));
      speciesTitles.push_back(String("#Sigma^{-}"));
      speciesTitles.push_back(String("#Xi^{0}"));
      speciesTitles.push_back(String("#Xi^{-}"));
      speciesTitles.push_back(String("#Omega^{-}"));
      speciesPath = "Baryons/";

      break;

      case 3:
      speciesNames.push_back(String("KP"));
      speciesNames.push_back(String("Lambda0"));
      speciesNames.push_back(String("SigmaP"));
      speciesNames.push_back(String("Sigma0"));
      speciesNames.push_back(String("SigmaM"));
      speciesNames.push_back(String("Xi0"));
      speciesNames.push_back(String("XiM"));
      speciesNames.push_back(String("OmegaM"));

      speciesTitles.push_back(String("K^{+}"));
      speciesTitles.push_back(String("#Lambda^{0}"));
      speciesTitles.push_back(String("#Sigma^{+}"));
      speciesTitles.push_back(String("#Sigma^{0}"));
      speciesTitles.push_back(String("#Sigma^{-}"));
      speciesTitles.push_back(String("#Xi^{0}"));
      speciesTitles.push_back(String("#Xi^{-}"));
      speciesTitles.push_back(String("#Omega^{-}"));
      speciesPath = "Strangeness/";

      break;

      default:
      cout << "Option not available" << endl;
      break;
    }

  Size_t nSpecies = speciesNames.size();
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("nSpecies",nSpecies);
    printItem("speciesPath",speciesPath);
    for (Size_t iSpecies1=0; iSpecies1<nSpecies; iSpecies1++)
      {
      cout << " iSpecies:" << iSpecies1 << "    " << speciesNames[iSpecies1] << "   " << speciesTitles[iSpecies1] << endl;
      }
    }
  if (nSpecies<1) throw TaskException("nSpecies<1","BalFctPlotter::setSpeciesArrays(int option)");
  // setup pairs...
  String pairName;
  String pairTitle;
  String pairFirstTitle;
  String pairCumulTitle;
  String pairTitlePlus;
  for (int iSpecies2=0; iSpecies2<nSpecies; iSpecies2++)
    {
    if (reportDebug(__FUNCTION__)) cout << " iSpecies2.................. : " << iSpecies2 << endl;
    pairTitlePlus = "";
    for (int iSpecies1=0; iSpecies1<nSpecies; iSpecies1++)
      {
      if (reportDebug(__FUNCTION__)) cout << " iSpecies1.................. : " << iSpecies1 << endl;
      pairTitle     = speciesTitles[iSpecies1] + speciesTitles[iSpecies2];
      pairName      = (speciesNames[iSpecies1]+"_")+speciesNames[iSpecies2];
      if (iSpecies1==0)
        {
        pairFirstTitle  = pairTitle;
        pairCumulTitle  = pairTitle;
        }
      else if (iSpecies1==1)
        {
        pairCumulTitle = pairFirstTitle;
        pairCumulTitle += "+";
        pairCumulTitle += pairTitle;
        }
      else  if (iSpecies1>1)
        {
        pairCumulTitle = "...";    //          pairTitlePlus += "+ ... +";
        pairCumulTitle += "+";
        pairCumulTitle += pairTitle;
        }
      pairNames.push_back(pairName);
      pairTitles.push_back(pairTitle);
      pairCumulTitles.push_back(pairCumulTitle);
      }
    }
  if (reportInfo(__FUNCTION__))
    {
    int nPairs = pairNames.size();
    cout << " nPairs................... :" << nPairs << endl;
    for (int k=0; k<nPairs; k++)
      {
      cout << " k:" << k << "    " << pairNames[k] << "   " << pairTitles[k] << "   " << pairCumulTitles[k] << endl;
      }
    }
}

void BalFctMasterPlotter::setBFArrays(int option)
{
  if (reportInfo(__FUNCTION__)) cout << "BalFctTypeOption:" << option << endl;

  switch (option)
    {
      case 0:
      {
      correlatorSourceNames.push_back(String("_B2_DyDphi_shft_B2_1Bar_2"));
      correlatorSourceNames.push_back(String("_B2_DyDphi_shft_B2_1_2Bar"));
      correlatorSourceNames.push_back(String("_B2_DyDphi_shft_B2_12Sum"));
      originCorrelatorPath = "B2Derived/";
      // B vs Y,Phi
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.3);
      // B vs Y
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.3);
      // B vs phi
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.24);
      // I vs Y
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.24);
      // Isum vs Y
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.24);
      // B width
      balFct_Minima.push_back( 0.00);
      balFct_Maxima.push_back( 2.00);
      }
      break;

      case 1:
      {
      cout << "Processing BalFctTypeOption == 1" << endl;
      correlatorSourceNames.push_back(String("_A2_DyDphi_shft_B2_1Bar_2"));
      correlatorSourceNames.push_back(String("_A2_DyDphi_shft_B2_1_2Bar"));
      correlatorSourceNames.push_back(String("_A2_DyDphi_shft_B2_12Sum"));
      originCorrelatorPath = "A2Derived/";

      // B vs Y,Phi
      balFct_Minima.push_back(-0.049);
      balFct_Maxima.push_back( 0.399);
      // B vs Y
      balFct_Minima.push_back(-0.019);
      balFct_Maxima.push_back( 0.399);
      // B vs phi
      balFct_Minima.push_back(-0.019);
      balFct_Maxima.push_back( 0.199);
      // I vs Y
      balFct_Minima.push_back(-0.019);
      balFct_Maxima.push_back( 1.099);
      // Isum vs Y
      balFct_Minima.push_back(-0.019);
      balFct_Maxima.push_back( 1.099);
      // B width
      balFct_Minima.push_back( -0.001);
      balFct_Maxima.push_back( 2.119);
      break;
      }

      default:
      cout << "Option not available" << endl;
      break;
    }
  if (reportInfo(__FUNCTION__))
    {
    cout << " originCorrelatorPath............ : " << originCorrelatorPath  << endl;
    cout << " correlatorSourceNames.size().... : " << correlatorSourceNames.size() << endl;
    cout << " balFct_Minima.size()............ : " << balFct_Minima.size() << endl;
    cout << " balFct_Maxima.size()............ : " << balFct_Maxima.size() << endl;
    }
}


void BalFctPlotter::setLegendConfigurations()
{
  balFct_LegendConfig2Ds.clear();

  balFct_LegendConfig1D_DeltaY.clear();
  balFct_LegendConfig1D_DeltaY_VsPair.clear();
  balFct_LegendConfig1D_DeltaPhi.clear();
  balFct_LegendConfig1D_Integral.clear();
  balFct_LegendConfig1D_IntegralSum.clear();
  balFct_LegendConfig1D_IntegralVsPair.clear();
  balFct_LegendConfig1D_Width.clear();
  int nSpecies = speciesNames.size();
  int iPair;
  LegendConfiguration * lc;

  for (int iSpecies2=0; iSpecies2<nSpecies; iSpecies2++)
    {
    // B vs Delta y
    lc = new LegendConfiguration(0.65, 0.85, 0.5, 0.9, 0.07);
    lc->setParameter("useLegend",true);
    lc->setParameter("useLabels",true);
    lc->setParameter("useTitles",false);
    lc->setParameter("textIndex",42);
    lc->setParameter("nColumns",2);
    balFct_LegendConfig1D_DeltaY.push_back(lc);
    // B vs Delta phi
    lc = new LegendConfiguration(0.5, 0.85, 0.5, 0.94, 0.07);
    lc->setParameter("useLegend",true);
    lc->setParameter("useLabels",true);
    lc->setParameter("useTitles",false);
    lc->setParameter("textIndex",42);
    lc->setParameter("nColumns",3);
    balFct_LegendConfig1D_DeltaPhi.push_back(lc);
    // I vs Delta y
    lc = new LegendConfiguration(0.20, 0.95, 0.81, 0.98, 0.05);
    lc->setParameter("useLegend",true);
    lc->setParameter("useLabels",true);
    lc->setParameter("useTitles",false);
    lc->setParameter("textIndex",42);
    lc->setParameter("nColumns",3);
    balFct_LegendConfig1D_Integral.push_back(lc);
    // Isum vs Delta y
    lc = new LegendConfiguration(0.20, 0.95, 0.81, 0.98, 0.045);
    lc->setParameter("useLegend",true);
    lc->setParameter("useLabels",true);
    lc->setParameter("useTitles",false);
    lc->setParameter("textIndex",42);
    lc->setParameter("nColumns",3);
    balFct_LegendConfig1D_IntegralSum.push_back(lc);

    // I vs Pair
    lc = new LegendConfiguration(0.57, 0.77, 0.62, 0.9, 0.045);
    //lc = new LegendConfiguration(0.20, 0.95, 0.81, 0.98, 0.045);
    lc->setParameter("useLegend",true);
    lc->setParameter("useLabels",true);
    lc->setParameter("useTitles",false);
    lc->setParameter("textIndex",42);
    lc->setParameter("nColumns",1);
    balFct_LegendConfig1D_IntegralVsPair.push_back(lc);

    // width
    //lc = new LegendConfiguration(0.55, 0.8, 0.25, 0.45, 0.05);
    lc = new LegendConfiguration(0.25, 0.5, 0.22, 0.42, 0.05);
    lc->setParameter("useLegend",true);
    lc->setParameter("useLabels",true);
    lc->setParameter("useTitles",false);
    lc->setParameter("textIndex",42);
    lc->setParameter("nColumns",1);
    balFct_LegendConfig1D_Width.push_back(lc);

    for (int iSpecies1=0; iSpecies1<nSpecies; iSpecies1++)
      {
      // B vs Delta y
      lc = new LegendConfiguration(0.65, 0.75, 0.5, 0.9, 0.05);
      lc->setParameter("useLegend",true);
      lc->setParameter("useLabels",true);
      lc->setParameter("useTitles",false);
      lc->setParameter("textIndex",42);
      lc->setParameter("nColumns",1);
      for (int iFile=0; iFile<balFct_InputFiles.size(); iFile++)
        {
        int iPair = iSpecies2*nSpecies + iSpecies1;
        String title = BalFct_HistoTitleBases[iFile];
        title += pairTitles[iPair];
        lc->addLegend(title);
        }
      balFct_LegendConfig1D_DeltaY_VsPair.push_back(lc);

      iPair = iSpecies2*nSpecies + iSpecies1;
      balFct_LegendConfig1D_DeltaY[iSpecies2]->addLegend(pairTitles[iPair]);
      balFct_LegendConfig1D_DeltaPhi[iSpecies2]->addLegend(pairTitles[iPair]);
      balFct_LegendConfig1D_Integral[iSpecies2]->addLegend(pairTitles[iPair]);
      balFct_LegendConfig1D_IntegralSum[iSpecies2]->addLegend(pairCumulTitles[iPair]);
      //balFct_LegendConfig1D_Width[iSpecies2]->addLegend(pairTitles[iPair]);
      }

    int nFiles = balFct_InputFiles.size();
    for (int iFile=0; iFile<nFiles; iFile++)
      {
      if (reportDebug(__FUNCTION__)) cout << "iSpecies2=" << iSpecies2 <<  " iFile=" << iFile << " title=" << balFct_IntegralSumVsName_Titles[iFile*nSpecies + iSpecies2] << endl;
      balFct_LegendConfig1D_IntegralVsPair[iSpecies2]->addLegend(balFct_IntegralSumVsName_Titles[iFile*nSpecies + iSpecies2]);
      balFct_LegendConfig1D_Width[iSpecies2]->addLegend(balFct_IntegralSumVsName_Titles[iFile*nSpecies + iSpecies2]);
      }
    }
}



void BalFctMasterPlotter::execute()
{
  loadHistograms();

  if (doPlotsBfVsDeltaYDeltaPhi)
    {
    for (unsigned long iHist=0;iHist<bf_DeltaYDeltaPhi_Histos.size(); iHist++)
      {
      plot(bf_DeltaYDeltaPhi_CanvasNames[iHist],
           bf_DeltaYDeltaPhi_CanvasConfig,
           bf_DeltaYDeltaPhi_GraphConfig,
           bf_DeltaYDeltaPhi_LegendConfig,
           bf_DeltaYDeltaPhi_Histos[iHist],
           deltaY_Title,   deltaY_Minimum,    deltaY_Maximum,
           deltaPhi_Title, deltaPhi_Minimum,  deltaPhi_Maximum,
           bf_DeltaYDeltaPhi_Titles[iHist],
           bf_DeltaYDeltaPhi_Minima[iHist],
           bf_DeltaYDeltaPhi_Maxima[iHist]);
      }
    }

   if (doPlotsBfVsDeltaY)
     {
     plot(bf_DeltaY_CanvasName,
          bf_DeltaY_CanvasConfig,
          bf_DeltaY_GraphConfigs,
          bf_DeltaY_LegendConfig,
          bf_DeltaY_Histos,
          deltaY_Title,deltaY_Minimum,deltaY_Maximum,
          bf_Title,bf_DeltaY_Minima,bf_DeltaY_Maxima);
     }

    if (doPlotsBfVsDeltaPhi)
      {
      plot(bf_DeltaPhi_CanvasName,
           bf_DeltaPhi_CanvasConfig,
           bf_DeltaPhi_GraphConfigs,
           bf_DeltaPhi_LegendConfig,
           bf_DeltaPhi_Histos,
           deltaPhi_Title,deltaPhi_Minimum,deltaPhi_Maximum,
           bf_Title,bf_DeltaY_Minima,bf_DeltaY_Maxima);
      }

    if (doPlotsBfIntegralVsDeltaY)
      {
      plot(bf_Integral_DeltaY_CanvasName,
           bf_Integral_DeltaY_CanvasConfig,
           bf_Integral_DeltaY_GraphConfigs,
           bf_Integral_DeltaY_LegendConfig,
           bf_Integral_DeltaY_Graphs,
           deltaY_Title,deltaY_Minimum,deltaY_Maximum,
           bf_Title,bf_Integral_DeltaY_Minima,bf_Integral_DeltaY_Maxima);
      plot(bf_IntegralSum_DeltaY_CanvasName,
           bf_IntegralSum_DeltaY_CanvasConfig,
           bf_IntegralSum_DeltaY_GraphConfigs,
           bf_IntegralSum_DeltaY_LegendConfig,
           bf_IntegralSum_DeltaY_Graphs,
           deltaY_Title,deltaY_Minimum,deltaY_Maximum,
           bf_Title,bf_Integral_DeltaY_Minima,bf_Integral_DeltaY_Maxima);
      }

    if (doPlotsBfWidthDeltaY)
      {
      plot(bf_Width_DeltaY_CanvasName,
           bf_Width_DeltaY_CanvasConfig,
           bf_Width_DeltaY_GraphConfig,
           bf_Width_DeltaY_LegendConfig,
           bf_DeltaY_rmsWidth,
           deltaPhi_Title,deltaPhi_Minimum,deltaPhi_Maximum,
           bf_Title,bf_Integral_DeltaY_Minima,bf_Integral_DeltaY_Maxima);
      }

    if (doPrint)
      printAllCanvas(outputPath,doPrintGif,doPrintPdf,doPrintSvg,doPrintPng,doPrintC);
}
