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
#ifndef CAP__FilterCreator
#define CAP__FilterCreator
#include "EventTask.hpp"
#include "Event.hpp"
#include "EventFilter.hpp"
#include "ParticleType.hpp"
#include "ParticleDb.hpp"

namespace CAP
{
class FilterCreator : public EventTask
{

public:
  
  FilterCreator(const String & _name,
                const Configuration & _configuration);

  //!
  //! dtor
  //! 
  virtual ~FilterCreator() {}

  //!
  //! Initialize the configuration parameter of the task to their default value;
  //!
  virtual void setDefaultConfiguration();

  //!
  //! Configure  this analysis task
  //!
  virtual void configure();
  virtual void initialize();

  //!
  //! Execute this task
  //!
  void execute();

  void createEventFilterContainers();
  void createParticleFilterContainers();

  void createEventFilters(unsigned int type);
  void createParticleFilters(unsigned int type);

  void addEventFilter(unsigned int type, EventFilter* filter);
  void addParticleFilter(unsigned int type, ParticleFilter* filter);

  void addEventFilters(unsigned int type, vector<EventFilter*>  filters);
  void addParticleFilters(unsigned int type, vector<ParticleFilter*>  filters);

  static vector<EventFilter*> & getEventFiltersModel();
  static vector<EventFilter*> & getEventFiltersGlobal();
  static vector<EventFilter*> & getEventFiltersAnalysis();
  static vector<ParticleFilter*> & getParticleFiltersModel();
  static vector<ParticleFilter*> & getParticleFiltersGlobal();
  static vector<ParticleFilter*> &  getParticleFiltersAnalysis();

  //!
  //!  Create an open filter i.e., a filter that accepts all particles considered "live".
  //!
   vector<ParticleFilter*> createOpenParticleFilter();

  //!
  //!  Create a filter that simulates the ALICE min bias V0 trigger.
  //!
   vector<ParticleFilter*> createAliceV0Filter();

  //!
  //!  Create a filter accepting all neutral particles
  //!
   vector<ParticleFilter*> createNeutralParticleFilter(bool filteringOnPt,  double minPt,  double maxPt,
                                                             bool filteringOnEta, double minEta, double maxEta,
                                                             bool filteringOnY,   double minY,   double maxY);

  //!
  //!  Create a filter accepting all charged particles
  //!
   vector<ParticleFilter*> createChargedParticleFilter(bool filteringOnPt,  double minPt,  double maxPt,
                                                             bool filteringOnEta, double minEta, double maxEta,
                                                             bool filteringOnY,   double minY,   double maxY);

  //!
  //!  Create a filter accepting all negative particles
  //!
   vector<ParticleFilter*> createNegativeParticleFilter(bool filteringOnPt,  double minPt,  double maxPt,
                                                              bool filteringOnEta, double minEta, double maxEta,
                                                              bool filteringOnY,   double minY,   double maxY);

  //!
  //!  Create a filter accepting all positive particles
  //!
   vector<ParticleFilter*> createPositiveParticleFilter(bool filteringOnPt,  double minPt,  double maxPt,
                                                              bool filteringOnEta, double minEta, double maxEta,
                                                              bool filteringOnY,   double minY,   double maxY);

  //!
  //!  Create a filter accepting only the given pdg code with the given kinematical parameters
  //!
    ParticleFilter * createHadronFilter(int pdg, const String & _name, const String  & title,
                                              bool filteringOnPt,  double minPt,  double maxPt,
                                              bool filteringOnEta, double minEta, double maxEta,
                                              bool filteringOnY,   double minY,   double maxY);

  //!
  //!  Create a filter accepting only the given index code with the given kinematical parameters
  //!
   ParticleFilter * createIndexFilter(int index, const String & name, const String  & title,
                                            bool filteringOnPt,  double minPt,  double maxPt,
                                            bool filteringOnEta, double minEta, double maxEta,
                                            bool filteringOnY,   double minY,   double maxY);


  //!
  //!  Create filters accepting only the given index code range with the given kinematical parameters
  //!
   vector<ParticleFilter*> createIndexFilters(ParticleDb & particleDb,
                                                    bool filteringOnPt,  double minPt,  double maxPt,
                                                    bool filteringOnEta, double minEta, double maxEta,
                                                    bool filteringOnY,   double minY,   double maxY);


  //!
  //!  Create pos and neg hadron  filters with the given kinematical parameters
  //!
   vector<ParticleFilter*> createChargedHadronFilters(bool filteringOnPt,  double minPt,  double maxPt,
                                                            bool filteringOnEta, double minEta, double maxEta,
                                                            bool filteringOnY,   double minY,   double maxY);

  //!
  //!  Create pi+, K+, p+, pi-, K-, p- filters with the given kinematical parameters
  //!
   vector<ParticleFilter*> createPlusMinusHadronFilters(bool filteringOnPt,  double minPt,  double maxPt,
                                                              bool filteringOnEta, double minEta, double maxEta,
                                                              bool filteringOnY,   double minY,   double maxY);

  //!
  //! Create low mass (detectable) +B and -B baryon filters with the given kinematical parameters
  //! Baryon (and their respective anti-baryons) selected include
  //! proton  : 2212
  //! neutron : 2112
  //! lambda  : 3122
  //! Sigma+  : 3222
  //! Sigma0  : 3212
  //! Sigma-  : 3112
  //! Xi0     : 3322
  //! XiM     : 3312
  //! Omega-  : 3334
  //!
   vector<ParticleFilter*> createBaryonFilters(bool filteringOnPt,  double minPt,  double maxPt,
                                                     bool filteringOnEta, double minEta, double maxEta,
                                                     bool filteringOnY,   double minY,   double maxY);

   vector<ParticleFilter*> createStrangeHadronFilters(bool filteringOnPt,  double minPt,  double maxPt,
                                                            bool filteringOnEta, double minEta, double maxEta,
                                                            bool filteringOnY,   double minY,   double maxY);


  vector<EventFilter*> createOpenEventFilter();
  vector<EventFilter*> createAliceMBEventFilter();
  vector<EventFilter*> createImpactParameterFilters(vector<double> & bounds);
  vector<EventFilter*> createV0MultiplicityFilters(vector<double>  & bounds);
  vector<EventFilter*> createTpcMultiplicityFilters(vector<double> & bounds);


protected:

  static vector<EventFilter*>    * eventFiltersModel;
  static vector<ParticleFilter*> * particleFiltersModel;
  static vector<EventFilter*>    * eventFiltersGlobal;
  static vector<ParticleFilter*> * particleFiltersGlobal;
  static vector<EventFilter*>    * eventFiltersAnalysis;
  static vector<ParticleFilter*> * particleFiltersAnalysis;

  ClassDef(FilterCreator,0)
};

}

#endif /* CAP_FilterCreator */


