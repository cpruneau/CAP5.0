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
#include "BalFctPlotter.hpp"
using CAP::BalFctPlotter;
using CAP::Configuration;

ClassImp(BalFctPlotter);

BalFctPlotter::BalFctPlotter()
:
Plotter(),
groupName("group"),
outputPath("./"),
canvasBaseName("baseName"),
bf_Types(),
bf_Sources(),
bf_InputFiles(),
bf_rebin2Ds(),
bf_rebinFactorsX(),
bf_rebinFactorsY(),
bf_DeltaYDeltaPhi_HistoNames(),
bf_DeltaY_HistoNames(),
bf_DeltaPhi_HistoNames(),
bf_Width_DeltaY_Names(),
bf_General_Titles(),
bf_Width_DeltaY_Titles(),
bf_Width_DeltaPhi_Names(),
bf_Width_DeltaPhi_Titles(),
deltaY_Title("#Delta y"),
deltaPhi_Title("#Delta #varphi"),
bf_DeltaYDeltaPhi_Minima(),
bf_DeltaYDeltaPhi_Maxima(),
bf_DeltaY_Minima(),
bf_DeltaY_Maxima(),
bf_DeltaPhi_Minima(),
bf_DeltaPhi_Maxima(),
bf_Integral_DeltaY_Minima(),
bf_Integral_DeltaY_Maxima(),
deltaY_Minimum(-20.0),
deltaY_Maximum( 20.0),
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
bf_DeltaYDeltaPhi_CanvasConfig(CAP::CanvasConfiguration::Landscape, CAP::CanvasConfiguration::Linear),
bf_DeltaY_CanvasConfig(CAP::CanvasConfiguration::Landscape, CAP::CanvasConfiguration::Linear),
bf_DeltaPhi_CanvasConfig(CAP::CanvasConfiguration::Landscape, CAP::CanvasConfiguration::Linear),
bf_Integral_DeltaY_CanvasConfig(CAP::CanvasConfiguration::Landscape, CAP::CanvasConfiguration::LogX),
//bf_Integral_DeltaY_CanvasConfig(CAP::CanvasConfiguration::LandscapeXtop, CAP::CanvasConfiguration::LogX),
bf_IntegralSum_DeltaY_CanvasConfig(CAP::CanvasConfiguration::LandscapeXtop, CAP::CanvasConfiguration::LogX),
bf_Width_DeltaY_CanvasConfig(CAP::CanvasConfiguration::Landscape, CAP::CanvasConfiguration::Linear),
bf_Width_DeltaPhi_CanvasConfig(CAP::CanvasConfiguration::Landscape, CAP::CanvasConfiguration::Linear),
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
rapidityLowEdgeIntegral(0.2),
rapidityHighEdgeIntegral(20.0)
{}


void BalFctPlotter::loadHistograms()
{
  Size_t nFiles = bf_InputFiles.size();
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("bf_InputFiles.size()",nFiles);
    }

  for (Size_t iFile=0; iFile<nFiles; iFile++)
    {
    Size_t nPairs = pairNames.size();
    printItem("nPairs",nPairs);
    for (Size_t iPair=0; iPair<nPairs; iPair++)
      {
      printItem("iPair",iPair);
      printItem("pairName", pairNames[iPair]);
      printItem("pairTitle",pairTitles[iPair]);
      Size_t index = iFile*pairNames.size() + iPair;
      printItem("bf_DeltaYDeltaPhi_HistoName",bf_DeltaYDeltaPhi_HistoNames[index]);
      printItem("bf_DeltaY_HistoNames",bf_DeltaY_HistoNames[index]);
      printItem("bf_DeltaPhi_HistoNames",bf_DeltaPhi_HistoNames[index]);

      // load 2D
      TH2 * h2  = (TH2*) bf_InputFiles[iFile]->Get(bf_DeltaYDeltaPhi_HistoNames[index]);
      if (!h2)
        {
        String s = "Failed to load 2d histo named:"; s += bf_DeltaYDeltaPhi_HistoNames[index]; s+= " at iPair: "; s+= iPair;
        throw CAP::Exception(s, "loadHistograms()");
        }
      if (bf_rebin2Ds[iFile])
        {
        int xR = bf_rebinFactorsX[iFile];
        int yR = bf_rebinFactorsY[iFile];
        h2->Rebin2D(xR,yR);
        h2->Scale(1.0/float(xR)/float(yR));
        // needs to be fixed -- should not be done here....
        //double dx = h2->GetXaxis()->GetBinWidth(1);
        double dy = h2->GetYaxis()->GetBinWidth(1);
        h2->Scale(1.0/dy);
        }

      // load 1D vs Delta y
      TH1 * h1x = (TH1*) bf_InputFiles[iFile]->Get(bf_DeltaY_HistoNames[index]);
      if (!h1x)
        {
        String s = "Failed to load 1d histo named:"; s += bf_DeltaY_HistoNames[index]; s+= " at iPair: "; s+= iPair;
        throw CAP::Exception(s, "loadHistograms()");
        }
      // load 1D vs Delta phi
      TH1 * h1y = (TH1*) bf_InputFiles[iFile]->Get(bf_DeltaPhi_HistoNames[index]);
      if (!h1y)
        {
        String s = "Failed to load 1d histo named:"; s += bf_DeltaPhi_HistoNames[index]; s+= " at iPair: "; s+= iPair;
        throw CAP::Exception(s, "loadHistograms()");
        }
      bf_DeltaYDeltaPhi_Histos.push_back(h2);
      bf_DeltaY_Histos.push_back(h1x);
      bf_DeltaPhi_Histos.push_back(h1y);
      }
    }
//  Size_t nn = bf_DeltaYDeltaPhi_Histos.size();
//  cout << "bf_DeltaYDeltaPhi_Histos:Size() " <<  nn << endl;
//  for (Size_t k=0;k<nn; k++)
//    {
//    cout << " k:" << k << " : " << bf_DeltaYDeltaPhi_Histos[k]->GetName() << endl;
//    }
//  exit(1);
}



void BalFctPlotter::calculateRmsWidths(double xLowEdge, double xHighEdge,
                                       double yLowEdge, double yHighEdge,
                                       int direction)
{
  if (reportInfo(__FUNCTION__))
    cout << " Computing RMS widths for direction=" << direction << endl;
  double mean;
  double meanError;
  double rmsWidth;
  double rmsWidthError;
  for (Size_t iHist=0;iHist<bf_DeltaYDeltaPhi_Histos.size(); iHist++)
    {
    TH2 * h = bf_DeltaYDeltaPhi_Histos[iHist];
    calculateRmsWidth(h,xLowEdge,xHighEdge,yLowEdge,yHighEdge,mean,meanError,rmsWidth,rmsWidthError,direction);
    switch (direction)
      {
        case 1:
        bf_means_DeltaY.push_back(mean);
        bf_meanErrors_DeltaY.push_back(meanError);
        bf_rmsWidths_DeltaY.push_back(rmsWidth);
        bf_rmsWidthErrors_DeltaY.push_back(rmsWidthError);
        break;
        case 2:
        bf_means_DeltaPhi.push_back(mean);
        bf_meanErrors_DeltaPhi.push_back(meanError);
        bf_rmsWidths_DeltaPhi.push_back(rmsWidth);
        bf_rmsWidthErrors_DeltaPhi.push_back(rmsWidthError);
        break;
      }
    }
}

void BalFctPlotter::calculateRmsWidths()
{
  if (doPlotsBfWidthDeltaY)
    calculateRmsWidths(rapidityLowEdge,rapidityHighEdge,phiLowEdge,phiHighEdge,1);
  if (doPlotsBfWidthDeltaPhi)
    calculateRmsWidths(rapidityLowEdge,rapidityHighEdge,phiLowEdge,phiHighEdge,2);
}

void BalFctPlotter::calculateBfSums()
{
  if (reportInfo(__FUNCTION__))
    cout << " Computing BF Sums" << endl;
  Size_t nSpecies = speciesNames.size();
  Size_t index;
  bf_SumDeltaY_Histos.clear();

  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    cout << endl;
    index = iTrigger*nSpecies;
    printItem("iTrigger",iTrigger);
    printItem("index",index);
    TH1 * sum = (TH1*) bf_DeltaY_Histos[index]->Clone();

    for (Size_t iAssoc=1; iAssoc<nSpecies; iAssoc++)
      {
      index = iTrigger*nSpecies + iAssoc;
      TH1 * h = (TH1*)  bf_DeltaY_Histos[index];
      sum->Add(h);
      }
    bf_SumDeltaY_Histos.push_back(sum);

//    for (Size_t iAssoc=0; iAssoc<nSpecies; iAssoc++)
//      {
//      index = iTrigger*nSpecies + iAssoc;
//      TH1 * h = (TH1*)  bf_DeltaY_Histos[index]->Clone();
//      h->Divide(sum);
//      bf_RatioDeltaY_Histos.push_back(h);
//      }
    }
}


void BalFctPlotter::calculateIntegrals()
{
  if (reportInfo(__FUNCTION__))
    cout << " Computing Integrals" << endl;
  Size_t nSpecies = speciesNames.size();
  Size_t nFiles   = bf_InputFiles.size();
  Size_t index;

  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    cout << endl;
    printItem("iTrigger",iTrigger);
    for (Size_t iAssoc=0; iAssoc<nSpecies; iAssoc++)
      {
      for (Size_t iFile=0; iFile<nFiles; iFile++)
        {
        index = iFile*nSpecies*nSpecies + iTrigger*nSpecies + iAssoc;
        TH1 * h = bf_DeltaY_Histos[index];
        TGraph * g = calculateIntegral1D(h,rapidityLowEdgeIntegral, rapidityHighEdgeIntegral,0.2);
        bf_Integral_DeltaY_Graphs.push_back(g);
        }
      }
    }
  if (reportInfo(__FUNCTION__))
    cout << " Computing Integral Sums" << endl;
  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    index = iTrigger*nSpecies;
    bf_IntegralSum_DeltaY_Graphs.push_back( (TGraph*) bf_Integral_DeltaY_Graphs[index]->Clone());
    for (Size_t iAssoc=1; iAssoc<nSpecies; iAssoc++)
      {
      index = iTrigger*nSpecies + iAssoc;
      TGraph * g1 = bf_IntegralSum_DeltaY_Graphs[index-1];
      TGraph * g2 = bf_Integral_DeltaY_Graphs[index];
      bf_IntegralSum_DeltaY_Graphs.push_back(sumGraphs(g1,g2));
      }
    }
}


void BalFctPlotter::calculateIntegralsVsFile()
{
  if (reportInfo(__FUNCTION__))
    cout << " Computing Integrals" << endl;
  Size_t nSpecies = speciesNames.size();
  Size_t nFiles   = bf_InputFiles.size();
  Size_t index;

  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    cout << endl;
    printItem("iTrigger",iTrigger);
    for (Size_t iAssoc=0; iAssoc<nSpecies; iAssoc++)
      {
      for (Size_t iFile=0; iFile<nFiles; iFile++)
        {
        index = iFile*nSpecies*nSpecies + iTrigger*nSpecies + iAssoc;
        TH1 * h = bf_DeltaY_Histos[index];
        TGraph * g = calculateIntegral1D(h,rapidityLowEdgeIntegral, rapidityHighEdgeIntegral,0.2);
        bf_Integral_DeltaY_Graphs.push_back(g);
        }
      }
    }
  if (reportInfo(__FUNCTION__))
    cout << " Computing Integral Sums" << endl;
  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    index = iTrigger*nSpecies;
    bf_IntegralSum_DeltaY_Graphs.push_back( (TGraph*) bf_Integral_DeltaY_Graphs[index]->Clone());
    for (Size_t iAssoc=1; iAssoc<nSpecies; iAssoc++)
      {
      for (Size_t iFile=0; iFile<nFiles; iFile++)
        {
        index = iFile*nSpecies*nSpecies + iTrigger*nSpecies + iAssoc;
        TGraph * g1 = bf_IntegralSum_DeltaY_Graphs[index-1];
        TGraph * g2 = bf_Integral_DeltaY_Graphs[index];
        bf_IntegralSum_DeltaY_Graphs.push_back(sumGraphs(g1,g2));
        }
      }
    }
}

void BalFctPlotter::addSystem(const String & inputPathName,
                              const String & inputFileName,
                              const String & inputFileTitle,
                              const String & histoBaseName,
                              const String & histoBaseTitle,
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
                              bool rebin2D,
                              int  rebinFactorX,
                              int  rebinFactorY)
{
  bf_InputPathNames.push_back(inputPathName);
  bf_InputFileNames.push_back(inputFileName);
  bf_InputFileTitles.push_back(inputFileTitle);
  bf_HistoNameBases.push_back(histoBaseName);
  bf_HistoTitleBases.push_back(histoBaseTitle);
  bf_CanvasNameBases.push_back(canvasBaseName);
  bf_rebin2Ds.push_back(rebin2D);
  bf_rebinFactorsX.push_back(rebinFactorX);
  bf_rebinFactorsY.push_back(rebinFactorY);
  bf_Types.push_back(bf_Type);
  bf_Sources.push_back(bf_Source);
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




void tweak(double & min, double & max)
{
  double range = max - min;
  cout << " min:" << min << "   max:" << max << "  range:  " << range << endl;
  if (max>0)
    {
    max *= 1.1;
    }
  else
    {
    max += 0.1*range;
    }
  if (min>=0)
    {
    min  = -0.05* range;
    }
  else
    {
    min *= 2.0;
    }

  if (max<0.0001)      max = 0.000099;
  else if (max<0.0002) max = 0.000199;
  else if (max<0.0003) max = 0.000299;
  else if (max<0.0004) max = 0.000399;
  else if (max<0.0005) max = 0.000499;
  else if (max<0.0006) max = 0.000599;
  else if (max<0.0007) max = 0.000699;
  else if (max<0.0008) max = 0.000799;
  else if (max<0.0009) max = 0.000899;
  else if (max<0.001)  max = 0.00099;
  else if (max<0.002) max = 0.00199;
  else if (max<0.003) max = 0.00299;
  else if (max<0.004) max = 0.00399;
  else if (max<0.005) max = 0.00499;
  else if (max<0.006) max = 0.00599;
  else if (max<0.007) max = 0.00699;
  else if (max<0.008) max = 0.00799;
  else if (max<0.009) max = 0.00899;
  else if (max<0.01) max = 0.0099;
  else if (max<0.02) max = 0.0199;
  else if (max<0.03) max = 0.0299;
  else if (max<0.04) max = 0.0399;
  else if (max<0.05) max = 0.0499;
  else if (max<0.06) max = 0.0599;
  else if (max<0.07) max = 0.0699;
  else if (max<0.08) max = 0.0799;
  else if (max<0.09) max = 0.0899;
  else if (max<0.1)  max = 0.099;
  else if (max<0.15) max = 0.1499;
  else if (max<0.2)  max = 0.199;
  else if (max<0.25) max = 0.2499;
  else if (max<0.3)  max = 0.299;
  else if (max<0.35) max = 0.349;
  else if (max<0.4) max = 0.399;
  else if (max<0.5) max = 0.499;
  else if (max<0.6) max = 0.599;
  else if (max<0.7) max = 0.699;
  else if (max<0.8) max = 0.799;
  else if (max<0.9) max = 0.899;
  else if (max<1.0) max = 0.999;
  else if (max<1.1) max = 1.099;
  else if (max<1.2) max = 1.199;
  else if (max<1.3) max = 1.299;

  if (min<0)
    {
    if (min>-0.0001) min = -0.0001;
    else if (min>-0.0002) min = -0.0002;
    else if (min>-0.0003) min = -0.0003;
    else if (min>-0.0004) min = -0.0004;
    else if (min>-0.0005) min = -0.0005;
    else if (min>-0.0006) min = -0.0006;
    else if (min>-0.0007) min = -0.0007;
    else if (min>-0.0008) min = -0.0008;
    else if (min>-0.0009) min = -0.0009;
    else if (min>-0.001) min = -0.001;
    else if (min>-0.002) min = -0.002;
    else if (min>-0.003) min = -0.003;
    else if (min>-0.004) min = -0.004;
    else if (min>-0.005) min = -0.005;
    else if (min>-0.006) min = -0.006;
    else if (min>-0.007) min = -0.007;
    else if (min>-0.008) min = -0.008;
    else if (min>-0.009) min = -0.009;
    else if (min>-0.01)  min = -0.01;
    else if (min>-0.011) min = -0.011;
    else if (min>-0.012) min = -0.012;
    else if (min>-0.013) min = -0.013;
    else if (min>-0.014) min = -0.014;
    else if (min>-0.015) min = -0.015;
    else if (min>-0.016) min = -0.016;
    else if (min>-0.017) min = -0.017;
    else if (min>-0.018) min = -0.018;
    else if (min>-0.019) min = -0.019;
    else if (min>-0.020) min = -0.020;
    else if (min>-0.030) min = -0.030;
    else if (min>-0.040) min = -0.040;
    else if (min>-0.050) min = -0.050;
    //  else if (min>-0.100) min = -0.100;
    //  else if (min>-0.200) min = -0.200;
    }

}

void BalFctPlotter::plotBF2D()
{
  Size_t nSpecies = speciesNames.size();
  Size_t nFiles   = bf_InputFiles.size();
  String bf_Title = "B^{s}";
  double bf_min = 0.0;
  double bf_max = 1.0;
  cout << endl;

   for (Size_t iFile=0; iFile<nFiles; iFile++)
    {
    printItem("iFile",iFile);
    for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
      {
      cout << endl;
      printItem("iTrigger",iTrigger);
      for (Size_t iAssoc=0; iAssoc<nSpecies; iAssoc++)
        {
        printItem("iAssoc",iAssoc);

        Size_t index = iFile*nSpecies*nSpecies + iTrigger*nSpecies + iAssoc;
        printItem("histo index",index);
        TH2 * h = bf_DeltaYDeltaPhi_Histos[index];
        bf_min = findHistoMinimum2D(h);
        bf_max = findHistoMaximum2D(h);
        tweak(bf_min,bf_max);

        String canvasName =  outputFileNameBase;
        canvasName += "_";
        canvasName += bf_CanvasNameBases[iFile];
        canvasName += correlatorSourceNames[bf_Types[iFile]];
        canvasName += "_";
        canvasName += pairNames[iTrigger*nSpecies+iAssoc];
        canvasName += "_";
        canvasName += deltaY_Name;
        canvasName += deltaPhi_Name;

        bf_DeltaYDeltaPhi_LegendConfig.clearLabels();
        bf_DeltaYDeltaPhi_LegendConfig.clearLegend();
        bf_DeltaYDeltaPhi_LegendConfig.addLabel(bf_InputFileTitles[iFile],-0.80,0.87,0.0,1,0.06);
        bf_DeltaYDeltaPhi_LegendConfig.addLabel(pairTitles[iTrigger*nSpecies+iAssoc],-0.80,0.72,0.0,1,0.06);
        bf_DeltaYDeltaPhi_LegendConfig.addParameter("xLeft", 0.0);
        bf_DeltaYDeltaPhi_LegendConfig.addParameter("xRight",0.0);
        bf_DeltaYDeltaPhi_LegendConfig.addParameter("yLow",  0.0);
        bf_DeltaYDeltaPhi_LegendConfig.addParameter("yHigh", 0.0);
        bf_DeltaYDeltaPhi_LegendConfig.addParameter("useLegend",false);
        bf_DeltaYDeltaPhi_LegendConfig.addParameter("useTitles",false);
        bf_DeltaYDeltaPhi_LegendConfig.addParameter("useLabels",true);
        bf_DeltaYDeltaPhi_LegendConfig.addParameter("useNDC",false); // use NDC or PAD coordinates

        plot(canvasName,
             bf_DeltaYDeltaPhi_CanvasConfig,
             bf_DeltaYDeltaPhi_GraphConfig,
             bf_DeltaYDeltaPhi_LegendConfig,
             h,
             deltaY_Title,   deltaY_Minimum,    deltaY_Maximum,
             deltaPhi_Title, deltaPhi_Minimum,  deltaPhi_Maximum,
             bf_Title,
             bf_min,
             bf_max);
        }
      }
    }
}

void BalFctPlotter::plotBfVsPairvsDeltaYVsFile()
{
  Size_t nSpecies = speciesNames.size();
  Size_t nFiles   = bf_InputFiles.size();
  vector<TH1*>   histos;
  vector<double> minima;
  vector<double> maxima;
  String bf_Title = "B^{s}";
  
  switch (rangeOption)
    {
      case 0:
      deltaY_Minimum = -20.0;
      deltaY_Maximum = +20.0;
      break;
      case 1:
      deltaY_Minimum = -10.0;
      deltaY_Maximum = +10.0;
      break;
      case 2:
      deltaY_Minimum = -4.0;
      deltaY_Maximum = +4.0;
    }


  double bf_min = 0.0;
  double bf_max = 1.0;
  double xMin   = -100.0;
  double xMax   =  100.0;
  double xRange =  xMax-xMin;
  double x      =  0.0;
  double yMin   = bf_min;
  double yMax   = bf_max;
  double yRange = yMax-yMin;
  double y      = 0.0;



  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    cout << endl;
    printItem("iTrigger",iTrigger);
    for (Size_t iAssoc=0; iAssoc<nSpecies; iAssoc++)
      {
      printItem("iAssoc",iAssoc);
      histos.clear();
      minima.clear();
      maxima.clear();
      bf_DeltaY_LegendConfig.clearLabels();
      bf_DeltaY_LegendConfig.clearLegend();
      for (Size_t iFile=0; iFile<nFiles; iFile++)
        {
        printItem("iFile",iFile);
        Size_t index = iFile*nSpecies*nSpecies + iTrigger*nSpecies + iAssoc;
        printItem("histo index",index);
        TH1 * h = bf_DeltaY_Histos[index];
        histos.push_back(h);
        minima.push_back(findHistoMinimum(h));
        maxima.push_back(findHistoMaximum(h));
        xMin = h->GetXaxis()->GetXmin();
        xMax = h->GetXaxis()->GetXmax();
        xRange =  xMax-xMin;
        bf_DeltaY_LegendConfig.addLegend(bf_InputFileTitles[iFile]);
        }
//      printItem("histos.size()",histos.size());
//      printItem("minima.size()",minima.size());
//      printItem("maxima.size()",maxima.size());

      xMin = deltaY_Minimum;
      xMax = deltaY_Maximum;
      xRange =  xMax-xMin;
      x = xMin + 0.05*xRange;

      bf_Title = bf_TypeTitles[bf_Types[0]];
      bf_min   = findMinimum(minima);
      bf_max   = findMaximum(maxima);
      tweak(bf_min,bf_max);

      yMin   = bf_min;
      yMax   = bf_max;
      yRange = yMax-yMin;
      y = yMax - 0.11*yRange;
      bf_DeltaY_LegendConfig.addLabel(bf_General_Titles[0],x,y,0.0,1,0.06);
      y = yMax - 0.18*yRange;
      bf_DeltaY_LegendConfig.addLabel(pairTitles[iTrigger*nSpecies+iAssoc],x,y,0.0,1,0.06);
      bf_DeltaY_LegendConfig.addParameter("xLeft", x);
      bf_DeltaY_LegendConfig.addParameter("xRight",x+0.2*xRange);
      bf_DeltaY_LegendConfig.addParameter("yLow",  yMax - 0.7*yRange);
      bf_DeltaY_LegendConfig.addParameter("yHigh", yMax - 0.3*yRange);
      bf_DeltaY_LegendConfig.addParameter("useLegend",true);
      bf_DeltaY_LegendConfig.addParameter("useTitles",false);
      bf_DeltaY_LegendConfig.addParameter("useLabels",true);
      bf_DeltaY_LegendConfig.addParameter("textSize", 0.065);
      if (histos.size()<5)
        bf_DeltaY_LegendConfig.addParameter("nColumns",     1);
      else
        bf_DeltaY_LegendConfig.addParameter("nColumns",     2);


      Size_t index = 0*nSpecies + iTrigger;
      String canvasName =  outputFileNameBase;
      canvasName += "_";
      canvasName += bf_CanvasNameBases[0];
      canvasName += bf_TypeNames[bf_Types[0]];
      canvasName += "_";
      canvasName += pairNames[iTrigger*nSpecies+iAssoc];
      canvasName += "_";
      canvasName += deltaY_Name;
      printItem("canvasName",canvasName);

      plot(canvasName,
           bf_DeltaY_CanvasConfig,
           bf_DeltaY_GraphConfigs,
           bf_DeltaY_LegendConfig,
           histos,
           deltaY_Title,deltaY_Minimum,deltaY_Maximum,
           bf_Title, bf_min, bf_max);
      }
    }
}


// run this version for one file or system
void BalFctPlotter::plotBfVsPairvsDeltaY()
{
  Size_t nSpecies = speciesNames.size();
  Size_t nFiles   = bf_InputFiles.size();
  vector<TH1*>   histos;
  //vector<TH1*>   histoRatios;
  vector<double> minima;
  vector<double> maxima;
  String bf_Title;
  double bf_min = 0.0;
  double bf_max = 1.0;
  double xMin   = -100.0;
  double xMax   =  100.0;
  double xRange =  xMax-xMin;
  double x      =  0.0;
  double yMin   = bf_min;
  double yMax   = bf_max;
  double yRange = yMax-yMin;
  double y      = 0.0;

  switch (rangeOption)
    {
      case 0:
      deltaY_Minimum = -20.0;
      deltaY_Maximum =  20.0;
      break;
      case 1:
      deltaY_Minimum = -10.0;
      deltaY_Maximum =  10.0;
      break;
      case 2:
      deltaY_Minimum = -4.0;
      deltaY_Maximum =  4.0;
    }

  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    cout << endl;
    printItem("iTrigger",iTrigger);
    histos.clear();
//    histoRatios.clear();
    minima.clear();
    maxima.clear();
    bf_DeltaY_LegendConfig.clearLabels();
    bf_DeltaY_LegendConfig.clearLegend();

    TH1 * h = bf_SumDeltaY_Histos[iTrigger];
    histos.push_back(h);
    minima.push_back(findHistoMinimum(h));
    maxima.push_back(findHistoMaximum(h));
    bf_DeltaY_LegendConfig.addLegend("#sum");

    for (Size_t iAssoc=0; iAssoc<nSpecies; iAssoc++)
      {
      printItem("iAssoc",iAssoc);
      for (Size_t iFile=0; iFile<nFiles; iFile++)
        {
        printItem("iFile",iFile);
        Size_t index = iFile*nSpecies*nSpecies + iTrigger*nSpecies + iAssoc;
        printItem("histo index",index);
        TH1 * h = bf_DeltaY_Histos[index];
        histos.push_back(h);
        minima.push_back(findHistoMinimum(h));
        maxima.push_back(findHistoMaximum(h));

//        h = bf_RatioDeltaY_Histos[index];
//        histoRatios.push_back(h);

        bf_DeltaY_LegendConfig.addLegend(pairTitles[iTrigger*nSpecies+iAssoc]);

        }
      }



    xMin = deltaY_Minimum;  // ZZZZZZZ
    xMax = deltaY_Maximum;
    xRange =  xMax-xMin;
    x = xMin + 0.05*xRange;

    bf_Title = bf_TypeTitles[bf_Types[0]];
    bf_min   = findMinimum(minima);
    bf_max   = findMaximum(maxima);
    tweak(bf_min,bf_max);

    yMin   = bf_min;
    yMax   = bf_max;
    yRange = yMax-yMin;
    y = yMax - 0.1*yRange;

    bf_DeltaY_LegendConfig.addLabel(bf_General_Titles[0],x,y,0.0,1,0.06);

    //bf_DeltaY_LegendConfig.addLabel(,x,y,0.0,1,0.05);
    bf_DeltaY_LegendConfig.addParameter("xLeft", x);
    bf_DeltaY_LegendConfig.addParameter("xRight",x+0.3*xRange);
    bf_DeltaY_LegendConfig.addParameter("yLow",  yMax - 0.7*yRange);
    bf_DeltaY_LegendConfig.addParameter("yHigh", yMax - 0.2*yRange);
    bf_DeltaY_LegendConfig.addParameter("useLegend",true);
    bf_DeltaY_LegendConfig.addParameter("useTitles",false);
    bf_DeltaY_LegendConfig.addParameter("useLabels",true);
    bf_DeltaY_LegendConfig.addParameter("useNDC",false);
    bf_DeltaY_LegendConfig.addParameter("textColor",    1);
    bf_DeltaY_LegendConfig.addParameter("textSize",     0.06);
    if (histos.size()<5)
      bf_DeltaY_LegendConfig.addParameter("nColumns",     1);
    else
      bf_DeltaY_LegendConfig.addParameter("nColumns",     2);

    String canvasName =  outputFileNameBase;
    canvasName += "_";
    canvasName += bf_CanvasNameBases[0];
    canvasName += bf_TypeNames[bf_Types[0]];
    canvasName += "_";
    canvasName += speciesNames[iTrigger];
    canvasName += "_";
    canvasName += deltaY_Name;
    plot(canvasName,
         bf_DeltaY_CanvasConfig,
         bf_DeltaY_GraphConfigs,
         bf_DeltaY_LegendConfig,
         histos,
         deltaY_Title,deltaY_Minimum,deltaY_Maximum,
         bf_Title, bf_min, bf_max);

//    canvasName =  outputFileNameBase;
//    canvasName += "_";
//    canvasName += bf_CanvasNameBases[0];
//    canvasName += bf_TypeNames[bf_Types[0]];
//    canvasName += "_";
//    canvasName += speciesNames[iTrigger];
//    canvasName += "_";
//    canvasName += deltaY_Name;
//    canvasName += "_Ratios";
//
//    plot(canvasName,
//         bf_DeltaY_CanvasConfig,
//         bf_DeltaY_GraphConfigs,
//         bf_DeltaY_LegendConfig,
//         histoRatios,
//         deltaY_Title,deltaY_Minimum,deltaY_Maximum,
//         "B^{s}/\sum B^{s}", -0.05, 1.0499);

    }
}

void BalFctPlotter::plotBfVsPairvsDeltaPhi()
{

}


void BalFctPlotter::plotBfIntegralVsPairvsDeltaY()
{
  Size_t nSpecies = speciesNames.size();
  Size_t nFiles   = bf_InputFiles.size();
  vector<TGraph*> graphs;
  String bf_Title;
  double bf_min = -0.1;
  double bf_max = 1.2;
  double xMin   =  0.01;
  double xMax   =  20.0;
  double xRange =  xMax-xMin;
  double x      =  0.0;
  double yMin   = bf_min;
  double yMax   = bf_max;
  double yRange = yMax-yMin;
  double y      = 0.0;

  if (bf_Integral_DeltaY_Graphs.size()<1)
    {
    throw TaskException("bf_Integral_DeltaY_Graphs.size()<1","plotBfIntegralVsPairvsDeltaY()");
    }

  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    cout << endl;
    printItem("iTrigger",iTrigger);
    graphs.clear();
    bf_Integral_DeltaY_LegendConfig.clearLabels();
    bf_Integral_DeltaY_LegendConfig.clearLegend();

    Size_t index = iTrigger*nSpecies + nSpecies - 1;
    TGraph * g = bf_IntegralSum_DeltaY_Graphs[index];
    graphs.push_back(g);
    bf_Integral_DeltaY_LegendConfig.addLegend("#sum");

    for (Size_t iAssoc=0; iAssoc<nSpecies; iAssoc++)
      {
      printItem("iAssoc",iAssoc);
      Size_t index = iTrigger*nSpecies + iAssoc;
      printItem("histo index",index);
      g = bf_Integral_DeltaY_Graphs[index];
      graphs.push_back(g);
      xMin = g->GetXaxis()->GetXmin();
      xMax = g->GetXaxis()->GetXmax();
      xRange =  xMax-xMin;
      bf_Integral_DeltaY_LegendConfig.addLegend(pairTitles[iTrigger*nSpecies+iAssoc]);
      }

    printItem("graphs.size()",graphs.size());
    bf_Title = bf_IntegralTypeTitles[bf_Types[0]];

    if (false)
      {
      x = 0.2;
      yMin   = bf_min;
      yMax   = bf_max;
      yRange = yMax-yMin;
      y = yMax - 0.1*yRange;
      bf_Integral_DeltaY_LegendConfig.addLabel(bf_General_Titles[0],x,y,0.0,1,0.06);
      bf_Integral_DeltaY_LegendConfig.addParameter("xLeft", x);
      bf_Integral_DeltaY_LegendConfig.addParameter("xRight",x+0.15*xRange);
      bf_Integral_DeltaY_LegendConfig.addParameter("yLow",  yMax - 0.5*yRange);
      bf_Integral_DeltaY_LegendConfig.addParameter("yHigh", yMax - 0.2*yRange);
      bf_Integral_DeltaY_LegendConfig.addParameter("useLegend",true);
      bf_Integral_DeltaY_LegendConfig.addParameter("useTitles",false);
      bf_Integral_DeltaY_LegendConfig.addParameter("useLabels",true);
      bf_Integral_DeltaY_LegendConfig.addParameter("useNDC",false);
      bf_Integral_DeltaY_LegendConfig.addParameter("textColor",    1);
      bf_Integral_DeltaY_LegendConfig.addParameter("textSize",     0.05);
      bf_Integral_DeltaY_LegendConfig.addParameter("nColumns",     1);
      }
    else
      {
      x = 0.25;
      y = 1.35;
      bf_max = 1.5;
      yRange = 0.3;
      bf_Integral_DeltaY_LegendConfig.addLabel(bf_General_Titles[0],x,y,0.0,1,0.06);
      bf_Integral_DeltaY_LegendConfig.addParameter("xLeft", 0.25);
      bf_Integral_DeltaY_LegendConfig.addParameter("xRight",1.20);
      bf_Integral_DeltaY_LegendConfig.addParameter("yLow",  0.60);
      bf_Integral_DeltaY_LegendConfig.addParameter("yHigh", 1.250);
      bf_Integral_DeltaY_LegendConfig.addParameter("useLegend",true);
      bf_Integral_DeltaY_LegendConfig.addParameter("useTitles",false);
      bf_Integral_DeltaY_LegendConfig.addParameter("useLabels",true);
      bf_Integral_DeltaY_LegendConfig.addParameter("useNDC",false);
      bf_Integral_DeltaY_LegendConfig.addParameter("textColor",    1);
      bf_Integral_DeltaY_LegendConfig.addParameter("textSize",     0.055);
      bf_Integral_DeltaY_LegendConfig.addParameter("nColumns",     3);
      }



    String canvasName =  outputFileNameBase;
    canvasName += "_";
    canvasName += bf_CanvasNameBases[0];
    canvasName += bf_IntegralTypeNames[bf_Types[0]];
    canvasName += "_";
    canvasName += speciesNames[iTrigger];
    canvasName += "_";
    canvasName += deltaY_Name;
    plot(canvasName,
         bf_Integral_DeltaY_CanvasConfig,
         bf_DeltaY_GraphConfigs,
         bf_Integral_DeltaY_LegendConfig,
         graphs,
         deltaY_Title,0.18,20.0,
         "I^{s}", -0.1, bf_max);
    //bf_Title, -0.1, bf_max);

    }
}

void BalFctPlotter::plotBfIntegralVsPairvsDeltaYVsFile()
{
  Size_t nSpecies = speciesNames.size();
  Size_t nFiles   = bf_InputFiles.size();
  vector<TGraph*> graphs;
  vector<double>  minima;
  vector<double>  maxima;
  String bf_Title;
  double bf_min = -0.1;
  double bf_max = 1.2;
  double xMin   =  0.01;
  double xMax   =  20.0;
  double xRange =  xMax-xMin;
  double x      =  0.0;
  double yMin   = bf_min;
  double yMax   = bf_max;
  double yRange = yMax-yMin;
  double y      = 0.0;

  if (bf_Integral_DeltaY_Graphs.size()<1)
    {
    throw TaskException("bf_Integral_DeltaY_Graphs.size()<1","plotBfIntegralVsPairvsDeltaYVsFile()");
    }


  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    cout << endl;
    printItem("iTrigger",iTrigger);

    for (Size_t iAssoc=0; iAssoc<nSpecies; iAssoc++)
      {
      graphs.clear();
      minima.clear();
      maxima.clear();
      bf_Integral_DeltaY_LegendConfig.clearLabels();
      bf_Integral_DeltaY_LegendConfig.clearLegend();

      printItem("iAssoc",iAssoc);
      for (Size_t iFile=0; iFile<nFiles; iFile++)
        {
        printItem("iFile",iFile);
        Size_t index = nFiles*(iTrigger*nSpecies + iAssoc) + iFile;
        printItem("histo index",index);
        TGraph * h = bf_Integral_DeltaY_Graphs[index];
        graphs.push_back(h);
        minima.push_back(findGraphMinimum(h));
        maxima.push_back(findGraphMaximum(h));
        xMin = h->GetXaxis()->GetXmin();
        xMax = h->GetXaxis()->GetXmax();
        xRange =  xMax-xMin;
        bf_Integral_DeltaY_LegendConfig.addLegend(bf_InputFileTitles[iFile]);
   }

      printItem("graphs.size()",graphs.size());
      printItem("minima.size()",minima.size());
      printItem("maxima.size()",maxima.size());
      bf_Title = bf_IntegralTypeTitles[bf_Types[0]];
      bf_min   = findMinimum(minima);
      bf_max   = 1.3*findMaximum(maxima);

      printItem("bf_Title",bf_Title);
      printItem("pre-tweak - bf_min",bf_min);
      printItem("pre-tweak - bf_max",bf_max);

      tweak(bf_min,bf_max);
      printItem("post-tweak - bf_min",bf_min);
      printItem("post-tweak - bf_max",bf_max);

      x = 0.25;
      yMin   = bf_min;
      yMax   = bf_max;
      yRange = yMax-yMin;
      y = yMax - 0.1*yRange;
      bf_Integral_DeltaY_LegendConfig.addLabel(bf_General_Titles[0],x,y,0.0,1,0.05);
      y = yMax - 0.19*yRange;
      bf_Integral_DeltaY_LegendConfig.addLabel(pairTitles[iTrigger*nSpecies+iAssoc],x,y,0.0,1,0.055);

      bf_Integral_DeltaY_LegendConfig.addParameter("xLeft", 0.25);
      bf_Integral_DeltaY_LegendConfig.addParameter("xRight",0.65);
//      bf_Integral_DeltaY_LegendConfig.addParameter("xLeft", x);
//      bf_Integral_DeltaY_LegendConfig.addParameter("xRight",x+0.12*xRange);
      bf_Integral_DeltaY_LegendConfig.addParameter("yLow",  yMax - 0.55*yRange);
      bf_Integral_DeltaY_LegendConfig.addParameter("yHigh", yMax - 0.25*yRange);
//      bf_Integral_DeltaY_LegendConfig.addParameter("yLow",  yMax + 0.015*yRange);
//      bf_Integral_DeltaY_LegendConfig.addParameter("yHigh", yMax + 0.35*yRange);
      bf_Integral_DeltaY_LegendConfig.addParameter("useLegend",true);
      bf_Integral_DeltaY_LegendConfig.addParameter("useTitles",false);
      bf_Integral_DeltaY_LegendConfig.addParameter("useLabels",true);
      bf_Integral_DeltaY_LegendConfig.addParameter("useNDC",false);
      bf_Integral_DeltaY_LegendConfig.addParameter("textColor",    1);
      bf_Integral_DeltaY_LegendConfig.addParameter("textSize",     0.06);
      bf_Integral_DeltaY_LegendConfig.addParameter("nColumns",     1);


      String canvasName =  outputFileNameBase;
      canvasName += "_";
      canvasName += bf_CanvasNameBases[0];
      canvasName += bf_IntegralTypeNames[bf_Types[0]];
      canvasName += "_";
      canvasName += pairNames[iTrigger*nSpecies+iAssoc];;
      canvasName += "_";
      canvasName += deltaY_Name;
      plot(canvasName,
           bf_Integral_DeltaY_CanvasConfig,
           bf_DeltaY_GraphConfigs,
           bf_Integral_DeltaY_LegendConfig,
           graphs,
           deltaY_Title,0.18,20.0,
           bf_Title, bf_min, bf_max);
      }
    }
}

void BalFctPlotter::plotBFIntegralSumvsPairvsDeltaY()
{
  Size_t nSpecies = speciesNames.size();
  Size_t nFiles   = bf_InputFiles.size();
  vector<TGraph*> graphs;
  String bf_Title;
  double bf_min = -0.1;
  double bf_max = 1.2;
  double xMin   =  0.01;
  double xMax   =  20.0;
  double xRange =  xMax-xMin;
  double x      =  0.0;
  double yMin   = bf_min;
  double yMax   = bf_max;
  double yRange = yMax-yMin;
  double y      = 0.0;

  if (bf_IntegralSum_DeltaY_Graphs.size()<1)
    {
    throw TaskException("bf_Integral_DeltaY_Graphs.size()<1","plotBfIntegralVsPairvsDeltaY()");
    }

  for (Size_t iTrigger=0; iTrigger<nSpecies; iTrigger++)
    {
    cout << endl;
    printItem("iTrigger",iTrigger);
    graphs.clear();

    bf_Integral_DeltaY_LegendConfig.clearLabels();
    bf_Integral_DeltaY_LegendConfig.clearLegend();

    for (Size_t iAssoc=0; iAssoc<nSpecies; iAssoc++)
      {
      printItem("iAssoc",iAssoc);
      for (Size_t iFile=0; iFile<nFiles; iFile++)
        {
        printItem("iFile",iFile);
        Size_t index = iFile*nSpecies*nSpecies + iTrigger*nSpecies + iAssoc;
        printItem("histo index",index);
        TGraph * h = bf_IntegralSum_DeltaY_Graphs[index];
        graphs.push_back(h);
        xMin = h->GetXaxis()->GetXmin();
        xMax = h->GetXaxis()->GetXmax();
        xRange =  xMax-xMin;
        String title;
        if (iAssoc==0) 
          {
          title = pairTitles[iTrigger*nSpecies+iAssoc];
          }
        else if (iAssoc==1)
          {
          title = pairTitles[iTrigger*nSpecies];
          title += "+";
          title += pairTitles[iTrigger*nSpecies+iAssoc];
          }
        else if (iAssoc>1)
          {
          title = pairTitles[iTrigger*nSpecies];
          title += "+...+";
          title += pairTitles[iTrigger*nSpecies+iAssoc];
          }
        bf_Integral_DeltaY_LegendConfig.addLegend(title);
        }
      }

    printItem("graphs.size()",graphs.size());
    //bf_Title = bf_IntegralSumTypeTitles[bf_Types[0]];
    x = 0.25;
    yMin   = bf_min;
    yMax   = bf_max;
    yRange = yMax-yMin;
    y = yMax - 0.1*yRange;
    bf_Integral_DeltaY_LegendConfig.addLabel(bf_General_Titles[0],x,y,0.0,1,0.06);

    x = 0.20;
    bf_Integral_DeltaY_LegendConfig.addParameter("xLeft", x);
    bf_Integral_DeltaY_LegendConfig.addParameter("xRight",x+0.95*xRange);
//    bf_Integral_DeltaY_LegendConfig.addParameter("yLow",  yMax - 0.5*yRange);
//    bf_Integral_DeltaY_LegendConfig.addParameter("yHigh", yMax - 0.2*yRange);
    bf_Integral_DeltaY_LegendConfig.addParameter("yLow",  yMax + 0.01*yRange);
    bf_Integral_DeltaY_LegendConfig.addParameter("yHigh", yMax + 0.3*yRange);
    bf_Integral_DeltaY_LegendConfig.addParameter("useLegend",true);
    bf_Integral_DeltaY_LegendConfig.addParameter("useTitles",false);
    bf_Integral_DeltaY_LegendConfig.addParameter("useLabels",true);
    bf_Integral_DeltaY_LegendConfig.addParameter("useNDC",false);
    bf_Integral_DeltaY_LegendConfig.addParameter("textColor",    1);
    bf_Integral_DeltaY_LegendConfig.addParameter("textSize",     0.05);
    bf_Integral_DeltaY_LegendConfig.addParameter("nColumns",     3);

    String canvasName =  outputFileNameBase;
    canvasName += "_";
    canvasName += bf_CanvasNameBases[0];
    canvasName += bf_IntegralSumTypeNames[bf_Types[0]];
    canvasName += "_";
    canvasName += speciesNames[iTrigger];
    canvasName += "_";
    canvasName += deltaY_Name;
    plot(canvasName,
         bf_IntegralSum_DeltaY_CanvasConfig,
         bf_DeltaY_GraphConfigs,
         bf_Integral_DeltaY_LegendConfig,
         graphs,
         deltaY_Title,0.18,20.0,
         bf_IntegralSumTypeTitles[bf_Types[0]], bf_min, bf_max);

    }
}

void BalFctPlotter::plotRmsWidths()
{

}

void BalFctPlotter::execute()
{
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("rangeOption",rangeOption);
    //printItem("correlationOption",correlationOption);
    printItem("speciesOption",speciesOption);
    printItem("rapidityOption",rapidityOption);
    }

  setDefaultOptions(1);
  setSpeciesArrays();
  openInputFiles();
  createNames();

  loadHistograms();
  Size_t nFiles   = bf_InputFiles.size();
  Size_t nSpecies = speciesNames.size();

  //bf_DeltaYDeltaPhi_GraphConfig = createGraphConfigurationPalette(1,2);
  bf_DeltaY_GraphConfigs = createGraphConfigurationPalette(16,1);

  if (reportInfo(__FUNCTION__)) printItem("doPlotsBfVsDeltaYDeltaPhi",doPlotsBfVsDeltaYDeltaPhi);
  if (doPlotsBfVsDeltaYDeltaPhi) plotBF2D();

  if (reportInfo(__FUNCTION__)) printItem("doPlotsBfVsDeltaY",doPlotsBfVsDeltaY);
  if (doPlotsBfVsDeltaY) 
    {
    if (nFiles==1)
    {
    calculateBfSums();
    plotBfVsPairvsDeltaY();
    }
    if (nFiles> 1)
      {
      plotBfVsPairvsDeltaYVsFile();
      }
    }
  if (reportInfo(__FUNCTION__)) printItem("doPlotsBfVsDeltaPhi",doPlotsBfVsDeltaPhi);
  if (doPlotsBfVsDeltaPhi) plotBfVsPairvsDeltaPhi();
  if (reportInfo(__FUNCTION__)) printItem("doPlotsBfIntegralVsDeltaY",doPlotsBfIntegralVsDeltaY);
  if (doPlotsBfIntegralVsDeltaY) 
    {
    calculateIntegrals();
    if (nFiles==1) 
      {
      plotBfIntegralVsPairvsDeltaY();
      //plotBFIntegralSumvsPairvsDeltaY();
      }
    else if (nFiles>1)
      {
      plotBfIntegralVsPairvsDeltaYVsFile();
      //plotBFIntegralSumvsPairvsDeltaYvsFile();
      }
    }
  if (doPlotsBfWidthDeltaY || doPlotsBfWidthDeltaPhi)
    {
    calculateRmsWidths();
    plotRmsWidths();
    }
  outputPath = outputPathNameBase;
  //outputPath += outputFileNameBase;

  if (doPrint)
    printAllCanvas(outputPath,doPrintGif,doPrintPdf,doPrintSvg,doPrintPng,doPrintC);
}

void BalFctPlotter::setSpeciesArrays()
{
  if (reportInfo(__FUNCTION__)) printItem("SpeciesOption",speciesOption);
  speciesNames.clear();
  speciesTitles.clear();
  speciesPath = "";
  switch (speciesOption)
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
      speciesTitles.push_back(String("p"));
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
    cout << " nSpecies................... :" << nSpecies    << endl;
    cout << " speciesPath................ :" << speciesPath << endl;
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
  for (Size_t iSpecies2=0; iSpecies2<nSpecies; iSpecies2++)
    {
    if (reportDebug(__FUNCTION__)) cout << " iSpecies2.................. : " << iSpecies2 << endl;
    pairTitlePlus = "";
    for (Size_t iSpecies1=0; iSpecies1<nSpecies; iSpecies1++)
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
    Size_t nPairs = pairNames.size();
    cout << " nPairs................... :" << nPairs << endl;
    for (Size_t k=0; k<nPairs; k++)
      {
      cout << " k:" << k << "    " << pairNames[k] << "   " << pairTitles[k] << "   " << pairCumulTitles[k] << endl;
      }
    }
}




void BalFctPlotter::createNames()
{
  deltaPhi_Name  = "DeltaPhi";
  deltaPhi_Title = "#Delta #varphi";
  switch (rapidityOption)
    {
      default:
      case 0: deltaY_Title   = "#Delta y";    deltaY_Name    = "DeltaY";    break;
      case 1: deltaY_Title   = "#Delta #eta"; deltaY_Name    = "DeltaEta";  break;
    }

  // correlation source name
  correlatorSourceNames.push_back(String("_A2_DyDphi_shft_"));
  correlatorSourceNames.push_back(String("_B2_DyDphi_shft_"));
  correlatorSourceNames.push_back(String("_C2_DyDphi_shft_"));
  correlatorSourceNames.push_back(String("_D2_DyDphi_shft_"));

  // bf_Type == 0
  bf_TypeNames.push_back(String("B2_1Bar_2"));
  bf_IntegralTypeNames.push_back(String("I2_1Bar_2"));
  bf_IntegralSumTypeNames.push_back(String("SumI2_1Bar_2"));
  bf_WidthDeltaYTypeNames.push_back(String("SigmaB2_1Bar_2"));

  bf_TypeTitles.push_back(String("B^{#bar{#alpha}#beta}"));
  bf_IntegralTypeTitles.push_back(String("I^{#bar{#alpha}#beta}"));
  bf_IntegralSumTypeTitles.push_back(String("#sum I^{#bar{#alpha}#beta}"));
  bf_WidthDeltaYTypeTitles.push_back(String("#sigma^{B^{#bar{#alpha}#beta}}_{#Delta y}"));

  // bf_Type == 1
  bf_TypeNames.push_back(String("B2_1_2Bar"));
  bf_IntegralTypeNames.push_back(String("I2_1_2Bar"));
  bf_IntegralSumTypeNames.push_back(String("SumI2_1_2Bar"));
  bf_WidthDeltaYTypeNames.push_back(String("SigmaB2_1_2Bar"));

  bf_TypeTitles.push_back(String("B^{#alpha#bar#beta}"));
  bf_IntegralTypeTitles.push_back(String("I^{#bar{#alpha}#bar{#beta}}"));
  bf_IntegralSumTypeTitles.push_back(String("#sum I^{#alpha#bar{#beta}}"));
  bf_WidthDeltaYTypeTitles.push_back(String("#sigma^{B^{#alpha#bar{#beta}}_{#Delta y}}"));

  // bf_Type == 2
  bf_TypeNames.push_back(String("B2_12Sum"));
  bf_IntegralTypeNames.push_back(String("I2_12Sum"));
  bf_IntegralSumTypeNames.push_back(String("SumI2_12Sum"));
  bf_WidthDeltaYTypeNames.push_back(String("SigmaB2_12Sum"));

  bf_TypeTitles.push_back(String("B^{s}"));
  bf_IntegralTypeTitles.push_back(String("I^{s}"));
  bf_IntegralSumTypeTitles.push_back(String("#sum I^{s}"));
  bf_WidthDeltaYTypeTitles.push_back(String("#sigma^{B^{s}}_{#Delta y}"));

  String vsPairName = "VsPairName";
  String baseHistoName;
  String baseCanvasName;
  String baseHistoTitle;
  String pairName;
  String pairTitle;
  String title;
  String underscore = "_";
  String correlatorSourceName;

  Size_t nFiles = bf_InputFiles.size();
  printItem("nFiles",nFiles);
  for (Size_t iFile=0; iFile<nFiles; iFile++)
    {
    printItem("file index",iFile);
    baseHistoName  = bf_HistoNameBases[iFile];
    baseHistoTitle = bf_HistoTitleBases[iFile];
    baseCanvasName = bf_CanvasNameBases[iFile];
    correlatorSourceName = correlatorSourceNames[bf_Sources[iFile]];
    correlatorSourceName += bf_TypeNames[bf_Types[iFile]];
    printItem("baseHistoName",baseHistoName);
    printItem("baseHistoTitle",baseHistoTitle);
    printItem("baseCanvasName",baseCanvasName);
    printItem("correlatorSourceName",correlatorSourceName);


    for (Size_t iPair=0; iPair<pairNames.size(); iPair++)
      {
      pairName  = pairNames[iPair];
      pairTitle = pairTitles[iPair];

      String bf_DeltaYDeltaPhi_InputName     = baseHistoName+pairName+correlatorSourceName;
      String bf_DeltaY_InputName             = baseHistoName+pairName+correlatorSourceName+"_x";
      String bf_DeltaPhi_InputName           = baseHistoName+pairName+correlatorSourceName+"_y";
      bf_DeltaYDeltaPhi_HistoNames.push_back( bf_DeltaYDeltaPhi_InputName);
      bf_DeltaY_HistoNames.push_back(         bf_DeltaY_InputName);
      bf_DeltaPhi_HistoNames.push_back(       bf_DeltaPhi_InputName);

      title = baseHistoTitle;
      title += " ";
      title += pairTitle;
      bf_DeltaYDeltaPhi_Titles.push_back(    title  );
      bf_DeltaY_Titles.push_back(            title  );
      bf_DeltaPhi_Titles.push_back(          title  );
      bf_Integral_DeltaY_Titles.push_back(   title  );
      bf_IntegralSum_DeltaY_Titles.push_back(title  );

      printItem("pair index",iPair);
      printItem("pairName",pairName);
      printItem("pairTitle",pairTitle);
      printItem("bf_DeltaYDeltaPhi_InputName",bf_DeltaYDeltaPhi_InputName);
      printItem("bf_DeltaY_InputName",bf_DeltaY_InputName);
      printItem("bf_DeltaPhi_InputName",bf_DeltaPhi_InputName);
      printItem("bf_DeltaYDeltaPhi_Title",title);
      printItem("bf_DeltaY_Titles",title);
      printItem("bf_DeltaPhi_Title",title);
      printItem("bf_Integral_DeltaY_Title",title);
      printItem("bf_IntegralSum_DeltaY_Title",title);
      }
    }
}

void BalFctPlotter::setLegendConfigurations()
{
  //bf_LegendConfig2Ds.clear();

//  bf_LegendConfig1D_DeltaY.clear();
//  bf_LegendConfig1D_DeltaY_VsPair.clear();
//  bf_LegendConfig1D_DeltaPhi.clear();
//  bf_LegendConfig1D_Integral.clear();
//  bf_LegendConfig1D_IntegralSum.clear();
//  bf_LegendConfig1D_IntegralVsPair.clear();
//  bf_LegendConfig1D_Width.clear();
//  int nSpecies = speciesNames.size();
//  int iPair;
//  LegendConfiguration * lc;
//
//  for (Size_t iSpecies2=0; iSpecies2<nSpecies; iSpecies2++)
//    {
//    // B vs Delta y
//    lc = new LegendConfiguration(0.65, 0.85, 0.5, 0.9, 0.07);
//    lc->setParameter("useLegend",true);
//    lc->setParameter("useLabels",true);
//    lc->setParameter("useTitles",false);
//    lc->setParameter("textIndex",42);
//    lc->setParameter("nColumns",2);
//    bf_LegendConfig1D_DeltaY.push_back(lc);
//    // B vs Delta phi
//    lc = new LegendConfiguration(0.5, 0.85, 0.5, 0.94, 0.07);
//    lc->setParameter("useLegend",true);
//    lc->setParameter("useLabels",true);
//    lc->setParameter("useTitles",false);
//    lc->setParameter("textIndex",42);
//    lc->setParameter("nColumns",3);
//    bf_LegendConfig1D_DeltaPhi.push_back(lc);
//    // I vs Delta y
//    lc = new LegendConfiguration(0.20, 0.95, 0.81, 0.98, 0.05);
//    lc->setParameter("useLegend",true);
//    lc->setParameter("useLabels",true);
//    lc->setParameter("useTitles",false);
//    lc->setParameter("textIndex",42);
//    lc->setParameter("nColumns",3);
//    bf_LegendConfig1D_Integral.push_back(lc);
//    // Isum vs Delta y
//    lc = new LegendConfiguration(0.20, 0.95, 0.81, 0.98, 0.045);
//    lc->setParameter("useLegend",true);
//    lc->setParameter("useLabels",true);
//    lc->setParameter("useTitles",false);
//    lc->setParameter("textIndex",42);
//    lc->setParameter("nColumns",3);
//    bf_LegendConfig1D_IntegralSum.push_back(lc);
//
//    // I vs Pair
//    lc = new LegendConfiguration(0.57, 0.77, 0.62, 0.9, 0.045);
//    //lc = new LegendConfiguration(0.20, 0.95, 0.81, 0.98, 0.045);
//    lc->setParameter("useLegend",true);
//    lc->setParameter("useLabels",true);
//    lc->setParameter("useTitles",false);
//    lc->setParameter("textIndex",42);
//    lc->setParameter("nColumns",1);
//    bf_LegendConfig1D_IntegralVsPair.push_back(lc);
//
//    // width
//    //lc = new LegendConfiguration(0.55, 0.8, 0.25, 0.45, 0.05);
//    lc = new LegendConfiguration(0.25, 0.5, 0.22, 0.42, 0.05);
//    lc->setParameter("useLegend",true);
//    lc->setParameter("useLabels",true);
//    lc->setParameter("useTitles",false);
//    lc->setParameter("textIndex",42);
//    lc->setParameter("nColumns",1);
//    bf_LegendConfig1D_Width.push_back(lc);
//
//    for (Size_t iSpecies1=0; iSpecies1<nSpecies; iSpecies1++)
//      {
//      // B vs Delta y
//      lc = new LegendConfiguration(0.65, 0.75, 0.5, 0.9, 0.05);
//      lc->setParameter("useLegend",true);
//      lc->setParameter("useLabels",true);
//      lc->setParameter("useTitles",false);
//      lc->setParameter("textIndex",42);
//      lc->setParameter("nColumns",1);
//      for (Size_t iFile=0; iFile<bf_InputFiles.size(); iFile++)
//        {
//        int iPair = iSpecies2*nSpecies + iSpecies1;
//        String  title = BalFct_HistoTitleBases[iFile];
//        title += pairTitles[iPair];
//        lc->addLegend(title);
//        }
//      bf_LegendConfig1D_DeltaY_VsPair.push_back(lc);
//
//      iPair = iSpecies2*nSpecies + iSpecies1;
//      bf_LegendConfig1D_DeltaY[iSpecies2]->addLegend(pairTitles[iPair]);
//      bf_LegendConfig1D_DeltaPhi[iSpecies2]->addLegend(pairTitles[iPair]);
//      bf_LegendConfig1D_Integral[iSpecies2]->addLegend(pairTitles[iPair]);
//      bf_LegendConfig1D_IntegralSum[iSpecies2]->addLegend(pairCumulTitles[iPair]);
//      //bf_LegendConfig1D_Width[iSpecies2]->addLegend(pairTitles[iPair]);
//      }
//
//    int nFiles = bf_InputFiles.size();
//    for (Size_t iFile=0; iFile<nFiles; iFile++)
//      {
//      if (reportDebug(__FUNCTION__)) cout << "iSpecies2=" << iSpecies2 <<  " iFile=" << iFile << " title=" << bf_IntegralSumVsName_Titles[iFile*nSpecies + iSpecies2] << endl;
//      bf_LegendConfig1D_IntegralVsPair[iSpecies2]->addLegend(bf_IntegralSumVsName_Titles[iFile*nSpecies + iSpecies2]);
//      bf_LegendConfig1D_Width[iSpecies2]->addLegend(bf_IntegralSumVsName_Titles[iFile*nSpecies + iSpecies2]);
//      }
//    }
}



void BalFctPlotter::openInputFiles()
{
  Size_t nFiles = bf_InputPathNames.size();
  if (reportInfo(__FUNCTION__)) printItem("nFiles",nFiles);
  for (Size_t iFile=0; iFile<nFiles; iFile++)
    {
    String inputPathName = bf_InputPathNames[iFile];
    String inputFileName = bf_InputFileNames[iFile];
    TFile * f = openRootFile(inputPathName,inputFileName,"OLD");
    if (!f) throw FileException(inputPathName+inputFileName,"Not found","BalFctPlotter::openInputFiles()");
    bf_InputFiles.push_back(f);
    if (reportInfo(__FUNCTION__))
      {
      cout << endl;
      printItem("iFile",iFile);
      printItem("Input path",bf_InputPathNames[iFile]);
      printItem("File name",bf_InputFileNames[iFile]);
      printItem("Title base",bf_InputFileTitles[iFile]);
      printItem("Histo Name Base",bf_HistoNameBases[iFile]);
      printItem("Histo Title Base",bf_HistoTitleBases[iFile]);
      printItem("Canvas Name Base",bf_CanvasNameBases[iFile]);
      }
    }
}
