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
#ifndef CAP__BalFctPlotter
#define CAP__BalFctPlotter

#include <vector>
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TH1.h"
#include "TH2.h"
#include "Aliases.hpp"
#include "Plotter.hpp"

using std::vector;

namespace CAP
{


//!
//!Class used to aggregate and plots ovrlays of BF graphs
//!
class BalFctPlotter : public Plotter
{
public:

  String groupName;
  String outputPath;
  String canvasBaseName;


  int rangeOption;
  //int correlationOption;
  int speciesOption;
  int rapidityOption;
  //int bfOption;

//  String inputPathName;
//  String inputFileNameBase;


  String outputPathNameBase;
  String outputFileNameBase;

  vector<int>     bf_Types;   // B1Bar2, B12Bar, Bs
  vector<int>     bf_Sources; // A, B, C, or D correlations
  vector<TFile*>  bf_InputFiles;
  vector<int>     bf_rebin2Ds;
  vector<int>     bf_rebinFactorsX;
  vector<int>     bf_rebinFactorsY;

  vector<String>  bf_InputPathNames;
  vector<String>  bf_InputFileNames;
  vector<String>  bf_InputFileTitles;
  vector<String>  bf_HistoNameBases;
  vector<String>  bf_HistoTitleBases;
  vector<String>  bf_CanvasNameBases;




  vector<String>  bf_DeltaYDeltaPhi_HistoNames;
  vector<String>  bf_DeltaY_HistoNames;
  vector<String>  bf_DeltaPhi_HistoNames;

  vector<String>  bf_Width_DeltaY_Names;
  vector<String>  bf_Width_DeltaPhi_Names;

  vector<String>  bf_General_Titles;
  vector<String>  bf_DeltaYDeltaPhi_Titles;
  vector<String>  bf_DeltaY_Titles;
  vector<String>  bf_DeltaPhi_Titles;
  vector<String>  bf_Integral_DeltaY_Titles;
  vector<String>  bf_IntegralSum_DeltaY_Titles;
  vector<String>  bf_Width_DeltaY_Titles;
  vector<String>  bf_Width_DeltaPhi_Titles;
  vector<String>  bf_IntegralSumVsName_Titles;

  String  deltaY_Name;
  String  deltaPhi_Name;
  String  deltaY_Title;
  String  deltaPhi_Title;

  String speciesPath;
  vector<String> bf_TypeTitles;
  vector<String> bf_IntegralTypeTitles;
  vector<String> bf_IntegralSumTypeTitles;
  vector<String> bf_WidthDeltaYTypeTitles;

  vector<String> bf_SourceNames;
  vector<String> bf_TypeNames;
  vector<String> correlatorSourceNames;
  vector<String> bf_IntegralTypeNames;
  vector<String> bf_IntegralSumTypeNames;
  vector<String> bf_WidthDeltaYTypeNames;


  vector<String> speciesNames;
  vector<String> speciesTitles;
  vector<String> pairNames;
  vector<String> pairTitles;
  vector<String> pairCumulTitles;

  vector<double>  bf_DeltaYDeltaPhi_Minima;
  vector<double>  bf_DeltaYDeltaPhi_Maxima;
  vector<double>  bf_DeltaY_Minima;
  vector<double>  bf_DeltaY_Maxima;
  vector<double>  bf_DeltaPhi_Minima;
  vector<double>  bf_DeltaPhi_Maxima;
  vector<double>  bf_Integral_DeltaY_Minima;
  vector<double>  bf_Integral_DeltaY_Maxima;
  vector<double>  bf_IntegralSum_DeltaY_Minima;
  vector<double>  bf_IntegralSum_DeltaY_Maxima;
  double  deltaY_Minimum;
  double  deltaY_Maximum;
  double  deltaPhi_Minimum;
  double  deltaPhi_Maximum;
  vector<double>  bf_Width_DeltaY_Minima;
  vector<double>  bf_Width_DeltaY_Maxima;

  vector<TH2*>    bf_DeltaYDeltaPhi_Histos;
  vector<TH1*>    bf_DeltaY_Histos;
  vector<TH1*>    bf_DeltaPhi_Histos;
  vector<TH1*>    bf_SumDeltaY_Histos;
  vector<TH1*>    bf_RatioDeltaY_Histos;

  vector<TGraph*> bf_Integral_DeltaY_Graphs;
  vector<TGraph*> bf_IntegralSum_DeltaY_Graphs;
  TGraph * bf_DeltaY_rmsWidth;
  TGraph* bf_DeltaPhi_rmsWidth;

  vector<double> bf_means_DeltaY;
  vector<double> bf_meanErrors_DeltaY;
  vector<double> bf_rmsWidths_DeltaY;
  vector<double> bf_rmsWidthErrors_DeltaY;
 

  vector<double> bf_means_DeltaPhi;
  vector<double> bf_meanErrors_DeltaPhi;
  vector<double> bf_rmsWidths_DeltaPhi;
  vector<double> bf_rmsWidthErrors_DeltaPhi;
  String  bf_DeltaPhi_rmsWidth_Name;
  String  bf_DeltaPhi_rmsWidth_Title;

  CanvasConfiguration bf_DeltaYDeltaPhi_CanvasConfig;
  CanvasConfiguration bf_DeltaY_CanvasConfig;
  CanvasConfiguration bf_DeltaPhi_CanvasConfig;
  CanvasConfiguration bf_Integral_DeltaY_CanvasConfig;
  CanvasConfiguration bf_IntegralSum_DeltaY_CanvasConfig;
  CanvasConfiguration bf_Width_DeltaY_CanvasConfig;
  CanvasConfiguration bf_Width_DeltaPhi_CanvasConfig;

  GraphConfiguration bf_DeltaYDeltaPhi_GraphConfig;
  vector<GraphConfiguration*> bf_DeltaY_GraphConfigs;
  vector<GraphConfiguration*> bf_DeltaPhi_GraphConfigs;
  vector<GraphConfiguration*> bf_Integral_DeltaY_GraphConfigs;
  vector<GraphConfiguration*> bf_IntegralSum_DeltaY_GraphConfigs;
  GraphConfiguration bf_Width_DeltaY_GraphConfig;
  GraphConfiguration bf_Width_DeltaPhi_GraphConfig;

  LegendConfiguration bf_DeltaYDeltaPhi_LegendConfig;
  LegendConfiguration bf_DeltaY_LegendConfig;
  LegendConfiguration bf_DeltaPhi_LegendConfig;
  LegendConfiguration bf_Integral_DeltaY_LegendConfig;
  LegendConfiguration bf_IntegralSum_DeltaY_LegendConfig;
  LegendConfiguration bf_Width_DeltaY_LegendConfig;
  LegendConfiguration bf_Width_DeltaPhi_LegendConfig;

  bool doPlotsBfVsDeltaYDeltaPhi;
  bool doPlotsBfVsDeltaY;
  bool doPlotsBfVsDeltaPhi;

  bool doPlotsBfIntegralVsDeltaY;
  bool doPlotsBfIntegralSumVsDeltaY;
  bool doPlotsBfWidthDeltaY;
  bool doPlotsBfWidthDeltaPhi;

  bool doPrint;
  bool doPrintGif;
  bool doPrintPdf;
  bool doPrintSvg;
  bool doPrintPng;
  bool doPrintC;

  double rapidityLowEdge;
  double rapidityHighEdge;
  double phiLowEdge;
  double phiHighEdge;

  double rapidityLowEdgeIntegral;
  double rapidityHighEdgeIntegral;


  BalFctPlotter();

  virtual ~BalFctPlotter() {}

  void setSpeciesArrays();
  void createNames();
  void setLegendConfigurations();
  void openInputFiles();

 

  void addSystem(const String & inputPathName,
                 const String & inputFileName,
                 const String & inputFileTitle,
                 const String & histoBaseTitle,
                 const String & histoBaseName,
                 const String & canvasBaseName,
                 int    bf_Type,
                 int    bf_Source,
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
                 double bf_Width_DeltaYMax,
                 bool rebin2D=0,
                 int  rebinFactorX=1,
                 int  rebinFactorY=1);


  void loadHistograms();
  void execute();

  void calculateRmsWidths();
  void calculateRmsWidths(double xLowEdge, double xHighEdge,
                          double yLowEdge, double yHighEdge,
                          int direction=1);
  void calculateBfSums();
  void calculateIntegrals();
  void calculateIntegralsVsFile();


  void plotBF2D();
  void plotBfVsPairvsDeltaY();
  void plotBfVsPairvsDeltaYVsFile();
  void plotBfVsPairvsDeltaPhi();
  void plotBfIntegralVsPairvsDeltaY();
  void plotBfIntegralVsPairvsDeltaYVsFile();
  void plotBFIntegralSumvsPairvsDeltaY();
  void plotRmsWidths();

  ClassDef(BalFctPlotter,0)
};

} // namespace CAP

#endif /* BalFctPlots */
