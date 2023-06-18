/* **********************************************************************
 * Copyright (C) 2019-2022, Claude Pruneau, Victor Gonzalez, Sumit Basu
 * Copyright (C) 2016, Chun Shen
 * All rights reserved.
 *
 * Based on the ROOT package and environment
 *
 * For the licensing terms see LICENSE.
 *
 * Author: Claude Pruneau,   04/01/2022
 *
 * *********************************************************************/
#ifndef CAP__ParticlePartition
#define CAP__ParticlePartition
#include <iostream>
#include "TString.h"
#include <string>
#include <ostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Collection.hpp"
#include "ParticleType.hpp"

using namespace std;


namespace CAP
{

class ParticleType;

class ParticlePartition
{
protected:

  vector<ParticleType*> particleTypes;
  vector<double> averageMultiplicity;
  vector<int> lowestMultiplicity;
  vector<int> highestMultiplicity;
  vector<int> workPartition;

  vector< vector<int> > validPartitions;


public:

  // const String& _name, bool _ownership, Severity logLevel
  ParticlePartition();
  virtual ~ParticlePartition() {}
  void readFromFile(const String & inputFileName);
  void writeToFile(const String &  outputFileName, bool printDecayProperties=true);

  void createBounds();
  bool isValid(int netCharge=0, int netBaryon=0, int netStrange=0);
  bool incrementPartition();


  ostream & print(ostream & os);

  ClassDef(ParticlePartition,0)
};

} //namespace CAP

#endif  // CAP__ParticlePartition

