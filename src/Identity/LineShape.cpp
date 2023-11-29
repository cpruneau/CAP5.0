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

  printItem("LineShape:nBins_p",     nBins_p     );
  printItem("LineShape:Min_p",       min_p       );
  printItem("LineShape:Max_p",       max_p       );
  printItem("LineShape:range_p",     range_p     );
  printItem("LineShape:nBins_dEdx",  nBins_dEdx  );
  printItem("LineShape:Min_dEdx",    min_dEdx    );
  printItem("LineShape:Max_dEdx",    max_dEdx    );
  printItem("LineShape:range_dEdx",  range_dEdx  );

  //  h_lineShapeVsDedx_e  = createHistogram("lineShape_e", nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_lineShapeVsDedx_pi = createHistogram("lineShape_pi", nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_lineShapeVsDedx_k  = createHistogram("lineShape_k",  nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");
  h_lineShapeVsDedx_p  = createHistogram("lineShape_p",  nBins_p,  min_p,  max_p, nBins_dEdx, min_dEdx, max_dEdx, "p (GeV/c)", "dE/dx", "P(dE/dx)");

  //double m_e = 0.51;
  double m_pi = 0.139;
  double m_k  = 0.4500;
  double m_p  = 0.9380;
  double a    = 0.005;
  double b    = 0.00;

  cout << " FILL HISTOS" << endl;
  for (int k=0; k<nBins_p; k++)
    {
    double p = min_p + (double(k)+0.5)*width_p;
    double dedx = dedxExpectation(m_pi,p,a,b);
    double dedxRms = dedxRmsExpectation(m_pi,p,a,b);
    //cout << " p:" << p << " pi dedx: " << dedx << endl;
    h_lineShapeVsDedx_pi->Fill(p,dedx);
    dedx = dedxExpectation(m_k,p,a,b);
    dedxRms = dedxRmsExpectation(m_k,p,a,b);
    //cout << " p:" << p << " K  dedx: " << dedx << endl;
    h_lineShapeVsDedx_k->Fill(p,dedx);
    dedx = dedxExpectation(m_p,p,a,b);
    dedxRms = dedxRmsExpectation(m_p,p,a,b);
    //cout << " p:" << p << " p  dedx: " << dedx << endl;
    h_lineShapeVsDedx_p->Fill(p,dedx);
    }
  TFile * outputFile = openRootFile("","test.root","RECREATE");
  h_lineShapeVsDedx_pi->Write();
  h_lineShapeVsDedx_k->Write();
  h_lineShapeVsDedx_p->Write();
  outputFile->Close();
}

double LineShape::dedxExpectation(double m, double p, double a, double b)
{
  // assume a/beta + b for now...
  double energy = sqrt(m*m+p*p);
  double beta = p/energy;
  return a/beta + b;
}

double LineShape::dedxRmsExpectation(double m, double p, double a, double b)
{
  // assume a/beta + b for now...
  double energy = sqrt(m*m+p*p);
  double beta = p/energy;
  return a/beta + b;
}


void LineShape::importHistograms(TFile & inputFile)
{

}

