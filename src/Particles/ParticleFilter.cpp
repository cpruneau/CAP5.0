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
// #include <TMath.h>
#include "ParticleFilter.hpp"
using CAP::Filter;
using CAP::Particle;
using CAP::ParticleFilter;
using namespace std;

ClassImp(Filter<Particle>);

ClassImp(ParticleFilter);

ParticleFilter::ParticleFilter()
:
Filter<Particle>()
{
  // no ops
}

ParticleFilter::ParticleFilter(const ParticleFilter & otherFilter)
:
Filter<Particle>(otherFilter)
{
 // no ops
}

ParticleFilter & ParticleFilter::operator=(const ParticleFilter & otherFilter)
{
  if (this!=&otherFilter)
    {
    Filter<Particle>::operator=(otherFilter);
    }
  return *this;
}


bool ParticleFilter::accept(const Particle & particle)
{
  //cout << " ParticleFilter::accept(const Particle & particle): "  << endl;
  const LorentzVector & momentum1 = particle.getMomentum();
//  double pt1   = momentum1.Pt();
//  double e1    = momentum1.E();
//  double phi1  = momentum1.Phi();
//  double eta1  = momentum1.Eta();
//  double y1    = momentum1.Rapidity();
  //cout << "particle: " << particle.getType().getName() << "  y1: " << y1 << "  phi1: " << phi1 << " pt1: " << pt1 << endl;

  unsigned int nConditions = getNConditions();
  if (nConditions<1) return true;

  double value     = 0.0;
  bool   accepting = false;
  ParticleType & type = particle.getType();

  //cout << "ParticleFilter::accept() nConditions = " << nConditions << endl;

  for (unsigned int k = 0; k<nConditions; k++)
    {
    Condition & condition = *(conditions[k]);
    unsigned int filterType    = condition.filterType;
    unsigned int filterSubType = condition.filterSubtype;
    //cout << "filterType: " << filterType << "   filterSubType: " << filterSubType << endl;
    switch (filterType)
      {
        case 0: // live or not to be considered at all
        switch (filterSubType)
          {
            case  0: accepting = !particle.isLive(); break;  // decayed or removed particles only
            case  1: accepting = particle.isLive(); break;   // undecayed particles only
            case  2: accepting = 1; break;                   // all
          }
        //if (!accepting) return false;
        break;

        case 1: // Charge, Neutral, Plus, or Minus
          {
          int charge = type.getCharge();
          switch (filterSubType)
            {
              case  0: accepting = (charge==0); break;  // accepts neutral only
              case  1: accepting = (charge!=0); break;  // accepts all charged particles
              case  2: accepting = (charge<0);  break;  // accepts -ve only
              case  3: accepting = (charge>0);  break;  // accepts +ve only
            }
          //if (!accepting) return false;
          }
        break;

        case 2: // PDG Code
        {
        accepting = condition.accept(type.getPdgCode());
//        int pdg = type.getPdgCode();
//        if (pdg==-211)
//          {
//          cout
//          << "            filterType: " << condition.filterType
//          << " filterSubtype: " << condition.filterSubtype
//          << "  minimum: " << condition.minimum
//          << "  maximum: " << condition.maximum
//          << endl;
//          //cout << "particle: " << particle.getType().getName() << "  y1: " << y1 << "  phi1: " << phi1 << " pt1: " << pt1 << endl;
//          cout << "       case 2: accepting: " << accepting << endl;
//          }
        }
        //if (!accepting) return false;
        break;

        case 3: // Particle index
        accepting = condition.accept(type.getIndex());
        //if (!accepting) return false;
        break;

        case 4: // Type selection
        switch (filterSubType)
          {
            case 0: accepting = type.isPhoton();     break;
            case 10: accepting = type.isLepton();         break;
            case 11: accepting = type.isElectron() || type.isPositron(); break;
            case 12: accepting = type.isElectron();   break;
            case 13: accepting = type.isPositron();   break;
            case 14: accepting = type.isMuon() || type.isAntiMuon();     break;
            case 15: accepting = type.isMuon();       break;
            case 16: accepting = type.isAntiMuon();   break;
            case 17: accepting = type.isTau()  || type.isAntiTau();      break;
            case 18: accepting = type.isTau();       break;
            case 19: accepting = type.isAntiTau();  break;

            case 40: accepting = type.isStrange();        break;
            case 41: accepting = type.isStrangePlus();    break;
            case 42: accepting = type.isStrangeMinus();   break;

            case 50: accepting = type.isCharm();          break;
            case 51: accepting = type.isCharmPlus();      break;
            case 52: accepting = type.isCharmMinus();     break;

            case 60: accepting = type.isBottom();         break;
            case 61: accepting = type.isBottomPlus();     break;
            case 62: accepting = type.isBottomMinus();    break;

            case 70: accepting = type.isTop();            break;

            case 1100: accepting = type.isHadron();   break; // any hadron
            case 1101: accepting = type.isHadron() && type.isCharged();   break; // any charged hadron
            case 1102: accepting =
            type.isPionP() ||
            type.isPionM() ||
            type.isKaonP() ||
            type.isKaonM() ||
            type.isProton() ||
            type.isAntiProton(); // pi+, pi-, K+, K-, p, pBar
            break; // any charge hadron
            case 1103: accepting =
            type.isPionP() ||
            type.isKaonP() ||
            type.isProton(); // pi+, K+, p
            break;
            case 1104: accepting =
            type.isPionM() ||
            type.isKaonM() ||
            type.isAntiProton(); // pi-, K-, pBar
            break;

            case 1110: accepting = type.isPion();     break;
            case 1111: accepting = type.isPionP(); break;
            case 1112: accepting = type.isPion0(); break;
            case 1113: accepting = type.isPionM(); break;

            case 1120: accepting = type.isKaon();     break;
            case 1121: accepting = type.isKaonP();    break;
            case 1122: accepting = type.isKaonM();    break;
            case 1123: accepting = type.isKaon0();    break;
            case 1124: accepting = type.isKaon0Bar(); break;
            case 1125: accepting = type.isKaon0S();   break;
            case 1126: accepting = type.isKaon0L();   break;

            case 1200: accepting = type.isBaryon();         break;
            case 1201: accepting = type.isBaryonPlus();     break;
            case 1202: accepting = type.isBaryonMinus();    break;

            case 1210: accepting = type.isProton() || type.isAntiProton();   break;
            case 1211: accepting = type.isProton();     break;
            case 1212: accepting = type.isAntiProton(); break;

            case 1220: accepting = type.isLambda() || type.isAntiLambda();   break;
            case 1221: accepting = type.isLambda();     break;
            case 1222: accepting = type.isAntiLambda(); break;

            case 1230: accepting = type.isSigmaP();       break;
            case 1231: accepting = type.isSigma0();       break;
            case 1232: accepting = type.isSigmaM();       break;
            case 1241: accepting = type.isAntiSigmaP();   break;
            case 1242: accepting = type.isAntiSigma0();   break;
            case 1243: accepting = type.isAntiSigmaM();   break;
            case 1244: accepting = type.isXi0();          break;
            case 1245: accepting = type.isXiM();          break;
            case 1246: accepting = type.isAntiXi0();      break;
            case 1247: accepting = type.isAntiXiM();      break;
            case 1248: accepting = type.isOmegaM();       break;
            case 1249: accepting = type.isAntiOmegaM();   break;
          }
        //if (!accepting) return false;
        break;

        case 5: // kinematic selection/filtering
        const LorentzVector & momentum = particle.getMomentum();
        switch (filterSubType)
          {
            case 0: value = momentum.P();   break;    // momentum
            case 1: value = momentum.Pt();  break;   // transverse momentum
            case 2: value = momentum.E();   break;    // energy
            case 3: value = momentum.Px();  break;   // p_x
            case 4: value = momentum.Py();  break;   // p_y
            case 5: value = momentum.Pz();  break;   // p_z
            case 6: value = momentum.Phi(); break;   // phi azimuth
            case 7: value = momentum.Eta(); break;   // pseudo rapidity
            case 8: value = momentum.Rapidity(); break;   // rapidity
          }
        accepting = conditions[k]->accept(value);
        //cout << "k:" << k << " case 5: filterSubType: " << filterSubType << " value:" << value << " accepting:" << accepting << endl;
        //if (!accepting) return false;
        break;
      }
    if (!accepting)  return false;
    }
  return true;
}
