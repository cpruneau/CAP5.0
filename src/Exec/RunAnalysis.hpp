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
#ifndef CAP__RunAnalysis
#define CAP__RunAnalysis
#include <vector>
#include "Task.hpp"
//#include "EventTask.hpp"
//#include "Event.hpp"
//#include "Particle.hpp"
//#include "ParticleType.hpp"
using std::vector;

namespace CAP
{
class RunAnalysis : public Task
{
public:
  
  RunAnalysis(const String & _name,
              const Configuration & _configuration);

  //!
  //! dtor
  //! 
  virtual ~RunAnalysis() {}

  //!
  //! Initialize the configuration parameter of the task to their default value;
  //!
  virtual void setDefaultConfiguration();

  virtual void configureLabels();

  //!
  //! Configure  this analysis task
  //!
  virtual void configure();

  //!
  //! Execute this task
  //!
  void execute();

  void addBaseSubSampleTask(const String & basePath,
                            const String & bunchLabel,
                            int   nBunches,
                            const String & subPath,
                            int   maximumDepth,
                            const String & taskType);

  void addDerivedSubSampleTask(const String & basePath,
                               const String & bunchLabel,
                               int   nBunches,
                               const String & subPath,
                               int   maximumDepth,
                               const String & taskType);

  void addBalFctSubSampleTask(const String & basePath,
                              const String & bunchLabel,
                              int   nBunches,
                              const String & subPath,
                              int   maximumDepth,
                              const String & taskType);




protected:

  String labelParticleDb;
  String labelFilterCreator;
  String labelBunch;
  String labelSubBunch;
  String labelGlobal;
  String labelSpherocity;
  String labelSingle;
  String labelPair;
  String labelNuDyn;
  String labelSimAna;
  String labelDerived;
  String labelSum;
  String labelBalFct;
  String labelClosure;
  String labelGenerator;
  String labelReconstruction;
  String labelPythia;
  String labelHerwig;
  String labelHijing;
  String labelAmpt;
  String labelEpos;
  String labelUrqmd;
  String labelTherminator;
  String labelResonance;
  String labelPerformance;

  ClassDef(RunAnalysis,0)
};

}

#endif /* CAP_RunAnalysis */


