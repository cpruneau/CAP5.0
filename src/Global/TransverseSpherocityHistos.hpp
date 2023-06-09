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

#ifndef CAP__TransverseSpherocityHistos
#define CAP__TransverseSpherocityHistos
#include "HistogramGroup.hpp"
#include "ParticleFilter.hpp"

namespace CAP
{

class TransverseSpherocityHistos: public HistogramGroup
{
public:
  TransverseSpherocityHistos(Task * _parent,
                             const String & _name,
                             const Configuration & _configuration,
                             vector<ParticleFilter*> & _particleFilters);
  ~TransverseSpherocityHistos() {}
  virtual void createHistograms();
  virtual void importHistograms(TFile & inputFile);
  virtual void fill(vector<double> & s0, vector<double> & s1, double weight);
  
protected:
  bool   fillS0;
  bool   fillS1;
  bool   fillS1VsS0;
  bool   fillCorrelationHistos;
  int    nParticleFilters;
  vector<ParticleFilter*> particleFilters;
  vector<TH1 *> h_s0;
  vector<TH1 *> h_s1;
  vector<TH2 *> h_s1VsS0;
  vector<TH2 *> h_s0VsS0;
  
  ClassDef(TransverseSpherocityHistos, 1);
};

} // namespace CAP


#endif
