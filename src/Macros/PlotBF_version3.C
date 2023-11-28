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
void loadPlotting(const TString & includeBasePath);






TH1 * makeHistoWithNames(const TString & histoName, vector<TString> & entryNames, vector<double> & vy,  vector<double> & vey)
{
  cout << "<I> makeHistoWithNames(names,vy,vey) Starting the creation of histo called " << histoName << endl;

  int n = vy.size();
  int n1 = vey.size();
  cout << "<I> makeHistoWithNames(names,vy,vey) n:" << n << "  n1:" << n1 << endl;
  if ( n!=n1 || n<1 )
    {
    cout << "<E> makeHistoWithNames(names,vy,vey) arguments provided have incompatible sizes)" << endl;
    return nullptr;
    }
  TH1 * h = new TH1D(histoName,histoName,n,0.0, double(n));
  cout << "<I> makeHistoWithNames(names,vy,vey) Histogram created?" << endl;
  if (!h)
    {
    cout << "<E> makeHistoWithNames(names,vy,vey) Histogram pointer is null" << endl;
    return nullptr;
    }
  else
    {
    cout << "<E> makeHistoWithNames(names,vy,vey) Histogram pointer is NOT null" << endl;
    }

  for (int k=0;k<n;k++)
    {
    h->SetBinContent(k+1,vy[k]);
    h->SetBinError(k+1,vey[k]);
    h->GetXaxis()->SetBinLabel(k+1,entryNames[k]);
    }
  return h;
}

TFile *  Task::openRootFile(const String & inputPath, const String & fileName, const String & ioOption)
{
  if (reportStart(__FUNCTION__))
    ;


  // sometimes the caller sets the path within the file name... so one
  // should not prepend the path to the name... By convention, we assume that
  // if the file name begins with '/', it is an absolute path.
  String inputFileName;
  if (fileName.BeginsWith("/"))
    inputFileName = fileName;
  else
    {
    // make sure that if an inputPath is given, it ends with '/'
    String inputFilePath = inputPath;
    int slash = inputFilePath.First('/');
    int len   = inputFilePath.Length();
    if (len>0 && (len-1)!=slash) inputFilePath += "/";
    inputFileName = inputFilePath;
    inputFileName += fileName;
    }
  // make sure the root extension is included in the file name
  if (!inputFileName.EndsWith(".root")) inputFileName += ".root";
  if (reportDebug (__FUNCTION__))  cout << "Opening file: " << inputFileName << " with option: " << ioOption << endl;
  TFile * inputFile = new TFile(inputFileName,ioOption);
  if (!inputFile) throw  FileException(inputFileName,"File not found","Task::openRootFile()");
  if (!inputFile->IsOpen())  throw  FileException(inputFileName,"File not found/opened","Task::openRootFile()");
  if (reportDebug(__FUNCTION__)) cout << "File opened successfully." << endl;
  return inputFile;
}

TFile * openRootFile(CAP::Plotter * plotter, const TString & inputPath, const TString & fileName)
{
  TFile * f =  plotter->openRootFile(inputPath,fileName,"OLD");
  if (!f)
    {
    cout << " Could not open file named " << fileName << endl;
    cout << " ABORT!!!!" << endl;
    }
  return f;
}


TString makeName(const TString & s1, const TString & s2)
{
  TString s = s1;
  s += "_";
  s += s2;
  return s;
}

TString makeName(const TString & s1, const TString & s2, const TString & s3)
{
  TString s = s1;
  s += "_";
  s += s2;
  s += "_";
  s += s3;
  return s;
}

TString makeName(const TString & s1, const TString & s2, const TString & s3, const TString & s4)
{
  TString s = s1;
  s += "_";
  s += s2;
  s += "_";
  s += s3;
  s += "_";
  s += s4;
  return s;
}


int PlotBF_version3()
{

  

  if (plot1DHighRes>0)
    {
    cout << "" << endl;
    minRapidity     = -3.0;
    maxRapidity     =  3.0;
    minRapidityInt  =  0.1;
    maxRapidityInt  =  8.0;
    etaLow   =  0.1;
    etaHigh  =  maxRapidityInt-0.05;
    etaStep  =  0.2;
    }
  TLine * line = new TLine(0.1,1.0, maxRapidity,1.0);

  cout << "plot1DHighRes....:" << plot1DHighRes << endl;
  cout << "minRapidity......:" << minRapidity << endl;
  cout << "maxRapidity......:" << maxRapidity << endl;




    switch (balFct_Types[iFile])
      {
        case 0:
        balFct_Name                    = "B1Bar2";
        balFct_Integral_Name           = "I1Bar2";
        balFct_IntegralSum_Name        = "I1Bar2Sum";
        balFct_DeltaYDeltaPhi_Name     = makeName(prefix,balFct_Name, DeltaY_Name,DeltaPhi_Name);
        balFct_DeltaY_Name             = makeName(prefix,balFct_Name, DeltaY_Name);
        balFct_DeltaPhi_Name           = makeName(prefix,balFct_Name, DeltaPhi_Name);
        balFct_Integral_DeltaY_Name    = makeName(prefix,balFct_Integral_Name, DeltaY_Name);
        balFct_IntegralSum_DeltaY_Name = makeName(prefix,balFct_IntegralSum_Name, DeltaY_Name);

        balFct1Bar2_DeltaYDeltaPhi_Histos.push_back(h2);
        balFct1Bar2_DeltaYDeltaPhi_Names.push_back(balFct_DeltaYDeltaPhi_Name);
        balFct1Bar2_DeltaY_Histos.push_back(h1x);
        balFct1Bar2_DeltaY_Names.push_back(balFct_DeltaY_Name);
        balFct1Bar2_DeltaPhi_Histos.push_back(h1y);
        balFct1Bar2_DeltaPhi_Names.push_back(balFct_DeltaPhi_Name);
        calculateIntegrals(h2,balFct1Bar2_Integral_DeltaY_Graphs,etaLow,etaHigh,etaStep);
        break;

        case 1:
        balFct_Name                    = "B12Bar";
        balFct_Integral_Name           = "I12Bar";
        balFct_IntegralSum_Name        = "I12BarSum";
        balFct_DeltaYDeltaPhi_Name     = makeName(prefix,balFct_Name, DeltaY_Name,DeltaPhi_Name);
        balFct_DeltaY_Name             = makeName(prefix,balFct_Name, DeltaY_Name);
        balFct_DeltaPhi_Name           = makeName(prefix,balFct_Name, DeltaPhi_Name);
        balFct_Integral_DeltaY_Name    = makeName(prefix,balFct_Integral_Name, DeltaY_Name);
        balFct_IntegralSum_DeltaY_Name = makeName(prefix,balFct_IntegralSum_Name, DeltaY_Name);

        balFct12Bar_DeltaYDeltaPhi_Histos.push_back(h2);
        balFct12Bar_DeltaYDeltaPhi_Names.push_back(balFct_DeltaYDeltaPhi_Name);
        balFct12Bar_DeltaY_Histos.push_back(h1x);
        balFct12Bar_DeltaY_Names.push_back(balFct_DeltaY_Name);
        balFct12Bar_DeltaPhi_Histos.push_back(h1y);
        balFct12Bar_DeltaPhi_Names.push_back(balFct_DeltaPhi_Name);
        calculateIntegrals(h2,balFct12Bar_Integral_DeltaY_Graphs,etaLow,etaHigh,etaStep);
        break;

        case 2:
        balFct_Name                    = "B12s";
        balFct_Integral_Name           = "I12s";
        balFct_IntegralSum_Name        = "I12sSum";
        balFct_DeltaYDeltaPhi_Name     = makeName(prefix,balFct_Name, DeltaY_Name,DeltaPhi_Name);
        balFct_DeltaY_Name             = makeName(prefix,balFct_Name, DeltaY_Name);
        balFct_DeltaPhi_Name           = makeName(prefix,balFct_Name, DeltaPhi_Name);
        balFct_Integral_DeltaY_Name    = makeName(prefix,balFct_Integral_Name, DeltaY_Name);
        balFct_IntegralSum_DeltaY_Name = makeName(prefix,balFct_IntegralSum_Name, DeltaY_Name);

        balFct12s_DeltaYDeltaPhi_Histos.push_back(h2);
        balFct12s_DeltaYDeltaPhi_Names.push_back(balFct_DeltaYDeltaPhi_Name);
        balFct12s_DeltaY_Histos.push_back(h1x);
        balFct12s_DeltaY_Names.push_back(balFct_DeltaY_Name);
        balFct12s_DeltaPhi_Histos.push_back(h1y);
        balFct12s_DeltaPhi_Names.push_back(balFct_DeltaPhi_Name);
        calculateIntegrals(h2,balFct12s_Integral_DeltaY_Graphs,etaLow,etaHigh,etaStep);
        break;
      }

    //    if (plot2D)
    //      {
    //      plotter->plot(balFct_DeltaYDeltaPhi_Name,landscapeLinear,*graphConfiguration2D,legendConfig2D,
    //                    h2,
    //                    DeltaY_Title,minRapidity,maxRapidity,
    //                    DeltaPhi_Title,1.0,-1.0,
    //                    balFct_title,balFct2d_Min, balFct2d_Max);
    //      }
    cout << "Histo load of plots completed" << endl;
    }

  if (plotWidths)
    {


//    balFct12s_Width_name = "PythiaWidthsVsAcceptance";
//    TH1 * balFct12s_Width_Histos = makeHistoWithNames(balFct12s_Width_name, widthTitles, rmsWidths, rmsWidthErrors);
//    plotter->plot(balFct12s_Width_name,landscapeLinear, *widthGraphConfiguration, balFct12s_Width_legendConfig,
//                  balFct12s_Width_Histos,
//                  "",4.0,-4.0,"RMS",0.0,2.0,
//                  "",0.6, 0.3, 0.8, 0.4, 0.05);

    }

  prefix = outFileNameBase;
  cout << "    prefix: " << prefix << endl;

  if (plot1D)
    {
    if (balFct1Bar2_DeltaY_Histos.size()>0 && plot1D)
      {
      balFct_Title                   = "B^{#bar{#alpha}#beta}";
      balFct_Integral_Title          = "I^{#bar{#alpha}#beta}";
      balFct_IntegralSum_Title       = "#sum_{#bar#alpha} I^{#bar{#alpha}#beta}";
      balFct_Name                    = "B1Bar2";
      balFct_Integral_Name           = "I1Bar2";
      balFct_IntegralSum_Name        = "I1Bar2Sum";
      balFct_DeltaYDeltaPhi_Name     = makeName(prefix,balFct_Name, DeltaY_Name,DeltaPhi_Name);
      balFct_DeltaY_Name             = makeName(prefix,balFct_Name, DeltaY_Name);
      balFct_DeltaPhi_Name           = makeName(prefix,balFct_Name, DeltaPhi_Name);
      balFct_Integral_DeltaY_Name    = makeName(prefix,balFct_Integral_Name, DeltaY_Name);
      balFct_IntegralSum_DeltaY_Name = makeName(prefix,balFct_IntegralSum_Name, DeltaY_Name);

      createSumGraphs(balFct1Bar2_Integral_DeltaY_Graphs,balFct1Bar2_IntegralSum_DeltaY_Graphs);

      plotter->plot(balFct_DeltaY_Name,landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[1],
                    balFct1Bar2_DeltaY_Histos,
                    DeltaY_Title, minRapidity, maxRapidity,
                    balFct_Title, balFct_Minima[1], balFct_Maxima[1]);
      plotter->plot(balFct_DeltaPhi_Name,landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[2],
                    balFct1Bar2_DeltaPhi_Histos,
                    DeltaPhi_Title, 1.0, -1.0,
                    balFct_Title, balFct_Minima[2], balFct_Maxima[2]);
      plotter->plot(balFct_Integral_DeltaY_Name,landscapeLogX, graphConfigurations1D, *balFct_LegendConfigs[3],
                    balFct1Bar2_Integral_DeltaY_Graphs,
                    DeltaY_Title, 0.1, maxRapidity,
                    balFct_Integral_Title, balFct_Minima[3], balFct_Maxima[3]);
      line->Draw();
      plotter->plot(balFct_IntegralSum_DeltaY_Name,landscapeLogX, graphConfigurations1D, *balFct_LegendConfigs[4],
                    balFct1Bar2_IntegralSum_DeltaY_Graphs,
                    DeltaY_Title, 0.1, maxRapidity,
                    balFct_IntegralSum_Title, balFct_Minima[4], balFct_Maxima[4]);
      line->Draw();

      }
    if (balFct12Bar_DeltaY_Histos.size()>0 && plot1D)
      {
      balFct_Title                   = "B^{#alpha#bar#beta}";
      balFct_Integral_Title          = "I^{#alpha#bar#beta}";
      balFct_IntegralSum_Title       = "#sum_{#alpha} I^{#alpha#bar#beta}";

      balFct_Name                    = "B12Bar";
      balFct_Integral_Name           = "I12Bar";
      balFct_IntegralSum_Name        = "I12BarSum";
      balFct_DeltaYDeltaPhi_Name     = makeName(prefix,balFct_Name, DeltaY_Name,DeltaPhi_Name);
      balFct_DeltaY_Name             = makeName(prefix,balFct_Name, DeltaY_Name);
      balFct_DeltaPhi_Name           = makeName(prefix,balFct_Name, DeltaPhi_Name);
      balFct_Integral_DeltaY_Name    = makeName(prefix,balFct_Integral_Name, DeltaY_Name);
      balFct_IntegralSum_DeltaY_Name = makeName(prefix,balFct_IntegralSum_Name, DeltaY_Name);

      createSumGraphs(balFct12Bar_Integral_DeltaY_Graphs,balFct12Bar_IntegralSum_DeltaY_Graphs);

      plotter->plot(balFct_DeltaY_Name,landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[1],
                    balFct12Bar_DeltaY_Histos,
                    DeltaY_Title, minRapidity, maxRapidity,
                    balFct_Title, balFct_Minima[1], balFct_Maxima[1]);
      plotter->plot(balFct_DeltaPhi_Name,landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[2],
                    balFct12Bar_DeltaPhi_Histos,
                    DeltaPhi_Title, 1.0, -1.0,
                    balFct_Title, balFct_Minima[2], balFct_Maxima[2]);
      plotter->plot(balFct_Integral_DeltaY_Name,landscapeLogX, graphConfigurations1D, *balFct_LegendConfigs[3],
                    balFct12Bar_Integral_DeltaY_Graphs,
                    DeltaY_Title, 0.1, maxRapidity,
                    balFct_Integral_Title, balFct_Minima[3], balFct_Maxima[3]);
      line->Draw();
      plotter->plot(balFct_IntegralSum_DeltaY_Name,landscapeLogX, graphConfigurations1D, *balFct_LegendConfigs[4],
                    balFct12Bar_IntegralSum_DeltaY_Graphs,
                    DeltaY_Title, 0.1, maxRapidity,
                    balFct_IntegralSum_Title, balFct_Minima[4], balFct_Maxima[4]);
      line->Draw();
      }
    if (balFct12s_DeltaY_Histos.size()>0 && plot1D)
      {
      balFct_Title                   = "B^{s}";
      balFct_Integral_Title          = "I^{s}";
      balFct_IntegralSum_Title       = "#sum I^{s}";

      balFct_Name                    = "B12s";
      balFct_Integral_Name           = "I12s";
      balFct_IntegralSum_Name        = "I12sSum";
      balFct_DeltaYDeltaPhi_Name     = makeName(prefix,balFct_Name, DeltaY_Name,DeltaPhi_Name);
      balFct_DeltaY_Name             = makeName(prefix,balFct_Name, DeltaY_Name);
      balFct_DeltaPhi_Name           = makeName(prefix,balFct_Name, DeltaPhi_Name);
      balFct_Integral_DeltaY_Name    = makeName(prefix,balFct_Integral_Name, DeltaY_Name);
      balFct_IntegralSum_DeltaY_Name = makeName(prefix,balFct_IntegralSum_Name, DeltaY_Name);

      createSumGraphs(balFct12s_Integral_DeltaY_Graphs,balFct12s_IntegralSum_DeltaY_Graphs);

      plotBf2D(bf)
      plotter->plot(balFct_DeltaY_Name,landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[1],
                    balFct12s_DeltaY_Histos,
                    DeltaY_Title, minRapidity, maxRapidity,
                    balFct_Title, balFct_Minima[1], balFct_Maxima[1]);
      plotter->plot(balFct_DeltaPhi_Name,landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[2],
                    balFct12s_DeltaPhi_Histos,
                    DeltaPhi_Title, 1.0, -1.0,
                    balFct_Title, balFct_Minima[2], balFct_Maxima[2]);
      plotter->plot(balFct_Integral_DeltaY_Name,landscapeLogX, graphConfigurations1D, *balFct_LegendConfigs[3],
                    balFct12s_Integral_DeltaY_Graphs,
                    DeltaY_Title, 0.1, maxRapidity,
                    balFct_Integral_Title, balFct_Minima[3], balFct_Maxima[3]);
      line->Draw();
      plotter->plot(balFct_IntegralSum_DeltaY_Name,landscapeLogX, graphConfigurations1D, *balFct_LegendConfigs[4],
                    balFct12s_IntegralSum_DeltaY_Graphs,
                    DeltaY_Title, 0.1, maxRapidity,
                    balFct_IntegralSum_Title, balFct_Minima[4], balFct_Maxima[4]);
      line->Draw();

      }
    }

  return 0;
}




// setOption == 0 B2 based BalcFct
// setOption == 1 A2 based BalcFct
//
void setBfOption(int setOption,
                 TString & outputPathBase,
                 TString & outputPath,
                 TString & outFileNameBase,
                 vector<TString> & corrNames,
                 vector<double>  & balFct_Minima,
                 vector<double>  & balFct_Maxima)
{
  switch (setOption)
    {
      case 0:
      {
      corrNames.push_back(TString("_B2_DyDphi_shft_B2_1Bar_2"));
      corrNames.push_back(TString("_B2_DyDphi_shft_B2_1_2Bar"));
      corrNames.push_back(TString("_B2_DyDphi_shft_B2_12Sum"));
      outputPath = outputPathBase;
      outputPath += "/PiKP/Y10/B2Derived/";
      outFileNameBase = "PYTHIA_pp_13.0TeV_B2Based";
      // B vs Y,Phi
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.4);
      // B vs Y
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.4);
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
      outFileNameBase = "PYTHIA_pp_13.0TeV_A2Based";
      corrNames.push_back(TString("_A2_DyDphi_shft_B2_1Bar_2"));
      corrNames.push_back(TString("_A2_DyDphi_shft_B2_1_2Bar"));
      corrNames.push_back(TString("_A2_DyDphi_shft_B2_12Sum"));
      outputPath = outputPathBase;
      outputPath += "/PiKP/Y10/A2Derived/";
      // B vs Y,Phi
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.4);
      // B vs Y
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.4);
      // B vs phi
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 0.24);
      // I vs Y
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 1.19);
      // Isum vs Y
      balFct_Minima.push_back(-0.05);
      balFct_Maxima.push_back( 1.19);
      // B width
      balFct_Minima.push_back( 0.00);
      balFct_Maxima.push_back( 1.19);
      }
    }
}





class BfPlotter
{
public:
// methods
  BfPlotter();
  ~BfPlotter();
  void plot();

  void selectSources(int option=0);
  void createSpeciesName(int speciesSet=0);
  void createAxisNames(int option = 0);
  void createObservableNames(int option);

  CAP::LegendConfiguration * createLegendConfiguration(float xLow, float xHigh,
                                                      float yLow, float yHigh,
                                                      float fontSize=0.05,
                                                      bool useLegend=true,
                                                      bool useLabels=true,
                                                      bool useTitles=true,
                                                       bool textIndex=42);

// data members
  bool doPrint  = true;
  bool printGif = 0;
  bool printPdf = 1;
  bool printPng = 0;
  bool printSvg = 0;
  bool printC   = 1;
  bool useColor = true;
  bool rebin             = false;
  int  rapidityType      = 1;
  bool doPlot1Bar2       = true;
  bool doPlot12Bar       = false;
  bool doPlot12s         = false;
  bool doPlotBf2D        = false;
  bool doPlotBfDy        = true;
  bool doPlotBfDphi      = false;
  bool doPlotIDy         = false;
  bool doPlotIsumDy      = false;
  bool doPlotBfWidthDphi = false;
  bool doPlotBfWidthDy   = false;
  int  plotIntegralVsLogY = 1;

  // 0 : HP, HM
  // 1 : Pi, K, P
  // 2 : Baryons
  // 3 : Strange particles
  int  speciesSet = 1;
  // 0 : B2 based correlations
  // 1 : A2 based correlations
  int  setOption = 1;


  TString inputPath;
  TString outputPathBase;
  TString outputPath;
  TString titleBase;
  TString histoNameBase;
  vector<TString> histoInputFileNames;
  vector<TString> balFct_DeltaYDeltaPhi_Histo_Names;
  vector<TString> balFct_DeltaY_Histo_Names;
  vector<TString> balFct_DeltaPhi_Histo_Names;
  vector<TString> balFct_Titles;
  vector<TString> balFct_Output_Names;
  vector<int>     balFct_Types; // 0, 1, 2 : B1Bar2, B12Bar, Bs
  vector<double>  balFct_Minima;
  vector<double>  balFct_Maxima;
  TString         outFileNameBase;
  TString         outFileNameBase2;
  TString         balFct_Output_Name;
  vector<TString> speciesNames;
  vector<TString> speciesTitles;
  vector<TString> corrNames;
  vector<CAP::LegendConfiguration*> balFct_LegendConfigs;

  vector<TString> bf_Names,
  vector<TString> bf_Integral_Names,
  vector<TString> bf_IntegralSum_Name,
  TString DeltaY_Name,
  TString DeltaPhi_Name,
  TString DeltaY_Title,
  TString DeltaPhi_Title
  TString DeltaYWidth_Title;
  TString DeltaPhiWidth_Title;

  vector<TString> & speciesNames;
  vector<TString> & speciesTitles;

  vector<TString> & corrNames;
  int iCorrType;
  vector<TString> & pairNames;
  vector<TString> & pairTitles;
  vector<TString> & pairNameCorrs;

  vector<double>  rmsWidths;
  vector<double>  rmsWidthErrors;

};

void BfPlotter::createSpeciesName(int speciesSet)
{
  switch (speciesSet)
    {
      case 0:
      speciesNames.push_back(TString("HP"));  speciesTitles.push_back(TString("h^{+}"));
      speciesNames.push_back(TString("HM"));  speciesTitles.push_back(TString("h^{+}"));
      break;

      case 1:
      speciesNames.push_back(TString("PiP"));  speciesTitles.push_back(TString("#pi^{+}"));
      speciesNames.push_back(TString("KP"));   speciesTitles.push_back(TString("K"));
      speciesNames.push_back(TString("PP"));   speciesTitles.push_back(TString("p"));
      speciesNames.push_back(TString("PiM"));  speciesTitles.push_back(TString("#pi"));
      speciesNames.push_back(TString("KM"));   speciesTitles.push_back(TString("K"));
      speciesNames.push_back(TString("PM"));   speciesTitles.push_back(TString("p"));
      break;

      case 2:
      break;
    }
}

void BfPlotter::createSpeciesPairNames()
{
  int nSpecies = speciesNames.size();
  for (int iSpecies2=0; iSpecies2<nSpecies; iSpecies2++)
    {
    for (int iSpecies1=0; iSpecies1<nSpecies; iSpecies1++)
      {
      TString pairName      = (speciesNames[iSpecies1]+"_")+speciesNames[iSpecies2];
      TString pairTitle     = speciesTitles[iSpecies1] + speciesTitles[iSpecies2];
      TString pairNameCorr  = pairName+corrNames[iCorrType];
      pairNames.push_back(pairName);
      pairTitles.push_back(pairTitle);
      pairNameCorrs.push_back(pairNameCorr);
      balFct_Titles.push_back(                     titleBase+pairTitle);
      balFct_Types.push_back(                      iCorrType);
      balFct_DeltaYDeltaPhi_Histo_Names.push_back( histoNameBase+pairNameCorr     );
      balFct_DeltaY_Histo_Names.push_back(         histoNameBase+pairNameCorr+"_x");
      balFct_DeltaPhi_Histo_Names.push_back(       histoNameBase+pairNameCorr+"_y");
      }
    }
}



void BfPlotter::selectSources(int option)
{
  switch (option)
    {
      case 1:
      {
      inputPath       = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/";
      histoInputFileNames.push_back(TString("PP/13000/PiKp/y10/PairGenBalFctSum0TO9.root"));
      outputPathBase  = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/";
      outputPath;
      titleBase       = "#sqrt{s}=13.0 TeV; ";
      histoNameBase   = "PairGen_All_";

      histoInputFileNames;
      vector<TString> balFct_DeltaYDeltaPhi_Histo_Names;
      vector<TString> balFct_DeltaY_Histo_Names;
      vector<TString> balFct_DeltaPhi_Histo_Names;
      vector<TString> balFct_Titles;
      vector<TString> balFct_Output_Names;
      vector<int>     balFct_Types; // 0, 1, 2 : B1Bar2, B12Bar, Bs
      vector<double>  balFct_Minima;
      vector<double>  balFct_Maxima;
      TString         outFileNameBase;
      TString         outFileNameBase2;
      TString         balFct_Output_Name;

      break;
      }
    }

}

void BfPlotter::createAxisNames(int option)
{
  switch (option)
    {
      case 0:
      DeltaY_Name          = "DeltaY";
      DeltaPhi_Name        = "DeltaPhi";
      DeltaY_Title         = "#Delta y";
      DeltaPhi_Title       = "#Delta #varphi";
      DeltaYWidth_Title    = "#sigma_{#Delta y}";
      DeltaPhiWidth_Title  = "#sigma_{#Delta #varphi}";
      break;

      case 1:
      DeltaY_Name          = "DeltaEta";
      DeltaPhi_Name        = "DeltaPhi";
      DeltaY_Title         = "#Delta #eta";
      DeltaPhi_Title       = "#Delta #varphi";
      DeltaYWidth_Title    = "#sigma_{#Delta #eta}";
      DeltaPhiWidth_Title  = "#sigma_{#Delta #varphi}";
      break;

    }
}


void BfPlotter::createObservableNames(int option)
{
  bf_Names.push_back(TString("B1Bar2"));
  bf_Names.push_back(TString("B12Bar"));
  bf_Names.push_back(TString("B12s"));

  bf_Integral_Names.push_back(TString("I1Bar2"));
  bf_Integral_Names.push_back(TString("I12Bar"));
  bf_Integral_Names.push_back(TString("I12s"));

  bf_IntegralSum_Names.push_back(TString("I1Bar2Sum"));
  bf_IntegralSum_Names.push_back(TString("I2BarSum"));
  bf_IntegralSum_Names.push_back(TString("I2sSum"));
}




CAP::LegendConfiguration * BfPlotter::createLegendConfiguration(float xLow, float xHigh,
                                                                float yLow, float yHigh,
                                                                float fontSize=0.05,
                                                                bool useLegend=true,
                                                                bool useLabels=true,
                                                                bool useTitles=true,
                                                                bool textIndex=42)
{
  lc = new CAP::LegendConfiguration(xLow,xHigh,yLow,yHigh,fontSize);
  lc->addParameter("useLegend",useLegend);
  lc->addParameter("useLabels",useLabels);
  lc->addParameter("useTitles",useTitles);
  lc->addParameter("textIndex",textIndex);
}

void plot()
{
  selectSources(sourceOption);
  setBfOption(setOption);
  createSpeciesName(speciesSet);
  createSpeciesPairNames();
  createAxisNames(axisOption);
  createObservableNames(observableNameOption);

}


int PlotBF_version3()
{
  TString includeBasePath = getenv("CAP_SRC");
  cout << "PlotBF() Loading *hpp and lib from: " << includeBasePath << endl;
  loadBase(includeBasePath);

  BfPlotter * bfPlotter = new BfPlotter();
  bfPlotter->sourceOption = 0;
  bfPlotter->setOption    = 0;
  bfPlotter->speciesSet = 0;
  bfPlotter->observableNameOption = 0;
  bfPlotter->plot();


  createSpeciesName(speciesSet, speciesNames, speciesTitles);
  setBfOption(setOption,outputPathBase, outputPath,outFileNameBase,corrNames,balFct_Minima,balFct_Maxima);

  createSpeciesPairNames(histoNameBase,
                         titleBase,
                         speciesNames,
                         speciesTitles,
                         corrNames,
                         iCorrType,
                         pairNames,
                         pairTitles,
                         pairNameCorrs,
                         balFct_Titles,
                         balFct_Types,
                         balFct_DeltaYDeltaPhi_Histo_Names,
                         balFct_DeltaY_Histo_Names,
                         balFct_DeltaPhi_Histo_Names);
  CAP::Configuration plotterConfig;
  CAP::Plotter * plotter = new CAP::Plotter("Plotter",plotterConfig);
  plotter->setDefaultOptions(useColor);



  for (int iType=2; iType<3; iType++)
    {

    for (int iSpecies2=0; iSpecies2<nSpecies; iSpecies2++)
      {
      outFileNameBase2 = outFileNameBase;
      outFileNameBase2 += (speciesNames[iSpecies2]);
      outFileNameBase2 += "_";
      histoInputFileNames.clear();
      balFct_Types.clear();
      balFct_DeltaYDeltaPhi_Histo_Names.clear();
      balFct_DeltaY_Histo_Names.clear();
      balFct_DeltaPhi_Histo_Names.clear();
      balFct_Output_Name = makeName(outFileNameBase,speciesNames[iSpecies2]);
      balFct_LegendConfigs.clear();

      // B2D, B vs Delta y, B vs Delta phi, I vs Delta y, Isum vs Delta y
      balFct_LegendConfigs.push_back( createLegendConfiguration(0.65, 0.85, 0.5, 0.9, 0.05,false,true,false,42) );
      balFct_LegendConfigs.push_back( createLegendConfiguration(0.65, 0.85, 0.5, 0.9, 0.05,true,true,false,42) );
      balFct_LegendConfigs.push_back( createLegendConfiguration(0.65, 0.85, 0.5, 0.9, 0.05,true,true,false,42) );
      balFct_LegendConfigs.push_back( createLegendConfiguration(0.20, 0.45, 0.5, 0.8, 0.06,true,true,false,42) );
      balFct_LegendConfigs.push_back( createLegendConfiguration(0.20, 0.45, 0.5, 0.8, 0.06,true,true,false,42) );





      CAP::CanvasConfiguration landscapeLinear(CAP::CanvasConfiguration::LandscapeWide,CAP::CanvasConfiguration::Linear);
      CAP::CanvasConfiguration landscapeLogX(CAP::CanvasConfiguration::Landscape,CAP::CanvasConfiguration::LogX);
      CAP::CanvasConfiguration landscapeLogY(CAP::CanvasConfiguration::LandscapeWide,CAP::CanvasConfiguration::LogY);
      vector<CAP::GraphConfiguration*>  graphConfigurations1D = createGraphConfigurationPalette(15,1);
      CAP::GraphConfiguration * graphConfiguration2D    = create2DGraphConfiguration(0.07);
      CAP::GraphConfiguration * widthGraphConfiguration = create1DGraphConfiguration();


      TString DeltaY_Name    = "DeltaY";
      TString DeltaPhi_Name  = "DeltaPhi";
      TString DeltaY_Title   = "#Delta y";
      TString DeltaPhi_Title = "#Delta #varphi";
      TString prefix = "";
      double minRapidity     = -20.0;
      double maxRapidity     =  20.0;
      double minRapidityInt  =  0.0;
      double maxRapidityInt  =  20.0;
      double etaLow   =  0.1;
      double etaHigh  =  maxRapidityInt-0.05;
      double etaStep  =  0.2;

      vector<BalFctPlots *>  bfPLots;

      if (doPlot1Bar2)
        {
        BalFctPlots * plots = new BalFctPlots();
        plots->addPlot(file, bf_rebin2D,
                       makeName(prefix,bf_Names[0], DeltaY_Name,DeltaPhi_Name);,
                       makeTitle(bf_DeltaYDeltaPhi_Title),
                       makeName(prefix,bf_Names[0], DeltaY_Name),
                       makeTitle(bf_DeltaYDeltaPhi_Title),
                       makeName(prefix,bf_Names[0], DeltaY_Name),
                       makeTitle(bf_DeltaYDeltaPhi_Title),
                       makeName(bf_Integral_DeltaY_Name),
                       makeName(bf_Integral_DeltaY_Title ));
        plots->loadHistograms();
        bfPLots.push_back(plots);
        }
      if (doPlot12Bar)
        {
        BalFctPlots * plots = new BalFctPlots();
        plots->addPlot(file, bf_rebin2D,
                       makeName(prefix,bf_Names[0], DeltaY_Name,DeltaPhi_Name);,
                       makeTitle(bf_DeltaYDeltaPhi_Title),
                       makeName(prefix,bf_Names[0], DeltaY_Name),
                       makeTitle(bf_DeltaYDeltaPhi_Title),
                       makeName(prefix,bf_Names[0], DeltaY_Name),
                       makeTitle(bf_DeltaYDeltaPhi_Title),
                       makeName(bf_Integral_DeltaY_Name),
                       makeName(bf_Integral_DeltaY_Title ));
        plots->loadHistograms();
        bfPLots.push_back(plots);
        }

      if (doPlot12s)
        {
        BalFctPlots * plots = new BalFctPlots();
        plots->addPlot(file, bf_rebin2D,
                       makeName(prefix,bf_Names[0], DeltaY_Name,DeltaPhi_Name);,
                       makeTitle(bf_DeltaYDeltaPhi_Title),
                       makeName(prefix,bf_Names[0], DeltaY_Name),
                       makeTitle(bf_DeltaYDeltaPhi_Title),
                       makeName(prefix,bf_Names[0], DeltaY_Name),
                       makeTitle(bf_DeltaYDeltaPhi_Title),
                       makeName(bf_Integral_DeltaY_Name),
                       makeName(bf_Integral_DeltaY_Title ));
        plots->loadHistograms();
        bfPLots.push_back(plots);
        }



      TString bfPlotBaseName = "Bftest";
      int nSets = bfPLots.size();
      for (int k=0;k<nSets;k++)
        {
        if (doPlotBf2D)        plotBf2D(bfPlotBaseName,bfPlots[k],landscapeLinear, graphConfigurations2D, *balFct_LegendConfigs[k]);
        if (doPlotBfDy)        plotBfDy(bfPlotBaseName,bfPlots[k],landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[k]);
        if (doPlotBfDphi)      plotBfDphi(bfPlotBaseName,bfPlots[k],landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[k]);
        if (doPlotIDy)         plotIDy(bfPlotBaseName,bfPlots[k],landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[k]);
        if (doPlotIsumDy)      plotIsumDy(bfPlotBaseName,bfPlots[k],landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[k]);
        if (doPlotBfWidthDphi) plotBfWidthDphi(bfPlotBaseName,bfPlots[k],landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[k]);
        if (doPlotBfWidthDy)   plotBfWidthDy(bfPlotBaseName,bfPlots[k],landscapeLinear, graphConfigurations1D, *balFct_LegendConfigs[k]);
        }

  if (doPrint) plotter->printAllCanvas(outputPath, printGif, printPdf, printSvg, printPng, printC);
  return 0;
}

void loadBase(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Base/";
  gSystem->Load(includePath+"Timer.hpp");
  gSystem->Load(includePath+"MessageLogger.hpp");
  gSystem->Load(includePath+"Task.hpp");
  gSystem->Load(includePath+"TaskIterator.hpp");
  gSystem->Load(includePath+"Collection.hpp");
  gSystem->Load(includePath+"HistogramCollection.hpp");
  gSystem->Load(includePath+"Histograms.hpp");
  gSystem->Load(includePath+"Particle.hpp");
  gSystem->Load(includePath+"ParticleType.hpp");
  gSystem->Load(includePath+"ParticleTypeCollection.hpp");
  gSystem->Load(includePath+"ParticleDecayMode.hpp");
  gSystem->Load(includePath+"Plotter.hpp");
  gSystem->Load(includePath+"DerivedHistoIterator.hpp");
  gSystem->Load("libBase.dylib");
}

void loadPlotting(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Plotting/";
  gSystem->Load(includePath+"CanvasCollection.hpp");
  gSystem->Load(includePath+"CanvasConfiguration.hpp");
  gSystem->Load(includePath+"GraphConfiguration..hpp");
  gSystem->Load(includePath+"LegendConfiguration.hpp");
  gSystem->Load(includePath+"Plotter.hpp");
  gSystem->Load("libPlotting.dylib");
}

