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

TFile * openRootFile(const TString & path, const TString & fileName, const TString & ioOption="RECREATE")
{

  TString theFileName;
  if (fileName.BeginsWith("/"))
    theFileName = fileName;
  else
    {
    // make sure that if an inputPath is given, it ends with '/'
    TString theFilePath = path;
    int slash = theFilePath.First('/');
    int len   = theFilePath.Length();
    if (len>0 && (len-1)!=slash) theFilePath += "/";
    theFileName = theFilePath;
    theFileName += fileName;
    }
  // make sure the root extension is included in the file name
  if (!theFileName.EndsWith(".root")) theFileName += ".root";
  TFile * file = new TFile(theFileName,ioOption);
  if (!file)
    {
    cout << " Got null pointer for : " << theFileName << endl;
    exit(1);
    }
  if (!file->IsOpen())
    {
    cout << " Could not open file: " << theFileName << endl;
    exit(1);
    }
  cout << "File opened successfully: " << theFileName << endl;
  return file;
}



int BfStudies()
{
//  bool printGif = 0;
//  bool printPdf = 1;
//  bool printSvg = 0;
//  bool printC   = 1;
//  bool useColor = true;

//  TString includeBasePath = getenv("CAP_SRC");
//  loadBase(includeBasePath);
  TString exportPath = "/Volumes/ClaudeDisc4/OutputFiles/BFStudies/2Slope0.1/";
  TString fileName   = "BfStudies";

  double sigmaYbar     = 2.0;
  double sigmaDeltaY   = 1.0;
  double slope         = 0.1;
  int    pairRequested = 1000000000;
  double y0            = 1.0;
  double dyMax         = 2.0*y0;
  TH2* bfDeltayYbar    = new TH2F("bfDeltayYbar","bfDeltayYbar",      50,-y0,y0, 49, -dyMax, dyMax);
  TH2* bfDeltayYbarCut = new TH2F("bfDeltayYbarCut","bfDeltayYbarCut",50,-y0,y0, 49, -dyMax, dyMax);
  TH1* ratio           = new TH1D("ratio","ratio", 49, -dyMax, dyMax);

  for (int iPair=0; iPair<pairRequested; iPair++)
    {
    double yBar;
    if (sigmaYbar>10)
      yBar   = gRandom->Uniform(-y0,y0);
    else
      yBar   = gRandom->Gaus(0.0,sigmaYbar);
    double deltaY = gRandom->Gaus(0.0,sigmaDeltaY+slope*fabs(yBar));

    double y1     = yBar + deltaY/2.0;
    double y2     = yBar - deltaY/2.0;
    bfDeltayYbar->Fill(yBar,deltaY);
    if (fabs(y1)<y0 && fabs(y2)<y0)   bfDeltayYbarCut->Fill(yBar,deltaY);
    }
  TH1 * bfDeltayFull = bfDeltayYbar->ProjectionY("bfDeltayFull");
  TH1 * bfDeltayCut  = bfDeltayYbarCut->ProjectionY("bfDeltayCut");
  TH1 * bfDeltayCorr = bfDeltayYbarCut->ProjectionY("bfDeltayCor");

  for (int k = 1; k<=49; k++)
    {
    double v  = bfDeltayCorr->GetBinContent(k);
    double ev = bfDeltayCorr->GetBinError(k);
    double dy = fabs(bfDeltayCorr->GetBinCenter(k));
    double scale = 1.0/(1.0 - dy/2.0/y0);
    bfDeltayCorr->SetBinContent(k,scale*v);
    bfDeltayCorr->SetBinError(k,scale*ev);
    }
  double s1 = bfDeltayFull->Integral();
  bfDeltayFull->Scale(1.0/s1);
  double s2 = bfDeltayCut->Integral();
  bfDeltayCut->Scale(1.0/s2);
  double s3 = bfDeltayCorr->Integral();
  bfDeltayCorr->Scale(1.0/s3);

  ratio->Divide(bfDeltayCorr,bfDeltayFull);

  TCanvas * c1 = new TCanvas("BF2Dfull","BF2Dfull",600,800);
  bfDeltayYbar->Draw("ZCOL");

  TCanvas * c2 = new TCanvas("BF2Dcut","BF2Dcut",600,800);
  bfDeltayYbarCut->Draw("ZCOL");

  TCanvas * c3 = new TCanvas("BF","BF",600,800);

  bfDeltayFull->SetMinimum(-0.05);
  bfDeltayFull->SetMaximum(0.10);
  bfDeltayFull->SetLineColor(1);
  bfDeltayFull->SetLineWidth(2);
  bfDeltayFull->Draw();

  bfDeltayCut->SetLineColor(2);
  bfDeltayCut->SetLineWidth(2);
  bfDeltayCut->Draw("SAME");

  bfDeltayCorr->SetLineColor(4);
  bfDeltayCorr->SetLineWidth(2);
  bfDeltayCorr->Draw("SAME");
 

  TCanvas * c4 = new TCanvas("Ratio","Ratio",600,800);

  ratio->SetLineColor(6);
  ratio->SetLineWidth(2);
  ratio->Draw("SAME");

  c1->Print(exportPath+"BF2Dfull.pdf");
  c2->Print(exportPath+"BF2Dcut.pdf");
  c3->Print(exportPath+"BF.pdf");
  c4->Print(exportPath+"Ratio.pdf");


  TFile * rootOutputFile = openRootFile(exportPath,fileName,"RECREATE");
  bfDeltayYbar->Write();
  bfDeltayYbarCut->Write();
  bfDeltayFull->Write();
  bfDeltayCut->Write();
  bfDeltayCorr->Write();

  rootOutputFile->Close();
  return 0;
}
