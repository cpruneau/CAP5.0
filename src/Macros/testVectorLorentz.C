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
#include <TLorentzVector.h>
void loadBase(const TString & includeBasePath);
void loadMath(const TString & includeBasePath);

int testVectorLorentz()
{
  TString includeBasePath = getenv("CAP_SRC");
  cout << " includeBasePath: " << includeBasePath << endl;
  loadBase(includeBasePath);
  loadMath(includeBasePath);
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  cout << "- test -----------------------------------------------------------------------------------------------" << endl;
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  CAP::Timer timer;
  timer.start();
  TH1D * h = new TH1D("H","H",100,0.0,100.);

//  typedef  CAP::Math::VectorLorentz<float>  VectorLorentzF;
//  typedef  CAP::Math::VectorLorentz<double> VectorLorentzD;
 // typedef  CAP::Math::VectorLorentz<long double> VectorLorentzLD;

//  using CAP::Math::VectorLorentzF;
//  using CAP::Math::VectorLorentzD;
//  using CAP::Math::VectorLorentzLD;


  for (int k=0;k<1;k++)
    {
    try
      {
      double v = 1.0 + 10.0*gRandom->Rndm();
//    double v = 10.0*gRandom->Rndm();
//      VectorLorentzD v1(0.0, 1.0, 1.0, 1.0 ,0);
//      VectorLorentzD v2(0.0, 4.0, 2.0, 1.0);
//      VectorLorentzD v3 = v1+v2;
      CAP::Math::VectorLorentz<double> v1(v, 1.0, 1.0, 1.0, 0);
      CAP::Math::VectorLorentz<double> v2(10.0, 4.0, 0.0, 1.0, 0);
      v1.print();
      cout << " rapidity: " << v1.rapidity() << endl;
      //v1.boostZ(0.9999999);
      v1.rotateZ(3.14*45.0/180.0);
      v1.print();
      cout << " rapidity': " << v1.rapidity() << endl;
      cout << "    scalar: " << v1.scalarProduct(v2) << endl;
      cout << "      mass: " << v1.mass() << endl;
//      CAP::Math::VectorLorentz<double> v3 = v1+v2;
//      TLorentzVector  v1(1.0, 1.0, 1.0, v);
//      TLorentzVector  v2(1.0, 4.0, 0.0, 10.0);
//      TLorentzVector  v3 = v1+v2;


//      v3 += v1;
//      double mm = v3.M();
//      double mm = v2.modulus();
//      //double mm = 1.0;
//      h->Fill(mm);
      }
    catch (CAP::MathException e)
      {
      e.print();
      }
    }
  timer.stop();
  timer.print(cout);
  h->Draw();
  return 0;
}

void loadBase(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Base/";
  gSystem->Load(includePath+"Configuration.hpp");
  gSystem->Load(includePath+"Timer.hpp");
  gSystem->Load(includePath+"MessageLogger.hpp");
  gSystem->Load(includePath+"Task.hpp");
  gSystem->Load(includePath+"TaskIterator.hpp");
  gSystem->Load(includePath+"Collection.hpp");
  gSystem->Load(includePath+"HistogramCollection.hpp");
  //gSystem->Load(includePath+"Histograms.hpp");
  gSystem->Load(includePath+"DerivedHistoIterator.hpp");
  gSystem->Load("libBase.dylib");
}

void loadMath(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Math/";
  gSystem->Load(includePath+"BesselFunctions.hpp");
  gSystem->Load(includePath+"Complex.hpp");
  gSystem->Load(includePath+"MathBasicFunctions.hpp");
  gSystem->Load(includePath+"MathBasicGeometry.hpp");
  gSystem->Load(includePath+"MathBasicIntegration.hpp");
  gSystem->Load(includePath+"MathBasicInterpolation.hpp");
  gSystem->Load(includePath+"MathBasicSearch.hpp");
  gSystem->Load(includePath+"MathBasicSortingFunctions.hpp");
  gSystem->Load(includePath+"MathBasicStatistics.hpp");
  gSystem->Load(includePath+"MathConstants.hpp");
  gSystem->Load(includePath+"VectorLorentz.hpp");
  gSystem->Load("libMath.dylib");
}
