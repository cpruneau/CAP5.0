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
#include <vector>
#include "SelectionGenerator.hpp"
using std::cout;
using std::endl;
using CAP::SelectionGenerator;

ClassImp(SelectionGenerator);

SelectionGenerator::SelectionGenerator()
:
cumulativeProbability()
{    }

SelectionGenerator::SelectionGenerator(std::vector<double> & probabilities)
:
cumulativeProbability()
{
  initializeWith(probabilities);
}

SelectionGenerator & SelectionGenerator::operator=(const SelectionGenerator & source)
{
  if (this!=&source)
    {
    cumulativeProbability = source.cumulativeProbability;
    }
  return *this;
}

void SelectionGenerator::initializeWith(std::vector<double> & probabilities)
{
  cumulativeProbability.clear();
  int n = probabilities.size();
  double sum = 0.0;
  for (int k=0; k<n; k++)
    {
    sum += probabilities[k];
    }
  double prob = 0.0;
  for (int kk=0; kk<n; kk++)
    {
    prob += probabilities[kk]/sum;
    cumulativeProbability.push_back(prob);
    }
//  cout << "SelectionGenerator::initializeWith(std::vector<double> & probabilities) cumulativeProbability.size() : " << cumulativeProbability.size() << endl;

}


int SelectionGenerator::generate()
{
  double v = gRandom->Rndm();
  int n = cumulativeProbability.size();
  for (int k=0; k<n; k++)
  {
  if (v <= cumulativeProbability[k]) return k;
  }
  return n-1;
}

