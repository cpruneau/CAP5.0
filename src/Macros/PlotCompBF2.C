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
  vector<TH1 *>   aRatiosToA25;
  vector<TH1 *>   rRatiosToR25;
  vector<TH1 *>   dRatiosToD25;

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

  for (unsigned int iFile=0; iFile<4; iFile++)
    {
    TH1 * aRatioToA25 = (TH1*) aHistos[iFile]->Clone();
    aRatioToA25->Divide(aHistos[2]);
    aRatiosToA25.push_back(aRatioToA25);

    TH1 * dRatioToD25 = (TH1*) dHistos[iFile]->Clone();
    dRatioToD25->Divide(dHistos[2]);
    dRatiosToD25.push_back(dRatioToD25);

    TH1 * rRatioToR25 = (TH1*) rHistos[iFile]->Clone();
    rRatioToR25->Divide(rHistos[2]);
    rRatiosToR25.push_back(rRatioToR25);
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

  CAP::LegendConfiguration * lc_aToA10 = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_aToA10->addParameter("useLegend",true);
  lc_aToA10->addParameter("useLabels",true);
  lc_aToA10->addParameter("useTitles",false);
  lc_aToA10->addParameter("textIndex",42);
  lc_aToA10->addParameter("nColumns",1);
  lc_aToA10->addLegend("A(1.5)/A(10)");
  lc_aToA10->addLegend("A(1.8)/A(10)");
  lc_aToA10->addLegend("A(2.5)/A(10)");
  lc_aToA10->addLegend("A(4)/A(10)");
  lc_aToA10->addLegend("A(6)/A(10)");
  lc_aToA10->addLegend("A(10)/A(10)");
  plotter->plot("PYTHIA13TeV_pp_aToA10_NarrowY",
                landscapeLinear,gcs,*lc_aToA10,aRatiosToA10,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.449);

  CAP::LegendConfiguration * lc_dToA10 = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_dToA10->addParameter("useLegend",true);
  lc_dToA10->addParameter("useLabels",true);
  lc_dToA10->addParameter("useTitles",false);
  lc_dToA10->addParameter("textIndex",42);
  lc_dToA10->addParameter("nColumns",1);
  lc_dToA10->addLegend("D(1.5)/A(10)");
  lc_dToA10->addLegend("D(1.8)/A(10)");
  lc_dToA10->addLegend("D(2.5)/A(10)");
  lc_dToA10->addLegend("D(4)/A(10)");
  lc_dToA10->addLegend("D(6)/A(10)");
  lc_dToA10->addLegend("D(10)/A(10)");
  plotter->plot("PYTHIA13TeV_pp_dToA10_NarrowY",
                landscapeLinear,gcs,*lc_dToA10,dRatiosToA10,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.449);

  CAP::LegendConfiguration * lc_rToA10 = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_rToA10->addParameter("useLegend",true);
  lc_rToA10->addParameter("useLabels",true);
  lc_rToA10->addParameter("useTitles",false);
  lc_rToA10->addParameter("textIndex",42);
  lc_rToA10->addParameter("nColumns",1);
  lc_rToA10->addLegend("R(1.5)/A(10)");
  lc_rToA10->addLegend("R(1.8)/A(10)");
  lc_rToA10->addLegend("R(2.5)/A(10)");
  lc_rToA10->addLegend("R(4)/A(10)");
  lc_rToA10->addLegend("R(6)/A(10)");
  lc_rToA10->addLegend("R(10)/A(10)");
  plotter->plot("PYTHIA13TeV_pp_rToA10_NarrowY",
                landscapeLinear,gcs,*lc_rToA10,rRatiosToA10,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.449);

  CAP::LegendConfiguration * lc_dToD10 = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_dToD10->addParameter("useLegend",true);
  lc_dToD10->addParameter("useLabels",true);
  lc_dToD10->addParameter("useTitles",false);
  lc_dToD10->addParameter("textIndex",42);
  lc_dToD10->addParameter("nColumns",1);
  lc_dToD10->addLegend("D(1.5)/D(10)");
  lc_dToD10->addLegend("D(1.8)/D(10)");
  lc_dToD10->addLegend("D(2.5)/D(10)");
  lc_dToD10->addLegend("D(4)/D(10)");
  lc_dToD10->addLegend("D(6)/D(10)");
  lc_dToD10->addLegend("D(10)/D(10)");
  plotter->plot("PYTHIA13TeV_pp_dToD10_NarrowY",
                landscapeLinear,gcs,*lc_dToD10,dRatiosToD10,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.449);

  CAP::LegendConfiguration * lc_rToR10 = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_rToR10->addParameter("useLegend",true);
  lc_rToR10->addParameter("useLabels",true);
  lc_rToR10->addParameter("useTitles",false);
  lc_rToR10->addParameter("textIndex",42);
  lc_rToR10->addParameter("nColumns",1);
  lc_rToR10->addLegend("R(1.5)/R(10)");
  lc_rToR10->addLegend("R(1.8)/R(10)");
  lc_rToR10->addLegend("R(2.5)/R(10)");
  lc_rToR10->addLegend("R(4)/R(10)");
  lc_rToR10->addLegend("R(6)/R(10)");
  lc_rToR10->addLegend("R(10)/R(10)");
  plotter->plot("PYTHIA13TeV_pp_rToR10_NarrowY",
                landscapeLinear,gcs,*lc_rToR10,rRatiosToR10,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.449);

  CAP::LegendConfiguration * lc_aToR = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_aToR->addParameter("useLegend",true);
  lc_aToR->addParameter("useLabels",true);
  lc_aToR->addParameter("useTitles",false);
  lc_aToR->addParameter("textIndex",42);
  lc_aToR->addParameter("nColumns",1);
  lc_aToR->addLegend("A(1.5)/R(1.5)");
  lc_aToR->addLegend("A(1.8)/R(1.8)");
  lc_aToR->addLegend("A(2.5)/R(2.5)");
  lc_aToR->addLegend("A(4)/R(4)");
  lc_aToR->addLegend("A(6)/R(6)");
  lc_aToR->addLegend("A(10)/R(10)");
  plotter->plot("PYTHIA13TeV_pp_aToR_NarrowY",
                landscapeLinear,gcs,*lc_aToR,aRatiosToR,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.449);

  CAP::LegendConfiguration * lc_dToR = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_dToR->addParameter("useLegend",true);
  lc_dToR->addParameter("useLabels",true);
  lc_dToR->addParameter("useTitles",false);
  lc_dToR->addParameter("textIndex",42);
  lc_dToR->addParameter("nColumns",1);
  lc_dToR->addLegend("D(1.5)/R(1.5)");
  lc_dToR->addLegend("D(1.8)/R(1.8)");
  lc_dToR->addLegend("D(2.5)/R(2.5)");
  lc_dToR->addLegend("D(4)/R(4)");
  lc_dToR->addLegend("D(6)/R(6)");
  lc_dToR->addLegend("D(10)/R(10)");
  plotter->plot("PYTHIA13TeV_pp_dToR_NarrowY",
                landscapeLinear,gcs,*lc_dToR,dRatiosToR,
                "#Delta y", -2.0, 2.0,
                "Ratio", 0.9, 1.1);

  CAP::LegendConfiguration * lc_aToA25 = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_aToA25->addParameter("useLegend",true);
  lc_aToA25->addParameter("useLabels",true);
  lc_aToA25->addParameter("useTitles",false);
  lc_aToA25->addParameter("textIndex",42);
  lc_aToA25->addParameter("nColumns",1);
  lc_aToA25->addLegend("A(1.5)/A(2.5)");
  lc_aToA25->addLegend("A(1.8)/A(2.5)");
  lc_aToA25->addLegend("A(2.5)/A(2.5)");
  lc_aToA25->addLegend("A(4)/A(2.5)");
  plotter->plot("PYTHIA13TeV_pp_aToR25_NarrowY",
                landscapeLinear,gcs,*lc_aToA25,aRatiosToA25,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.1);

  CAP::LegendConfiguration * lc_dToD25 = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_dToD25->addParameter("useLegend",true);
  lc_dToD25->addParameter("useLabels",true);
  lc_dToD25->addParameter("useTitles",false);
  lc_dToD25->addParameter("textIndex",42);
  lc_dToD25->addParameter("nColumns",1);
  lc_dToD25->addLegend("D(1.5)/D(2.5)");
  lc_dToD25->addLegend("D(1.8)/D(2.5)");
  lc_dToD25->addLegend("D(2.5)/D(2.5)");
  lc_dToD25->addLegend("D(4)/D(2.5)");
  plotter->plot("PYTHIA13TeV_pp_dToD25_NarrowY",
                landscapeLinear,gcs,*lc_dToD25,dRatiosToD25,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.1);

  CAP::LegendConfiguration * lc_rToR25 = new CAP::LegendConfiguration(-1.5, 1.5, 0.1, 0.5, 0.04);
  lc_rToR25->addParameter("useLegend",true);
  lc_rToR25->addParameter("useLabels",true);
  lc_rToR25->addParameter("useTitles",false);
  lc_rToR25->addParameter("textIndex",42);
  lc_rToR25->addParameter("nColumns",1);
  lc_rToR25->addLegend("R(1.5)/R(2.5)");
  lc_rToR25->addLegend("R(1.8)/R(2.5)");
  lc_rToR25->addLegend("R(2.5)/R(2.5)");
  lc_rToR25->addLegend("R(4)/R(2.5)");
  plotter->plot("PYTHIA13TeV_pp_rToR25_NarrowY",
                landscapeLinear,gcs,*lc_rToR25,rRatiosToR25,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.1);

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

