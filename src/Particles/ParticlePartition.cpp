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

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "ParticlePartition.hpp"
using CAP::Collection;
using CAP::ParticleType;
using CAP::ParticlePartition;
using namespace std;

ClassImp(ParticlePartition);


ParticlePartition::ParticlePartition()
:
particleTypes(),
averageMultiplicities(),
lowestMultiplicities(),
highestMultiplicities(),
workPartition(),
validPartitions()
{  }

void ParticlePartition::createBounds()
{
  int nTypes = particleTypes.size();
  for (unsigned int iPart = 0; iPart < size(); iPart++)
    {
    double avgMult = averageMultiplicities[iPart];
    double range = 2.5*std::sqrt(avgMult);
    lowestMultiplicities[iPart]  = int(avgMult - range);
    highestMultiplicities[iPart] = int(avgMult + range +0.5);
    }
}

void ParticlePartition::initializePartition()
{
  workPartition.clear();
  for (unsigned int iPart = 0; iPart < size(); iPart++)
    {
    workPartition.push_back(lowestMultiplicities[iPart]);
    }
  currentType = 0;
}

int ParticlePartition::incrementPartition(int type)
{
  int mult = workPartition[type];
  if (mult<highestMultiplicities[type])
    {
    workPartition[type] = mult+1;
    return currentType;
    }
  else
    {
    workPartition[type] = lowestMultiplicities[type];
    type++;
    return increasePartition(mult);
    }
}


bool ParticlePartition::isPartitionValid() //int netQReq=0, int netSReq=0, int netBReq=0)
{
  int netQ = 0;
  int netS = 0;
  int netB = 0;
  for (unsigned int iPart = 0; iPart < size(); iPart++)
    {
    ParticleType * particleType = particleTypes[iPart];
    netQ += particleType->getCharge();
    netS += particleType->getStrangenessNumber();
    netB += particleType->getBaryonNumber();
    }
  if (netQ==netQReq && netS==netSReq && netB==netBReq)
    return true;
  return false;
}

void ParticlePartition::scanPartitions(int netQReq=0, int netSReq=0, int netBReq=0)
{
  initializePartition();
  int currentType = 0;
  while (currentType<nType)
    {
    if (isPartitionValid())
      {
      savePartition();
      }
    currentType = incrementPartition(currentType);
    }
}


void  ParticlePartition::savePartition()
{
  validPartitions.push_back(workPartition);
  double probability = calculatePartitionProbability(workPartition):
  partitionProbabilities.push_back(probability);
}



void ParticlePartition::calculateSpeciesProbabilities()
{
  double sum = sumVector(averageMultiplicities);
  for (int iType=0;iType<nTypes;iType++)
    {
    probabilities.push_back(averageMultiplicities[iType]/sum);
    }
}

double   ParticlePartition::calculatePartitionProbability(vector<int> partition)
{
  return multinomial(partition,probability);
}

double ParticlePartition::multinomial(vector<int> & partition, vecotr<double> probability)
{
  return exp(logMultinomial(partition,probability));
}

double ParticlePartition::logMultinomial(vector<int> & multiplicities, vecotr<double> probability)
{
  int sum = sumVector(multiplicities);
  double value = logFac(sum);
  for (iType=0;iType<nTypes;iType++)
    {
    int mult = multiplicities[iType];
    value += double(mult)*std::log(probability[iType])/logFac(mult);
    }
  return value;
}

vector<double> ParticlePartition::logFacArray;

void ParticlePartition::calculateLogFac()
{
  if (logFacArray.size()>0) return; // already initialized...
  logFacArray.push_back(0);
  logFacArray.push_back(0);
  for (int k=2; k< 20000; k++)
    {
    logFacArray.push_back( logFacArray[k-1] + std::log(double(k)));
    }
}

double ParticlePartition::logFac(int n)
{
  auto size = logFacArray.size();
  if (size<1) calculateLogFac();
  if (n<size) return logFacArray[n];
  throw MathException("n too large","logFac(int n)");
}

void  ParticlePartition::exportPartitions()
{
  int nPartitions = validPartitions.size();
  if (nPartitions<1)
    throw TaskException("No valid partitions to save","ParticlePartition::exportPartitions()");
  ofstream & outputFile = openOutputAsciiFile(particlePartitionExportPath,particlePartitionExportFile,".data");
  outputFile << nPartitions << endl;
  for (int iPartition=0; iPartition<nPartitions; iPartition++)
    {
    vector<int> & partition = validPartitions[iPartition];
    for (iType=0;iType<nTypes;iType++)
      {
      outputFile << "  " << partition[iType];
      }
    outputFile << partitionProbabilities[iType] << endl;
    }
  outputFile.close();
}

void  ParticlePartition::importPartitions()
{
  ifstream & inputFile = openInputAsciiFile(particlePartitionImportPath,particlePartitionImportFile,".data");
  char   buff[300];
  int mult;
  double probability;
  try
  {
  while (!inputFile.eof())
    {
    inputFile.getline(buff,5000);
    if (!(*buff) || (*buff == '#'))
      {
      continue;
      }
    istringstream * iss = new istringstream(buff);
    vector<int> partition;
    for (iType=0;iType<nTypes;iType++)
      {
      (*iss)  >> mult;
      partition.push_back(mult);
      }
    (*iss)  >> probability;
    validPartitions.push_back(partition);
    probabilities.push_back(probability);
    delete iss;
    }
  }
  catch (...)
  {
  throw FileException(particleDbImportPath,particleDbImportFile,"Error reading particle data base file","ParticleDbManager::importParticleDbNative()");
  }
}
