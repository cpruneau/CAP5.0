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
#include "LineShape.hpp"

using CAP::LineShape;

ClassImp(LineShape);

LineShape::LineShape(const String & _name,
                     const Configuration & _configuration)
:
Task(_name,_configuration),
HistogramCollection(_name)
{
  Task::appendClassName("LineShape");
  HistogramCollection::appendClassName("LineShape");
}

void LineShape::setDefaultConfiguration()
{
  Task::setDefaultConfiguration();
  addParameter("nBins_p",          300);
  addParameter("Min_p",            0.00);
  addParameter("Max_p",            3.00);
  addParameter("nBins_dEdx",       200);
  addParameter("Min_dEdx",         0.0);
  addParameter("Max_dEdx",         1.0); // arbitrary units for now.
  addParameter("nMc",              100000);
  addParameter("nParts",           10);
}

void LineShape::configure()
{
  Task::configure();

  if (Task::reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("nBins_p");
    printItem("Min_p");
    printItem("Max_p");
    printItem("nBins_dEdx");
    printItem("Min_dEdx");
    printItem("Max_dEdx");
    printItem("nMc");
    printItem("nParts");
    cout << endl;
    }
}

void LineShape::initialize()
{
  
}

void LineShape::createHistograms()
{
  if (Task::reportStart(__FUNCTION__))
    ;
  String ppn = "LineShape";
  const Configuration & configuration = getConfiguration();
  nBins_p = configuration.getValueInt(ppn,   "nBins_p");
  min_p   = configuration.getValueDouble(ppn,"Min_p");
  max_p   = configuration.getValueDouble(ppn,"Max_p");
  range_p = max_p - min_p;
  width_p = range_p/double(nBins_p);
  nBins_dEdx   = configuration.getValueInt(ppn,   "nBins_dEdx");
  min_dEdx     = configuration.getValueDouble(ppn,"Min_dEdx");
  max_dEdx     = configuration.getValueDouble(ppn,"Max_dEdx");
  range_dEdx   = max_dEdx - min_dEdx;

  nMc = configuration.getValueDouble(ppn,"nMc");
  nParts = configuration.getValueDouble(ppn,"nParts");
  printItem("LineShape:nBins_p",     nBins_p     );
  printItem("LineShape:Min_p",       min_p       );
  printItem("LineShape:Max_p",       max_p       );
  printItem("LineShape:range_p",     range_p     );
  printItem("LineShape:nBins_dEdx",  nBins_dEdx  );
  printItem("LineShape:Min_dEdx",    min_dEdx    );
  printItem("LineShape:Max_dEdx",    max_dEdx    );
  printItem("LineShape:range_dEdx",  range_dEdx  );
  printItem("LineShape:nMc",         nMc  );
  printItem("LineShape:nParts",      nParts  );

  //  h_lineShapeVsDedx_e  = createHistogram("lineShape_e", nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_lineShapeVsDedx_pi  = createHistogram("lineShape_pi", nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_lineShapeVsDedx_k   = createHistogram("lineShape_k",  nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_lineShapeVsDedx_p   = createHistogram("lineShape_p",  nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_lineShapeVsDedx_sum = createHistogram("lineShape_sum",nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");

  h_omegaVsDedx_pi  = createHistogram("omega_pi", nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_omegaVsDedx_k   = createHistogram("omega_k",  nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_omegaVsDedx_p   = createHistogram("omega_p",  nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_omegaVsDedx_sum = createHistogram("omega_sum",nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");


  h_yield_pi  =  createHistogram("yield_pi", nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");
  h_yield_k   =  createHistogram("yield_k",  nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");;
  h_yield_p   =  createHistogram("yield_p",  nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");;
  h_yield_sum =  createHistogram("yield_sum",nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");;
  h_frac_pi   =  createHistogram("frac_pi",  nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");
  h_frac_k    =  createHistogram("frac_k",   nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");;
  h_frac_p    =  createHistogram("frac_p",   nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");;
  h_frac_sum  =  createHistogram("frac_sum", nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");;

  h_mcYield_pi =  createHistogram("mcYield_pi", nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");
  h_mcYield_k  =  createHistogram("mcYield_k",  nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");
  h_mcYield_p  =  createHistogram("mcYield_p",  nBins_p,  min_p,  max_p, "p (GeV/c)", "P(p)");

  //double m_e = 0.51;
  double m_pi = 0.139;
  double m_k  = 0.4500;
  double m_p  = 0.9380;
  double a    = 0.2;
  double b    = -0.10;
  double aw    = 0.006;
  double bw    = 0.001;
  double t_pi  = 0.4;
  double t_k   = 0.5;
  double t_p   = 0.6;
  double p;

  cout << "Fill Yield Histos" << endl;
  for (int iter=0; iter<nMc; iter++)
    {
    p = gRandom->Exp(t_pi);
    h_yield_pi->Fill(p);
    p = gRandom->Exp(t_k);
    h_yield_k->Fill(p);
    p = gRandom->Exp(t_p);
    h_yield_p->Fill(p);
    }
  double integral_pi = h_yield_pi->Integral("WIDTH");
  double integral_k  = h_yield_k->Integral("WIDTH");
  double integral_p  = h_yield_p->Integral("WIDTH");
  double integral_sum = 0.75*integral_pi+0.15*integral_k+0.10*integral_p;
  double frac_pi = 0.75*integral_pi/integral_sum;
  double frac_k  = 0.15*integral_k/integral_sum;
  double frac_p  = 0.10*integral_p/integral_sum;
  double frac_pik  = frac_pi+frac_k;
  double frac_pikp = frac_pik+frac_p;

  cout << "  frac_pi: " << frac_pi << endl;
  cout << "   frac_k: " << frac_k << endl;
  cout << "   frac_p: " << frac_p << endl;
  cout << " frac_pik: " << frac_pik << endl;
  cout << "frac_pikp: " << frac_pikp << endl;


  h_yield_pi->Scale(0.75/integral_pi);
  h_yield_k->Scale(0.15/integral_k);
  h_yield_p->Scale(0.10/integral_p);
  h_yield_sum->Add(h_yield_pi,h_yield_k,1.0,1.0);
  h_yield_sum->Add(h_yield_p,1.0);
  h_frac_pi->Divide(h_yield_pi,h_yield_sum);
  h_frac_k->Divide(h_yield_k,h_yield_sum);
  h_frac_p->Divide(h_yield_p,h_yield_sum);
  h_frac_sum->Add(h_frac_pi,h_frac_k,1.0,1.0);
  h_frac_sum->Add(h_frac_p,1.0);

  cout << " FILL Line Profile HISTOS" << endl;
  for (int k=0; k<nBins_p; k++)
    {
    double p = min_p + (double(k)+0.5)*width_p;
    double dedxMean = dedxExpectation(m_pi,p,a,b);
    double dedxRms  = dedxRmsExpectation(m_pi,p,aw,bw);
    for (int iter=0; iter<nMc; iter++)
      {
      double dedx = gRandom->Gaus(dedxMean,dedxRms);
      h_lineShapeVsDedx_pi->Fill(p,dedx);
      }
    //cout << " p:" << p << " pi dedx: " << dedx << endl;
    dedxMean = dedxExpectation(m_k,p,a,b);
    dedxRms = dedxRmsExpectation(m_k,p,aw,bw);
    for (int iter=0; iter<nMc; iter++)
      {
      double dedx = gRandom->Gaus(dedxMean,dedxRms);
      h_lineShapeVsDedx_k->Fill(p,dedx);
      }

    dedxMean = dedxExpectation(m_p,p,a,b);
    dedxRms  = dedxRmsExpectation(m_p,p,aw,bw);
    for (int iter=0; iter<nMc; iter++)
      {
      double dedx = gRandom->Gaus(dedxMean,dedxRms);
      h_lineShapeVsDedx_p->Fill(p,dedx);
      }
    }
  double scale = 1.0/double(nMc);
  h_lineShapeVsDedx_pi->Scale(scale);
  h_lineShapeVsDedx_k->Scale(scale);
  h_lineShapeVsDedx_p->Scale(scale);


  for (int k=0; k<nBins_p; k++)
    {
    // sum the 3 spectra with weights

    double frac_pi = h_yield_pi->GetBinContent(k);
    double frac_k  = h_yield_k->GetBinContent(k);
    double frac_p  = h_yield_p->GetBinContent(k);
    double zero = 0.0;
    for (int iDedx=0; iDedx<nBins_dEdx; iDedx++)
      {
      double v_pi = frac_pi * h_lineShapeVsDedx_pi->GetBinContent(k,iDedx);
      double v_k  = frac_k  * h_lineShapeVsDedx_k->GetBinContent(k,iDedx);
      double v_p  = frac_p  * h_lineShapeVsDedx_p->GetBinContent(k,iDedx);
      h_lineShapeVsDedx_pi->SetBinContent(k,iDedx,v_pi);
      h_lineShapeVsDedx_k->SetBinContent(k,iDedx,v_k);
      h_lineShapeVsDedx_p->SetBinContent(k,iDedx,v_p);
      h_lineShapeVsDedx_sum->SetBinContent(k,iDedx,v_pi+v_k+v_p);
      h_lineShapeVsDedx_pi->SetBinError(k,iDedx,zero);
      h_lineShapeVsDedx_k->SetBinError(k,iDedx,zero);
      h_lineShapeVsDedx_p->SetBinError(k,iDedx,zero);
      h_lineShapeVsDedx_sum->SetBinError(k,iDedx,zero);
      }
//    if (total>0.0)
//      {
//      for (int iDedx=0; iDedx<nBins_dEdx; iDedx++)
//        {
//        double v = h_lineShapeVsDedx_sum->GetBinContent(k,iDedx);
//        h_lineShapeVsDedx_sum->SetBinContent(k,iDedx,v/total);
//        h_lineShapeVsDedx_sum->SetBinError(k,iDedx,0.0);
//        }
//      }
    }

  h_omegaVsDedx_pi->Divide(h_lineShapeVsDedx_pi,h_lineShapeVsDedx_sum,1.0,1.0);
  h_omegaVsDedx_k->Divide(h_lineShapeVsDedx_k,h_lineShapeVsDedx_sum,1.0,1.0);
  h_omegaVsDedx_p->Divide(h_lineShapeVsDedx_p,h_lineShapeVsDedx_sum,1.0,1.0);
  h_omegaVsDedx_sum->Add(h_omegaVsDedx_pi,h_omegaVsDedx_k);
  h_omegaVsDedx_sum->Add(h_omegaVsDedx_p);

  TFile * outputFile = openRootFile("","test.root","RECREATE");
  h_lineShapeVsDedx_pi->Write();
  h_lineShapeVsDedx_k->Write();
  h_lineShapeVsDedx_p->Write();
  h_lineShapeVsDedx_sum->Write();

  cout << "   frac_k: " << frac_k << endl;
  cout << "   frac_p: " << frac_p << endl;
  cout << " frac_pik: " << frac_pik << endl;
  cout << "frac_pikp: " << frac_pikp << endl;

// MC Phase
  for (int iEvent=0; iEvent<nMc; iEvent++)
    {
    for (int iPart=0; iPart<nParts; iPart++)
      {
      double r = gRandom->Rndm();
      if (r<frac_pi)
        {
        p = h_yield_pi->GetRandom();
        h_mcYield_pi->Fill(p);
        }
      else if (r<frac_pik)
        {
        p = h_yield_k->GetRandom();
        h_mcYield_k->Fill(p);
        }
      else
        {
        p = h_yield_p->GetRandom();
        h_mcYield_p->Fill(p);
        }
      }
    }


  h_yield_pi->Write();
  h_yield_k->Write();
  h_yield_p->Write();
  h_yield_sum->Write();
  h_frac_pi->Write();
  h_frac_k->Write();
  h_frac_p->Write();
  h_frac_sum->Write();

  h_mcYield_pi->Write();
  h_mcYield_k->Write();
  h_mcYield_p->Write();

  outputFile->Close();
}

double LineShape::dedxExpectation(double m, double p, double a, double b)
{
  // assume a/beta + b for now...
  double energy = sqrt(m*m+p*p);
  double beta = p/energy;
  return a/beta/beta + b;
}

double LineShape::dedxRmsExpectation(double m, double p, double a, double b)
{
  // assume a/beta + b for now...
  double energy = sqrt(m*m+p*p);
  double beta = p/energy;
  return a/beta/beta + b;
}


void LineShape::importHistograms(TFile & inputFile)
{

}

