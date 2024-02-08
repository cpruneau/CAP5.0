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
void loadBase(const TString & includeBasePath);
void loadPlotting(const TString & includeBasePath);

int PlotCompBF2()
{
  TString includeBasePath = getenv("CAP_SRC");
  loadBase(includeBasePath);
  loadPlotting(includeBasePath);

  bool printGif = 0;
  bool printPdf = 1;
  bool printSvg = 0;
  bool printC   = 0;
  bool printPng = 0;
  bool useColor = true;
  CAP::Plotter * plotter = new CAP::Plotter();
  plotter->setDefaultOptions(useColor);

  CAP::CanvasConfiguration landscapeLinear(CAP::CanvasConfiguration::LandscapeWide,CAP::CanvasConfiguration::Linear);
  CAP::CanvasConfiguration landscapeLogY(CAP::CanvasConfiguration::LandscapeWide,CAP::CanvasConfiguration::LogY);
  vector<CAP::GraphConfiguration*>  gcs = plotter->createGraphConfigurationPalette(16,1);

  vector<TString> fileNames;
  vector<TFile *> files;
  vector<TH1 *>   aHistos;
  vector<TH1 *>   dHistos;
  vector<TH1 *>   rHistos;
  vector<TH1 *>   aRatiosToA10;
  vector<TH1 *>   dRatiosToA10;
  vector<TH1 *>   rRatiosToA10;
  vector<TH1 *>   dRatiosToD10;
  vector<TH1 *>   rRatiosToR10;
  vector<TH1 *>   aRatiosToR;
  vector<TH1 *>   dRatiosToR;

  fileNames.push_back(TString("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PM/Y1.5/PairGenBalFctSum0TO19.root"));
  fileNames.push_back(TString("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PM/Y1.8/PairGenBalFctSum0TO19.root"));
  fileNames.push_back(TString("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PM/Y2.5/PairGenBalFctSum0TO19.root"));
  fileNames.push_back(TString("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PM/Y4/PairGenBalFctSum0TO19.root"));
  fileNames.push_back(TString("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PM/Y6/PairGenBalFctSum0TO19.root"));
  fileNames.push_back(TString("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PM/Y10/PairGenBalFctSum0TO19.root"));

  TString label1 = "PYTHIA; pp #sqrt{s}=13 TeV";
  TString outputPathNameBase = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PM/Acceptance/";
  TString outputNameBase = "PYTHIA_Monash_pp_PM_A2Based_Deltay20_";

  //
  // load histograms
  //
  for (unsigned int iFile=0; iFile<fileNames.size(); iFile++)
    {
    TString name = fileNames[iFile];
    TFile * file = TFile::Open(name);
    if (!file ||  ! file->IsOpen() )
      {
      cout << " File not found: " << name << endl;
      return 1;
      }
    else
      {
      cout << " Opened: " << name << endl;
      }
    TH1 * a = (TH1*) file->Get("PairGen_All_HP_HP_A2_DyDphi_shft_B2_12Sum_x");
    if (!a)
      {
      cout << " Histo not found: PairGen_All_HP_HP_A2_DyDphi_shft_B2_12Sum_x" << endl;
      return 1;
      }
    aHistos.push_back(a);
    TH1 * d = (TH1*) file->Get("PairGen_All_HP_HP_D2_DyDphi_shft_B2_12Sum_x");
    if (!d)
      {
      cout << " Histo not found: PairGen_All_HP_HP_D2_DyDphi_shft_B2_12Sum_x" << endl;
      return 1;
      }
    dHistos.push_back(d);
    TH1 * r = (TH1*) file->Get("PairGen_All_HP_HP_R2_DyDphi_shft_B2_12Sum_x");
    if (!r)
      {
      cout << " Histo not found: PairGen_All_HP_HP_R2_DyDphi_shft_B2_12Sum_x" << endl;
      return 1;
      }
    rHistos.push_back(d);
    r->Scale( a->GetBinContent(200)/r->GetBinContent(200));
    }

  //
  // compute ratios
  //
  unsigned int n = fileNames.size();
  for (unsigned int iFile=0; iFile<n; iFile++)
    {
    TH1 * aRatioToA10 = (TH1*) aHistos[iFile]->Clone();
    aRatioToA10->Divide(aHistos[n-1]);
    aRatiosToA10.push_back(aRatioToA10);

    TH1 * dRatioToA10 = (TH1*) dHistos[iFile]->Clone();
    dRatioToA10->Divide(aHistos[n-1]);
    dRatiosToA10.push_back(dRatioToA10);

    TH1 * rRatioToA10 = (TH1*) rHistos[iFile]->Clone();
    rRatioToA10->Divide(aHistos[n-1]);
    rRatiosToA10.push_back(rRatioToA10);

    TH1 * dRatioToD10 = (TH1*) dHistos[iFile]->Clone();
    dRatioToD10->Divide(dHistos[n-1]);
    dRatiosToD10.push_back(dRatioToD10);

    TH1 * rRatioToR10 = (TH1*) rHistos[iFile]->Clone();
    rRatioToR10->Divide(rHistos[n-1]);
    rRatiosToR10.push_back(rRatioToR10);

    TH1 * aRatioToR = (TH1*) aHistos[iFile]->Clone();
    aRatioToR->Divide(rHistos[iFile]);
    aRatiosToR.push_back(aRatioToR);

    TH1 * dRatioToR = (TH1*) dHistos[iFile]->Clone();
    dRatioToR->Divide(rHistos[iFile]);
    dRatiosToR.push_back(dRatioToR);
    }


  CAP::LegendConfiguration * lc_aVsY = new CAP::LegendConfiguration(-4.5, -3.0, 0.1, 0.3, 0.04);
  lc_aVsY->addParameter("useLegend",true);
  lc_aVsY->addParameter("useLabels",true);
  lc_aVsY->addParameter("useTitles",false);
  lc_aVsY->addParameter("textIndex",42);
  lc_aVsY->addParameter("nColumns",1);
  lc_aVsY->addLegend("Y1.5 (A)");
  lc_aVsY->addLegend("Y1.8 (A)");
  lc_aVsY->addLegend("Y2.5 (A)");
  lc_aVsY->addLegend("Y4 (A)");
  lc_aVsY->addLegend("Y6 (A)");
  lc_aVsY->addLegend("Y10 (A)");
  plotter->plot("PYTHIA13TeV_pp_aVsY_NarrowY",
                landscapeLinear,gcs,*lc_aVsY,aHistos,
                "#Delta y", -5.0, 5.0,
                "B^{s}(+-)", 0.0, 0.449);

  CAP::LegendConfiguration * lc_dVsY = new CAP::LegendConfiguration(-4.5, -3.0, 0.1, 0.3, 0.04);
  lc_dVsY->addParameter("useLegend",true);
  lc_dVsY->addParameter("useLabels",true);
  lc_dVsY->addParameter("useTitles",false);
  lc_dVsY->addParameter("textIndex",42);
  lc_dVsY->addParameter("nColumns",1);
  lc_dVsY->addLegend("Y1.5 (D)");
  lc_dVsY->addLegend("Y1.8 (D)");
  lc_dVsY->addLegend("Y2.5 (D)");
  lc_dVsY->addLegend("Y4 (D)");
  lc_dVsY->addLegend("Y6 (D)");
  lc_dVsY->addLegend("Y10 (D)");
  plotter->plot("PYTHIA13TeV_pp_dVsY_NarrowY",
                landscapeLinear,gcs,*lc_dVsY,dHistos,
                "#Delta y", -5.0, 5.0,
                "B^{s}(+-)", 0.0, 0.449);

  CAP::LegendConfiguration * lc_rVsY = new CAP::LegendConfiguration(-4.5, -3.0, 0.1, 0.3, 0.04);
  lc_rVsY->addParameter("useLegend",true);
  lc_rVsY->addParameter("useLabels",true);
  lc_rVsY->addParameter("useTitles",false);
  lc_rVsY->addParameter("textIndex",42);
  lc_rVsY->addParameter("nColumns",1);
  lc_rVsY->addLegend("Y1.5 (R)");
  lc_rVsY->addLegend("Y1.8 (R)");
  lc_rVsY->addLegend("Y2.5 (R)");
  lc_rVsY->addLegend("Y4 (R)");
  lc_rVsY->addLegend("Y6 (R)");
  lc_rVsY->addLegend("Y10 (R)");
  plotter->plot("PYTHIA13TeV_pp_rVsY_NarrowY",
                landscapeLinear,gcs,*lc_rVsY,rHistos,
                "#Delta y", -5.0, 5.0,
                "B^{s}(+-)", 0.0, 0.449);

  if (true) plotter->printAllCanvas(outputPathNameBase, printGif, printPdf, printSvg, printPng, printC);
  return 0;
}

void loadBase(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Base/";
  gSystem->Load(includePath+"Exceptions.hpp");
  gSystem->Load(includePath+"Timer.hpp");
  gSystem->Load(includePath+"MessageLogger.hpp");
  gSystem->Load(includePath+"Task.hpp");
  gSystem->Load(includePath+"Collection.hpp");
  gSystem->Load(includePath+"HistogramCollection.hpp");
  gSystem->Load(includePath+"HistogramGroup.hpp");
  gSystem->Load("libBase.dylib");
}

void loadPlotting(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Plotting/";
  gSystem->Load(includePath+"CanvasCollection.hpp");
  gSystem->Load(includePath+"GraphConfiguration.hpp");
  gSystem->Load(includePath+"CanvasConfiguration.hpp");
  gSystem->Load(includePath+"Plotter.hpp");
  gSystem->Load(includePath+"BalFctPlotter.hpp");
  gSystem->Load("libPlotting.dylib");
}

