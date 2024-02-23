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

int PlotBF(int choice = 1)
{
  const bool YES = true;
  const bool NO  = false;

  TString includeBasePath = getenv("CAP_SRC");
  loadBase(includeBasePath);
  loadPlotting(includeBasePath);

  double bf_DeltaYDeltPhiMin;
  double bf_DeltaYDeltPhiMax;
  double bf_DeltaYMin;
  double bf_DeltaYMax;
  double bf_DeltPhiMin;
  double bf_DeltPhiMax;
  double bf_Integral_DeltaYMin;
  double bf_Integral_DeltaYMax;
  double bf_IntegralSum_DeltaYMin;
  double bf_IntegralSum_DeltaYMax;
  double bf_Width_DeltaYMin;
  double bf_Width_DeltaYMax;

  CAP::BalFctPlotter * plotter = new CAP::BalFctPlotter();
  plotter->rangeOption               = 2;
  plotter->doPlotsBfVsDeltaYDeltaPhi = NO;
  plotter->doPlotsBfVsDeltaY         = YES;
  plotter->doPlotsBfVsDeltaPhi       = NO;
  plotter->doPlotsBfIntegralVsDeltaY = YES;
  plotter->doPlotsBfWidthDeltaY      = NO;
  plotter->doPlotsBfWidthDeltaPhi    = NO;
  plotter->doPrint                   = YES;
  plotter->doPrintGif                = NO;
  plotter->doPrintPdf                = YES;
  plotter->doPrintSvg                = NO;
  plotter->doPrintPng                = NO;
  plotter->doPrintC                  = NO;
//  plotter->deltaY_Minimum = -4.0;
//  plotter->deltaY_Maximum = 4.0;
  plotter->deltaY_Minimum = -20.0;
  plotter->deltaY_Maximum = 20.0;
  switch (choice)
    {
      case -1:
      bf_DeltaYDeltPhiMin = -0.05;
      bf_DeltaYDeltPhiMax =  0.3;
      bf_DeltaYMin = -0.05;
      bf_DeltaYMax =  0.3;
      bf_DeltPhiMin = -0.05;
      bf_DeltPhiMax =  0.2499;
      bf_Integral_DeltaYMin =  0.0;
      bf_Integral_DeltaYMax =  1.1;
      bf_IntegralSum_DeltaYMin =  0.0;
      bf_IntegralSum_DeltaYMax =  1.1;
      bf_Width_DeltaYMin =  0.0;
      bf_Width_DeltaYMax =  1.1;

      // plotter->correlationOption  = 2;
      plotter->speciesOption      = 2;
      plotter->rapidityOption     = 0;
      // plotter->bfOption           = 2;
      plotter->bf_General_Titles.push_back(TString("PYTHIA; pp at #sqrt{s}=13 TeV"));
      plotter->outputPathNameBase = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/Plots/";
      plotter->outputFileNameBase = "PYTHIA_pp_BaryonsVsS_A2Based_";

      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/Baryons/Y10/",
                         "PairGenBalFctSum0TO19.root",
                         "#sqrt{s}=13.0 TeV",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_Baryons_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      break;

      case 0:
      bf_DeltaYDeltPhiMin = -0.05;
      bf_DeltaYDeltPhiMax =  0.3;
      bf_DeltaYMin = -0.05;
      bf_DeltaYMax =  0.3;
      bf_DeltPhiMin = -0.05;
      bf_DeltPhiMax =  0.2499;
      bf_Integral_DeltaYMin =  0.0;
      bf_Integral_DeltaYMax =  1.1;
      bf_IntegralSum_DeltaYMin =  0.0;
      bf_IntegralSum_DeltaYMax =  1.1;
      bf_Width_DeltaYMin =  0.0;
      bf_Width_DeltaYMax =  1.1;

      plotter->bf_General_Titles.push_back(TString("PYTHIA; pp collisions"));
      // plotter->correlationOption  = 2;
      plotter->speciesOption      = 2;
      plotter->rapidityOption     = 0;
      // plotter->bfOption           = 2;
      plotter->outputPathNameBase = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/Plots/BaryonsVsS/";
      plotter->outputFileNameBase = "PYTHIA_pp_BaryonsVsS_A2Based_";
      plotter->addSystem("/Volumes/ClaudeDisc5/OutputFiles/PYTHIA/PP/900/Baryons/Y10/",
                         "PairGenBalFctSum0TO19.root",
                         "#sqrt{s}=0.90 TeV",
                         "PairGen_All_",
                         "PairGen_All_",
                         "900_Baryons_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/Baryons/Y10/",
                         "PairGenBalFctSum0TO19.root",
                         "#sqrt{s}=13.0 TeV",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_Baryons_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc5/OutputFiles/PYTHIA/PP/30000/Baryons/Y10/",
                         "PairGenBalFctSum0TO19.root",
                         "#sqrt{s}=30.0 TeV",
                         "PairGen_All_",
                         "PairGen_All_",
                         "30000_Baryons_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      break;

      case 1:
      bf_DeltaYDeltPhiMin = -0.05;
      bf_DeltaYDeltPhiMax =  0.3;
      bf_DeltaYMin = -0.05;
      bf_DeltaYMax =  0.3;
      bf_DeltPhiMin = -0.05;
      bf_DeltPhiMax =  0.2499;
      bf_Integral_DeltaYMin =  0.0;
      bf_Integral_DeltaYMax =  1.1;
      bf_IntegralSum_DeltaYMin =  0.0;
      bf_IntegralSum_DeltaYMax =  1.1;
      bf_Width_DeltaYMin =  0.0;
      bf_Width_DeltaYMax =  1.1;

      plotter->bf_General_Titles.push_back(TString("PYTHIA; pp collisions"));
      // plotter->correlationOption  = 2;
      plotter->speciesOption      = 2;
      plotter->rapidityOption     = 0;
      // plotter->bfOption           = 2;
      plotter->outputPathNameBase = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/Plots/BaryonsVsTune/";
      plotter->outputFileNameBase = "PYTHIA_pp_BaryonsVsTune_A2Based_";
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/Baryons/Y10",
                         "PairGenBalFctSum0TO19.root",
                         "Monash - ",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_Baryons_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
//      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/Baryons_Ropes",
//                         "PairGenBalFctSum0TO19.root",
//                         "Ropes - ",
//                         "PairGen_All_",
//                         "PairGen_All_",
//                         "13000_ropes_Baryons_Y10_",
//                         2,
//                         0,
//                         bf_DeltaYDeltPhiMin,
//                         bf_DeltaYDeltPhiMax,
//                         bf_DeltaYMin,
//                         bf_DeltaYMax,
//                         bf_DeltPhiMin,
//                         bf_DeltPhiMax,
//                         bf_Integral_DeltaYMin,
//                         bf_Integral_DeltaYMax,
//                         bf_IntegralSum_DeltaYMin,
//                         bf_IntegralSum_DeltaYMax,
//                         bf_Width_DeltaYMin,
//                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/Baryons_Shoving",
                         "PairGenBalFctSum0TO19.root",
                         "Shoving - ",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_shoving_Baryons_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      break;

      case 9:
      bf_DeltaYDeltPhiMin = -0.05;
      bf_DeltaYDeltPhiMax =  0.3;
      bf_DeltaYMin = -0.05;
      bf_DeltaYMax =  0.5;
      bf_DeltPhiMin = -0.05;
      bf_DeltPhiMax =  0.2499;
      bf_Integral_DeltaYMin =  0.0;
      bf_Integral_DeltaYMax =  1.1;
      bf_IntegralSum_DeltaYMin =  0.0;
      bf_IntegralSum_DeltaYMax =  1.1;
      bf_Width_DeltaYMin =  0.0;
      bf_Width_DeltaYMax =  1.1;


      plotter->bf_General_Titles.push_back(TString("PYTHIA; pp #sqrt{s}=13 TeV"));
      plotter->speciesOption      = 1;
      plotter->rapidityOption     = 0;
      plotter->outputPathNameBase = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/";
      plotter->outputFileNameBase = "PYTHIA_Monash_pp_PiKP_A2Based_Deltay20_";
      plotter->deltaY_Minimum = -20.0;
      plotter->deltaY_Maximum = 20.0;

      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Y2/",
                         "PairGenBalFctSum0TO19.root",
                         "|Y|<2 (D)",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_PiKp_Y2_",
                         2,
                         3,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Y2/",
                         "PairGenBalFctSum0TO19.root",
                         "|Y|<2 (A)",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_PiKp_Y2_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Y6/",
                         "PairGenBalFctSum0TO19.root",
                         "|Y|<6 (D)",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_PiKp_Y6_",
                         2,
                         3,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Y6/",
                         "PairGenBalFctSum0TO19.root",
                         "|Y|<6 (A)",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_PiKp_Y6_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);

      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PiKP/Y10/",
                         "PairGenBalFctSum0TO19.root",
                         "|Y|<10 (A)",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_PiKp_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);

      break;

      case 10:
      bf_DeltaYDeltPhiMin = -0.05;
      bf_DeltaYDeltPhiMax =  0.3;
      bf_DeltaYMin = -0.05;
      bf_DeltaYMax =  0.5;
      bf_DeltPhiMin = -0.05;
      bf_DeltPhiMax =  0.2499;
      bf_Integral_DeltaYMin =  0.0;
      bf_Integral_DeltaYMax =  1.1;
      bf_IntegralSum_DeltaYMin =  0.0;
      bf_IntegralSum_DeltaYMax =  1.1;
      bf_Width_DeltaYMin =  0.0;
      bf_Width_DeltaYMax =  1.1;


      plotter->bf_General_Titles.push_back(TString("PYTHIA; pp #sqrt{s}=13 TeV"));
      // plotter->correlationOption  = 2;
      plotter->speciesOption      = 1;
      plotter->rapidityOption     = 0;
      // plotter->bfOption           = 2;
      plotter->outputPathNameBase = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/Plots/";
//      plotter->outputFileNameBase = "PYTHIA_Monash_pp_PiKP_A2Based_";
//      plotter->deltaY_Minimum = -20.0;
//      plotter->deltaY_Maximum = 20.0;
      plotter->outputFileNameBase = "PYTHIA_Monash_pp_PiKP_A2Based_Deltay4_";
//      plotter->deltaY_Minimum = -4.0;
//      plotter->deltaY_Maximum = 4.0;
      plotter->deltaY_Minimum = -20.0;
      plotter->deltaY_Maximum = 20.0;

      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/PiKp/Y10",
                         "PairGenBalFctSum0TO9.root",
                         "Monash",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_PiKp_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);

      break;

      case 11:
      bf_DeltaYDeltPhiMin = -0.05;
      bf_DeltaYDeltPhiMax =  0.3;
      bf_DeltaYMin = -0.05;
      bf_DeltaYMax =  0.5;
      bf_DeltPhiMin = -0.05;
      bf_DeltPhiMax =  0.2499;
      bf_Integral_DeltaYMin =  0.0;
      bf_Integral_DeltaYMax =  1.1;
      bf_IntegralSum_DeltaYMin =  0.0;
      bf_IntegralSum_DeltaYMax =  1.1;
      bf_Width_DeltaYMin =  0.0;
      bf_Width_DeltaYMax =  1.1;

      plotter->bf_General_Titles.push_back(TString("PYTHIA; pp #sqrt{s}=13 TeV"));
      plotter->speciesOption      = 1;
      plotter->rapidityOption     = 0;
      plotter->outputPathNameBase = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/Plots/";
      plotter->outputFileNameBase = "PYTHIA_VsTune_pp_PiKP_A2Based_Deltay4";
      plotter->deltaY_Minimum = -20.0;
      plotter->deltaY_Maximum = 20.0;
      plotter->bf_General_Titles.push_back(TString("PYTHIA; pp collisions #sqrt{s}=13.0 TeV"));


      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/PiKp/Y10",
                         "PairGenBalFctSum0TO9.root",
                         "Monash",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_PiKp_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/PiKp_Ropes/Y10/",
                         "PairGenBalFctSum0TO9.root",
                         "Ropes",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_ropes_PiKp_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/PiKp_Shoving/Y10/",
                         "PairGenBalFctSum0TO7.root",
                         "Shoving",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_shoving_PiKp_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      break;


      case 12:
      bf_DeltaYDeltPhiMin = -0.05;
      bf_DeltaYDeltPhiMax =  0.3;
      bf_DeltaYMin = -0.05;
      bf_DeltaYMax =  0.5;
      bf_DeltPhiMin = -0.05;
      bf_DeltPhiMax =  0.2499;
      bf_Integral_DeltaYMin =  0.0;
      bf_Integral_DeltaYMax =  1.1;
      bf_IntegralSum_DeltaYMin =  0.0;
      bf_IntegralSum_DeltaYMax =  1.1;
      bf_Width_DeltaYMin =  0.0;
      bf_Width_DeltaYMax =  1.1;

      plotter->bf_General_Titles.push_back(TString("PYTHIA; pp #sqrt{s}=2.76, 5.02, 13 TeV"));
      plotter->speciesOption      = 1;
      plotter->rapidityOption     = 0;
      plotter->outputPathNameBase = "/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/Plots/";
      plotter->outputFileNameBase = "PYTHIA_Monash_pp_PiKP_A2Based_Deltay4_VsSqrt";
      plotter->deltaY_Minimum = -20.0;
      plotter->deltaY_Maximum = 20.0;
      plotter->bf_General_Titles.push_back(TString("PYTHIA; pp collisions"));

      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/2700/PiKp/",
                         "PairGenBalFctSum0TO9.root",
                         "2.76 TeV",
                         "PairGen_All_",
                         "PairGen_All_",
                         "2700_PiKp_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/5200/PiKp/Y10/",
                         "PairGenBalFctSum0TO9.root",
                         "5.02 TeV",
                         "PairGen_All_",
                         "PairGen_All_",
                         "5020_PiKp_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      plotter->addSystem("/Volumes/ClaudeDisc4/OutputFiles/PYTHIA/PP/13000/PiKp/Y10/",
                         "PairGenBalFctSum0TO9.root",
                         "13.0 TeV",
                         "PairGen_All_",
                         "PairGen_All_",
                         "13000_PiKp_Y10_",
                         2,
                         0,
                         bf_DeltaYDeltPhiMin,
                         bf_DeltaYDeltPhiMax,
                         bf_DeltaYMin,
                         bf_DeltaYMax,
                         bf_DeltPhiMin,
                         bf_DeltPhiMax,
                         bf_Integral_DeltaYMin,
                         bf_Integral_DeltaYMax,
                         bf_IntegralSum_DeltaYMin,
                         bf_IntegralSum_DeltaYMax,
                         bf_Width_DeltaYMin,
                         bf_Width_DeltaYMax);
      break;
    }
  //plotter->outputPath = "./TestOutput/";
  try
  {
  plotter->execute();
  }
  catch (CAP::TaskException & te)
  {
  te.print(); exit(1);
  }
  catch (CAP::ConfigurationException & ce)
  {
  ce.print(); exit(1);
  }
  catch (CAP::MathException & me)
  {
  me.print(); exit(1);
  }
  catch (CAP::FileException & fe)
  {
  fe.print(); exit(1);
  }
  catch (CAP::MemoryException & mme)
  {
  mme.print(); exit(1);
  }
  catch (CAP::HistogramException & he)
  {
  he.print(); exit(1);
  }
  catch (CAP::FactoryException & ffe)
  {
  ffe.print(); exit(1);
  }
  catch (CAP::Exception & e)
  {
  e.print(); exit(1);
  }
  return 0;
}

void loadBase(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Base/";
  gSystem->Load(includePath+"Exception.hpp");
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

