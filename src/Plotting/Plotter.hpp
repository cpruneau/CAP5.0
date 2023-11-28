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
#ifndef CAP__Plotter
#define CAP__Plotter
#include "TSystem.h"
#include "TStyle.h"
#include "HistogramCollection.hpp"
#include "CanvasCollection.hpp"
#include "CanvasConfiguration.hpp"
#include "GraphConfiguration.hpp"
#include "LegendConfiguration.hpp"
#include "DataGraph.hpp"
#include "Task.hpp"

namespace CAP
{


class Plotter : public Task
{
public:

  Plotter();
  
  virtual ~Plotter() {} 

  //!
  //! Initialize the configuration parameter of the task to their default value;
  //!
  virtual void setDefaultConfiguration();

  //!
  //! Configure  this analysis task
  //!
  virtual void configure();

  //!
  //! Function to plot a single 1D histogram in a new canvas with the given canvas configuration, graph configuration, and a legend. If the text of the legend is a null or empty
  //! string, no legend will be shown on the graph.
  //!
  //! @param canvasName Name to be given to the canvas
  //! @param cc   configuration of the canvas
  //! @param gc   configuration of the graph (histogram)
  //! @param xTitle title of the x-axis
  //! @param xMin mimum of the x-axis
  //! @param xMax maximum of the x-axis
  //! @param yTitle title of the y-axis
  //! @param yMin mimum of the y-axis
  //! @param yMax maximum of the y-axis
  //! @param h    pointer  to the histogram to be plotted
  //! @param legendText  text of the legend entry associated with the graph if any (OK to supply a null string)
  //! @param xMinLeg  x position of the left corner of the legend box
  //! @param yMinLeg  y position of the left corner of the legend box
  //! @param xMaxLeg  x position of the left corner of the legend box
  //! @param yMaxLeg  y position of the left corner of the legend box
  //! @param legendSize  size used to plot the legend's text.
  //!
//  TCanvas *  plot(TH1 * h,
//                  const String & canvasName,
//                  const Configuration & cc,
//                  const GraphConfiguration  & gc,
//                  const String & xTitle,  double xMin, double xMax,
//                  const String & yTitle,  double yMin, double yMax,
//                  const String & legendText,
//                  double xMinLeg, double yMinLeg, double xMaxLeg, double yMaxLeg,
//                  double legendSize);

  //!
  //! Function to plot a single 2D histogram in a new canvas with the given canvas configuration, graph configuration, and a legend. If the text of the legend is a null or empty
  //! string, no legend will be shown on the graph.
  //!
  //! @param canvasName Name to be given to the canvas
  //! @param cc   configuration of the canvas
  //! @param gc   configuration of the graph (histogram)
  //! @param xTitle title of the x-axis
  //! @param xMin mimum of the x-axis
  //! @param xMax maximum of the x-axis
  //! @param yTitle title of the y-axis
  //! @param yMin mimum of the y-axis
  //! @param yMax maximum of the y-axis
  //! @param zTitle title of the z-axis
  //! @param zMin mimum of the z-axis
  //! @param zMax maximum of the z-axis
  //! @param h    pointer  to the histogram to be plotted
  //! @param legendText  text of the legend entry associated with the graph if any (OK to supply a null string)
  //! @param xMinLeg  x position of the left corner of the legend box
  //! @param yMinLeg  y position of the left corner of the legend box
  //! @param xMaxLeg  x position of the left corner of the legend box
  //! @param yMaxLeg  y position of the left corner of the legend box
  //! @param legendSize  size used to plot the legend's text.
  //!
//  TCanvas *  plot(TH2 * h,
//                  const String & canvasName,
//                  const Configuration & cc,
//                  const GraphConfiguration  & gc,
//                  const String & xTitle,  double xMin, double xMax,
//                  const String & yTitle,  double yMin, double yMax,
//                  const String & zTitle,  double zMin, double zMax);
//
//  TCanvas *  plot(vector<TH1*> histograms,
//                  const vector<GraphConfiguration*> & graphConfigurations,
//                  const VectorString   &  legendTexts,
//                  const String & canvasName,
//                  const Configuration & canvasConfiguration,
//                  const String & xTitle,  double xMin, double xMax,
//                  const String & yTitle,  double yMin, double yMax,
//                  double xMinLeg, double yMinLeg, double xMaxLeg, double yMaxLeg,
//                  double legendSize);
//
//  TCanvas *  plot(vector<TGraph*> graphs,
//                  const vector<GraphConfiguration*> & graphConfigurations,
//                  const VectorString   &  legendTexts,
//                  const String & canvasName,
//                  const Configuration & canvasConfiguration,
//                  const String & xTitle,  double xMin, double xMax,
//                  const String & yTitle,  double yMin, double yMax,
//                  double xMinLeg, double yMinLeg, double xMaxLeg, double yMaxLeg,
//                  double legendSize);

  TCanvas *  plot(const String & canvasName,
                  const CanvasConfiguration  & cc,
                  const GraphConfiguration   & gc,
                  LegendConfiguration  & lc,
                  TH1 * h,
                  const String & xTitle,  double xMin, double xMax,
                  const String & yTitle,  double yMin, double yMax);

  TCanvas *  plot(const String & canvasName,
                  const CanvasConfiguration  & cc,
                  const GraphConfiguration   & gc,
                  LegendConfiguration  & lc,
                  TH2 * h,
                  const String & xTitle,  double xMin, double xMax,
                  const String & yTitle,  double yMin, double yMax,
                  const String & zTitle,  double zMin, double zMax);

  TCanvas *  plot(const String & canvasName,
                  const CanvasConfiguration  & cc,
                  const GraphConfiguration   & gc,
                  LegendConfiguration  & lc,
                  TGraph * h,
                  const String & xTitle,  double xMin, double xMax,
                  const String & yTitle,  double yMin, double yMax);

  TCanvas *  plot(const String & canvasName,
                  const CanvasConfiguration  & cc,
                  const vector<GraphConfiguration*> & gc,
                  LegendConfiguration  & lc,
                  vector<TH1*> histograms,
                  const String & xTitle,  double xMin, double xMax,
                  const String & yTitle,  double yMin, double yMax);

  TCanvas *  plot(const String & canvasName,
                  const CanvasConfiguration  & cc,
                  const vector<GraphConfiguration*> & gc,
                  LegendConfiguration  & lc,
                  vector<TGraph*> graphs,
                  const String & xTitle,  double xMin, double xMax,
                  const String & yTitle,  double yMin, double yMax);

  //  // ================================================================================================
  //  // Function to plot nHists 1D histogram
  //  // h       : vector of nHists pointers to histograms
  //  // legends : vector of nHists pointers to labels used as legends in the body of the plot
  //  // ================================================================================================
  //  TCanvas *  plot(String  canvasName, Configuration & cc, vector<GraphConfiguration*> gc,
  //                  String  xTitle,  double xMin, double xMax,
  //                  String  yTitle,  double yMin, double yMax,
  //                  vector<TH1*> histograms,
  //                  VectorString  legends,
  //                  double xMinLeg, double yMinLeg, double xMaxLeg, double yMaxLeg,double legendSize,
  //                  bool label1=0, String text1="", double x1=0.0, double y1=0.0, int color1=1,  double fontSize1=0.05,
  //                  bool label2=0, String text2="", double x2=0.0, double y2=0.0, int color2=1,  double fontSize2=0.05);
  //
  //  TCanvas * plot(String  canvasName, Configuration & cc,
  //                 String  xTitle,  double xMin, double xMax,
  //                 String  yTitle,  double yMin, double yMax,
  //                 vector<DataGraph*> graphs,
  //                 double xMinLeg, double yMinLeg, double xMaxLeg, double yMaxLeg,double legendSize);

  ////////////////////////////////////////////////////////////////////////
  // Setting Histogram Properties
  ////////////////////////////////////////////////////////////////////////

  void findMinMax(TH1* histogram, double & minimum, double & maximum);

  void setProperties(TH1 * h, const GraphConfiguration & graphConfiguration);
  void setProperties(TH1 * h, const GraphConfiguration & graphConfiguration, const String & xTitle, const String & yTitle, const String & zTitle="");

  void setProperties(TGraph * g, const GraphConfiguration & graphConfiguration);
  void setProperties(TGraph * g, const GraphConfiguration & graphConfiguration, const String & xTitle, const String & yTitle);

  TLatex  * createLabel(const String & text, double x, double y, double angle, int color,  double fontSize, bool doDraw=true);

  TLegend * createLegend(double x1, double y1, double x2, double y2, double fontSize);
  TLegend * createLegend(TH1*histogram, const String & legendText, double x1, double y1, double x2, double y2, double fontSize, bool doDraw=true);
  TLegend * createLegend(vector<TH1*> h,VectorString  legendTexts,double x1, double y1, double x2, double y2, double fontSize, bool doDraw=true);
  TLegend * createLegend(vector<TGraph*> h,VectorString  legendTexts,double x1, double y1, double x2, double y2, double fontSize, bool doDraw=true);
  TLegend * createLegend(vector<DataGraph*> graphs,double x1, double y1, double x2, double y2, double fontSize, bool doDraw=true);

  TLegend * createLegend(const LegendConfiguration & legendConfig);
  TLegend * createLegend(TH1*histogram, const LegendConfiguration & legendConfig);
  TLegend * createLegend(vector<TH1*> h,const LegendConfiguration & legendConfig);
  TLegend * createLegend(TGraph*graph, const LegendConfiguration & legendConfig);
  TLegend * createLegend(vector<TGraph*> h,const LegendConfiguration & legendConfig);
  TLegend * createLegend(vector<DataGraph*> graphs,const LegendConfiguration & legendConfig);

  TLine   * createLine(float x1, float y1, float x2, float y2, int style, int color, int width, bool doDraw=true);
  TArrow  * createArrow(float x1, float y1, float x2, float y2, float arrowSize, Option_t* option, int style, int color, int width, bool doDraw=true);
  void setDefaultOptions(bool color);

  void printAllCanvas(const String & outputPath, bool printGif, bool printPdf, bool printSvg, bool printPng, bool printC);
  void printAllCanvas(const String & outputPath);

  CanvasCollection & getCanvases()
  {
  return canvasCollection;
  }

  HistogramCollection & getHistogramCollection()
  {
  return histogramCollection;
  }

  double findHistoMinimum(TH1 * h);
  double findHistoMaximum(TH1 * h);
  double findHistoMinimum2D(TH2 * h);
  double findHistoMaximum2D(TH2 * h);
  double findGraphMinimum(TGraph * h);
  double findGraphMaximum(TGraph * h);
  double findMinimum(vector<double> & values);
  double findMaximum(vector<double> & values);

  String makeName(const String  & s1,
                  const String  & s2);
  String makeName(const String  & s1,
                  const String  & s2,
                  const String  & s3);
  String makeName(const String  & s1,
                  const String  & s2,
                  const String  & s3,
                  const String  & s4);
  String makeName(const String  & s1,
                  const String  & s2,
                  const String  & s3,
                  const String  & s4,
                  const String  & s5);

  TGraph * makeGraph(vector<double> vx,
                     vector<double> vex,
                     vector<double> vy,
                     vector<double> vey);

  vector<CAP::GraphConfiguration*> createGraphConfigurationPalette(int n, int dim);

  TGraph * sumGraphs(TGraph * g1, TGraph * g2);


  TGraph* calculateIntegral1D(TH1* h,
                            double etaLow,
                            double etaHigh,
                            double etaStep,
                            int size=500);

  TGraph* calculateIntegral(TH2* h2,
                            double etaLow,
                            double etaHigh,
                            double etaStep,
                            int size=500);

  void calculateRmsWidth(TH2 * h,
                         double xLowEdge, double xHighEdge,
                         double yLowEdge, double yHighEdge,
                         double & mean, double & meanError,
                         double & rmsWidth, double & rmsWidthError,
                         int direction=1);

  double GeneralizedGaussian(double *x, double *par);


protected:

  CanvasCollection canvasCollection;
  HistogramCollection histogramCollection;

  ClassDef(Plotter,0)
};

} // namespace CAP

#endif /* CAP__Plotter */
