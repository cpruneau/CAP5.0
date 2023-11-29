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
#ifndef CAP__LineShape
#define CAP__LineShape
#include "Task.hpp"
#include "HistogramCollection.hpp"
using CAP::Task;
using CAP::HistogramCollection;
using CAP::Configuration;

namespace CAP
{


class LineShape : Task, HistogramCollection
{
public:

  LineShape(const String & _name,
            const Configuration & _configuration);

  //!
  //! DTOR
  //!
  virtual ~LineShape() {}
  
  //!
  //! Sets the default  values of the configuration parameters used by this task
  //!
  virtual void setDefaultConfiguration();

  virtual void configure();

  virtual void initialize();

  double dedxExpectation(double m, double p, double a, double b);
  double dedxRmsExpectation(double m, double p, double a, double b);
  //!
  //! Creates the histograms  filled by this task at execution
  //!
  virtual void createHistograms();

  //!
  //! Loads the histograms required by this task at execution
  //!
  virtual void importHistograms(TFile & inputFile);
  
protected:

  int nBins_p;
  double min_p;
  double max_p;
  double range_p;
  double width_p;
  int nBins_dEdx;
  double min_dEdx;
  double max_dEdx;
  double range_dEdx;

  TH2 * h_lineShapeVsDedx_pi;
  TH2 * h_lineShapeVsDedx_k;
  TH2 * h_lineShapeVsDedx_p;


  ClassDef(LineShape,0)
};

} // namespace CAP

#endif /* CAP__LineShape */
