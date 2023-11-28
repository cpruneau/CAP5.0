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
#include "Plotter.hpp"
using CAP::Plotter;

ClassImp(Plotter);

Plotter::Plotter()
:
Task(),
canvasCollection(),
histogramCollection("Histos",Severity::Info)
{
  appendClassName("Plotter");
}

void Plotter::setDefaultConfiguration()
{
  Task::setDefaultConfiguration();
  bool YES = true;
  bool NO  = false;
  addParameter("DoPrint",                NO);
  addParameter("DoPrintGif",             NO);
  addParameter("DoPrintPdf",             NO);
  addParameter("DoPrintSvg",             NO);
  addParameter("DoPrintPng",             YES);
  addParameter("UseColor",               YES);
}

//!
//! Configure  this analysis task
//!
void Plotter::configure()
{
  Task::configure();
}



///
TCanvas *  Plotter::plot(const String & canvasName,
                         const CanvasConfiguration  & cc,
                         const GraphConfiguration   & gc,
                         LegendConfiguration  & lc,
                         TH1 * h,
                         const String & xTitle,  double xMin, double xMax,
                         const String & yTitle,  double yMin, double yMax)
{
  if (reportDebug(__FUNCTION__)) cout << "Creating canvas named:" << canvasName << endl;
  TCanvas * canvas  = canvasCollection.createCanvas(canvasName,cc);
  canvas->SetTicky(1);
  canvas->SetTickx(1);
  setProperties(h,gc);
  h->GetXaxis()->SetTitle(xTitle);
  h->GetYaxis()->SetTitle(yTitle);
  h->SetMinimum(yMin);
  h->SetMaximum(yMax);
  if (xMin<xMax) h->GetXaxis()->SetRangeUser(xMin,xMax);
  String plotOption = gc.getValueString("PlotOption");
  h->DrawCopy(plotOption);

  if (lc.useLegend()) createLegend(h,lc);
  if (lc.useLabels()) lc.drawLabels();
  return canvas;
}

TCanvas *  Plotter::plot(const String & canvasName,
                         const CanvasConfiguration  & cc,
                         const GraphConfiguration   & gc,
                         LegendConfiguration  & lc,
                         TH2 * h,
                         const String & xTitle,  double xMin, double xMax,
                         const String & yTitle,  double yMin, double yMax,
                         const String & zTitle,  double zMin, double zMax)
{
  if (reportDebug(__FUNCTION__)) cout << "Creating canvas named:" << canvasName << endl;
  TCanvas * canvas  = canvasCollection.createCanvas(canvasName,cc);
  setProperties(h,gc);
  h->GetXaxis()->SetTitle(xTitle);
  h->GetYaxis()->SetTitle(yTitle);
  h->GetZaxis()->SetTitle(zTitle);
  if (xMin < xMax) h->GetXaxis()->SetRangeUser(xMin,xMax);
  if (yMin < yMax) h->GetYaxis()->SetRangeUser(yMin,yMax);
  if (zMin < zMax)
    {
    h->SetMinimum(zMin);
    h->SetMaximum(zMax);
    }
  h->DrawCopy(gc.getValueString("PlotOption"));
  if (lc.useLegend()) createLegend(h,lc);
  if (lc.useLabels()) lc.drawLabels();
  return canvas;
}


TCanvas *  Plotter::plot(const String & canvasName,
                         const CanvasConfiguration  & cc,
                         const GraphConfiguration   & gc,
                         LegendConfiguration  & lc,
                         TGraph * h,
                         const String & xTitle,  double xMin, double xMax,
                         const String & yTitle,  double yMin, double yMax)
{
  if (reportDebug(__FUNCTION__)) cout << "Creating canvas named:" << canvasName << endl;
  TCanvas * canvas  = canvasCollection.createCanvas(canvasName,cc);
  canvas->SetTicky(1);
  canvas->SetTickx(1);
  setProperties(h,gc);
  h->GetXaxis()->SetTitle(xTitle);
  h->GetYaxis()->SetTitle(yTitle);
  h->SetMinimum(yMin);
  h->SetMaximum(yMax);
  if (xMin<xMax) h->GetXaxis()->SetRangeUser(xMin,xMax);
  String plotOption = gc.getValueString("PlotOption");
  h->Draw(plotOption);

  if (lc.useLegend()) createLegend(h,lc);
  if (lc.useLabels()) lc.drawLabels();
  return canvas;
}


TCanvas *  Plotter::plot(const String & canvasName,
                         const CanvasConfiguration  & cc,
                         const vector<GraphConfiguration*> & gc,
                         LegendConfiguration  & lc,
                         vector<TH1*> histograms,
                         const String & xTitle,  double xMin, double xMax,
                         const String & yTitle,  double yMin, double yMax)
{
  TCanvas * canvas = canvasCollection.createCanvas(canvasName,cc);
  canvas->SetTicky(1);
  canvas->SetTickx(1);
  TH1 * h;
  Size_t nGraphs = histograms.size();
  if (reportInfo(__FUNCTION__)) 
    {
    printItem("Creating canvas named",canvasName);
    printItem("nGraphs",nGraphs);
    printItem("gc.size",gc.size());
    }
  for (Size_t iGraph=0; iGraph<nGraphs; iGraph++)
    {
    printItem("iGraph",iGraph);
    h = histograms[iGraph];
    setProperties(h,*gc[iGraph]);
    h->GetXaxis()->SetTitle(xTitle);
    h->GetYaxis()->SetTitle(yTitle);
    if (yMin>=yMax) findMinMax(h,yMin,yMax);
    if (yMin>=yMax) yMax = yMin + 1.0E1;
    }
  h = histograms[0];
  h->GetXaxis()->SetTitle(xTitle);
  h->GetYaxis()->SetTitle(yTitle);
  h->SetMinimum(yMin);
  h->SetMaximum(yMax);
  if (xMin<xMax) h->GetXaxis()->SetRangeUser(xMin,xMax);
  String plotOption = gc[0]->getValueString("PlotOption");
  h->Draw(plotOption);
  for (unsigned int iGraph=1; iGraph<nGraphs; iGraph++)
    {
    plotOption = gc[iGraph]->getValueString("PlotOption");
    histograms[iGraph]->Draw(plotOption+" SAME");
    }
  if (lc.useLegend()) createLegend(histograms,lc);
  if (lc.useLabels()) lc.drawLabels();
  return canvas;
}

TCanvas *  Plotter::plot(const String & canvasName,
                         const CanvasConfiguration  & cc,
                         const vector<GraphConfiguration*> & gc,
                         LegendConfiguration  & lc,
                         vector<TGraph*> graphs,
                         const String & xTitle,  double xMin, double xMax,
                         const String & yTitle,  double yMin, double yMax)
{
  if (reportDebug(__FUNCTION__)) cout << "Creating canvas named:" << canvasName << endl;
  TCanvas * canvas = canvasCollection.createCanvas(canvasName,cc);
  TGraph * h;
  canvas->SetTicky(1);
  canvas->SetTickx(1);
  unsigned int nGraphs = graphs.size();
  //if (reportInfo(__FUNCTION__)) cout << "nGraphs:" << nGraphs << endl;

  for (unsigned int iGraph=0; iGraph<nGraphs; iGraph++)
    {
    //if (reportInfo(__FUNCTION__)) cout << "iGraph:" << iGraph << endl;
    h = graphs[iGraph];
    setProperties(h,*gc[iGraph]);
    h->GetXaxis()->SetTitle(xTitle);
    h->GetYaxis()->SetTitle(yTitle);
     }
  h = graphs[0];
  h->SetMinimum(yMin);
  h->SetMaximum(yMax);
  if (xMin<xMax) h->GetXaxis()->SetLimits(xMin,xMax);
  String plotOption = "ALP";
  h->Draw(plotOption);
  for (unsigned int iGraph=1; iGraph<nGraphs; iGraph++)
    {
    plotOption = "SAME LP";
    graphs[iGraph]->Draw(plotOption);
    }
  if (lc.useLegend()) createLegend(graphs,lc);
  if (lc.useLabels()) lc.drawLabels();
  return canvas;
}

void Plotter::printAllCanvas(const String & outputPath, bool printGif, bool printPdf, bool printSvg, bool printPng, bool printC)
{
  canvasCollection.printAllCanvas(outputPath, printGif, printPdf, printSvg, printPng, printC);
}

void Plotter::printAllCanvas(const String & outputPath)
{
  bool printGif = getValueBool("getVa");
  bool printPdf = getValueBool("DoPrintPdf");
  bool printSvg = getValueBool("DoPrintSvg");
  bool printPng = getValueBool("DoPrintPng");
  bool printC   = getValueBool("DoPrintC");
  canvasCollection.printAllCanvas(outputPath, printGif, printPdf, printSvg, printPng, printC);
}



void Plotter::findMinMax(TH1* histogram, double & minimum, double & maximum)
{
  minimum = histogram->GetBinContent(histogram->GetMinimumBin());
  maximum = histogram->GetBinContent(histogram->GetMaximumBin());
}


TLatex * Plotter::createLabel(const String & text, double x, double y, double angle, int color,  double fontSize, bool doDraw)
{
  if (reportDebug(__FUNCTION__)) cout << "Creating label with text:" << text << endl;
  TLatex * label;
  label = new TLatex(x,y,text);
  label->SetTextColor(color);
  label->SetTextAngle(angle);
  label->SetTextSize(fontSize);
  if (doDraw) label->Draw();
  return label;
}



TLegend * Plotter::createLegend(double x1, double y1, double x2, double y2, double fontSize)
{
  if (reportDebug(__FUNCTION__)) cout << "Create legend" << endl;
  TLegend *legend = new TLegend(x1,y1,x2,y2);
  legend->SetTextSize(fontSize);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  return legend;
}

TLegend * Plotter::createLegend(TH1*histogram, const String & legendText, double x1, double y1, double x2, double y2, double fontSize, bool doDraw)
{
  if (reportDebug(__FUNCTION__)) cout << "Create legend for one histogram" << endl;
  TLegend *legend = new TLegend(x1,y1,x2,y2);
  legend->SetTextSize(fontSize);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->AddEntry(histogram,legendText);
  if (doDraw) legend->Draw();
  return legend;
}

TLegend * Plotter::createLegend(vector<TH1*> histograms, VectorString  legendTexts, double x1, double y1, double x2, double y2, double fontSize, bool doDraw)
{
  if (reportDebug(__FUNCTION__)) cout << "Create legend for several histograms" << endl;
  TLegend *legend = new TLegend(x1,y1,x2,y2);
  legend->SetTextSize(fontSize);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  for (unsigned int iGraph=0; iGraph<histograms.size(); iGraph++)
    {
    legend->AddEntry(histograms[iGraph],legendTexts[iGraph]);
    }
  if (doDraw) legend->Draw();
  return legend;
}

TLegend * Plotter::createLegend(vector<TGraph*> graphs,VectorString  legendTexts,double x1, double y1, double x2, double y2, double fontSize, bool doDraw)
{
  if (reportDebug(__FUNCTION__)) cout << "Create legend for several graphs" << endl;
  TLegend *legend = new TLegend(x1,y1,x2,y2);
  legend->SetTextSize(fontSize);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  for (unsigned int iGraph=0; iGraph<graphs.size(); iGraph++)
    {
    legend->AddEntry(graphs[iGraph],legendTexts[iGraph]);
    }
  if (doDraw) legend->Draw();
  return legend;
}


TLegend * Plotter::createLegend(vector<DataGraph*> graphs,double x1, double y1, double x2, double y2, double fontSize, bool doDraw)
{
  if (reportDebug(__FUNCTION__)) cout << "Create legend for several histogram" << endl;
  TLegend *legend = new TLegend(x1,y1,x2,y2);
  legend->SetTextSize(fontSize);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  for (unsigned int iGraph=0; iGraph<graphs.size(); iGraph++)
    {
    legend->AddEntry(graphs[iGraph]->getDataGraph(),graphs[iGraph]->getLegendText());
    }
  if (doDraw) legend->Draw();
  return legend;
}

TLegend * Plotter::createLegend(const LegendConfiguration & legendConfig)
{
  int    nColumns    = legendConfig.getValueInt("nColumns");
  int    borderColor = legendConfig.getValueInt("borderColor");
  int    borderSize  = legendConfig.getValueInt("borderSize");
  int    fillColor   = legendConfig.getValueInt("fillColor");
  int    fillStyle   = legendConfig.getValueInt("fillStyle");
  int    fontIndex   = legendConfig.getValueInt("textIndex");
  int    textColor   = legendConfig.getValueInt("textColor");
  double textSize    = legendConfig.getValueDouble("textSize");
  int    textAlign   = legendConfig.getValueInt("textAlign");
  double xLeft       = legendConfig.getValueDouble("xLeft");
  double xRight      = legendConfig.getValueDouble("xRight");
  double yLow        = legendConfig.getValueDouble("yLow");
  double yHigh       = legendConfig.getValueDouble("yHigh");
  String header      = legendConfig.getValueString("header");
  bool   useNDC      = legendConfig.getValueBool("useNDC");

  cout << " Leg xLeft  :" << xLeft << endl;
  cout << " Leg xRight :" << xRight << endl;
  cout << " Leg yLow   :" << yLow << endl;
  cout << " Leg yHigh  :" << yHigh << endl;

  TLegend *legend;
  if (useNDC)
    {
    cout << " -- useNDC -- " << endl;
    legend = new TLegend(xLeft,yLow,xRight,yHigh,header,"NDC");
    }
  else
    {
    cout << " -- usePAD -- " << endl;
    legend = new TLegend(xLeft,yLow,xRight,yHigh,header,"PAD");
    }

  if (nColumns>1) legend->SetNColumns(nColumns);
  legend->SetLineColor(borderColor);
  legend->SetBorderSize(borderSize);
  legend->SetFillColor(fillColor);
  legend->SetFillStyle(fillStyle);
  legend->SetTextFont(fontIndex);
  legend->SetTextColor(textColor);
  legend->SetTextSize(textSize);
  legend->SetTextAlign(textAlign);
  if (header.Length()>0) legend->SetHeader(header);
  return legend;
}

TLegend * Plotter::createLegend(TH1*histogram, const LegendConfiguration & legendConfig)
{
  TLegend * legend = createLegend(legendConfig);
  if (legendConfig.getValueBool("useTitles"))
    legend->AddEntry(histogram,histogram->GetTitle());
  else
    legend->AddEntry(histogram,legendConfig.getLegendAt(0));
  if (legendConfig.getValueBool("drawLegend")) legend->Draw();
  return legend;
}


TLegend * Plotter::createLegend(vector<TH1*> histograms,const LegendConfiguration & legendConfig)
{
  TLegend * legend = createLegend(legendConfig);
  for (unsigned int iGraph=0; iGraph<histograms.size(); iGraph++)
    {
    if (legendConfig.getValueBool("useTitles"))
      {
      //cout << "Using histo title : " << histograms[iGraph]->GetTitle()  << endl;
      legend->AddEntry(histograms[iGraph],histograms[iGraph]->GetTitle());
      }
    else
      {
      //cout << "Using external legend  : " << legendConfig.getLegendAt(iGraph) << endl;
      legend->AddEntry(histograms[iGraph],legendConfig.getLegendAt(iGraph));
      }
    }
  if (legendConfig.getValueBool("drawLegend")) legend->Draw();
  return legend;
}

TLegend * Plotter::createLegend(TGraph*graph, const LegendConfiguration & legendConfig)
{
  TLegend * legend = createLegend(legendConfig);
  if (legendConfig.getValueBool("useTitles"))
    legend->AddEntry(graph,graph->GetTitle());
  else
    legend->AddEntry(graph,legendConfig.getLegendAt(0));
  if (legendConfig.getValueBool("drawLegend")) legend->Draw();
  return legend;
}

TLegend * Plotter::createLegend(vector<TGraph*> graphs,const LegendConfiguration & legendConfig)
{
  TLegend * legend = createLegend(legendConfig);
  for (unsigned int iGraph=0; iGraph<graphs.size(); iGraph++)
    {
    if (legendConfig.getValueBool("useTitles"))
      legend->AddEntry(graphs[iGraph],graphs[iGraph]->GetTitle());
    else
      legend->AddEntry(graphs[iGraph],legendConfig.getLegendAt(iGraph));
    }
  if (legendConfig.getValueBool("drawLegend")) legend->Draw();
  return legend;
}

TLegend * Plotter::createLegend(vector<DataGraph*> graphs,const LegendConfiguration & legendConfig)
{
  TLegend * legend = createLegend(legendConfig);
  for (unsigned int iGraph=0; iGraph<graphs.size(); iGraph++)
    {
    if (legendConfig.getValueBool("useTitles"))
      legend->AddEntry(graphs[iGraph]->getDataGraph(),graphs[iGraph]->getLegendText());
    else
      legend->AddEntry(graphs[iGraph]->getDataGraph(),legendConfig.getLegendAt(iGraph));
    }
  if (legendConfig.getValueBool("drawLegend")) legend->Draw();
  return legend;
}


////////////////////////////////////////////////////
// Create simple line
////////////////////////////////////////////////////
TLine * Plotter::createLine(float x1, float y1, float x2, float y2, int style, int color, int width, bool doDraw)
{
  if (reportDebug(__FUNCTION__))
    ;
  TLine *line = new TLine(x1,y1,x2,y2);
  line->SetLineStyle(style);
  line->SetLineColor(color);
  line->SetLineWidth(width);
  if (doDraw) line->Draw();
  return line;
}

////////////////////////////////////////////////////
// Create Arrow Line
////////////////////////////////////////////////////
TArrow * Plotter::createArrow(float x1, float y1, float x2, float y2, float arrowSize, Option_t* option, int style, int color, int width, bool doDraw)
{
  if (reportDebug(__FUNCTION__))
    ;
  TArrow *line = new TArrow(x1,y1,x2,y2,arrowSize,option);
  line->SetLineStyle(style);
  line->SetLineColor(color);
  line->SetLineWidth(width);
  if (doDraw) line->Draw();
  return line;
}


////////////////////////////////////////////////////////////////////////
// Setting Histogram Properties
////////////////////////////////////////////////////////////////////////
void Plotter::setProperties(TH1 * h, const GraphConfiguration & graphConfiguration)
{
  if (reportDebug(__FUNCTION__))
    {
    cout << "Setting properties of histo: " << h->GetName() << endl;
    }
  if (true)
    {
    h->SetLineColor(graphConfiguration.getValueInt("lineColor"));
    h->SetLineStyle(graphConfiguration.getValueInt("lineStyle"));
    h->SetLineWidth(graphConfiguration.getValueInt("lineWidth"));
    h->SetMarkerColor(graphConfiguration.getValueInt("markerColor"));
    h->SetMarkerStyle(graphConfiguration.getValueInt("markerStyle"));
    h->SetMarkerSize (graphConfiguration.getValueDouble("markerSize"));
    TAxis * xAxis = (TAxis *) h->GetXaxis();
    xAxis->SetNdivisions(graphConfiguration.getValueInt("nXDivisions"));
    xAxis->SetTitleSize(graphConfiguration.getValueDouble("xTitleSize"));
    xAxis->SetTitleOffset(graphConfiguration.getValueDouble("xTitleOffset"));
    xAxis->SetLabelSize(graphConfiguration.getValueDouble("xLabelSize"));
    xAxis->SetLabelOffset(graphConfiguration.getValueDouble("xLabelOffset"));
    TAxis * yAxis = (TAxis *) h->GetYaxis();
    yAxis->SetNdivisions(graphConfiguration.getValueInt("nYDivisions"));
    yAxis->SetTitleSize(graphConfiguration.getValueDouble("yTitleSize"));
    yAxis->SetTitleOffset(graphConfiguration.getValueDouble("yTitleOffset"));
    yAxis->SetLabelSize(graphConfiguration.getValueDouble("yLabelSize"));
    yAxis->SetLabelOffset(graphConfiguration.getValueDouble("yLabelOffset"));
    if (h->IsA() == TH2::Class()  || h->IsA() == TH2F::Class() || h->IsA() == TH2F::Class() )
      {
      if (reportDebug(__FUNCTION__)) cout << "Setting properties as 2D histo: " << h->GetTitle() << endl;
      TAxis * zAxis = (TAxis *) h->GetZaxis();
      zAxis->SetNdivisions(graphConfiguration.getValueInt("nZDivisions"));
      zAxis->SetTitleSize(graphConfiguration.getValueDouble("zTitleSize"));
      zAxis->SetTitleOffset(graphConfiguration.getValueDouble("zTitleOffset"));
      zAxis->SetLabelSize(graphConfiguration.getValueDouble("zLabelSize"));
      zAxis->SetLabelOffset(graphConfiguration.getValueDouble("zLabelOffset"));
      }
    }
  else
    {
    h->SetLineColor(graphConfiguration.getValueInt(getName(),"lineColor"));
    h->SetLineStyle(graphConfiguration.getValueInt(getName(),"lineStyle"));
    h->SetLineWidth(graphConfiguration.getValueInt(getName(),"lineWidth"));
    h->SetMarkerColor(graphConfiguration.getValueInt(getName(),"markerColor"));
    h->SetMarkerStyle(graphConfiguration.getValueInt(getName(),"markerStyle"));
    h->SetMarkerSize (graphConfiguration.getValueDouble(getName(),"markerSize"));
    TAxis * xAxis = (TAxis *) h->GetXaxis();
    xAxis->SetNdivisions(graphConfiguration.getValueInt(getName(),"nXDivisions"));
    xAxis->SetTitleSize(graphConfiguration.getValueDouble(getName(),"xTitleSize"));
    xAxis->SetTitleOffset(graphConfiguration.getValueDouble(getName(),"xTitleOffset"));
    xAxis->SetLabelSize(graphConfiguration.getValueDouble(getName(),"xLabelSize"));
    xAxis->SetLabelOffset(graphConfiguration.getValueDouble(getName(),"xLabelOffset"));
    TAxis * yAxis = (TAxis *) h->GetYaxis();
    yAxis->SetNdivisions(graphConfiguration.getValueInt(getName(),"nYDivisions"));
    yAxis->SetTitleSize(graphConfiguration.getValueDouble(getName(),"yTitleSize"));
    yAxis->SetTitleOffset(graphConfiguration.getValueDouble(getName(),"yTitleOffset"));
    yAxis->SetLabelSize(graphConfiguration.getValueDouble(getName(),"yLabelSize"));
    yAxis->SetLabelOffset(graphConfiguration.getValueDouble(getName(),"yLabelOffset"));
    if (h->IsA() == TH2::Class()  || h->IsA() == TH2F::Class() || h->IsA() == TH2D::Class() )
      {
      if (reportDebug(__FUNCTION__)) cout << "Setting properties as 2D histo: " << h->GetTitle() << endl;
      TAxis * zAxis = (TAxis *) h->GetZaxis();
      zAxis->SetNdivisions(graphConfiguration.getValueInt(getName(),"nZDivisions"));
      zAxis->SetTitleSize(graphConfiguration.getValueDouble(getName(),"zTitleSize"));
      zAxis->SetTitleOffset(graphConfiguration.getValueDouble(getName(),"zTitleOffset"));
      zAxis->SetLabelSize(graphConfiguration.getValueDouble(getName(),"zLabelSize"));
      zAxis->SetLabelOffset(graphConfiguration.getValueDouble(getName(),"zLabelOffset"));
      }
    }
}

void Plotter::setProperties(TH1 * h, const GraphConfiguration & graphConfiguration,
                            const String & xTitle, const String & yTitle, const String & zTitle)
{
  if (reportDebug(__FUNCTION__))
    {
    cout << "Setting properties of histo: " << h->GetTitle() << endl;
    }
  setProperties(h, graphConfiguration);
  TAxis * xAxis = (TAxis *) h->GetXaxis();
  xAxis->SetTitle(xTitle);
  TAxis * yAxis = (TAxis *) h->GetYaxis();
  yAxis->SetTitle(yTitle);
  if (h->IsA() == TH2::Class()  || h->IsA() == TH2F::Class() || h->IsA() == TH2F::Class() )
    {
    TAxis * zAxis = (TAxis *) h->GetZaxis();
    zAxis->SetTitle(zTitle);
    }
}

void Plotter::setProperties(TGraph * g, const GraphConfiguration & graphConfiguration)
{
  if (reportDebug(__FUNCTION__))
    {
    cout << "Setting properties of graph "<< g->GetTitle()  << endl;
    }
  if (true)
    {
    g->SetLineColor(graphConfiguration.getValueInt("lineColor"));
    g->SetLineStyle(graphConfiguration.getValueInt("lineStyle"));
    g->SetLineWidth(graphConfiguration.getValueInt("lineWidth"));
    g->SetMarkerColor(graphConfiguration.getValueInt("markerColor"));
    g->SetMarkerStyle(graphConfiguration.getValueInt("markerStyle"));
    g->SetMarkerSize (graphConfiguration.getValueDouble("markerSize"));
    TAxis * xAxis = (TAxis *) g->GetXaxis();
    xAxis->SetNdivisions(graphConfiguration.getValueInt("nXDivisions"));
    xAxis->SetTitleSize(graphConfiguration.getValueDouble("xTitleSize"));
    xAxis->SetTitleOffset(graphConfiguration.getValueDouble("xTitleOffset"));
    xAxis->SetLabelSize(graphConfiguration.getValueDouble("xLabelSize"));
    xAxis->SetLabelOffset(graphConfiguration.getValueDouble("xLabelOffset"));
    TAxis * yAxis = (TAxis *) g->GetYaxis();
    yAxis->SetNdivisions(graphConfiguration.getValueInt("nYDivisions"));
    yAxis->SetTitleSize(graphConfiguration.getValueDouble("yTitleSize"));
    yAxis->SetTitleOffset(graphConfiguration.getValueDouble("yTitleOffset"));
    yAxis->SetLabelSize(graphConfiguration.getValueDouble("yLabelSize"));
    yAxis->SetLabelOffset(graphConfiguration.getValueDouble("yLabelOffset"));
    }
  else
    {
    g->SetLineColor(graphConfiguration.getValueInt(getName(),"lineColor"));
    g->SetLineStyle(graphConfiguration.getValueInt(getName(),"lineStyle"));
    g->SetLineWidth(graphConfiguration.getValueInt(getName(),"lineWidth"));
    g->SetMarkerColor(graphConfiguration.getValueInt(getName(),"markerColor"));
    g->SetMarkerStyle(graphConfiguration.getValueInt(getName(),"markerStyle"));
    g->SetMarkerSize (graphConfiguration.getValueDouble(getName(),"markerSize"));
    TAxis * xAxis = (TAxis *) g->GetXaxis();
    xAxis->SetNdivisions(graphConfiguration.getValueInt(getName(),"nXDivisions"));
    xAxis->SetTitleSize(graphConfiguration.getValueDouble(getName(),"xTitleSize"));
    xAxis->SetTitleOffset(graphConfiguration.getValueDouble(getName(),"xTitleOffset"));
    xAxis->SetLabelSize(graphConfiguration.getValueDouble(getName(),"xLabelSize"));
    xAxis->SetLabelOffset(graphConfiguration.getValueDouble(getName(),"xLabelOffset"));
    TAxis * yAxis = (TAxis *) g->GetYaxis();
    yAxis->SetNdivisions(graphConfiguration.getValueInt(getName(),"nYDivisions"));
    yAxis->SetTitleSize(graphConfiguration.getValueDouble(getName(),"yTitleSize"));
    yAxis->SetTitleOffset(graphConfiguration.getValueDouble(getName(),"yTitleOffset"));
    yAxis->SetLabelSize(graphConfiguration.getValueDouble(getName(),"yLabelSize"));
    yAxis->SetLabelOffset(graphConfiguration.getValueDouble(getName(),"yLabelOffset"));
    }

}


void Plotter::setProperties(TGraph * g, const GraphConfiguration & graphConfiguration, const String & xTitle, const String & yTitle)
{
  if (reportInfo(__FUNCTION__))
    {
    cout << "Setting properties of graph " << g->GetTitle() << endl;
    }
  setProperties(g,graphConfiguration);
  if (reportDebug(__FUNCTION__)) cout << "Setting properties of histo: " << g->GetTitle() << endl;
  TAxis * xAxis = (TAxis *) g->GetXaxis();
  xAxis->SetTitle(xTitle);
  TAxis * yAxis = (TAxis *) g->GetYaxis();
  yAxis->SetTitle(yTitle);
}


// ======================================================================
// Set Default Style for Plots
// ======================================================================
void Plotter::setDefaultOptions(bool color)
{
  if (color)
    gStyle->SetPalette(1,0);
  else
    gStyle->SetPalette(7,0);
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  gStyle->SetOptDate(0);
  gStyle->SetOptTitle(0);
  gStyle->SetPadBorderMode(0);

}

double Plotter::findHistoMinimum(TH1 * h)
{
  return h->GetBinContent(h->GetMinimumBin());
}

double Plotter::findHistoMaximum(TH1 * h)
{
  return h->GetBinContent(h->GetMaximumBin());
}

double Plotter::findHistoMinimum2D(TH2 * h)
{
  int x, y, z;
  h->GetMinimumBin(x,y,z);
  return h->GetBinContent(x,y);
}

double Plotter::findHistoMaximum2D(TH2 * h)
{
  int x, y, z;
  h->GetMaximumBin(x,y,z);
  return h->GetBinContent(x,y);
}

double Plotter::findGraphMinimum(TGraph * h)
{
  double min = 1.0E100;
  int n = h->GetN();
  for (int k=0; k<n; k++)
    {
    double y = h->GetPointY(k);
    if (y<min) min = y;
    }
  return min;
}

double Plotter::findGraphMaximum(TGraph * h)
{
  double max = -1.0E100;
  int n = h->GetN();
  for (int k=0; k<n; k++)
    {
    double y = h->GetPointY(k);
    if (y>max) max = y;
    }
  return max;
}

double Plotter::findMinimum(vector<double> & values)
{
  double min = 1.0E100;
  for (Size_t k=0; k<values.size(); k++)
    {
    if (values[k]<min) min = values[k];
    cout << "k   " << k << " v: " << values[k] << " min: " << min << endl;
    }
  return min;
}

double Plotter::findMaximum(vector<double> & values)
{
  double max = -1.0E100;
  for (Size_t k=0; k<values.size(); k++)
    {
    if (values[k]>max) max = values[k];
    cout << "k   " << k << " v: " << values[k] << " max: " << max << endl;
    }
  return max;
}

CAP::String  Plotter::makeName(const String  & s1, const String  & s2)
{
  String  s = s1;
  s += "_";
  s += s2;
  return s;
}

CAP::String  Plotter::makeName(const String  & s1, const String  & s2, const String  & s3)
{
  String  s = s1;
  s += "_";
  s += s2;
  s += "_";
  s += s3;
  return s;
}

CAP::String  Plotter::makeName(const String  & s1, const String  & s2, const String  & s3, const String  & s4)
{
  String  s = s1;
  s += "_";
  s += s2;
  s += "_";
  s += s3;
  s += "_";
  s += s4;
  return s;
}

CAP::String  Plotter::makeName(const String  & s1,
                               const String  & s2,
                               const String  & s3,
                               const String  & s4,
                               const String  & s5)
{
  String  s = s1;
  s += "_";
  s += s2;
  s += "_";
  s += s3;
  s += "_";
  s += s4;
  s += "_";
  s += s5;
  return s;
}


TGraph * Plotter::makeGraph(vector<double> vx,
                            vector<double> vex,
                            vector<double> vy,
                            vector<double> vey)
{
  auto n = vx.size();
  if ( vex.size()!=n || vy.size()!=n || vey.size()!=n )
      throw TaskException("Arguments provided have incompatible sizes","makeGraph(vx,vex,vy,vey)");
  double * x  = new double[n];
  double * ex = new double[n];
  double * y  = new double[n];
  double * ey = new double[n];
  for (unsigned long k=0;k<n;k++)
    {
    x[k]  = vx[k];
    ex[k] = vex[k];
    y[k]  = vy[k];
    ey[k] = vey[k];
    }
  return new TGraphErrors(n,x,y,ex,ey);
}


vector<CAP::GraphConfiguration*> Plotter::createGraphConfigurationPalette(int n, int dim)
{
  vector<CAP::GraphConfiguration*>  gc = CAP::GraphConfiguration::createConfigurationPalette(n,dim);
  for (int k=0;k<n;k++)
    {

    gc[k]->addParametersWith(1, k);

//    gc[k]->addParameter("xTitleSize",   double(0.08));
//    gc[k]->addParameter("xTitleOffset", double(0.8));
//    gc[k]->addParameter("yTitleSize",   double(0.08));
//    gc[k]->addParameter("yTitleOffset", double(0.8));
//    gc[k]->addParameter("xLabelSize",   double(0.07));
//    gc[k]->addParameter("yLabelSize",   double(0.07));
//    gc[k]->addParameter("lineColor",    int(21+2*k));
//    gc[k]->addParameter("markerColor",  int(21+2*k));
//    gc[k]->addParameter("markerStyle",  int(kFullSquare));
//    gc[k]->addParameter("markerSize",   double(0.9));
    }
  return gc;
}


TGraph *  Plotter::sumGraphs(TGraph * g1, TGraph * g2)
{
  if (reportInfo(__FUNCTION__)) cout << "Summing two graphs" << endl;
  int  n1 = g1->GetN();
  int  n2 = g2->GetN();
  if (n1 != n2)
    throw TaskException("Args do not have same number of points","sumGraphs(TGraph * g1, TGraph * g2)");
  double * x  = new double[n1];
  double * ex = new double[n1];
  double * y  = new double[n1];
  double * ey = new double[n1];
  for (int index=0; index<n1; index++)
    {
    double x1  = g1->GetPointX(index);
    double ex1 = g1->GetErrorX(index);
    double y1  = g1->GetPointY(index);
    double ey1 = g1->GetErrorY(index);
    double x2  = g2->GetPointX(index);
    //double ex2 = g2->GetErrorX(index);
    double y2  = g2->GetPointY(index);
    double ey2 = g2->GetErrorY(index);
    if (x1!=x2)
      {
      //cout << "sumGraphs(TGraph * g1, TGraph * g2, TGraph * gSum) x1 ne x2" << endl;
      delete[] x;
      delete[] ex;
      delete[] y;
      delete[] ey;
      return nullptr;
      }
    x[index]  = x1;
    ex[index] = ex1;
    y[index]  = y1 + y2;
    ey[index] = sqrt(ey1*ey1 + ey2*ey2);
    }
  TGraph * g = new TGraphErrors(n1, x,y,ex,ey);
  //cout << "sumGraphs(...) Ends" << endl;
  return g;
}

TGraph* Plotter::calculateIntegral1D(TH1* h,
                                     double etaLow,
                                     double etaHigh,
                                     double etaStep,
                                     int size)
{
  if (!h)
    throw TaskException("Given h is a null ptr","calculateIntegral1D(TH1* h,...)");
  if (reportInfo(__FUNCTION__))
  {
    cout << endl;
    printItem("Histo Name", h->GetName());
    printItem("etaLow", etaLow);
    printItem("etaHigh",etaHigh);
    printItem("etaStep",etaStep);
    printItem("size", size);
  }
  double * x  = new double[size];
  double * ex = new double[size];
  double * y  = new double[size];
  double * ey = new double[size];

  const TAxis * xAxis  = h->GetXaxis();
  int xLow;
  int xHigh;
  int nPoints = 0;
  double sum  = 0;
  double esum = 0;
  for (double eta=etaLow; eta<etaHigh; eta+=etaStep)
  {
    xLow  = xAxis->FindBin(-eta);
    xHigh = xAxis->FindBin( eta);
    sum = h->IntegralAndError(xLow,xHigh,esum,"WIDTH");
    x[nPoints]  = eta;
    ex[nPoints] = 0.001;
    y[nPoints]  = sum; ///TMath::TwoPi();
    ey[nPoints] = esum; ///TMath::TwoPi();
    nPoints++;
  }
  TGraph * g = new TGraphErrors(nPoints, x,y,ex,ey);
  return g;
}


TGraph* Plotter::calculateIntegral(TH2* h2,
                                   double etaLow,
                                   double etaHigh,
                                   double etaStep,
                                   int size)
{
  if (!h2)
    throw TaskException("Given h2 is a null ptr","calculateIntegral1D(TH2* h,...)");
  if (reportInfo(__FUNCTION__))
  {
    cout << endl;
    printItem("Histo Name", h2->GetName());
    printItem("etaLow", etaLow);
    printItem("etaHigh",etaHigh);
    printItem("etaStep",etaStep);
    printItem("size", size);
  }
  double * x  = new double[size];
  double * ex = new double[size];
  double * y  = new double[size];
  double * ey = new double[size];

  const TAxis * xAxis  = h2->GetXaxis();
  const TAxis * yAxis  = h2->GetYaxis();
  int xLow;
  int xHigh;
  int yLow  = yAxis->GetXmin();
  int yHigh = yAxis->GetXmax();
  int nPoints = 0;
  double sum  = 0;
  double esum = 0;
  for (double eta=etaLow; eta<etaHigh; eta+=etaStep)
  {
    xLow  = xAxis->FindBin(-eta);
    xHigh = xAxis->FindBin( eta);
    // this needs to be fixed...
    //double factor = 1-eta/xHigh;
    sum = h2->IntegralAndError(xLow,xHigh,yLow,yHigh,esum,"WIDTH");
    x[nPoints]  = eta;
    ex[nPoints] = 0.001;
    y[nPoints]  = sum; ///TMath::TwoPi();
    ey[nPoints] = esum; ///TMath::TwoPi();
    nPoints++;
  }
  TGraph * g = new TGraphErrors(nPoints, x,y,ex,ey);
  return g;
}

// ============================================================================================================
// 4 parameters function
// ============================================================================================================
// 0  : a        : peak amplitude
// 1  : omegaEta : longitudinal peak width (eta)
// 2  : gammaEta : generalized gaussian exponent -- eta
// 3  : a0       : constant offset
// ============================================================================================================
double Plotter::GeneralizedGaussian(double *x, double *par)
{
  double eta = x[0];
  //double etaSq = eta*eta;
  double a        = par[0];
  double omegaEta = par[1];
  double gammaEta = par[2];
  double a0       = par[3];

  // generalized gaussian peak
  double norm   = gammaEta/2.0/omegaEta/TMath::Gamma(1.0/gammaEta);
  double arg1   = TMath::Abs(eta/omegaEta);
  double peak   = norm * TMath::Exp(-(TMath::Power(arg1,gammaEta) ));
  double result = a*peak;
  result += a0;
  return result;
}


void Plotter::calculateRmsWidth(TH2 * h,
                                double xLowEdge, double xHighEdge,
                                double yLowEdge, double yHighEdge,
                                double & mean, double & meanError,
                                double & rmsWidth,
                                double & rmsWidthError,
                                int direction)
{
  int nx = h->GetXaxis()->GetNbins();
  int xLowBin  = h->GetXaxis()->FindBin(xLowEdge);
  int xHighBin = h->GetXaxis()->FindBin(xHighEdge);
  if (xLowBin<1) xLowBin = 1;
  if (xHighBin>nx)  xHighBin = nx;

  int ny = h->GetNbinsY();
  int yLowBin  = h->GetYaxis()->FindBin(yLowEdge);
  int yHighBin = h->GetYaxis()->FindBin(yHighEdge);
  if (yLowBin<1) yLowBin = 1;
  if (yHighBin>ny)  yHighBin = ny;

  double sum    = 0.0;
  double xSum   = 0.0;
  double x2Sum  = 0.0;
  //  double eXSum  = 0.0;
  //  double eX2Sum = 0.0;
  double m1  = 0.0;
  double m2  = 0.0;
  mean       = 0.0;
  meanError  = 0.0;
  rmsWidth   = 0.0;
  rmsWidthError  = 0.0;
  double c, v, ev, arg;


  // two passes: pass 1 to get the mean, pass 2 to get the rms error,
  for (int iY=yLowBin; iY<=yHighBin; iY++)
    {
    for (int  iX=xLowBin; iX<xHighBin; iX++ )
      {
      switch (direction)
        {
          case 1: c = h->GetXaxis()->GetBinCenter(iX); break;
          case 2: c = h->GetYaxis()->GetBinCenter(iY); break;
        }
      v  = h->GetBinContent(iX,iY);
      sum   += v;
      xSum  += c*v;
      x2Sum += c*c*v;
      }
    }

  if (sum>0)
    {
    m1 = xSum/sum;
    m2 = x2Sum/sum - m1*m1;
    if (m2>0.0) rmsWidth = sqrt(m2);

    for (int iY=yLowBin; iY<=yHighBin; iY++)
      {
      for (int iX=xLowBin; iX<xHighBin; iX++ )
        {
        switch (direction)
          {
            case 1: c = h->GetXaxis()->GetBinCenter(iX); break;
            case 2: c = h->GetYaxis()->GetBinCenter(iY); break;
          }
        v  = h->GetBinContent(iX,iY);
        ev  = h->GetBinError(iX,iY);
        xSum  += c*c*ev*ev;
        x2Sum += c*c*v;
        arg = c*c - 2*m1*c;
        x2Sum += arg*arg * ev*ev;
        }
      }
    // need to compute and output error
    }
}
