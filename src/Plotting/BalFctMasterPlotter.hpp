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
#ifndef CAP__BalFctMasterPlotter
#define CAP__BalFctMasterPlotter
#include "BalFctPlotter.hpp"

using std::vector;

namespace CAP
{


//!
//!Class used to aggregate and plots ovrlays of BF graphs
//!
class BalFctMasterPlotter : public Plotter
{
public:

  String groupName;
  String outputPath;
  String canvasBaseName;

  vector<TFile*>  bf_Files;



  vector<int>     bf_rebin2Ds;
  vector<int>     bf_rebinFactorsX;
  vector<int>     bf_rebinFactorsY;
  vector<String>  bf_DeltaYDeltaPhi_HistoNames;
  vector<String>  bf_DeltaY_HistoNames;
  vector<String>  bf_DeltaPhi_HistoNames;

  String          bf_DeltaY_rmsWidth_Name;
  String          bf_DeltaY_rmsWidth_Title;

  int    balFctType;
  int    rapidityType;
  String deltaPhi_Name;
  String deltaY_Name;


  String  bf_Title;
  String  bf_Integral_Title;
  String  bf_IntegralSum_Title;
  String  bf_Width_DeltaY_Title;
  String  bf_Width_DeltaPhi_Title;
  String  deltaY_Title;
  String  deltaPhi_Title;

  vector<String> bf_DeltaYDeltaPhi_CanvasNames;
  String bf_DeltaY_CanvasName;
  String bf_DeltaPhi_CanvasName;
  String bf_Integral_DeltaY_CanvasName;
  String bf_IntegralSum_DeltaY_CanvasName;
  String bf_Width_DeltaY_CanvasName;
  String bf_Width_DeltaPhi_CanvasName;

  vector<double>   bf_DeltaYDeltaPhi_Minima;
  vector<double>   bf_DeltaYDeltaPhi_Maxima;
  vector<double>   bf_DeltaY_Minima;
  vector<double>   bf_DeltaY_Maxima;
  vector<double>   bf_DeltaPhi_Minima;
  vector<double>   bf_DeltaPhi_Maxima;
  vector<double>   bf_Integral_DeltaY_Minima;
  vector<double>   bf_Integral_DeltaY_Maxima;
  vector<double>   bf_IntegralSum_DeltaY_Minima;
  vector<double>   bf_IntegralSum_DeltaY_Maxima;
  vector<double>   bf_Width_DeltaY_Minima;
  vector<double>   bf_Width_DeltaY_Maxima;

  double  deltaY_Minimum;
  double  deltaY_Maximum;
  double  deltaPhi_Minimum;
  double  deltaPhi_Maximum;

  double  bf_Width_DeltaY_Minima;
  double  bf_Width_DeltaY_Maxima;

  vector<TH2*>    bf_DeltaYDeltaPhi_Histos;
  vector<TH1*>    bf_DeltaY_Histos;
  vector<TH1*>    bf_DeltaPhi_Histos;
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

  bool doPlotsBfVsDeltaYDeltaPhi;
  bool doPlotsBfVsDeltaY;
  bool doPlotsBfVsDeltaPhi;

  bool doPlotsBfIntegralVsDeltaY;
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


  BalFctMasterPlotter(const String & _name,
                const Configuration & _configuration);

  virtual ~BalFctMasterPlotter() {}


  void execute();

  void setBFArrays(int option);
  void setSpeciesArrays(int option);
  void createNames();

  ClassDef(BalFctMasterPlotter,0)
};

} // namespace CAP

#endif /* BalFctPlots */
