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
#include "Task.hpp"
#include "ParticlePairDerivedHistos.hpp"

ClassImp(CAP::ParticlePairDerivedHistos);

namespace CAP
{


ParticlePairDerivedHistos::ParticlePairDerivedHistos(Task * _parent,
                                                     const String & _name,
                                                     const Configuration & _configuration)
:
HistogramGroup(_parent,_name,_configuration),
fillEta(0),
fillY(0),
fillP2(0),
nBins_pt(0),
min_pt(0),
max_pt(0),
nBins_phi(0),
min_phi(0),
max_phi(0),
nBins_eta(0),
min_eta(0),
max_eta(0),
nBins_y(0),
min_y(0),
max_y(0),
nBins_Dphi(0),
min_Dphi(0),
max_Dphi(0),
nBins_Deta(0),
min_Deta(0),
max_Deta(0),
nBins_Dy(0),
min_Dy(0),
max_Dy(0),
h_n1n1_ptpt(nullptr),
h_A2_ptpt(nullptr),
h_B2_ptpt(nullptr),
h_C2_ptpt(nullptr),
h_R2_ptpt(nullptr),

h_n1n1_phiPhi(nullptr),
h_A2_phiPhi(nullptr),
h_B2_phiPhi(nullptr),
h_C2_phiPhi(nullptr),
h_R2_phiPhi(nullptr),

h_pt1pt1_phiPhi(nullptr),
h_DptDpt_phiPhi(nullptr),
h_P2_phiPhi(nullptr),
h_G2_phiPhi(nullptr),

h_n1n1_etaEta(nullptr),
h_A2_etaEta(nullptr),
h_B2_etaEta(nullptr),
h_C2_etaEta(nullptr),
h_R2_etaEta(nullptr),

h_pt1pt1_etaEta(nullptr),
h_DptDpt_etaEta(nullptr),
h_G2_etaEta(nullptr),
h_P2_etaEta(nullptr),

h_n1n1_DetaDphi(nullptr),
h_rho2_DetaDphi(nullptr),
h_A2_DetaDphi(nullptr),
h_B2_DetaDphi(nullptr),
h_C2_DetaDphi(nullptr),
h_D2_DetaDphi(nullptr),
h_R2_DetaDphi(nullptr),
h_P2_DetaDphi(nullptr),
h_G2_DetaDphi(nullptr),

h_pt1pt1_DetaDphi(nullptr),
h_DptDpt_DetaDphi(nullptr),

h_rho2_DetaDphi_shft(nullptr),
h_A2_DetaDphi_shft(nullptr),
h_B2_DetaDphi_shft(nullptr),
h_C2_DetaDphi_shft(nullptr),
h_D2_DetaDphi_shft(nullptr),
h_R2_DetaDphi_shft(nullptr),
h_DptDpt_DetaDphi_shft(nullptr),
h_P2_DetaDphi_shft(nullptr),
h_G2_DetaDphi_shft(nullptr),

h_n1n1_yY(nullptr),
h_A2_yY(nullptr),
h_B2_yY(nullptr),
h_C2_yY(nullptr),
h_R2_yY(nullptr),

h_pt1pt1_yY(nullptr),
h_DptDpt_yY(nullptr),
h_G2_yY(nullptr),
h_P2_yY(nullptr),

h_n1n1_DyDphi(nullptr),
h_rho2_DyDphi(nullptr),
h_A2_DyDphi(nullptr),
h_B2_DyDphi(nullptr),
h_C2_DyDphi(nullptr),
h_D2_DyDphi(nullptr),
h_R2_DyDphi(nullptr),
h_P2_DyDphi(nullptr),
h_G2_DyDphi(nullptr),

h_rho2_DyDphi_shft(nullptr),
h_A2_DyDphi_shft(nullptr),
h_B2_DyDphi_shft(nullptr),
h_C2_DyDphi_shft(nullptr),
h_D2_DyDphi_shft(nullptr),
h_R2_DyDphi_shft(nullptr),
h_DptDpt_DyDphi_shft(nullptr),
h_P2_DyDphi_shft(nullptr),
h_G2_DyDphi_shft(nullptr),

h_pt1pt1_DyDphi(nullptr),
h_DptDpt_DyDphi(nullptr)
{
  appendClassName("ParticlePairDerivedHistos");
}

void ParticlePairDerivedHistos::createHistograms()
{
  if (reportStart(__FUNCTION__))
    ;
  const String & bn  = getName();
  const String & ptn = getParentTask()->getName();
  const String & ppn = getParentPathName();
  const Configuration & configuration = getConfiguration();
  nBins_n2   = configuration.getValueInt(ppn,"nBins_n2");
  min_n2     = configuration.getValueDouble(ppn,"Min_n2");
  max_n2     = configuration.getValueDouble(ppn,"Max_n2");
  nBins_n2   = configuration.getValueInt(ppn,"nBins_n2");
  min_n2     = configuration.getValueDouble(ppn,"Min_n2");
  max_n2     = configuration.getValueDouble(ppn,"Max_n2");
  nBins_pt   = configuration.getValueInt(ppn,"nBins_pt");
  min_pt     = configuration.getValueDouble(ppn,"Min_pt");
  max_pt     = configuration.getValueDouble(ppn,"Max_pt");
  nBins_phi  = configuration.getValueInt(ppn,"nBins_phi");
  min_phi    = configuration.getValueDouble(ppn,"Min_phi");
  max_phi    = configuration.getValueDouble(ppn,"Max_phi");
  fillEta    = configuration.getValueBool(ppn,"FillEta");
  fillY      = configuration.getValueBool(ppn,"FillY");
  fillP2     = configuration.getValueBool(ppn,"FillP2");

  double scale_phi   = max_phi - min_phi;
  double width_Dphi  = scale_phi/nBins_phi;

  nBins_Dphi       = nBins_phi;
  min_Dphi         = 0.0; //-width_Dphi/2.;
  max_Dphi         = CAP::Math::twoPi(); // - width_Dphi/2.;
  nBins_Dphi_shft  = int(double(nBins_Dphi)/4.0);
  min_Dphi_shft    = min_Dphi - width_Dphi*double(nBins_Dphi_shft);
  max_Dphi_shft    = max_Dphi - width_Dphi*double(nBins_Dphi_shft);

  nBins_eta = configuration.getValueInt(ppn,"nBins_eta");
  min_eta   = configuration.getValueDouble(ppn,"Min_eta");
  max_eta   = configuration.getValueDouble(ppn,"Max_eta");
  double range_eta = max_eta - min_eta;

  nBins_Deta= 2*nBins_eta-1;
  min_Deta  = -range_eta;
  max_Deta  = range_eta;

  nBins_y = configuration.getValueInt(ppn,"nBins_y");
  min_y   = configuration.getValueDouble(ppn,"Min_y");
  max_y   = configuration.getValueDouble(ppn,"Max_y");
  max_yAcc= configuration.getValueDouble(ppn,"Max_yAcc");

  double range_y = max_y - min_y;

  nBins_Dy  = 2*nBins_y-1;
  min_Dy    = -range_y;
  max_Dy    = range_y;

  if (reportDebug(__FUNCTION__))
    {
    cout << endl;
    printItem("Pair:Parent Task Name",  ptn);
    printItem("Pair:Parent Path Name",  ppn);
    printItem("Pair:Histo Base Name",   bn);
    printItem("Pair:nBins_n2",          int(nBins_n2));
    printItem("Pair:Min_n2",            min_n2);
    printItem("Pair:Max_n2",            max_n2);
    printItem("Pair:nBins_pt",          int(nBins_pt));
    printItem("Pair:Min_pt",            min_pt);
    printItem("Pair:Max_pt",            max_pt);
    printItem("Pair:nBins_phi",         int(nBins_phi));
    printItem("Pair:Min_phi",           min_phi);
    printItem("Pair:Max_phi",           max_phi);
    printItem("Pair:scale_phi",         scale_phi);

    printItem("Pair:nBins_Dphi",     int(nBins_Dphi));
    printItem("Pair:Min_Dphi",       min_Dphi);
    printItem("Pair:Max_Dphi",       max_Dphi);
    printItem("Pair:width_Dphi",     width_Dphi);
    printItem("Pair:nBins_Dphi_shft",int(nBins_Dphi_shft));
    printItem("Pair:min_Dphi_shft",  min_Dphi_shft);
    printItem("Pair:max_Dphi_shft",  max_Dphi_shft);

    printItem("Pair:nBins_eta",   int(nBins_eta));
    printItem("Pair:Min_eta",     min_eta);
    printItem("Pair:Max_eta",     max_eta);
    printItem("Pair:range_eta",   range_eta);
    printItem("Pair:nBins_Deta",  int(nBins_Deta));
    printItem("Pair:min_Deta",    min_Deta);
    printItem("Pair:max_Deta",    max_Deta);

    printItem("Pair:nBins_y",  int(nBins_y));
    printItem("Pair:Min_y",    min_y);
    printItem("Pair:Max_y",    max_y);
    printItem("Pair:range_y",  range_y);
    printItem("Pair:nBins_Dy", int(nBins_Dy));
    printItem("Pair:min_Dy",   min_Dy);
    printItem("Pair:max_Dy",   max_Dy);

    printItem("Pair:FillEta",  fillEta);
    printItem("Pair:FillY",    fillY);
    printItem("Pair:FillP2",   fillP2);
    }


  h_n1n1_ptpt            = createHistogram(createName(bn,"n1n1_ptpt"),   nBins_pt,  min_pt,  max_pt,  nBins_pt,  min_pt,   max_pt,   "p_{T,1}", "p_{T,2}", "<n_{1}><n_{2}>");
  h_A2_ptpt              = createHistogram(createName(bn,"A2_ptpt"),     nBins_pt,  min_pt,  max_pt,  nBins_pt,  min_pt,   max_pt,   "p_{T,1}", "p_{T,2}", "A_{2}");
  h_B2_ptpt              = createHistogram(createName(bn,"B2_ptpt"),     nBins_pt,  min_pt,  max_pt,  nBins_pt,  min_pt,   max_pt,   "p_{T,1}", "p_{T,2}", "B_{2}");
  h_C2_ptpt              = createHistogram(createName(bn,"C2_ptpt"),     nBins_pt,  min_pt,  max_pt,  nBins_pt,  min_pt,   max_pt,   "p_{T,1}", "p_{T,2}", "C_{2}");
  h_R2_ptpt              = createHistogram(createName(bn,"R2_ptpt"),     nBins_pt,  min_pt,  max_pt,  nBins_pt,  min_pt,   max_pt,   "p_{T,1}", "p_{T,2}", "R_{2}");

  h_n1n1_phiPhi          = createHistogram(createName(bn,"n1n1_phiPhi"), nBins_phi, min_phi, max_phi, nBins_phi, min_phi,  max_phi,  "#varphi_{1}", "#varphi_{2}", "<n_{1}><n_{2}>");
  h_A2_phiPhi            = createHistogram(createName(bn,"A2_phiPhi"),   nBins_phi, min_phi, max_phi, nBins_phi, min_phi,  max_phi,  "#varphi_{1}", "#varphi_{2}", "A_{2}");
  h_B2_phiPhi            = createHistogram(createName(bn,"B2_phiPhi"),   nBins_phi, min_phi, max_phi, nBins_phi, min_phi,  max_phi,  "#varphi_{1}", "#varphi_{2}", "B_{2}");
  h_C2_phiPhi            = createHistogram(createName(bn,"C2_phiPhi"),   nBins_phi, min_phi, max_phi, nBins_phi, min_phi,  max_phi,  "#varphi_{1}", "#varphi_{2}", "C_{2}");
  h_R2_phiPhi            = createHistogram(createName(bn,"R2_phiPhi"),   nBins_phi, min_phi, max_phi, nBins_phi, min_phi,  max_phi,  "#varphi_{1}", "#varphi_{2}", "R_{2}");

  if (fillP2)
    {
    h_pt1pt1_phiPhi      = createHistogram(createName(bn,"pt1pt1_phiPhi"), nBins_phi, min_phi, max_phi, nBins_phi, min_phi,  max_phi,  "#varphi_{1}","#varphi_{2}",   "pt1pt1");
    h_DptDpt_phiPhi      = createHistogram(createName(bn,"DptDpt_phiPhi"), nBins_phi, min_phi, max_phi, nBins_phi, min_phi,  max_phi,  "#varphi_{1}", "#varphi_{2}",   "<#Delta p_{T} #Delta p_{T}>");
    h_P2_phiPhi          = createHistogram(createName(bn,"P2_phiPhi"),     nBins_phi, min_phi, max_phi, nBins_phi, min_phi,  max_phi,  "#varphi_{1}", "#varphi_{2}",   "P_{2}");
    h_G2_phiPhi          = createHistogram(createName(bn,"G2_phiPhi"),     nBins_phi, min_phi, max_phi, nBins_phi, min_phi,  max_phi,  "#varphi_{1}", "#varphi_{2}",   "G_{2}");
    }
  
  if (fillEta)
    {
    h_n1n1_etaEta        = createHistogram(createName(bn,"n1n1_etaEta"),    nBins_eta,   min_eta,   max_eta,   nBins_eta,   min_eta,  max_eta,  "#eta_{1}", "#eta_{2}", "<n_{1}><n_{2}>");
    h_A2_etaEta          = createHistogram(createName(bn,"A2_etaEta"),      nBins_eta,   min_eta,   max_eta,   nBins_eta,   min_eta,  max_eta,  "#eta_{1}", "#eta_{2}", "A_{2}");
    h_B2_etaEta          = createHistogram(createName(bn,"B2_etaEta"),      nBins_eta,   min_eta,   max_eta,   nBins_eta,   min_eta,  max_eta,  "#eta_{1}", "#eta_{2}", "B_{2}");
    h_C2_etaEta          = createHistogram(createName(bn,"C2_etaEta"),      nBins_eta,   min_eta,   max_eta,   nBins_eta,   min_eta,  max_eta,  "#eta_{1}", "#eta_{2}", "C_{2}");
    h_R2_etaEta          = createHistogram(createName(bn,"R2_etaEta"),      nBins_eta,   min_eta,   max_eta,   nBins_eta,   min_eta,  max_eta,  "#eta_{1}", "#eta_{2}", "R_{2}");

    h_n1n1_DetaDphi      = createHistogram(createName(bn,"n1n1_DetaDphi"),  nBins_Deta, min_Deta, max_Deta, nBins_Dphi, min_Dphi, max_Dphi, "#Delta#eta","#Delta#varphi", "<n_{1}><n_{1}>");
    h_rho2_DetaDphi      = createHistogram(createName(bn,"rho2_DetaDphi"),  nBins_Deta, min_Deta, max_Deta, nBins_Dphi, min_Dphi, max_Dphi, "#Delta#eta","#Delta#varphi", "#rho_{2}");
    h_A2_DetaDphi        = createHistogram(createName(bn,"A2_DetaDphi"),    nBins_Deta, min_Deta, max_Deta, nBins_Dphi, min_Dphi, max_Dphi, "#Delta#eta","#Delta#varphi", "A_{2}");
    h_B2_DetaDphi        = createHistogram(createName(bn,"B2_DetaDphi"),    nBins_Deta, min_Deta, max_Deta, nBins_Dphi, min_Dphi, max_Dphi, "#Delta#eta","#Delta#varphi", "B_{2}");
    h_C2_DetaDphi        = createHistogram(createName(bn,"C2_DetaDphi"),    nBins_Deta, min_Deta, max_Deta, nBins_Dphi, min_Dphi, max_Dphi, "#Delta#eta","#Delta#varphi", "C_{2}");
    h_D2_DetaDphi        = createHistogram(createName(bn,"D2_DetaDphi"),    nBins_Deta, min_Deta, max_Deta, nBins_Dphi, min_Dphi, max_Dphi, "#Delta#eta","#Delta#varphi", "D_{2}");
    h_R2_DetaDphi        = createHistogram(createName(bn,"R2_DetaDphi"),    nBins_Deta, min_Deta, max_Deta, nBins_Dphi, min_Dphi, max_Dphi, "#Delta#eta","#Delta#varphi", "R_{2}");
    
    h_rho2_DetaDphi_shft = createHistogram(createName(bn,"rho2_DetaDphi_shft"),  nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta#eta","#Delta#varphi", "#rho_{2}");
    h_A2_DetaDphi_shft   = createHistogram(createName(bn,"A2_DetaDphi_shft"),    nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta#eta","#Delta#varphi", "A_{2}");
    h_B2_DetaDphi_shft   = createHistogram(createName(bn,"B2_DetaDphi_shft"),    nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta#eta","#Delta#varphi", "B_{2}");
    h_C2_DetaDphi_shft   = createHistogram(createName(bn,"C2_DetaDphi_shft"),    nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta#eta","#Delta#varphi", "C_{2}");
    h_D2_DetaDphi_shft   = createHistogram(createName(bn,"D2_DetaDphi_shft"),    nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta#eta","#Delta#varphi", "D_{2}");
    h_R2_DetaDphi_shft   = createHistogram(createName(bn,"R2_DetaDphi_shft"),    nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta#eta","#Delta#varphi", "R_{2}");

    if (fillP2)
      {
      h_pt1pt1_etaEta        = createHistogram(createName(bn,"pt1pt1_etaEta"),  nBins_eta,   min_eta,   max_eta,   nBins_eta,   min_eta,  max_eta,            "#eta_{1}", "#eta_{2}",      "pt1pt1");
      h_DptDpt_etaEta        = createHistogram(createName(bn,"DptDpt_etaEta"),  nBins_eta,   min_eta,   max_eta,   nBins_eta,   min_eta,  max_eta,            "#eta_{1}", "#eta_{2}",      "<#Delta p_{T} #Delta p_{T}>");
      h_P2_etaEta            = createHistogram(createName(bn,"P2_etaEta"),      nBins_eta,   min_eta,   max_eta,   nBins_eta,   min_eta,  max_eta,            "#eta_{1}", "#eta_{2}",      "P_{2}");
      h_G2_etaEta            = createHistogram(createName(bn,"G2_etaEta"),      nBins_eta,   min_eta,   max_eta,   nBins_eta,   min_eta,  max_eta,            "#eta_{1}", "#eta_{2}",         "G_{2}");
      
      h_pt1pt1_DetaDphi      = createHistogram(createName(bn,"pt1pt1_DetaDphi"),nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi,      max_Dphi,      "#Delta#eta", "#Delta#varphi", "pt1pt1");
      h_DptDpt_DetaDphi      = createHistogram(createName(bn,"DptDpt_DetaDphi"),nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi,      max_Dphi,      "#Delta#eta",  "#Delta#varphi", "<#Delta p_{T}#Delta p_{T}>");
      h_P2_DetaDphi          = createHistogram(createName(bn,"P2_DetaDphi"),    nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi,      max_Dphi,      "#Delta#eta",  "#Delta#varphi", "P_{2}");
      h_G2_DetaDphi          = createHistogram(createName(bn,"G2_DetaDphi"),    nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi,      max_Dphi,      "#Delta#eta","#Delta#varphi",   "G_{2}");
      h_DptDpt_DetaDphi_shft = createHistogram(createName(bn,"DptDpt_DetaDphi_shft"),nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta#eta",  "#Delta#varphi", "<#Delta p_{T} #Delta p_{T}>");
      h_P2_DetaDphi_shft     = createHistogram(createName(bn,"P2_DetaDphi_shft"),    nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta#eta",  "#Delta#varphi", "P_{2}");
      h_G2_DetaDphi_shft     = createHistogram(createName(bn,"G2_DetaDphi_shft"),    nBins_Deta,  min_Deta,  max_Deta,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta#eta", "#Delta#varphi",  "G_{2}");
      }
    }
  
  if (fillY)
    {
    h_n1n1_yY           = createHistogram(createName(bn,"n1n1_yY"),      nBins_y,   min_y,   max_y,   nBins_y,   min_y,  max_y,                 "y_{1}",     "y_{2}", "<n_{1}><n_{1}>");
    h_A2_yY             = createHistogram(createName(bn,"A2_yY"),        nBins_y,   min_y,   max_y,   nBins_y,   min_y,  max_y,                 "y_{1}",    "y_{2}", "A_{2}");
    h_B2_yY             = createHistogram(createName(bn,"B2_yY"),        nBins_y,   min_y,   max_y,   nBins_y,   min_y,  max_y,                 "y_{1}",    "y_{2}", "B_{2}");
    h_C2_yY             = createHistogram(createName(bn,"C2_yY"),        nBins_y,   min_y,   max_y,   nBins_y,   min_y,  max_y,                 "y_{1}",    "y_{2}", "C_{2}");
    h_R2_yY             = createHistogram(createName(bn,"R2_yY"),        nBins_y,   min_y,   max_y,   nBins_y,   min_y,  max_y,                 "y_{1}",    "y_{2}", "R_{2}");

    h_n1n1_DyDphi       = createHistogram(createName(bn,"n1n1_DyDphi"),  nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,     "#Delta y",  "#Delta#varphi", "<n_{1}><n_{1}>");
    h_rho2_DyDphi       = createHistogram(createName(bn,"rho2_DyDphi"),  nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,     "#Delta y",  "#Delta#varphi", "#rho_{2}>");
    h_A2_DyDphi         = createHistogram(createName(bn,"A2_DyDphi"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,     "#Delta y",  "#Delta#varphi", "A_{2}");
    h_B2_DyDphi         = createHistogram(createName(bn,"B2_DyDphi"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,     "#Delta y",  "#Delta#varphi", "B_{2}");
    h_C2_DyDphi         = createHistogram(createName(bn,"C2_DyDphi"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,     "#Delta y",  "#Delta#varphi", "C_{2}");
    h_D2_DyDphi         = createHistogram(createName(bn,"D2_DyDphi"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,     "#Delta y",  "#Delta#varphi", "D_{2}");
    h_R2_DyDphi         = createHistogram(createName(bn,"R2_DyDphi"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,     "#Delta y",  "#Delta#varphi", "R_{2}");

    h_rho2_DyDphi_shft  = createHistogram(createName(bn,"rho2_DyDphi_shft"),  nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "#rho_{2}>");
    h_A2_DyDphi_shft    = createHistogram(createName(bn,"A2_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "A_{2}");
    h_B2_DyDphi_shft    = createHistogram(createName(bn,"B2_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "B_{2}");
    h_C2_DyDphi_shft    = createHistogram(createName(bn,"C2_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "C_{2}");
    h_D2_DyDphi_shft    = createHistogram(createName(bn,"D2_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "D_{2}");
    h_R2_DyDphi_shft    = createHistogram(createName(bn,"R2_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "R_{2}");

    // the following histos are for average along (y1+y2)/2

//    h_A2A_DyDphi_shft    = createHistogram(createName(bn,"A2A_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "A_{2}");
//    h_B2A_DyDphi_shft    = createHistogram(createName(bn,"B2A_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "B_{2}");
//    h_C2A_DyDphi_shft    = createHistogram(createName(bn,"C2A_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "C_{2}");
//    h_D2A_DyDphi_shft    = createHistogram(createName(bn,"D2A_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "D_{2}");
//    h_R2A_DyDphi_shft    = createHistogram(createName(bn,"R2A_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "R_{2}");

    if (fillP2)
      {
      h_pt1pt1_yY         = createHistogram(createName(bn,"pt1pt1_yY"),    nBins_y,   min_y,   max_y,   nBins_y,   min_y,  max_y,                  "y_{1}",    "y_{2}", "pt1pt1");
      h_DptDpt_yY         = createHistogram(createName(bn,"DptDpt_yY"),    nBins_y,   min_y,   max_y,   nBins_y,   min_y,  max_y,                  "y_{1}",    "y_{2}", "<#Delta p_{T} #Delta p_{T}>");
      h_P2_yY             = createHistogram(createName(bn,"P2_yY"),        nBins_y,   min_y,   max_y,   nBins_y,     min_y,         max_y,         "y_{1}",    "y_{2}",         "P_{2}");
      h_G2_yY             = createHistogram(createName(bn,"G2_yY"),        nBins_y,   min_y,   max_y,   nBins_y,   min_y,  max_y,                  "y_{1}",    "y_{2}", "G_{2}");
      
      h_pt1pt1_DyDphi     = createHistogram(createName(bn,"pt1pt1_DyDphi"),nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,      "#Delta y", "#Delta#varphi", "pt1pt1");
      h_DptDpt_DyDphi     = createHistogram(createName(bn,"DptDpt_DyDphi"),nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,      "#Delta y", "#Delta#varphi", "<#Delta p_{T}#Delta p_{T}>");
      h_P2_DyDphi         = createHistogram(createName(bn,"P2_DyDphi"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,      "#Delta y", "#Delta#varphi", "P_{2}");
      h_G2_DyDphi         = createHistogram(createName(bn,"G2_DyDphi"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi,      max_Dphi,      "#Delta y", "#Delta#varphi", "G_{2}");
      
      h_DptDpt_DyDphi_shft= createHistogram(createName(bn,"DptDpt_DyDphi_shft"),nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "<#Delta p_{T}#Delta p_{T}>");
      h_P2_DyDphi_shft    = createHistogram(createName(bn,"P2_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "P_{2}");
      h_G2_DyDphi_shft    = createHistogram(createName(bn,"G2_DyDphi_shft"),    nBins_Dy,  min_Dy,  max_Dy,  nBins_Dphi,  min_Dphi_shft, max_Dphi_shft, "#Delta y", "#Delta#varphi", "G_{2}");
      }
    }
  if (reportEnd(__FUNCTION__))
    ;
}

void ParticlePairDerivedHistos::importHistograms(TFile & inputFile)
{
  if (reportDebug(__FUNCTION__))
    ;
  const String & bn  = getName();
  const String & ptn = getParentTask()->getName();
  const String & ppn = getParentPathName();
  const Configuration & configuration = getConfiguration();

  fillEta    = configuration.getValueBool(ppn,"FillEta");
  fillY      = configuration.getValueBool(ppn,"FillY");
  fillP2     = configuration.getValueBool(ppn,"FillP2");
  if (reportDebug(__FUNCTION__))
    {
    cout << endl;
    printItem("Pair:Parent Task Name",  ptn);
    printItem("Pair:Parent Path Name",  ppn);
    printItem("Pair:Histo Base Name",   bn);
    printItem("Pair:FillEta",           fillEta);
    printItem("Pair:FillY",             fillY);
    printItem("Pair:FillP2",            fillP2);
    }

  h_n1n1_phiPhi          = loadH2(inputFile, CAP::createName(bn,"n1n1_phiPhi"));
  h_A2_phiPhi            = loadH2(inputFile, CAP::createName(bn,"A2_phiPhi"));
  h_B2_phiPhi            = loadH2(inputFile, CAP::createName(bn,"B2_phiPhi"));
  h_C2_phiPhi            = loadH2(inputFile, CAP::createName(bn,"C2_phiPhi"));
  h_R2_phiPhi            = loadH2(inputFile, CAP::createName(bn,"R2_phiPhi"));

  h_n1n1_ptpt            = loadH2(inputFile, CAP::createName(bn,"n1n1_ptpt"));
  h_A2_ptpt              = loadH2(inputFile, CAP::createName(bn,"A2_ptpt"));
  h_B2_ptpt              = loadH2(inputFile, CAP::createName(bn,"B2_ptpt"));
  h_C2_ptpt              = loadH2(inputFile, CAP::createName(bn,"C2_ptpt"));
  h_R2_ptpt              = loadH2(inputFile, CAP::createName(bn,"R2_ptpt"));

  if (fillP2)
    {
    h_pt1pt1_phiPhi      = loadH2(inputFile, CAP::createName(bn,"pt1pt1_phiPhi"));
    h_DptDpt_phiPhi      = loadH2(inputFile, CAP::createName(bn,"DptDpt_phiPhi"));
    h_P2_phiPhi          = loadH2(inputFile, CAP::createName(bn,"P2_phiPhi"));
    h_G2_phiPhi          = loadH2(inputFile, CAP::createName(bn,"G2_phiPhi"));
    }

  if (fillEta)
    {
    h_n1n1_etaEta        = loadH2(inputFile, CAP::createName(bn,"n1n1_etaEta"));
    h_A2_etaEta          = loadH2(inputFile, CAP::createName(bn,"A2_etaEta"));
    h_B2_etaEta          = loadH2(inputFile, CAP::createName(bn,"B2_etaEta"));
    h_C2_etaEta          = loadH2(inputFile, CAP::createName(bn,"C2_etaEta"));
    h_R2_etaEta          = loadH2(inputFile, CAP::createName(bn,"R2_etaEta"));

    h_n1n1_DetaDphi      = loadH2(inputFile, CAP::createName(bn,"n1n1_DetaDphi"));
    h_rho2_DetaDphi      = loadH2(inputFile, CAP::createName(bn,"rho2_DetaDphi"));
    h_A2_DetaDphi        = loadH2(inputFile, CAP::createName(bn,"A2_DetaDphi"));
    h_B2_DetaDphi        = loadH2(inputFile, CAP::createName(bn,"B2_DetaDphi"));
    h_C2_DetaDphi        = loadH2(inputFile, CAP::createName(bn,"C2_DetaDphi"));
    h_R2_DetaDphi        = loadH2(inputFile, CAP::createName(bn,"R2_DetaDphi"));

    h_rho2_DetaDphi_shft = loadH2(inputFile, CAP::createName(bn,"rho2_DetaDphi_shft"));
    h_A2_DetaDphi_shft   = loadH2(inputFile, CAP::createName(bn,"A2_DetaDphi_shft"));
    h_B2_DetaDphi_shft   = loadH2(inputFile, CAP::createName(bn,"B2_DetaDphi_shft"));
    h_C2_DetaDphi_shft   = loadH2(inputFile, CAP::createName(bn,"C2_DetaDphi_shft"));
    h_R2_DetaDphi_shft   = loadH2(inputFile, CAP::createName(bn,"R2_DetaDphi_shft"));

    if (fillP2)
      {
      h_pt1pt1_etaEta        = loadH2(inputFile, CAP::createName(bn,"pt1pt1_etaEta"));
      h_DptDpt_etaEta        = loadH2(inputFile, CAP::createName(bn,"DptDpt_etaEta"));
      h_P2_etaEta            = loadH2(inputFile, CAP::createName(bn,"P2_etaEta"));
      h_G2_etaEta            = loadH2(inputFile, CAP::createName(bn,"G2_etaEta"));

      h_pt1pt1_DetaDphi      = loadH2(inputFile, CAP::createName(bn,"pt1pt1_DetaDphi"));
      h_DptDpt_DetaDphi      = loadH2(inputFile, CAP::createName(bn,"DptDpt_DetaDphi"));
      h_P2_DetaDphi          = loadH2(inputFile, CAP::createName(bn,"P2_DetaDphi"));
      h_G2_DetaDphi          = loadH2(inputFile, CAP::createName(bn,"G2_DetaDphi"));
      h_DptDpt_DetaDphi_shft = loadH2(inputFile, CAP::createName(bn,"DptDpt_DetaDphi_shft"));
      h_P2_DetaDphi_shft     = loadH2(inputFile, CAP::createName(bn,"P2_DetaDphi_shft"));
      h_G2_DetaDphi_shft     = loadH2(inputFile, CAP::createName(bn,"G2_DetaDphi_shft"));
      }
    }

  if (fillY)
    {
    h_n1n1_yY           = loadH2(inputFile, CAP::createName(bn,"n1n1_yY"));
    h_A2_yY             = loadH2(inputFile, CAP::createName(bn,"A2_yY"));
    h_B2_yY             = loadH2(inputFile, CAP::createName(bn,"B2_yY"));
    h_C2_yY             = loadH2(inputFile, CAP::createName(bn,"C2_yY"));
    h_R2_yY             = loadH2(inputFile, CAP::createName(bn,"R2_yY"));

    h_n1n1_DyDphi       = loadH2(inputFile, CAP::createName(bn,"n1n1_DyDphi"));
    h_rho2_DyDphi       = loadH2(inputFile, CAP::createName(bn,"rho2_DyDphi"));
    h_A2_DyDphi         = loadH2(inputFile, CAP::createName(bn,"A2_DyDphi"));
    h_B2_DyDphi         = loadH2(inputFile, CAP::createName(bn,"B2_DyDphi"));
    h_C2_DyDphi         = loadH2(inputFile, CAP::createName(bn,"C2_DyDphi"));
    h_D2_DyDphi         = loadH2(inputFile, CAP::createName(bn,"D2_DyDphi"));
    h_R2_DyDphi         = loadH2(inputFile, CAP::createName(bn,"R2_DyDphi"));

    h_rho2_DyDphi_shft  = loadH2(inputFile, CAP::createName(bn,"rho2_DyDphi_shft"));
    h_A2_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"A2_DyDphi_shft"));
    h_B2_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"B2_DyDphi_shft"));
    h_C2_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"C2_DyDphi_shft"));
    h_D2_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"C2_DyDphi_shft"));
    h_R2_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"R2_DyDphi_shft"));

//    h_A2A_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"A2A_DyDphi_shft"));
//    h_B2A_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"B2A_DyDphi_shft"));
//    h_C2A_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"C2A_DyDphi_shft"));
//    h_R2A_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"R2A_DyDphi_shft"));


    if (fillP2)
      {
      h_pt1pt1_yY         = loadH2(inputFile, CAP::createName(bn,"pt1pt1_yY"));
      h_DptDpt_yY         = loadH2(inputFile, CAP::createName(bn,"DptDpt_yY"));
      h_P2_yY             = loadH2(inputFile, CAP::createName(bn,"P2_yY"));
      h_G2_yY             = loadH2(inputFile, CAP::createName(bn,"G2_yY"));

      h_pt1pt1_DyDphi     = loadH2(inputFile, CAP::createName(bn,"pt1pt1_DyDphi"));
      h_DptDpt_DyDphi     = loadH2(inputFile, CAP::createName(bn,"DptDpt_DyDphi"));
      h_P2_DyDphi         = loadH2(inputFile, CAP::createName(bn,"P2_DyDphi"));
      h_G2_DyDphi         = loadH2(inputFile, CAP::createName(bn,"G2_DyDphi"));

      h_DptDpt_DyDphi_shft= loadH2(inputFile, CAP::createName(bn,"DptDpt_DyDphi_shft"));
      h_P2_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"P2_DyDphi_shft"));
      h_G2_DyDphi_shft    = loadH2(inputFile, CAP::createName(bn,"G2_DyDphi_shft"));
      }
    }
}

void quickCopy(TH2 * source, TH2 * target)
{
  int sNx = source->GetNbinsX();
  int sNy = source->GetNbinsY();
  int tNx = target->GetNbinsX();
  int tNy = target->GetNbinsY();


  if (sNx!=tNx || sNy!=tNy)
    {
    TString s = source->GetName();
    s += "-->";
    s += target->GetName();
    throw CAP::HistogramException(s,"sNx!=tNx || sNy!=tNy","ParticlePairDerivedHistos::quickCopy(TH2 * source, TH2 * target)");
    }
  for (int iX=1; iX<sNx; iX++)
    {
    for (int iY=1; iY<sNy; iY++)
      {
      double v  = source->GetBinContent(iX,iY);
      double ev = source->GetBinError(iX,iY);
      target->SetBinContent(iX,iY,v);
      target->SetBinError(iX,iY,ev);
      }
    }
}


// HistogramGroup from ParticlePairDerivedHistos must be normalized "per event" before calling this function
void ParticlePairDerivedHistos::calculatePairDerivedHistograms(ParticleSingleHistos         & part1BaseHistos,
                                                               ParticleSingleHistos         & part2BaseHistos,
                                                               ParticleSingleDerivedHistos  & part1DerivedHistos,
                                                               ParticleSingleDerivedHistos  & part2DerivedHistos,
                                                               ParticlePairHistos     & pairHistos,
                                                               double bincorrection)
{
  if (reportStart(__FUNCTION__))
    ;
  //double yield1;
  double yield2;
  double avgPt1Phi;
  double avgPt2Phi;
  double scalingFactorPhi;
  double avgPt1Eta;
  double avgPt2Eta;
  double avgPt1Y;
  double avgPt2Y;
  double scalingFactorEta;
  double scalingFactorY;
  int ijNormalization = 0;


  //
  // pt vs pt
  //
  if (reportDebug(__FUNCTION__))
    {
    if (!part1BaseHistos.h_n1_pt ) throw HistogramException("LOGIC","!part1BaseHistos.h_n1_pt","ParticlePairDerivedHistos::calculatePairDerivedHistograms()");
    if (!part2BaseHistos.h_n1_pt ) throw HistogramException("LOGIC","!part2BaseHistos.h_n1_pt","ParticlePairDerivedHistos::calculatePairDerivedHistograms()");
    if (!pairHistos.h_n2_ptpt )    throw HistogramException("LOGIC","!pairHistos.h_n2_ptpt","ParticlePairDerivedHistos::calculatePairDerivedHistograms()");
    if (!h_n1n1_ptpt ) throw HistogramException("LOGIC","!h_n1n1_ptpt","ParticlePairDerivedHistos::calculatePairDerivedHistograms()");
    if (!h_C2_ptpt )   throw HistogramException("LOGIC","!h_C2_ptpt","ParticlePairDerivedHistos::calculatePairDerivedHistograms()");
    if (!h_B2_ptpt )   throw HistogramException("LOGIC","!h_B2_ptpt","ParticlePairDerivedHistos::calculatePairDerivedHistograms()");
    if (!h_A2_ptpt )   throw HistogramException("LOGIC","!h_A2_ptpt","ParticlePairDerivedHistos::calculatePairDerivedHistograms()");
    if (!h_R2_ptpt )   throw HistogramException("LOGIC","!h_R2_ptpt","ParticlePairDerivedHistos::calculatePairDerivedHistograms()");
    }
  //  yield1 = part1BaseHistos.h_n1_pt->Integral();
  yield2 = part2BaseHistos.h_n1_pt->Integral();
  calculateN1N1_H1H1H2( part1BaseHistos.h_n1_pt,   part2BaseHistos.h_n1_pt,  h_n1n1_ptpt,1.0, 1.0);
  h_C2_ptpt->Add(pairHistos.h_n2_ptpt,h_n1n1_ptpt,1.0,-1.0);
  h_B2_ptpt->Add(pairHistos.h_n2_ptpt);
  h_B2_ptpt->Scale(1.0/yield2);
  h_A2_ptpt->Add(h_C2_ptpt);
  h_A2_ptpt->Scale(1.0/yield2);
  calculateR2_H2H2H2(pairHistos.h_n2_ptpt,h_n1n1_ptpt,h_R2_ptpt,0, 1.0, 1.0);

  //
  // phi vs phi
  //
  if (reportDebug(__FUNCTION__))  cout << "Calculate XXX_phiPhi" << endl;
  //  yield1 = part1DerivedHistos.h_n1_phi->Integral();
  yield2 = part2DerivedHistos.h_n1_phi->Integral();
  calculateN1N1_H1H1H2( part1DerivedHistos.h_n1_phi,  part2DerivedHistos.h_n1_phi, h_n1n1_phiPhi,1.0, 1.0);
  h_C2_phiPhi->Add(pairHistos.h_n2_phiPhi,h_n1n1_phiPhi,1.0,-1.0);
  h_B2_phiPhi->Add(pairHistos.h_n2_phiPhi);
  h_B2_phiPhi->Scale(1.0/yield2);
  h_A2_phiPhi->Add(h_C2_phiPhi);
  h_A2_phiPhi->Scale(1.0/yield2);
  calculateR2_H2H2H2(pairHistos.h_n2_phiPhi,h_n1n1_phiPhi,h_R2_phiPhi,0, 1.0, 1.0);

  if (fillP2)
    {
    if (reportDebug(__FUNCTION__))  cout << " Calculate P2 vs phiPhi" << endl;
    avgPt1Phi = avgValue(part1DerivedHistos.h_pt_phi);
    avgPt2Phi = avgValue(part2DerivedHistos.h_pt_phi);
    scalingFactorPhi = 1.0/avgPt1Phi/avgPt2Phi;
    h_P2_phiPhi->Add(h_DptDpt_phiPhi,h_DptDpt_phiPhi,1.0,0.0);
    h_P2_phiPhi->Scale(scalingFactorPhi);
    }
  
  
  if (fillEta)
    {

    //
    // eta vs eta
    //
    if (reportDebug(__FUNCTION__))  cout <<  "Calculate XXX_etaEta" << endl;
    //    yield1 = part1DerivedHistos.h_n1_eta->Integral();
    yield2 = part2DerivedHistos.h_n1_eta->Integral();
    calculateN1N1_H1H1H2(part1DerivedHistos.h_n1_eta,part2DerivedHistos.h_n1_eta,h_n1n1_etaEta,1.0, 1.0);
    h_C2_etaEta->Add(pairHistos.h_n2_etaEta,h_n1n1_etaEta,1.0,-1.0);
    h_B2_etaEta->Add(pairHistos.h_n2_etaEta);
    h_B2_etaEta->Scale(1.0/yield2);
    h_A2_etaEta->Add(h_C2_etaEta);
    h_A2_etaEta->Scale(1.0/yield2);
    calculateR2_H2H2H2(pairHistos.h_n2_etaEta,h_n1n1_etaEta,h_R2_etaEta,0, 1.0, 1.0);

    //
    // Deta vs Dphi
    //
    if (reportDebug(__FUNCTION__))  cout << "Calculate XXX_DetaDphi" << endl;
    reduce_n1EtaPhiN1EtaPhiOntoN1N1DetaDphi(part1BaseHistos.h_n1_phiEta,part2BaseHistos.h_n1_phiEta,h_n1n1_DetaDphi,nBins_Deta,nBins_Dphi);
    h_rho2_DetaDphi->Add(pairHistos.h_n2_DetaDphi);
    h_C2_DetaDphi->Add(h_rho2_DetaDphi,h_n1n1_DetaDphi, 1.0, -1.0);
    h_B2_DetaDphi->Add(h_rho2_DetaDphi);
    h_B2_DetaDphi->Scale(1.0/yield2);
    h_A2_DetaDphi->Add(h_C2_DetaDphi);
    h_A2_DetaDphi->Scale(1.0/yield2);
    calculateR2_H2H2H2(h_rho2_DetaDphi,h_n1n1_DetaDphi,h_R2_DetaDphi,0,1.0,1.0);

    if (reportDebug(__FUNCTION__))  cout <<  " shiftY XXX_DetaDphi" << endl;
    shiftY(*h_rho2_DetaDphi,*h_rho2_DetaDphi_shft,nBins_Dphi_shft);
    shiftY(*h_A2_DetaDphi,*h_A2_DetaDphi_shft,nBins_Dphi_shft);
    shiftY(*h_B2_DetaDphi,*h_B2_DetaDphi_shft,nBins_Dphi_shft);
    shiftY(*h_C2_DetaDphi,*h_C2_DetaDphi_shft,nBins_Dphi_shft);
    shiftY(*h_R2_DetaDphi,*h_R2_DetaDphi_shft,nBins_Dphi_shft);
    
    if (fillP2)
      {
      avgPt1Eta = avgValue(part1DerivedHistos.h_pt_eta);
      avgPt2Eta = avgValue(part2DerivedHistos.h_pt_eta);
      scalingFactorEta = 1.0/avgPt1Eta/avgPt2Eta;
      h_P2_etaEta->Add(h_DptDpt_etaEta,h_DptDpt_etaEta,1.0,0.0);
      h_P2_etaEta->Scale(scalingFactorEta);
      
      if (reportDebug(__FUNCTION__))  cout <<  " shiftY(*h_R2_DetaDphi,*h_R2_DetaDphi_shft,nBins_Dphi_shft)" << endl;
      
      shiftY(*h_DptDpt_DetaDphi, *h_DptDpt_DetaDphi_shft,nBins_Dphi_shft);
      
      /// calculate average pt base on h_pt_eta histograms
      h_P2_DetaDphi->Add(h_DptDpt_DetaDphi,h_DptDpt_DetaDphi,1.0,0.0);
      h_P2_DetaDphi->Scale(scalingFactorEta);
      //symmetrizeDeltaEtaDeltaPhi(h_P2_DetaDphi,ijNormalization);
      shiftY(*h_P2_DetaDphi,*h_P2_DetaDphi_shft, nBins_Dphi_shft);
      
      calculateG2_H2H2H2H2( h_DptDpt_etaEta,   h_n1n1_etaEta,   h_pt1pt1_etaEta,   h_G2_etaEta,   ijNormalization, bincorrection, 1.0);
      calculateG2_H2H2H2H2( h_DptDpt_phiPhi,   h_n1n1_phiPhi,   h_pt1pt1_phiPhi,   h_G2_phiPhi,   ijNormalization, bincorrection, 1.0);
      calculateG2_H2H2H2H2( h_DptDpt_DetaDphi, h_n1n1_DetaDphi, h_pt1pt1_DetaDphi, h_G2_DetaDphi, ijNormalization, bincorrection, 1.0);
      shiftY(*h_G2_DetaDphi,*h_G2_DetaDphi_shft,nBins_Dphi_shft);
      }
    }
  
  if (fillY)
    {
    //
    // y vs y
    //
    if (reportDebug(__FUNCTION__))  cout <<  "Calculate XXX_yY" << endl;
    //    yield1 = part1DerivedHistos.h_n1_y->Integral();
    yield2 = part2DerivedHistos.h_n1_y->Integral();
    calculateN1N1_H1H1H2(part1DerivedHistos.h_n1_y,part2DerivedHistos.h_n1_y,h_n1n1_yY,1.0, 1.0);
    h_C2_yY->Add(pairHistos.h_n2_yY,h_n1n1_yY,1.0,-1.0);
    h_B2_yY->Add(pairHistos.h_n2_yY);
    h_B2_yY->Scale(1.0/yield2);
    h_A2_yY->Add(h_C2_yY);
    h_A2_yY->Scale(1.0/yield2);
    calculateR2_H2H2H2(pairHistos.h_n2_yY,h_n1n1_yY,h_R2_yY,0, 1.0, 1.0);

    //
    // Dy vs Dphi
    //
    if (reportDebug(__FUNCTION__))  cout << "Calculate XXX_DyDphi" << endl;
    reduce_n1EtaPhiN1EtaPhiOntoN1N1DetaDphi(part1BaseHistos.h_n1_phiY,part2BaseHistos.h_n1_phiY,h_n1n1_DyDphi,nBins_Dy,nBins_Dphi);
    h_rho2_DyDphi->Add(pairHistos.h_n2_DyDphi);
    h_C2_DyDphi->Add(h_rho2_DyDphi,h_n1n1_DyDphi, 1.0, -1.0);
    h_B2_DyDphi->Add(h_rho2_DyDphi);
    h_B2_DyDphi->Scale(1.0/yield2);
    h_A2_DyDphi->Add(h_C2_DyDphi);
    h_A2_DyDphi->Scale(1.0/yield2);
    calculateR2_H2H2H2(h_rho2_DyDphi,h_n1n1_DyDphi,h_R2_DyDphi,0,1.0,1.0);

    vector<double> omegaFactor;
    omegaFactor.clear();
    calculateOmegaFactor(h_A2_DyDphi, omegaFactor);
    calculateAverageYbar(h_A2_DyDphi, h_D2_DyDphi, omegaFactor);

    if (reportDebug(__FUNCTION__))  cout <<  " shift XXX_DyDphi" << endl;
    shiftY(*h_rho2_DyDphi,*h_rho2_DyDphi_shft,   nBins_Dphi_shft);
    shiftY(*h_A2_DyDphi,  *h_A2_DyDphi_shft,     nBins_Dphi_shft);
    shiftY(*h_B2_DyDphi,  *h_B2_DyDphi_shft,     nBins_Dphi_shft);
    shiftY(*h_C2_DyDphi,  *h_C2_DyDphi_shft,     nBins_Dphi_shft);
    shiftY(*h_D2_DyDphi,  *h_D2_DyDphi_shft,     nBins_Dphi_shft);
    shiftY(*h_R2_DyDphi,  *h_R2_DyDphi_shft,     nBins_Dphi_shft);

    //    vector<double> omegaFactor;
    //    calculateOmegaFactor(h_rho2_DyDphi, omegaFactor)
    //    calculateAverageYbar(h_A2_DyDphi, h_A2A_DyDphi, omegaFactor);
    //    calculateAverageYbar(h_B2_DyDphi, h_B2A_DyDphi, omegaFactor);
    //    calculateAverageYbar(h_C2_DyDphi, h_C2A_DyDphi, omegaFactor);
    //    calculateAverageYbar(h_R2_DyDphi, h_R2A_DyDphi, omegaFactor);


    if (fillP2)
      {
      avgPt1Y = avgValue(part1DerivedHistos.h_pt_y);
      avgPt2Y = avgValue(part2DerivedHistos.h_pt_y);
      scalingFactorY = 1.0/avgPt1Y/avgPt2Y;
      h_P2_yY->Add(h_DptDpt_yY,h_DptDpt_yY,1.0,0.0);
      h_P2_yY->Scale(scalingFactorY);
      
      if (reportDebug(__FUNCTION__))  cout <<  " shiftY(*h_R2_DyDphi,*h_R2_DyDphi_shft,nBins_Dphi_shft)" << endl;
      
      shiftY(*h_DptDpt_DyDphi, *h_DptDpt_DyDphi_shft,nBins_Dphi_shft);
      
      /// calculate average pt base on h_pt_eta histograms
      h_P2_DyDphi->Add(h_DptDpt_DyDphi,h_DptDpt_DyDphi,1.0,0.0);
      h_P2_DyDphi->Scale(scalingFactorY);
      //symmetrizeDeltaEtaDeltaPhi(h_P2_DetaDphi,ijNormalization);
      shiftY(*h_P2_DyDphi,*h_P2_DyDphi_shft, nBins_Dphi_shft);
      
      calculateG2_H2H2H2H2( h_DptDpt_yY,       h_n1n1_yY,       h_pt1pt1_yY,       h_G2_yY,       ijNormalization, bincorrection, 1.0);
      calculateG2_H2H2H2H2( h_DptDpt_phiPhi,   h_n1n1_phiPhi,   h_pt1pt1_phiPhi,   h_G2_phiPhi,   ijNormalization, bincorrection, 1.0);
      calculateG2_H2H2H2H2( h_DptDpt_DetaDphi, h_n1n1_DetaDphi, h_pt1pt1_DetaDphi, h_G2_DetaDphi, ijNormalization, bincorrection, 1.0);
      shiftY(*h_G2_DetaDphi,*h_G2_DetaDphi_shft,nBins_Dphi_shft);
      }
    }
  if (reportEnd(__FUNCTION__))
    ;
}

void ParticlePairDerivedHistos::calculateOmegaFactor(TH2 * source, vector<double> & omegaFactor)
{
  int nY  = source->GetNbinsX(); // bins in delta rapidity
  double y0;
//  String name = source->GetName();
//  name += "_tempo_x";
//  TH1 * proj = source->ProjectionX(name);
//  int iRap = nY;
//  double y0 = proj->GetXaxis()->GetBinUpEdge(nY);
//  for (int iY=0; iY<(nY+1)/2; iY++)
//    {
//    if (proj->GetBinContent(iRap)>0)
//      {
//      y0 = proj->GetXaxis()->GetBinUpEdge(iRap);
//      break;
//      }
//    iRap--;
//    }
  y0 = 2.0*max_yAcc;
  for (int iY=1; iY<=nY; iY++) // delta rapidity loop
    {
    double dy = source->GetXaxis()->GetBinCenter(iY);
    omegaFactor.push_back(1.0- TMath::Abs(dy/y0));
    //cout << " index : " << iY << "  dy: " << dy << " Omega: " << omegaFactor[iY] << endl;
    }
}


void ParticlePairDerivedHistos::calculateAverageYbar(TH2 * source,
                                                     TH2 * target,
                                                     vector<double> & omegaFactor)
{
  cout << "calculateAverageYbar(TH2 *source,TH2*target,vector<double>&omegaFactor)" << endl;

  double scale = 1.0;
  int nX = source->GetNbinsX();
  int nY = source->GetNbinsY();
  //cout << " HISTO: " << source->GetName() << endl;
  //cout << " nX: " << nX << "    nY:" << nY << endl;
  for (int iX=1; iX<=nX; iX++)
    {
    scale = 1.0/omegaFactor[iX-1];
    //if (iX>180 && iX<220) cout << " iX: " << iX << " omegaFactor: " << omegaFactor[iX-1] << " scale:" << scale << endl;
    for (int iY=1; iY<=nY; iY++)
      {
      double v  =  source->GetBinContent(iX,iY);
      double ev =  source->GetBinError(iX,iY);
      //if (iX>190 && iX<210) cout << " v: " << v << "+-" << ev << " v*scale:" << v*scale << "+-" << ev*scale << endl;
      target->SetBinContent(iX,iY,v*scale);
      target->SetBinError(iX,iY,ev*scale);
      }
    }
//  exit(1);
}


} // namespace CAP
