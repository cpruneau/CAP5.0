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
#ifndef CAP__IdentityAnalyzer
#define CAP__IdentityAnalyzer
#include "EventTask.hpp"
#include "ParticleDigit.hpp"
using CAP::EventTask;
using CAP::Configuration;
using CAP::EventFilter;
using CAP::ParticleFilter;
using CAP::ParticleDigit;

namespace CAP
{


//! Task used for the analysis of particle  pair distributions and correlations. As for other tasks classes of this package, use event filters and particle filters to determine the
//! event selection and particle types and kinematic ranges across which  particle pair  distributions are studied. Particle particle distributions are computed
//! (histogrammed) with instances of the ParticlePairHistos class. The behavior of the class, i.e., what type and the range of filled histograms are determined by
//! class configuration provided at task (object) construction.
//!
//! The following configuration parameters determine what types of histograms are filled (default values in brackets):
//! - fillEta [true]: whether to fill histograms  vs. pseudorapidity "eta"
//! - fillY [false]: whether to fill histograms  vs. rapidity "y"
//! - fillP2 [false]: whether to fill histograms used in the determination of P2 and G2 pT correlators
//!
//! The following parameters specify  the configuration of histograms filled by this task (default values in brackets):
//!
//! - Multiplicity of pair histogram
//!  + nBins_n2 [100]: Number of bins
//!  + min_n2 [0.0]: Minimum multiplicity
//!  + max_n2 [100]: Maximum multiplicity
//! - Particle transverse momemtum
//!  + nBins_pt [100]: Number of bins
//!  + min_pt [0.0]: Minimum value
//!  + max_pt [100.0]: Maximum value
//! - Particle pseudorapidity
//!  + nBins_eta [20]: Number of bins
//!  + min_eta [-1.0]: Minimum value
//!  + max_eta [1.0]: Maximum value
//! - Particle rapidity
//!  + nBins_y [20]: Number of bins
//!  + min_y [-1.0]: Minimum value
//!  + max_y [1.0]: Maximum value
//! - Particle azimuthal angle
//!  + nBins_phi [36]: Number of bins
//!  + min_phi [0.0]: Minimum value
//!  + max_phi [2pi]: Maximum value
//!
class IdentityAnalyzer : public EventTask
{
public:

  IdentityAnalyzer(const String & _name,
                       const Configuration & _configuration);
  
  //!
  //! DTOR
  //!
  virtual ~IdentityAnalyzer() {}
  
  //!
  //! Sets the default  values of the configuration parameters used by this task
  //!
  virtual void setDefaultConfiguration();

  virtual void configure();

  virtual void initialize();
  virtual void initializeHistogramManager();
 
  //!
  //! Executes this task based on the configuration and class variable specified at construction
  //!
  virtual void analyzeEvent();
  
  //!
  //! Creates the histograms  filled by this task at execution
  //!
  virtual void createHistograms();

  //!
  //! Loads the histograms required by this task at execution
  //!
  virtual void importHistograms(TFile & inputFile);
  
  //!
  //! Scales the pair histograms by the number of events accepted in each event filter category.
  //!
  virtual void scaleHistograms();

  virtual void createDerivedHistograms();

  virtual void importDerivedHistograms(TFile & inputFile __attribute__((unused)));

  virtual void calculateDerivedHistograms();

protected:

   ClassDef(IdentityAnalyzer,0)
};

} // namespace CAP

#endif /* CAP__IdentityAnalyzer */
