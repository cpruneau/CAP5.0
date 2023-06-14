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
#include "ParticlePairHistos.hpp"
using CAP::ParticlePairHistos;

ClassImp(ParticlePairHistos);

ParticlePairHistos::ParticlePairHistos(Task * _parent,
                                       const String & _name,
                                       const Configuration & _configuration)
:
HistogramGroup(_parent,_name,_configuration),
nBins_n1(0),
min_n1(0),
max_n1(0),
nBins_n2(0),
min_n2(0),
max_n2(0),
nBins_pt(0),
min_pt(0),
max_pt(0),
range_pt(0),
scale_pt(0),
nBins_phi(0),
min_phi(0),
max_phi(0),
range_phi(0),
scale_phi(0),
nBins_eta(0),
min_eta(0),
max_eta(0),
range_eta(0),
scale_eta(0),
nBins_y(0),
min_y(0),
max_y(0),
range_y(0),
scale_y(0),
nBins_Dphi(0),
min_Dphi(0),
max_Dphi(0),
width_Dphi(0),
nBins_Deta(0),
min_Deta(0),
max_Deta(0),
nBins_Dy(0),
min_Dy(0),
max_Dy(0),
nBins_Dphi_shft(0),
min_Dphi_shft(0),
max_Dphi_shft(0),
fillEta(false),
fillY(false),
fillP2(false),
h_n2(nullptr),
h_n2_ptpt(nullptr),
h_n2_etaEta(nullptr),
h_DptDpt_etaEta(nullptr),
h_n2_phiPhi(nullptr),
h_DptDpt_phiPhi(nullptr),
h_n2_yY(nullptr),
h_DptDpt_yY(nullptr),
h_n2_DetaDphi(nullptr),
h_DptDpt_DetaDphi(nullptr),
h_n2_DyDphi(nullptr),
h_DptDpt_DyDphi(nullptr)
{
  appendClassName("ParticlePairHistos");
}

void ParticlePairHistos::createHistograms()
{
  if ( reportStart(__FUNCTION__))
    { }

  const String & bn  = getName();
  const String & ptn = getParentName();
  const String & ppn = getParentPathName();
  const Configuration & configuration = getConfiguration();

  nBins_n2  = configuration.getValueInt(ppn,   "nBins_n2");
  min_n2    = configuration.getValueDouble(ppn,"Min_n2");
  max_n2    = configuration.getValueDouble(ppn,"Max_n2");
  
  nBins_n2  = configuration.getValueInt(ppn,   "nBins_n2");
  min_n2    = configuration.getValueDouble(ppn,"Min_n2");
  max_n2    = configuration.getValueDouble(ppn,"Max_n2");

  nBins_pt = configuration.getValueInt(ppn,   "nBins_pt");
  min_pt   = configuration.getValueDouble(ppn,"Min_pt");
  max_pt   = configuration.getValueDouble(ppn,"Max_pt");
  range_pt = max_pt - min_pt;
  scale_pt = double(nBins_pt)/range_pt;

  nBins_phi   = configuration.getValueInt(ppn,   "nBins_phi");
  min_phi     = configuration.getValueDouble(ppn,"Min_phi");
  max_phi     = configuration.getValueDouble(ppn,"Max_phi");
  range_phi   = max_phi - min_phi;
  scale_phi   = double(nBins_phi)/range_phi;
  width_Dphi  = range_phi/double(nBins_phi);

  nBins_Dphi       = nBins_phi;
  min_Dphi         = 0.0; //-width_Dphi/2.;
  max_Dphi         = CAP::Math::twoPi(); // - width_Dphi/2.;
  nBins_Dphi_shft  = int(double(nBins_Dphi)/4.0);
  min_Dphi_shft    = min_Dphi - width_Dphi*double(nBins_Dphi_shft);
  max_Dphi_shft    = max_Dphi - width_Dphi*double(nBins_Dphi_shft);

  nBins_eta = configuration.getValueInt(ppn,   "nBins_eta");
  min_eta   = configuration.getValueDouble(ppn,"Min_eta");
  max_eta   = configuration.getValueDouble(ppn,"Max_eta");
  range_eta = max_eta - min_eta;
  scale_eta = double(nBins_eta)/range_eta;

  nBins_Deta= 2*nBins_eta-1;
  min_Deta  = -range_eta;
  max_Deta  = range_eta;

  nBins_y = configuration.getValueInt(ppn,   "nBins_y");
  min_y   = configuration.getValueDouble(ppn,"Min_y");
  max_y   = configuration.getValueDouble(ppn,"Max_y");
  range_y = max_y - min_y;
  scale_y = double(nBins_y)/range_y;

  //  nBins_DeltaP  = configuration.getValueInt(ppn,"nBins_DeltaP");
  //  min_DeltaP    = configuration.getValueDouble(ppn,"Min_DeltaP");
  //  max_DeltaP    = configuration.getValueDouble(ppn,"Max_DeltaP");

  nBins_Dy  = 2*nBins_y-1;
  min_Dy    = -range_y;
  max_Dy    = range_y;

  fillEta    = configuration.getValueBool(ppn,"FillEta");
  fillY      = configuration.getValueBool(ppn,"FillY");
  fillP2     = configuration.getValueBool(ppn,"FillP2");
  //fill3D     = configuration.getValueBool(ppn,"Fill3D");

  if (reportDebug(__FUNCTION__))
    {
    cout << endl;
    printItem("Pair:Parent Task Name",    ptn);
    printItem("Pair:Parent Path Name",    ppn);
    printItem("Pair:Histo Base Name",    bn);
    printItem("Pair:FillEta",    fillEta    );
    printItem("Pair:FillY",    fillY      );
    printItem("Pair:FillP2",    fillP2     );
    printItem("Pair:nBins_n2",    nBins_n2   );
    printItem("Pair:Min_n2",    min_n2     );
    printItem("Pair:Max_n2",    max_n2     );
    printItem("Pair:nBins_pt",    nBins_pt     );
    printItem("Pair:Min_pt",    min_pt       );
    printItem("Pair:Max_pt",    max_pt       );
    printItem("Pair:range_pt",    range_pt     );
    printItem("Pair:scale_pt",    scale_pt     );
    printItem("Pair:nBins_phi",    nBins_phi   );
    printItem("Pair:Min_phi",    min_phi     );
    printItem("Pair:Max_phi",    max_phi     );
    printItem("Pair:range_phi",    range_phi   );
    printItem("Pair:scale_phi",    scale_phi   );
    printItem("Pair:width_Dphi",    width_Dphi  );
    printItem("Pair:nBins_Dphi",    nBins_Dphi  );
    printItem("Pair:min_Dphi",    min_Dphi    );
    printItem("Pair:max_Dphi",    max_Dphi    );
    printItem("Pair:nBins_Dphi_shft",    nBins_Dphi_shft);
    printItem("Pair:min_Dphi_shft",    min_Dphi_shft  );
    printItem("Pair:max_Dphi_shft",    max_Dphi_shft  );
    printItem("Pair:nBins_eta",    nBins_eta   );
    printItem("Pair:Min_eta",    min_eta     );
    printItem("Pair:Max_eta",    max_eta     );
    printItem("Pair:range_eta",    range_eta   );
    printItem("Pair:scale_eta",    scale_eta   );
    printItem("Pair:nBins_Deta",    nBins_Deta  );
    printItem("Pair:min_Deta",    min_Deta    );
    printItem("Pair:max_Deta",    max_Deta    );
    printItem("Pair:nBins_y",    nBins_y     );
    printItem("Pair:Min_y",    min_y       );
    printItem("Pair:Max_y",    max_y       );
    printItem("Pair:range_y",    range_y     );
    printItem("Pair:scale_y",    scale_y     );
    printItem("Pair:nBins_Dy",    nBins_Dy    );
    printItem("Pair:Min_Dy",    min_Dy      );
    printItem("Pair:Max_Dy",    max_Dy      );
//    printItem("Pair:nBins_DeltaP",    standaloneMode     );
//    printItem("Pair:Min_DeltaP",    standaloneMode     );
//    printItem("Pair:Max_DeltaP",    standaloneMode     );
    }

  h_n2          = createHistogram(createName(bn,"n2"),         nBins_n2,  min_n2,  max_n2, "n_{2}", "Yield");
  h_n2_ptpt     = createHistogram(createName(bn,"n2_ptpt"),    nBins_pt,  min_pt,  max_pt, nBins_pt, min_pt, max_pt,   "p_{T,1}",  "p_{T,2}", "N_{2}");
  h_n2_phiPhi   = createHistogram(createName(bn,"n2_phiPhi"),  nBins_phi, min_phi, max_phi, nBins_phi, min_phi, max_phi, "#varphi_{1}", "#varphi_{2}", "N_{2}");

  if (fillP2)
    {
    h_DptDpt_phiPhi = createHistogram(createName(bn,"ptpt_phiPhi"),   nBins_phi, min_phi, max_phi, nBins_phi, min_phi, max_phi, "#varphi_{1}", "#varphi_{2}", "p_{T}xp_{T}");
    }

  if (fillEta)
    {
    h_n2_etaEta   = createHistogram(createName(bn,"n2_etaEta"),   nBins_eta,  min_eta, max_eta, nBins_eta, min_eta, max_eta, "#eta_{1}", "#eta_{2}", "N_{2}");
    h_n2_DetaDphi = createHistogram(createName(bn,"n2_DetaDphi"), nBins_Deta, min_Deta, max_Deta, nBins_Dphi, min_Dphi, max_Dphi, "#Delta#eta", "#Delta#phi", "N_{2}");
    if (fillP2)
      {
      h_DptDpt_etaEta = createHistogram(createName(bn,"ptpt_etaEta"), nBins_eta, min_eta, max_eta, nBins_eta, min_eta, max_eta, "#eta_{1}", "#eta_{2}", "p_{T}xp_{T}");
      h_DptDpt_DetaDphi = createHistogram(createName(bn,"ptpt_DetaDphi"),nBins_Deta, min_Deta, max_Deta, nBins_Dphi, min_Dphi, max_Dphi, "#Delta#eta", "#Delta#phi", "ptpt");
      }
    }

  if (fillY)
    {
    h_n2_yY     = createHistogram(createName(bn,"n2_yY"),     nBins_y,  min_y,  max_y,  nBins_y, min_y, max_y, "y_{1}","y_{2}", "N_{2}");
    h_n2_DyDphi = createHistogram(createName(bn,"n2_DyDphi"), nBins_Dy, min_Dy, max_Dy, nBins_Dphi, min_Dphi, max_Dphi, "#Delta y", "#Delta#phi", "N_{2}");
    if (fillP2)
      {
      h_DptDpt_yY    = createHistogram(createName(bn,"ptpt_yY"),  nBins_y,  min_y, max_y, nBins_y, min_y, max_y, "y_{1}","y_{2}", "p_{T}xp_{T}");
      h_DptDpt_DyDphi = createHistogram(createName(bn,"ptpt_DyDphi"),nBins_Dy, min_Dy, max_Dy, nBins_Dphi, min_Dphi, max_Dphi, "#Delta y", "#Delta#phi", "ptpt");
      }
    }

  //  if (fill3D)
  //    {
  //    h_n2_DeltaP    = createHistogram(createName(bn,"n2_DeltaP"),
  //                                     nBins_DeltaP,  min_DeltaP, max_DeltaP,
  //                                     nBins_DeltaP,  min_DeltaP, max_DeltaP,
  //                                     nBins_DeltaP,  min_DeltaP, max_DeltaP,
  //                                     "p_{s}","p_{o}", "p_{l}","n_{2}");
  //    }

  if ( reportEnd(__FUNCTION__))
    { }
}

//________________________________________________________________________
void ParticlePairHistos::importHistograms(TFile & inputFile)
{
  if (reportStart(__FUNCTION__))
    ;
   const String & bn  = getName();
  const String & ptn = getParentName();
  const String & ppn = getParentPathName();
  fillEta       = configuration.getValueBool(ppn,"FillEta");
  fillY         = configuration.getValueBool(ppn,"FillY");
  fillP2        = configuration.getValueBool(ppn,"FillP2");
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("Pair:Parent Task Name",   ptn);
    printItem("Pair:Parent Path Name",   ppn);
    printItem("Pair:Histo Base Name",    bn);
    printItem("Pair:FillEta",            fillEta);
    printItem("Pair:FillY",              fillY);
    printItem("Pair:FillP2",             fillP2);
    }
  h_n2          = loadH1(inputFile, CAP::createName(bn,"n2"));
  h_n2_ptpt     = loadH2(inputFile, CAP::createName(bn,"n2_ptpt"));
  h_n2_phiPhi   = loadH2(inputFile, CAP::createName(bn,"n2_phiPhi"));

  if (fillP2)
    {
    h_DptDpt_phiPhi = loadH2(inputFile, CAP::createName(bn,"ptpt_phiPhi"));
    }

  if (fillEta)
    {
    h_n2_etaEta   = loadH2(inputFile, CAP::createName(bn,"n2_etaEta"));
    h_n2_DetaDphi = loadH2(inputFile, CAP::createName(bn,"n2_DetaDphi"));
    if (fillP2)
      {
      h_DptDpt_etaEta   = loadH2(inputFile, CAP::createName(bn,"ptpt_etaEta"));
      h_DptDpt_DetaDphi = loadH2(inputFile, CAP::createName(bn,"ptpt_DetaDphi"));
      }
    }
  if (fillY)
    {
    h_n2_yY     = loadH2(inputFile, CAP::createName(bn,"n2_yY"));
    h_n2_DyDphi = loadH2(inputFile, CAP::createName(bn,"n2_DyDphi"));
    if (fillP2)
      {
      h_DptDpt_yY     = loadH2(inputFile, CAP::createName(bn,"ptpt_yY"));
      h_DptDpt_DyDphi = loadH2(inputFile, CAP::createName(bn,"ptpt_DyDphi"));
      }
    }
  if (reportEnd(__FUNCTION__))
    ;
}

void ParticlePairHistos::fill(vector<ParticleDigit*> & particle1, vector<ParticleDigit*> & particle2, bool same, double weight)
{
//  double nPairs    = 0;
//  double nPairsEta = 0;
//  double nPairsY   = 0;
//  int iG;
//
//  for (unsigned int iPart1=0; iPart1<particle1.size(); iPart1++)
//    {
//    float pt1 = particle1[iPart1]->pt;
//    float dpt1 = pt1; // - avgPt1
//    unsigned int iPt_1  = particle1[iPart1]->iPt;
//    unsigned int iPhi_1 = particle1[iPart1]->iPhi;
//    unsigned int iEta_1 = particle1[iPart1]->iEta;
//    unsigned int iY_1   = particle1[iPart1]->iY;
//
//    for (unsigned int iPart2=(same?iPart1+1: 0); iPart2<particle2.size(); iPart2++)
//      {
//      float pt2 = particle2[iPart2]->pt;
//      float dpt2 = pt2; // - avgPt2
//      unsigned int iPt_2  = particle2[iPart2]->iPt;
//      unsigned int iPhi_2 = particle2[iPart2]->iPhi;
//      unsigned int iEta_2 = particle2[iPart2]->iEta;
//      unsigned int iY_2   = particle2[iPart2]->iY;
//
//      nPairs++;
//      iG = h_n2_ptpt->GetBin(iPt_1,iPt_2);
//      h_n2_ptpt->AddBinContent(iG,  weight);
//
//      iG = h_n2_phiPhi->GetBin(iPhi_1,iPhi_2);
//      h_n2_phiPhi->AddBinContent(iG,  weight);
//      if (fillP2)
//        {
//        h_DptDpt_phiPhi ->AddBinContent(iG,weight*dpt1*dpt2);
//        }
//      if (same)
//        {
//        nPairs++;
//        iG = h_n2_ptpt->GetBin(iPt_2,iPt_1);
//        h_n2_ptpt->AddBinContent(iG,  weight);
//        iG = h_n2_phiPhi->GetBin(iPhi_2,iPhi_1);
//        h_n2_phiPhi->AddBinContent(iG,  weight);
//        if (fillP2)
//          {
//          h_DptDpt_phiPhi->AddBinContent(iG,weight*pt1*pt2);
//          }
//        }
//
//      if (fillEta && iEta_1!=0 && iEta_2!=0 )
//        {
//        nPairsEta++;
//        // delta-eta maps onto a 2n-1 range i.e., 0 to 2n-2
//        int iDeltaEta  = iEta_1-iEta_2 + nBins_eta-1;
//        int iDeltaPhi  = iPhi_1-iPhi_2;
//        if (iDeltaPhi < 0) iDeltaPhi += nBins_phi;
//
//        iG = h_n2_etaEta->GetBin(iEta_1,iEta_2);
//        h_n2_etaEta->AddBinContent(iG,weight);
//        if (fillP2)
//          {
//          h_DptDpt_etaEta->AddBinContent(iG,weight*pt1*pt2);
//          }
//
//        iG = h_n2_DetaDphi->GetBin(iDeltaEta+1,iDeltaPhi+1);
//        h_n2_DetaDphi->AddBinContent(iG,weight);
//        if (fillP2)
//          {
//          h_DptDpt_DetaDphi->AddBinContent(iG,weight*pt1*pt2);
//          }
//        if (same)
//          {
//          nPairsEta++;
//          // delta-eta maps onto a 2n-1 range i.e., 0 to 2n-2
//          iDeltaEta  = iEta_2-iEta_1 + nBins_eta-1;
//          iDeltaPhi  = iPhi_2-iPhi_1;
//          if (iDeltaPhi < 0) iDeltaPhi += nBins_phi;
//          iG = h_n2_etaEta->GetBin(iEta_2,iEta_1);
//          h_n2_etaEta->AddBinContent(iG,weight);
//          if (fillP2)
//            {
//            h_DptDpt_etaEta->AddBinContent(iG,weight*pt1*pt2);
//            }
//
//          iG = h_n2_DetaDphi->GetBin(iDeltaEta+1,iDeltaPhi+1);
//          h_n2_DetaDphi->AddBinContent(iG,weight);
//          if (fillP2)
//            {
//            h_DptDpt_DetaDphi->AddBinContent(iG,weight*pt1*pt2);
//            }
//          }
//        }
//
//      if (fillY && iY_1!=0 && iY_2!=0 )
//        {
//        nPairsY++;
//        int iDeltaY    = iY_1-iY_2 + nBins_y-1;
//        int iDeltaPhi  = iPhi_1-iPhi_2;
//        if (iDeltaPhi < 0) iDeltaPhi += nBins_phi;
//
//        iG = h_n2_yY->GetBin(iY_1,iY_2);
//        h_n2_yY->AddBinContent(iG,weight);
//        if (fillP2)
//          {
//          h_DptDpt_yY->AddBinContent(iG,weight*pt1*pt2);
//          }
//
//        iG = h_n2_DyDphi->GetBin(iDeltaY+1,iDeltaPhi+1);
//        h_n2_DyDphi  ->AddBinContent(iG,weight);
//        if (fillP2)
//          {
//          h_DptDpt_DyDphi->AddBinContent(iG,weight*pt1*pt2);
//          }
//        if (same)
//          {
//          nPairsY++;
//          int iDeltaY   = iY_2-iY_1 + nBins_y-1;
//          int iDeltaPhi  = iPhi_2-iPhi_1;
//          if (iDeltaPhi < 0) iDeltaPhi += nBins_phi;
//
//          iG = h_n2_yY->GetBin(iY_1,iY_2);
//          h_n2_yY->AddBinContent(iG,weight);
//          if (fillP2)
//            {
//            h_DptDpt_yY->AddBinContent(iG,weight*pt1*pt2);
//            }
//
//          iG = h_n2_DyDphi->GetBin(iDeltaY+1,iDeltaPhi+1);
//          h_n2_DyDphi  ->AddBinContent(iG,weight);
//          if (fillP2)
//            {
//            h_DptDpt_DyDphi->AddBinContent(iG,weight*pt1*pt2);
//            }
//          }
//        }
//      }
//    }
//
//  // Update number of entries
//  h_n2_ptpt->SetEntries(h_n2_ptpt->GetEntries()+nPairs);
//  h_n2_phiPhi->SetEntries(h_n2_phiPhi->GetEntries()+nPairs);
//  if (fillP2)
//    {
//    h_DptDpt_phiPhi->SetEntries(h_DptDpt_phiPhi->GetEntries()+nPairs);
//    }
//  if (fillEta)
//    {
//    h_n2_etaEta->SetEntries(h_n2_etaEta->GetEntries()+nPairsEta);
//    h_n2_DetaDphi->SetEntries(h_n2_DetaDphi->GetEntries()+nPairsEta);
//    if (fillP2)
//      {
//      h_DptDpt_etaEta->SetEntries(h_DptDpt_etaEta->GetEntries()+nPairsEta);
//      h_DptDpt_DetaDphi->SetEntries(h_DptDpt_DetaDphi->GetEntries()+nPairsEta);
//      }
//    }
//
//  if (fillY)
//    {
//    h_n2_yY->SetEntries(h_n2_yY->GetEntries()+nPairsY);
//    h_n2_DyDphi->SetEntries(h_n2_DyDphi->GetEntries()+nPairsY);
//    if (fillP2)
//      {
//      h_DptDpt_yY->SetEntries(h_DptDpt_yY->GetEntries()+nPairsY);
//      h_DptDpt_DyDphi->SetEntries(h_DptDpt_DyDphi->GetEntries()+nPairsY);
//      }
//    }
//  h_n2->Fill(double(nPairs),weight);
}

void ParticlePairHistos::fill(Particle & particle1, Particle & particle2, double weight)
{
//  if (reportInfo(__FUNCTION__))
//    ;

 int iPhi1, iPt1, iEta1, iY1;
  int iPhi2, iPt2, iEta2, iY2;
  int iGPtPt;
  int iGPhiPhi;
  int iGEtaEta;
  int iGYY;
  int iGDeltaEtaDeltaPhi;
  int iGDeltaYDeltaPhi;

  LorentzVector & momentum1 = particle1.getMomentum();
  double pt1   = momentum1.Pt();        iPt1 = getPtBinFor(pt1);
  double phi1  = momentum1.Phi();       if (phi1<0.0) phi1 += CAP::Math::twoPi(); iPhi1 = getPhiBinFor(phi1);
  double eta1  = momentum1.Eta();       iEta1 = fillEta ? getEtaBinFor(eta1) : 0;
  double y1    = momentum1.Rapidity();  iY1   = fillY   ? getYBinFor(y1)     : 0;

  LorentzVector & momentum2 = particle2.getMomentum();
  double pt2   = momentum2.Pt();        iPt2 = getPtBinFor(pt2);
  double phi2  = momentum2.Phi();       if (phi2<0.0) phi2 += CAP::Math::twoPi(); iPhi2 = getPhiBinFor(phi2);
  double eta2  = momentum2.Eta();       iEta2 = fillEta ? getEtaBinFor(eta2) : 0;
  double y2    = momentum2.Rapidity();  iY2   = fillY   ? getYBinFor(y2)     : 0;

//  cout <<  "pt1:" << pt1 << " phi1:" << phi1 << " y1:" << y1 << " iPt1: " << iPt1 << " iPhi1:" <<  iPhi1 << " iY1:" <<  iY1 << endl;
//  cout <<  "pt2:" << pt2 << " phi2:" << phi2 << " y2:" << y2 << " iPt2: " << iPt2 << " iPhi2:" <<  iPhi2 << " iY2:" <<  iY2 << endl;

  if (iPt1==0  || iPt2==0)  return;
  if (iPhi1==0 || iPhi1==0) return;
  if (iEta1==0 && iY1==0) return;
  if (iEta2==0 && iY2==0) return;
  int iDeltaEta  = iEta1-iEta2 + nBins_eta-1;
  int iDeltaY    = iY1-iY2 + nBins_y-1;
  int iDeltaPhi  = iPhi1-iPhi2;
  if (iDeltaPhi < 0) iDeltaPhi += nBins_phi;
  //cout <<  "iDeltaY:" << iDeltaY << " iDeltaPhi: " << iDeltaPhi << endl;
  fillP2 = false;
  fillY  = true;

  iGPtPt   = h_n2_ptpt->GetBin(iPt1,iPt2);
  iGPhiPhi = h_n2_phiPhi->GetBin(iPhi1,iPhi2);

  h_n2_ptpt   ->AddBinContent(iGPtPt,    weight);  h_n2_ptpt  ->SetEntries(h_n2_ptpt  ->GetEntries()+1);
  h_n2_phiPhi ->AddBinContent(iGPhiPhi,  weight);  h_n2_phiPhi->SetEntries(h_n2_phiPhi->GetEntries()+1);

  if (fillP2)
    {
    h_DptDpt_phiPhi->AddBinContent(iGPhiPhi,weight*pt1*pt2);
    h_DptDpt_phiPhi->SetEntries(h_DptDpt_phiPhi->GetEntries()+1);
    }

  if (fillEta && iEta1!=0 && iEta2!=0 )
    {
    iGEtaEta           = h_n2_etaEta->GetBin(iEta1,iEta2);
    iGDeltaEtaDeltaPhi = h_n2_DetaDphi->GetBin(iDeltaEta+1,iDeltaPhi+1);
    h_n2_etaEta->AddBinContent(iGEtaEta,weight);             h_n2_etaEta  ->SetEntries(h_n2_etaEta  ->GetEntries()+1);
    h_n2_DetaDphi->AddBinContent(iGDeltaEtaDeltaPhi,weight); h_n2_DetaDphi->SetEntries(h_n2_DetaDphi->GetEntries()+1);

    if (fillP2)
      {
      h_DptDpt_etaEta   ->AddBinContent(iGEtaEta,           weight*pt1*pt2); h_DptDpt_etaEta->SetEntries(h_DptDpt_etaEta    ->GetEntries()+1);
      h_DptDpt_DetaDphi ->AddBinContent(iGDeltaEtaDeltaPhi, weight*pt1*pt2); h_DptDpt_DetaDphi->SetEntries(h_DptDpt_DetaDphi->GetEntries()+1);
      }
    }

  if (fillY && iY1!=0 && iY2!=0 )
    {
    iGYY             = h_n2_yY->GetBin(iY1,iY2);
    iGDeltaYDeltaPhi = h_n2_DyDphi->GetBin(iDeltaY+1,iDeltaPhi+1);
    h_n2_yY      ->AddBinContent(iGYY,weight);              h_n2_yY      ->SetEntries(h_n2_yY      ->GetEntries()+1);
    h_n2_DyDphi  ->AddBinContent(iGDeltaYDeltaPhi,weight);  h_n2_DyDphi  ->SetEntries(h_n2_DyDphi  ->GetEntries()+1);
    if (fillP2)
      {
      h_DptDpt_yY     ->AddBinContent(iGYY, weight*pt1*pt2);               h_DptDpt_yY ->SetEntries(   h_DptDpt_yY     ->GetEntries()+1);
      h_DptDpt_DyDphi ->AddBinContent(iGDeltaEtaDeltaPhi, weight*pt1*pt2); h_DptDpt_DyDphi->SetEntries(h_DptDpt_DyDphi->GetEntries()+1);
      }
    }

  //if (fillP2)h_DptDpt_phiPhi ->AddBinContent(iG,weight*dpt1*dpt2);

//  if (fillEta)
//    {
//    double deta = eta1 - eta2;
//    h_n2_etaEta   ->Fill(eta1,eta2);
//    h_n2_DetaDphi ->Fill(deta,dphi);
//    if (fillP2)
//      {
//      h_n2_etaEta->SetEntries(h_n2_etaEta->GetEntries()+nPairsEta);
//      h_n2_DetaDphi->SetEntries(h_n2_DetaDphi->GetEntries()+nPairsEta);
//
//      h_DptDpt_etaEta->Fill(eta1,eta2,weight*pt1*pt2);  // needs attention
//      h_DptDpt_DetaDphi->Fill(deta,dphi,weight*pt1*pt2); // needs attention
//      }
//    }
//  if (fillY)
//    {
//    double dy = y1 - y2;
//    h_n2_yY     ->Fill(y1,y2);
//    h_n2_DyDphi ->Fill(dy,dphi);
//    if (fillP2)
//      {
//      h_DptDpt_yY->Fill(y1,y2,weight*pt1*pt2); // needs attention
//      h_DptDpt_DyDphi->Fill(dy,dphi,weight*pt1*pt2); // needs attention
//      }
//    }
//  if (reportInfo(__FUNCTION__))
//    ;
}

