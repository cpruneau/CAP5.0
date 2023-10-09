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
#include "ParticleSingleAnalyzer.hpp"
#include "ParticleSingleHistos.hpp"
#include "ParticleSingleDerivedHistos.hpp"

ClassImp(CAP::ParticleSingleAnalyzer);

namespace CAP
{


ParticleSingleAnalyzer::ParticleSingleAnalyzer(const String & _name,
                                               const Configuration & _configuration)
:
EventTask(_name,_configuration)
//fillEta(true),
//fillY(false),
//fillP2(false)
{
  appendClassName("ParticleSingleAnalyzer");
}

void ParticleSingleAnalyzer::setDefaultConfiguration()
{
  EventTask::setDefaultConfiguration();
  addParameter( "UseParticles",      true);
  addParameter( "HistogramsCreate",  true);
  addParameter( "HistogramsExport",  true);
  addParameter( "EventsAnalyze",     true);
  addParameter( "EventsUseStream0",  true);
  addParameter( "EventsUseStream1",  false);
  addParameter( "nBins_n1",  100);
  addParameter( "Min_n1",    0.0);
  addParameter( "Max_n1",  100.0);

  addParameter( "nBins_eTot",  100);
  addParameter( "Min_eTot",    0.0);
  addParameter( "Max_eTot",  100.0);

  addParameter( "nBins_pt",  100);
  addParameter( "Min_pt",    0.0);
  addParameter( "Max_pt",  100.0);

  addParameter( "nBins_eta",  20);
  addParameter( "Min_eta",   -1.0);
  addParameter( "Max_eta",    1.0);

  addParameter( "nBins_y",  20);
  addParameter( "Min_y",   -1.0);
  addParameter( "Max_y",    1.0);

  addParameter( "nBins_phi",  36);
  addParameter( "Min_phi",    0.0);
  addParameter( "Max_phi",    CAP::Math::twoPi());

  addParameter( "nBins_phiEta",    720);
  addParameter( "nBins_phiEtaPt",  7200);
  addParameter( "nBins_phiY",      720);
  addParameter( "nBins_phiYPt",    7200);
  addParameter( "FillEta",         true);
  addParameter( "FillY",           false);
  addParameter( "FillP2",          false);
}

void ParticleSingleAnalyzer::configure()
{
  EventTask::configure();
//  fillEta = getValueBool("FillEta");
//  fillY   = getValueBool("FillY");
//  fillP2  = getValueBool("FillP2");

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("EventsAnalyze");
    printItem("EventsUseStream0");
    printItem("EventsUseStream1");
    printItem("EventsUseStream2");
    printItem("EventsUseStream3");
    printItem("HistogramsCreate");
    printItem("HistogramsImport");
    printItem("HistogramsImportPath");
    printItem("HistogramsExport");
    printItem("HistogramsExportPath");
    printItem("EventsUseStream0");
    printItem("EventsUseStream1");
    printItem("nBins_n1");
    printItem("Min_n1");
    printItem("Max_n1");
    printItem("nBins_eTot");
    printItem("Min_eTot");
    printItem("Max_eTot");
    printItem("nBins_pt");
    printItem("Min_pt");
    printItem("Max_pt");
    printItem("nBins_eta");
    printItem("Min_eta");
    printItem("Max_eta");
    printItem("nBins_y");
    printItem("Min_y");
    printItem("Max_y");
    printItem("nBins_phi");
    printItem("Min_phi");
    printItem("Max_phi");
    printItem("FillEta");
    printItem("FillY");
    printItem("FillP2");
    cout << endl;
    }
}

void ParticleSingleAnalyzer::initialize()
{
  EventTask::initialize();
  for (unsigned int k=0; k<particleFilters.size(); k++)
    {
    vector<ParticleDigit*> list;
    filteredParticles.push_back(list);
    }
}

void ParticleSingleAnalyzer::initializeHistogramManager()
{
  histogramManager.addSet("single");
  histogramManager.addSet("derived");
}

void ParticleSingleAnalyzer::createHistograms()
{
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("Creating Histogram(s)", "");
    printItem("nEventFilters",   int(nEventFilters));
    printItem("nParticleFilters",int(nParticleFilters));
    cout << endl;
    }
  if (nEventFilters<1) throw TaskException("nEventFilters<1","ParticleSingleAnalyzer::createHistograms()");
  if (nParticleFilters<1) throw TaskException("nParticleFilters<1","ParticleSingleAnalyzer::createHistograms()");
  for (int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    String efn = eventFilters[iEventFilter]->getName();
    for (int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ )
      {
      String pfn = particleFilters[iParticleFilter]->getName();
      ParticleSingleHistos * histos = new ParticleSingleHistos(this,createName(getName(),efn,pfn),configuration);
      histos->createHistograms();
      histogramManager.addGroupInSet(0,histos);
      }
    }
  if (reportEnd(__FUNCTION__))
    ;
}


void ParticleSingleAnalyzer::importHistograms(TFile & inputFile)
{
  if (reportStart(__FUNCTION__))
    ;
  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("Loading Histogram(s)", "");
    printItem("nEventFilters",   int(nEventFilters));
    printItem("nParticleFilters",int(nParticleFilters));
    cout << endl;
    }
  if (nEventFilters<1) throw TaskException("nEventFilters<1","ParticleSingleAnalyzer::importHistograms(TFile & inputFile)");
  if (nParticleFilters<1) throw TaskException("nParticleFilters<1","ParticleSingleAnalyzer::importHistograms(TFile & inputFile)");
  for (int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    String efn = eventFilters[iEventFilter]->getName();
    //    cout << efn << endl;
    for (int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ )
      {
      String pfn = particleFilters[iParticleFilter]->getName();
      String baseName = createName(getName(),efn,pfn);
      //      cout << pfn << endl;
      //      cout << baseName << endl;
      
      ParticleSingleHistos * histos = new ParticleSingleHistos(this,baseName,configuration);
      histos->importHistograms(inputFile);
      histogramManager.addGroupInSet(0,histos);
      }
    }
  if (reportEnd(__FUNCTION__))
    ;
}

void ParticleSingleAnalyzer::analyzeEvent()
{
//  if (eventStreams.size() < 1) throw TaskException("eventStreams.size() < 1","ParticleSingleAnalyzer::analyzeEvent()");
//  if (!eventStreams[0])  throw TaskException("!eventStreams[0]","ParticleSingleAnalyzer::analyzeEvent()");
//  if (nEventFilters<1)   throw TaskException("nEventFilters<1","ParticleSingleAnalyzer::analyzeEvent()");
  Event & event = *eventStreams[0];
  //Is this event accepted by this task's event filters?
  bool analyzeThisEvent = false;
  resetNParticlesAcceptedEvent();
  vector<unsigned int> eventFilterPassed;
  for (int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    if (eventFilters.size()<1) throw TaskException("eventFilters.size()<1","ParticleSingleAnalyzer::analyzeEvent()");
    if (!eventFilters[iEventFilter]) throw TaskException("!eventFilters[iEventFilter]","ParticleSingleAnalyzer::analyzeEvent()");
    if (!eventFilters[iEventFilter]->accept(event)) continue;
    incrementNEventsAccepted(iEventFilter);
    eventFilterPassed.push_back(iEventFilter);
    analyzeThisEvent = true;
    }
  if (!analyzeThisEvent) return;
  // The event is accepted at least one event filter
  // but it may not have  pairs. If so skip out.
  // Doing the checks in this order guarantees the accepted
  // event count is correct for normalization purposes.
  unsigned int nParticles = event.getNParticles();
  // cout << "ParticleSingleAnalyzer::analyzeEvent() nParticles:" << nParticles << endl;
  if (nParticles<1) return;

  vector<double> nAccepted(nParticleFilters,0.0);
  vector<double> totalEnergy(nParticleFilters,0.0);

  if (eventFilterPassed.size()>1 || nParticleFilters>1)
    {
    // multiple events filters or particle filters
    // let us first reduce the number of particles to look at
    // and generate sublists for each particle filter
    // and use them to do the histo filling.
    Factory<ParticleDigit> * factory = ParticleDigit::getFactory();
    factory->reset();
    int index;
    int iEventFilter = 0;
    //    float pt,e;
    //    int iPt, iPhi, iEta, iY;
    ParticleSingleHistos * histos = (ParticleSingleHistos *) histogramManager.getGroup(0,iEventFilter);
    for (int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ ) filteredParticles[iParticleFilter].clear();

    resetNParticlesAcceptedEvent();
    for (unsigned int iParticle=0; iParticle<nParticles; iParticle++)
      {
      Particle & particle = * event.getParticleAt(iParticle);
      double  pt,e,phi;
      int iPt, iPhi, iEta, iY;
      ParticleDigit * pd;
      bool digitized = false;
      for (int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ )
        {
        if (particleFilters[iParticleFilter]->accept(particle))
          {
          incrementNParticlesAccepted(iEventFilter,iParticleFilter);
          if (!digitized)
            {
            LorentzVector & momentum = particle.getMomentum();
            pt     = momentum.Pt();
            e      = momentum.E();
            phi    = momentum.Phi();
            if (phi<0.0) phi += CAP::Math::twoPi();
            iPt    = histos->getPtBinFor(pt);
            iPhi   = histos->getPhiBinFor(phi);
            iEta   = histos->getEtaBinFor(momentum.Eta());
            iY     = histos->getYBinFor(momentum.Rapidity());
            pd     = factory->getNextObject();
            pd->iY   = iY;
            pd->iEta = iEta;
            pd->iPt  = iPt;
            pd->iPhi = iPhi;
            pd->pt   = pt;
            pd->e    = e;
            digitized = true; // so no need to digitize this particle again..
            }
          if (digitized && ( iPt>0 || iPhi>0 || iEta>=0 || iY>=0))
            {
            filteredParticles[iParticleFilter].push_back(pd);
            }
          } // particle accepted by filter
        } // filter loop
      } //particle loop

    // use the filter particles to fill the histos for the accepted event filters
    for (unsigned int jEventFilter=0; jEventFilter<eventFilterPassed.size(); jEventFilter++ )
      {
      iEventFilter = eventFilterPassed[jEventFilter];
      for (int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ )
        {
        index = iParticleFilter+iEventFilter*nParticleFilters;
        ParticleSingleHistos * histos = (ParticleSingleHistos *)  histogramManager.getGroup(0,index);
        histos->fill(filteredParticles[iParticleFilter],1.0);
        } // iParticleFilter loop
      } // jEventFilter loop
    }
  else
    {

    // 1 event filter and 1 particle filter: just scan the particles..
    // no need for sublists.
    int iParticleFilter = 0;
    int iEventFilter = eventFilterPassed[0];
    int index = iParticleFilter+iEventFilter*nParticleFilters;
   ParticleSingleHistos * histos = (ParticleSingleHistos *) histogramManager.getGroup(0,index);
   for (unsigned int iParticle=0; iParticle<nParticles; iParticle++)
      {
      Particle & particle = * event.getParticleAt(iParticle);
      //particle.printProperties();
      if (particleFilters[iParticleFilter]->accept(particle))
        {
        incrementNParticlesAccepted(0,0);
        nAccepted[iParticleFilter]++;
        totalEnergy[iParticleFilter] += particle.getMomentum().E();
        histos->fill(particle,1.0);
        }
      }
    histos->fillMultiplicity(nAccepted[iParticleFilter],totalEnergy[iParticleFilter],1.0);
    }
  // all done with this event..
}

void ParticleSingleAnalyzer::createDerivedHistograms()
{
  if (reportStart(__FUNCTION__))
    ;
  String bn  = getName();
  if (reportDebug(__FUNCTION__))
    {
    cout << endl;
    printItem("Creating derived Histogram(s)", "");
    printItem("nEventFilters",   int(nEventFilters));
    printItem("nParticleFilters",int(nParticleFilters));
    cout << endl;
    }
  if (nEventFilters<1) throw TaskException("nEventFilters<1","ParticleSingleAnalyzer::createDerivedHistograms()");
  if (nParticleFilters<1) throw TaskException("nParticleFilters<1","ParticleSingleAnalyzer::createDerivedHistograms()");
  ParticleSingleDerivedHistos * histos;
  for (int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    String efn = eventFilters[iEventFilter]->getName();
    for (int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ )
      {
      String pfn = particleFilters[iParticleFilter]->getName();
      histos = new ParticleSingleDerivedHistos(this,createName(bn,efn,pfn),configuration);
      histos->createHistograms();
      histogramManager.addGroupInSet(1,histos);
      }
    }
  if (reportEnd(__FUNCTION__))
    ;
}


void ParticleSingleAnalyzer::importDerivedHistograms(TFile & inputFile __attribute__((unused)))
{

}

void ParticleSingleAnalyzer::calculateDerivedHistograms()
{
  if (reportStart(__FUNCTION__))
    ;
  //incrementTaskExecuted();
  unsigned int nEventFilters    = eventFilters.size();
  unsigned int nParticleFilters = particleFilters.size();
  if (reportDebug(__FUNCTION__))
    {
    cout << endl;
    printItem("Calculating derived Histogram(s)", "");
    printItem("nEventFilters",   int(nEventFilters));
    printItem("nParticleFilters",int(nParticleFilters));
    cout << endl;
    }
  if (nEventFilters<1) throw TaskException("nEventFilters<1","ParticleSingleAnalyzer::calculateDerivedHistograms()");
  if (nParticleFilters<1) throw TaskException("nParticleFilters<1","ParticleSingleAnalyzer::calculateDerivedHistograms()");

  ParticleSingleHistos        * baseHistos;
  ParticleSingleDerivedHistos * derivedHistos;
  unsigned index;

  //!Mode 1: Running rigth after Analysis: base histograms pointers  are copied from analyzer to baseSingleHistograms
  //!Mode 2: Running as standalone: base histograms are loaded from file.
  for (unsigned int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    for (unsigned int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ )
      {
      index = iEventFilter*nParticleFilters + iParticleFilter;
      if (reportInfo(__FUNCTION__)) cout << " histogramManager.getGroup(0,index) iEventFilter:" << iEventFilter << " iParticleFilter:" << iParticleFilter << endl;
      baseHistos    = (ParticleSingleHistos *)  histogramManager.getGroup(0,index);
      if (reportInfo(__FUNCTION__)) cout << " histogramManager.getGroup(1,index) " << endl;
      derivedHistos = (ParticleSingleDerivedHistos *)  histogramManager.getGroup(1,index);
      if (!baseHistos) throw TaskException("!baseHistos","ParticleSingleAnalyzer::calculateDerivedHistograms()");
      if (!derivedHistos) throw TaskException("!derivedHistos","ParticleSingleAnalyzer::calculateDerivedHistograms()");
      if (reportInfo(__FUNCTION__)) cout << " derivedHistos->calculateDerivedHistograms(baseHistos)"  << endl;
      derivedHistos->calculateDerivedHistograms(baseHistos);
      if (reportInfo(__FUNCTION__)) cout << " done with these event/particle filters"  << endl;
      }
    }
  if (reportEnd(__FUNCTION__))
    { }
}

//!
//! Scale (all) the histograms held in all the histogram groups owned by this Task instance. This operation is executed automatically within the finalize() method call if
//! and only if the HistogramsScale parameter of the Configuration instance controlling this Task is set to "true".
//!
void ParticleSingleAnalyzer::scaleHistograms()
{
  if (reportStart(__FUNCTION__))
    ;
  //double scalingFactor;
  for (int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    long nEvents = nEventsAccepted[iEventFilter];
    if (reportInfo(__FUNCTION__))
      {
      cout << endl;
      printItem("iEventFilter",iEventFilter);
      printItem("nEventsAccepted[iEventFilter]",nEvents);
      }
    if (nEvents<2) continue;
    double scalingFactor = 1.0/double(nEvents);
    for (int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ )
      {
      int groupIndex = iEventFilter*nParticleFilters + iParticleFilter;
      ParticleSingleHistos * group = (ParticleSingleHistos*) histogramManager.getGroup(0,groupIndex);
      group->scale(scalingFactor);
      }
    }
  if (reportEnd(__FUNCTION__))
    ;
}

} // namespace CAP
