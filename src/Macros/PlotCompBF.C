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

int PlotCompBF()
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


  TString fileName1 = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Y2/PairGenBalFctSum0TO19.root";
  TString fileName2 = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Y6/PairGenBalFctSum0TO19.root";
  TString fileName3 = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Y10/PairGenBalFctSum0TO19.root";

  TString label1 = "PYTHIA; pp #sqrt{s}=13 TeV";

  TString outputPathNameBase = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Acceptance/";
  TString outputNameBase = "PYTHIA_Monash_pp_PiKP_A2Based_Deltay20_";

  TFile * file1 = TFile::Open(fileName1);
  TFile * file2 = TFile::Open(fileName2);
  TFile * file3 = TFile::Open(fileName3);
  if ( ! (file1->IsOpen() && file2->IsOpen() && file3->IsOpen() ))
    {
    cout << " file1: " << file1->IsOpen() << endl;
    cout << " file2: " << file2->IsOpen() << endl;
    cout << " file3: " << file3->IsOpen() << endl;
    }

  TH1 * aPiPiY2 = (TH1*) file1->Get("PairGen_All_PiP_PiP_A2_DyDphi_shft_B2_12Sum_x");
  TH1 * dPiPiY2 = (TH1*) file1->Get("PairGen_All_PiP_PiP_D2_DyDphi_shft_B2_12Sum_x");
  TH1 * rPiPiY2 = (TH1*) file1->Get("PairGen_All_PiP_PiP_R2_DyDphi_shft_B2_12Sum_x");

  TH1 * aPiPiY6 = (TH1*) file2->Get("PairGen_All_PiP_PiP_A2_DyDphi_shft_B2_12Sum_x");
  TH1 * dPiPiY6 = (TH1*) file2->Get("PairGen_All_PiP_PiP_D2_DyDphi_shft_B2_12Sum_x");
  TH1 * rPiPiY6 = (TH1*) file2->Get("PairGen_All_PiP_PiP_R2_DyDphi_shft_B2_12Sum_x");

  TH1 * aPiPiY10 = (TH1*) file3->Get("PairGen_All_PiP_PiP_A2_DyDphi_shft_B2_12Sum_x");
  TH1 * dPiPiY10 = (TH1*) file3->Get("PairGen_All_PiP_PiP_D2_DyDphi_shft_B2_12Sum_x");
  TH1 * rPiPiY10 = (TH1*) file3->Get("PairGen_All_PiP_PiP_R2_DyDphi_shft_B2_12Sum_x");

  rPiPiY2->Scale( aPiPiY2->GetBinContent(200)/rPiPiY2->GetBinContent(200));
  rPiPiY6->Scale( aPiPiY6->GetBinContent(200)/rPiPiY6->GetBinContent(200));
  rPiPiY10->Scale(aPiPiY10->GetBinContent(200)/rPiPiY10->GetBinContent(200));

  TH1 * ratio_aPiPiY2_aPiPiY10 = (TH1*) aPiPiY2->Clone();
  TH1 * ratio_aPiPiY6_aPiPiY10 = (TH1*) aPiPiY6->Clone();
  ratio_aPiPiY2_aPiPiY10->Divide(aPiPiY10);
  ratio_aPiPiY6_aPiPiY10->Divide(aPiPiY10);

  TH1 * ratio_dPiPiY2_aPiPiY10 = (TH1*) dPiPiY2->Clone();
  TH1 * ratio_dPiPiY6_aPiPiY10 = (TH1*) dPiPiY6->Clone();
  ratio_dPiPiY2_aPiPiY10->Divide(aPiPiY10);
  ratio_dPiPiY6_aPiPiY10->Divide(aPiPiY10);

  TH1 * ratio_rPiPiY2_aPiPiY10  = (TH1*) rPiPiY2->Clone();
  TH1 * ratio_rPiPiY6_aPiPiY10  = (TH1*) rPiPiY6->Clone();
  ratio_rPiPiY2_aPiPiY10->Divide(aPiPiY10);
  ratio_rPiPiY6_aPiPiY10->Divide(aPiPiY10);

  TH1 * ratio_aPiPiY2_rPiPiY2 = (TH1*) aPiPiY2->Clone();
  TH1 * ratio_dPiPiY2_rPiPiY2 = (TH1*) dPiPiY2->Clone();
  ratio_aPiPiY2_rPiPiY2->Divide(rPiPiY2);
  ratio_dPiPiY2_rPiPiY2->Divide(rPiPiY2);

  TH1 * ratio_aPiPiY6_rPiPiY6 = (TH1*) aPiPiY6->Clone();
  TH1 * ratio_dPiPiY6_rPiPiY6 = (TH1*) dPiPiY6->Clone();
  ratio_aPiPiY6_rPiPiY6->Divide(rPiPiY6);
  ratio_dPiPiY6_rPiPiY6->Divide(rPiPiY6);

  TH1 * ratio_aPiPiY10_rPiPiY10 = (TH1*) aPiPiY10->Clone();
  TH1 * ratio_dPiPiY10_rPiPiY10 = (TH1*) dPiPiY10->Clone();
  ratio_aPiPiY10_rPiPiY10->Divide(rPiPiY10);
  ratio_dPiPiY10_rPiPiY10->Divide(rPiPiY10);

// make plots
  vector<TH1*>    histos;


  CAP::LegendConfiguration * lc_ay2_ay6_ay10 = new CAP::LegendConfiguration(-4.5, -3.0, 0.1, 0.3, 0.04);
  lc_ay2_ay6_ay10->addParameter("useLegend",true);
  lc_ay2_ay6_ay10->addParameter("useLabels",true);
  lc_ay2_ay6_ay10->addParameter("useTitles",false);
  lc_ay2_ay6_ay10->addParameter("textIndex",42);
  lc_ay2_ay6_ay10->addParameter("nColumns",1);
  lc_ay2_ay6_ay10->addLegend("Y2 (A)");
  lc_ay2_ay6_ay10->addLegend("Y6 (A)");
  lc_ay2_ay6_ay10->addLegend("Y10 (A)");
  histos.clear();
  histos.push_back((TH1*)aPiPiY2->Clone());
  histos.push_back((TH1*)aPiPiY6->Clone());
  histos.push_back((TH1*)aPiPiY10->Clone());
  plotter->plot("PYTHIA13TeV_pp_aY2_aY6_ay10_NarrowY",
                landscapeLinear,gcs,*lc_ay2_ay6_ay10,histos,
                "#Delta y", -5.0, 5.0,
                "B^{s}(#pi#pi)", 0.0, 0.349);

  CAP::LegendConfiguration * lc_ay2_ay6_to_ay10 = new CAP::LegendConfiguration(-4.5, -3.0, 1.1, 1.5, 0.04);
  lc_ay2_ay6_to_ay10->addParameter("useLegend",true);
  lc_ay2_ay6_to_ay10->addParameter("useLabels",true);
  lc_ay2_ay6_to_ay10->addParameter("useTitles",false);
  lc_ay2_ay6_to_ay10->addParameter("textIndex",42);
  lc_ay2_ay6_to_ay10->addParameter("nColumns",1);
  lc_ay2_ay6_to_ay10->addLegend("Y2(A)/Y10(A)");
  lc_ay2_ay6_to_ay10->addLegend("Y6(A)/Y10(A)");
  histos.clear();
  histos.push_back(ratio_aPiPiY2_aPiPiY10);
  histos.push_back(ratio_aPiPiY6_aPiPiY10);
  plotter->plot("PYTHIA13TeV_pp_aY2_aY6_to_ay10_NarrowY",
                landscapeLinear,gcs,*lc_ay2_ay6_to_ay10,histos,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.99);


  // y2
  CAP::LegendConfiguration * lc_ay2_dy2_ry2 = new CAP::LegendConfiguration(-4.5, -3.0, 0.1, 0.3, 0.04);
  lc_ay2_dy2_ry2->addParameter("useLegend",true);
  lc_ay2_dy2_ry2->addParameter("useLabels",true);
  lc_ay2_dy2_ry2->addParameter("useTitles",false);
  lc_ay2_dy2_ry2->addParameter("textIndex",42);
  lc_ay2_dy2_ry2->addParameter("nColumns",1);
  lc_ay2_dy2_ry2->addLegend("Y2(A)");
  lc_ay2_dy2_ry2->addLegend("Y2(D)");
  lc_ay2_dy2_ry2->addLegend("Y2(R)");
  histos.clear();
  histos.push_back((TH1*)aPiPiY2->Clone());
  histos.push_back((TH1*)dPiPiY2->Clone());
  histos.push_back((TH1*)rPiPiY2->Clone());
  plotter->plot("PYTHIA13TeV_pp_aY2_dY2_ry2_NarrowY",
                landscapeLinear,gcs,*lc_ay2_dy2_ry2,histos,
                "#Delta y", -5.0, 5.0,
                "B^{s}(#pi#pi)", 0.0, 0.349);

  CAP::LegendConfiguration * lc_ay2_dy2_to_ry2 = new CAP::LegendConfiguration(-1.5, 1.5, 1.1, 1.5, 0.04);
  lc_ay2_dy2_to_ry2->addParameter("useLegend",true);
  lc_ay2_dy2_to_ry2->addParameter("useLabels",true);
  lc_ay2_dy2_to_ry2->addParameter("useTitles",false);
  lc_ay2_dy2_to_ry2->addParameter("textIndex",42);
  lc_ay2_dy2_to_ry2->addParameter("nColumns",1);
  lc_ay2_dy2_to_ry2->addLegend("Y2(A)/Y2(R)");
  lc_ay2_dy2_to_ry2->addLegend("Y2(D)/Y2(R)");
  histos.clear();
  histos.push_back(ratio_aPiPiY2_rPiPiY2);
  histos.push_back(ratio_dPiPiY2_rPiPiY2);
  plotter->plot("PYTHIA13TeV_pp_aY2_dY2_to_ry2_NarrowY",
                landscapeLinear,gcs,*lc_ay2_dy2_to_ry2,histos,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.99);

  // y6
  CAP::LegendConfiguration * lc_ay6_dy6_ry6 = new CAP::LegendConfiguration(-4.5, -3.0, 0.1, 0.3, 0.04);
  lc_ay6_dy6_ry6->addParameter("useLegend",true);
  lc_ay6_dy6_ry6->addParameter("useLabels",true);
  lc_ay6_dy6_ry6->addParameter("useTitles",false);
  lc_ay6_dy6_ry6->addParameter("textIndex",42);
  lc_ay6_dy6_ry6->addParameter("nColumns",1);
  lc_ay6_dy6_ry6->addLegend("Y6(A)");
  lc_ay6_dy6_ry6->addLegend("Y6(D)");
  lc_ay6_dy6_ry6->addLegend("Y6(R)");
  histos.clear();
  histos.push_back(aPiPiY6);
  histos.push_back(dPiPiY6);
  histos.push_back(rPiPiY6);
  plotter->plot("PYTHIA13TeV_pp_aY6_dY6_ry6_NarrowY",
                landscapeLinear,gcs,*lc_ay6_dy6_ry6,histos,
                "#Delta y", -5.0, 5.0,
                "B^{s}(#pi#pi)", 0.0, 0.349);

  CAP::LegendConfiguration * lc_ay6_dy6_to_ry6 = new CAP::LegendConfiguration(-1.5, 1.5, 1.1, 1.5, 0.04);
  lc_ay6_dy6_to_ry6->addParameter("useLegend",true);
  lc_ay6_dy6_to_ry6->addParameter("useLabels",true);
  lc_ay6_dy6_to_ry6->addParameter("useTitles",false);
  lc_ay6_dy6_to_ry6->addParameter("textIndex",42);
  lc_ay6_dy6_to_ry6->addParameter("nColumns",1);
  lc_ay6_dy6_to_ry6->addLegend("Y6(A)/Y6(R)");
  lc_ay6_dy6_to_ry6->addLegend("Y6(D)/Y6(R)");
  histos.clear();
  histos.push_back(ratio_aPiPiY6_rPiPiY6);
  histos.push_back(ratio_dPiPiY6_rPiPiY6);
  plotter->plot("PYTHIA13TeV_pp_aY6_dY6_to_ry6_NarrowY",
                landscapeLinear,gcs,*lc_ay6_dy6_to_ry6,histos,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.99);


  // y10
  CAP::LegendConfiguration * lc_ay10_dy10_ry10 = new CAP::LegendConfiguration(-4.5, -3.0, 0.1, 0.3, 0.04);
  lc_ay10_dy10_ry10->addParameter("useLegend",true);
  lc_ay10_dy10_ry10->addParameter("useLabels",true);
  lc_ay10_dy10_ry10->addParameter("useTitles",false);
  lc_ay10_dy10_ry10->addParameter("textIndex",42);
  lc_ay10_dy10_ry10->addParameter("nColumns",1);
  lc_ay10_dy10_ry10->addLegend("Y10(A)");
  lc_ay10_dy10_ry10->addLegend("Y10(D)");
  lc_ay10_dy10_ry10->addLegend("Y10(R)");
  histos.clear();
  histos.push_back(aPiPiY10);
  histos.push_back(dPiPiY10);
  histos.push_back(rPiPiY10);
  plotter->plot("PYTHIA13TeV_pp_aY10_dY10_ry10_NarrowY",
                landscapeLinear,gcs,*lc_ay10_dy10_ry10,histos,
                "#Delta y", -5.0, 5.0,
                "B^{s}(#pi#pi)", 0.0, 0.349);

  CAP::LegendConfiguration * lc_ay10_dy10_to_ry10 = new CAP::LegendConfiguration(-1.5, 1.5, 1.1, 1.5, 0.04);
  lc_ay10_dy10_to_ry10->addParameter("useLegend",true);
  lc_ay10_dy10_to_ry10->addParameter("useLabels",true);
  lc_ay10_dy10_to_ry10->addParameter("useTitles",false);
  lc_ay10_dy10_to_ry10->addParameter("textIndex",42);
  lc_ay10_dy10_to_ry10->addParameter("nColumns",1);
  lc_ay10_dy10_to_ry10->addLegend("Y10(A)/Y10(R)");
  lc_ay10_dy10_to_ry10->addLegend("Y10(D)/Y10(R)");
  histos.clear();
  histos.push_back(ratio_aPiPiY10_rPiPiY10);
  histos.push_back(ratio_dPiPiY10_rPiPiY10);
  plotter->plot("PYTHIA13TeV_pp_aY10_dY10_to_ry10_NarrowY",
                landscapeLinear,gcs,*lc_ay10_dy10_to_ry10,histos,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.99);


  // y2 y6 y10 based on D
  CAP::LegendConfiguration * lc_dy2_dy6_ay10 = new CAP::LegendConfiguration(-4.5, -3.0, 0.1, 0.3, 0.04);
  lc_dy2_dy6_ay10->addParameter("useLegend",true);
  lc_dy2_dy6_ay10->addParameter("useLabels",true);
  lc_dy2_dy6_ay10->addParameter("useTitles",false);
  lc_dy2_dy6_ay10->addParameter("textIndex",42);
  lc_dy2_dy6_ay10->addParameter("nColumns",1);
  lc_dy2_dy6_ay10->addLegend("Y2(D)");
  lc_dy2_dy6_ay10->addLegend("Y6(D)");
  lc_dy2_dy6_ay10->addLegend("Y10(A)");
  histos.clear();
  histos.push_back((TH1*)dPiPiY2->Clone());
  histos.push_back((TH1*)dPiPiY6->Clone());
  histos.push_back((TH1*)aPiPiY10->Clone());
  plotter->plot("PYTHIA13TeV_pp_dy2_dy6_ay10_NarrowY",
                landscapeLinear,gcs,*lc_dy2_dy6_ay10,histos,
                "#Delta y", -5.0, 5.0,
                "B^{s}(#pi#pi)", 0.0, 0.349);

  CAP::LegendConfiguration * lc_dy2_dy6_to_ay10 = new CAP::LegendConfiguration(-1.5, 1.5, 1.1, 1.5, 0.04);
  lc_dy2_dy6_to_ay10->addParameter("useLegend",true);
  lc_dy2_dy6_to_ay10->addParameter("useLabels",true);
  lc_dy2_dy6_to_ay10->addParameter("useTitles",false);
  lc_dy2_dy6_to_ay10->addParameter("textIndex",42);
  lc_dy2_dy6_to_ay10->addParameter("nColumns",1);
  lc_dy2_dy6_to_ay10->addLegend("Y2(D)/Y10(A)");
  lc_dy2_dy6_to_ay10->addLegend("Y6(D)/Y10(A)");
  histos.clear();
  histos.push_back(ratio_dPiPiY2_aPiPiY10);
  histos.push_back(ratio_dPiPiY6_aPiPiY10);
  plotter->plot("PYTHIA13TeV_pp_dy2_dy6_to_ay10_NarrowY",
                landscapeLinear,gcs,*lc_dy2_dy6_to_ay10,histos,
                "#Delta y", -5.0, 5.0,
                "Ratio", 0.0, 1.99);

  // y2 y6 y10 based on R
  CAP::LegendConfiguration * lc_ry2_ry6_ay10 = new CAP::LegendConfiguration(-4.5, -3.0, 0.1, 0.3, 0.04);
  lc_ry2_ry6_ay10->addParameter("useLegend",true);
  lc_ry2_ry6_ay10->addParameter("useLabels",true);
  lc_ry2_ry6_ay10->addParameter("useTitles",false);
  lc_ry2_ry6_ay10->addParameter("textIndex",42);
  lc_ry2_ry6_ay10->addParameter("nColumns",1);
  lc_ry2_ry6_ay10->addLegend("Y2(R)");
  lc_ry2_ry6_ay10->addLegend("Y6(R)");
  lc_ry2_ry6_ay10->addLegend("Y10(A)");
  histos.clear();
  histos.push_back((TH1*)rPiPiY2->Clone());
  histos.push_back((TH1*)rPiPiY6->Clone());
  histos.push_back((TH1*)aPiPiY10->Clone());
  plotter->plot("PYTHIA13TeV_pp_ry2_ry6_ay10_NarrowY",
                landscapeLinear,gcs,*lc_ry2_ry6_ay10,histos,
                "#Delta y", -10.0, 10.0,
                "B^{s}(#pi#pi)", 0.0, 0.349);

  CAP::LegendConfiguration * lc_ry2_ry6_to_ay10 = new CAP::LegendConfiguration(-1.5, 1.5, 1.1, 1.5, 0.04);
  lc_ry2_ry6_to_ay10->addParameter("useLegend",true);
  lc_ry2_ry6_to_ay10->addParameter("useLabels",true);
  lc_ry2_ry6_to_ay10->addParameter("useTitles",false);
  lc_ry2_ry6_to_ay10->addParameter("textIndex",42);
  lc_ry2_ry6_to_ay10->addParameter("nColumns",1);
  lc_ry2_ry6_to_ay10->addLegend("Y2(R)/Y10(A)");
  lc_ry2_ry6_to_ay10->addLegend("Y6(R)/Y10(A)");
  histos.clear();
  histos.push_back(ratio_rPiPiY2_aPiPiY10);
  histos.push_back(ratio_rPiPiY6_aPiPiY10);
  plotter->plot("PYTHIA13TeV_pp_ry2_ry6_to_ay10_NarrowY",
                landscapeLinear,gcs,*lc_ry2_ry6_to_ay10,histos,
                "#Delta y", -10.0, 10.0,
                "Ratio", 0.0, 1.99);

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

