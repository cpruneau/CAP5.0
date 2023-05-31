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
//void loadBase(const TString & includeBasePath);
//void loadMath(const TString & includeBasePath);

//template <typename T>
//T polynomial(T x, const T * coeffs, int n)
//{
//  T result = coeffs[n-1];
//  for (unsigned int i=n-1; i>0; i--) result = coeffs[i-1] + x*result;
//  return result;
//}

//template double polynomial<double>(double x, const double * c, int n);
double CAP::Math::polynomial<double>(double x, const double * c, int n);

int testPolynomial()
{
  TString includeBasePath = getenv("CAP_SRC");
  cout << " includeBasePath: " << includeBasePath << endl;
  //loadBase(includeBasePath);
  //loadMath(includeBasePath);
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  cout << "- testPolynomial -----------------------------------------------------------------------------------------------" << endl;
  cout << "------------------------------------------------------------------------------------------------------" << endl;

  double * c = new double[3];
  c[0] = 2.0;
  c[1] = 1.0;
  c[2] = 1.0;

  double v =  CAP::Math::polynomial<double>(1.0,c,4);

  cout << "  v:" << v << endl;
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
  gSystem->Load(includePath+"Vector3.hpp");
  gSystem->Load("libMath.dylib");
}
