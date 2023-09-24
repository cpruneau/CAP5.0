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

  int nTypes;
  vector<ParticleType*> particleTypes;
  vector<double> averageMultiplicities;
  vector<double> probabilities;
  vector<int> lowestMultiplicities;
  vector<int> highestMultiplicities;
  vector<int> workPartition;

  vector< vector<int> > validPartitions;
  vector< double > partitionProbabilities;

  static vector<double> logFacArray;
  static void calculateLogFac();


public:

  // const String& _name, bool _ownership, Severity logLevel
  ParticlePartition();
  virtual ~ParticlePartition() {}
  void readFromFile(const String & inputFileName);
  void writeToFile(const String &  outputFileName, bool printDecayProperties=true);

  void createBounds();
  bool isValid(int netCharge=0, int netBaryon=0, int netStrange=0);
  void initializePartition();
  int  incrementPartition(int type);
  bool isPartitionValid();
  void scanPartitions(int netQReq=0, int netSReq=0, int netBReq=0);
  void savePartition();
  void calculateSpeciesProbabilities();
  double calculatePartitionProbability(vector<int> partition);
  double multinomial(vector<int> & partition, vecotr<double> probability);
  double logMultinomial(vector<int> & multiplicities, vecotr<double> probability);
  double logFac(int n);
  void   exportPartitions();
  void importPartitions();
  void exportPartitions();


  templage<typename T>
  T  Partition::sumVector(vector<T> & vector)
  {
  int  sum = 0;
  for (int k=0; k<vector.size(); k++) sum += vector[k];
  return sum;
  }

  ostream & print(ostream & os);

  ClassDef(ParticlePartition,0)
};

} //namespace CAP

#endif  // CAP__ParticlePartition

