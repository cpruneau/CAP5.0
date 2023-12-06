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

#include "GlobalAnalyzer.hpp"
#include "GlobalHistos.hpp"
#include "GlobalDerivedHistos.hpp"
using CAP::GlobalAnalyzer;
using CAP::GlobalHistos;
using CAP::GlobalDerivedHistos;

ClassImp(GlobalAnalyzer);

GlobalAnalyzer::GlobalAnalyzer(const String & _name,
                               const Configuration & _configuration)
:
EventTask(_name,_configuration),
setEvent(false),
n(),
e(),
q(),
s(),
b(),
ptSum()
{
  appendClassName("GlobalAnalyzer");
}

//!
//!
void GlobalAnalyzer::setDefaultConfiguration()
{
  EventTask::setDefaultConfiguration();
  addParameter("HistogramsCreate",     true);
  addParameter("HistogramsExport",     true);
  addParameter("EventsAnalyze",        true);
  addParameter("EventsUseStream0",     true);
  addParameter("EventsUseStream1",     false);
  addParameter("SetEvent",             true);
  addParameter("FillCorrelationHistos",false);
  addParameter("Fill2D",               false);
  addParameter("nBins_n",              500);
  addParameter("nBins_n2",              50);
  addParameter("Min_n",                0.0);
  addParameter("Max_n",                5000.0);
  addParameter("nBins_e",              500);
  addParameter("nBins_e2",              50);
  addParameter("Min_e",                0.0);
  addParameter("Max_e",                10000.0);
  addParameter("nBins_q",              200);
  addParameter("nBins_q2",              20);
  addParameter("Min_q",                -100.0);
  addParameter("Max_q",                100.0);
  addParameter("nBins_s",              200);
  addParameter("nBins_s2",              20);
  addParameter("Min_s",                -100.0);
  addParameter("Max_s",                100.0);
  addParameter("nBins_b",              200);
  addParameter("nBins_b2",              20);
  addParameter("Min_b",                -100.0);
  addParameter("Max_b",                100.0);

  addParameter("nBins_ptSum",           100.0);
  addParameter("nBins_ptSum2",          10.0);
  addParameter("Min_ptSum",             0.0);
  addParameter("Max_ptSum",             10000.0);
  addParameter("nBins_ptAvg",           100.0);
  addParameter("nBins_ptAvg2",          10.0);
  addParameter("Min_ptAvg",             0.0);
  addParameter("Max_ptAvg",             10.0);

}

void GlobalAnalyzer::configure()
{
  EventTask::configure();
  setEvent = getValueBool("SetEvent");
//  if (reportInfo(__FUNCTION__))
//    {
//    cout << endl;
//    printItem("EventsAnalyze");
//    printItem("EventsUseStream0");
//    printItem("EventsUseStream1");
//    printItem("EventsUseStream2");
//    printItem("EventsUseStream3");
//    printItem("HistogramsCreate");
//    printItem("HistogramsExport");
//    printItem("EventsUseStream0");
//    printItem("EventsUseStream1");
//    printItem("SetEvent");
//    printItem("FillCorrelationHistos");
//    printItem("Fill2D");
//    printItem("nBins_n");
//    printItem("nBins_n2");
//    printItem("Min_n");
//    printItem("Max_n");
//    printItem("range_n");
//    printItem("nBins_e");
//    printItem("nBins_e2");
//    printItem("Min_e");
//    printItem("Max_e");
//    printItem("range_e");
//    printItem("nBins_q");
//    printItem("nBins_q2");
//    printItem("Min_q");
//    printItem("Max_q");
//    printItem("range_n");
//    printItem("nBins_b");
//    printItem("nBins_b2");
//    printItem("Min_b");
//    printItem("Max_b");
//    printItem("nBins_s");
//    printItem("Min_s");
//    printItem("Max_s");
//    printItem("nBins_ptSum");
//    printItem("nBins_ptSum2");
//    printItem("Min_ptSum");
//    printItem("Max_ptSum");
//    printItem("nBins_ptAvg");
//    printItem("nBins_ptAvg2");
//    printItem("Min_ptAvg");
//    printItem("Max_ptAvg");
//    cout << endl;
//    }
}

void GlobalAnalyzer::initializeHistogramManager()
{
  histogramManager.addSet("global");
  histogramManager.addSet("derived");
}

void GlobalAnalyzer::initialize()
{
  if (reportStart(__FUNCTION__))
    ;
  EventTask::initialize();
  nParticleFilters = particleFilters.size();
  setEvent = true;//getValueBool("SetEvent");
  if (reportDebug(__FUNCTION__)) 
    {
    cout << endl;
    printItem("nEventFilters",nEventFilters);
    printItem("nParticleFilters",nParticleFilters);
    printItem("setEvent",setEvent);
    }
    cout << " #event added streams: "  << getNEventStreams() << endl;

  n.assign(nParticleFilters,0.0);
  ptSum.assign(nParticleFilters,0.0);
  e.assign(nParticleFilters,0.0);
  q.assign(nParticleFilters,0.0);
  s.assign(nParticleFilters,0.0);
  b.assign(nParticleFilters,0.0);
  if (reportDebug(__FUNCTION__)) cout << " #event added streams: "  << getNEventStreams() << endl;
}

void GlobalAnalyzer::createHistograms()
{
  if (reportStart(__FUNCTION__))
    ;
  String bn  = getName( );
  if (reportInfo(__FUNCTION__))
    {
    printItem("Creating HistogramGroup for",bn);
    printItem("nEventFilters",nEventFilters);
    printItem("nParticleFilters",nParticleFilters);
    }
  for (int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    String efn = eventFilters[iEventFilter]->getName();
    String name = bn;
    name += "_";
    name += efn;
    GlobalHistos * histos = new GlobalHistos(this,name,configuration,particleFilters);
    histos->createHistograms();
    histogramManager.addGroupInSet(0,histos);
    }
  if (reportEnd(__FUNCTION__))
    ;
}

//Task * _parent,
//const String & _name,
//const Configuration & _configuration,
//vector<ParticleFilter*> _particleFilters

void GlobalAnalyzer::importHistograms(TFile & inputFile)
{
  if (reportStart(__FUNCTION__))
    ;
  String bn  = getParentName( );
  if (reportDebug(__FUNCTION__))
    {
    printItem("Loading HistogramGroup for ",bn);
    printItem("nEventFilters",nEventFilters);
    printItem("nParticleFilters",nParticleFilters);
    }
  for (int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    String efn = eventFilters[iEventFilter]->getName();
    String name = bn;
    name += "_";
    name += efn;
    GlobalHistos * histos = new GlobalHistos(this,name,configuration,particleFilters);
    histos->importHistograms(inputFile);
    histogramManager.addGroupInSet(0,histos);
    }
  if (reportEnd(__FUNCTION__))
    ;
}

void GlobalAnalyzer::analyzeEvent()
{
  Event & event = * getEventStream(0);
  // count eventStreams used to fill histograms and for scaling at the end..
  // resetParticleCounters();
  unsigned int nEventFilters    = eventFilters.size();
  unsigned int nParticleFilters = particleFilters.size();
  unsigned int nParticles       = event.getNParticles();
  resetNParticlesAcceptedEvent();

//  if (reportInfo(__FUNCTION__))
//    {
//    cout << endl;
//    printItem("nEventFilters",nEventFilters);
//    printItem("nParticleFilters",nParticleFilters);
//    printItem("setEvent",setEvent);
//    }

  for (unsigned int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    if (!eventFilters[iEventFilter]->accept(event)) continue;
    incrementNEventsAccepted(iEventFilter);
    if (nParticles<1) continue;
    
    n.assign(nParticleFilters,0.0);
    e.assign(nParticleFilters,0.0);
    q.assign(nParticleFilters,0.0);
    s.assign(nParticleFilters,0.0);
    b.assign(nParticleFilters,0.0);
    ptSum.assign(nParticleFilters,0.0);
    for (unsigned int iParticle=0; iParticle<event.getNParticles(); iParticle++)
      {
      Particle & particle = * event.getParticleAt(iParticle);
      for (unsigned int iParticleFilter=0; iParticleFilter<nParticleFilters; iParticleFilter++ )
        {
        //cout << iParticleFilter << "  " << particle.getType().getName() << endl;
        if (particleFilters[iParticleFilter]->accept(particle))
          {
          incrementNParticlesAccepted(iEventFilter,iParticleFilter);
          // // incrementParticlesAccepted();
          ParticleType & type = particle.getType();
          LorentzVector & momentum = particle.getMomentum();
          n[iParticleFilter]++;
          e[iParticleFilter] += momentum.E();
          q[iParticleFilter] += type.getCharge();
          s[iParticleFilter] += type.getStrangessNumber();
          b[iParticleFilter] += type.getBaryonNumber();
          ptSum[iParticleFilter] += momentum.Pt();
          }
        }
      }
//    if (reportInfo(__FUNCTION__))
//      {
//      printItem("iEventFilter",iEventFilter);
//      printItem("setEvent",setEvent);
//      for (int k=0; k<nParticleFilters; k++)
//        {
//        cout << " n[" << k << "] = " << n[k] << endl;
//        cout << " e[" << k << "] = " << e[k] << endl;
//        cout << " q[" << k << "] = " << q[k] << endl;
//        cout << " s[" << k << "] = " << s[k] << endl;
//        cout << " b[" << k << "] = " << b[k] << endl;
//        }
//      }
    if (iEventFilter==0 && setEvent)
      {
      EventProperties * ep = event.getEventProperties();
      ep->fill(n,ptSum, e,q,s,b);
      //ep->printProperties(cout);
      }
    //Sexit(1);
    //cout << "Global counts " << n[0] << " charge: " << q[0]  << endl;
    GlobalHistos * globalHistos = (GlobalHistos * ) histogramManager.getGroup(0,iEventFilter);
    globalHistos->fill(n,ptSum,e,q,s,b,1.0);
    }
}

void GlobalAnalyzer::createDerivedHistograms()
{
  if (reportStart(__FUNCTION__))
    ;
  String bn  = getName();
  if (reportInfo(__FUNCTION__))
    {
    cout << "Creating histograms for " << bn << endl;
    cout << "nEventFilters............... : " << nEventFilters << endl;
    cout << "nParticleFilters............ : " << nParticleFilters << endl;
    }
  for (int iEventFilter=0; iEventFilter<nEventFilters; iEventFilter++ )
    {
    String efn = eventFilters[iEventFilter]->getName();
    String name = bn;
    name += "_";
    name += efn;
    GlobalDerivedHistos * histos = new GlobalDerivedHistos(this,name,configuration,particleFilters);
    histos->createHistograms();
    histogramManager.addGroupInSet(1,histos);
    }
  if (reportEnd(__FUNCTION__))
    ;
}

void GlobalAnalyzer::importDerivedHistograms(TFile & inputFile __attribute__((unused)))
{
  if (reportStart(__FUNCTION__))
    ;
  if (reportEnd(__FUNCTION__))
    ;
}

void GlobalAnalyzer::calculateDerivedHistograms()
{
  if (reportDebug(__FUNCTION__))
    {
    cout << endl;
    cout << "Computing derived histograms for....: " << endl;
    cout << "nEventFilters.......................: " << nEventFilters << endl;
    cout << "nParticleFilters....................: " << nParticleFilters << endl;
    }
  GlobalHistos        * baseHistos;
  GlobalDerivedHistos * derivedHistos;

  //!Mode 1: Running rigth after Analysis: base histograms pointers  are copied from analyzer to baseSingleHistograms
  //!Mode 2: Running as standalone: base histograms are loaded from file.
  for (int iEventFilter=0; iEventFilter< nEventFilters; iEventFilter++ )
    {
    baseHistos    = (GlobalHistos *) histogramManager.getGroup(0,iEventFilter);
    derivedHistos = (GlobalDerivedHistos *) histogramManager.getGroup(0,iEventFilter);
    derivedHistos->calculateDerivedHistograms(baseHistos);
    }
  if (reportEnd(__FUNCTION__))
    ;
}
