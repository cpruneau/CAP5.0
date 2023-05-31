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

  static void createEventFiltersModel();
  static void createEventFiltersAnalysis();
  static void createParticleFiltersModel();
  static void createParticleFiltersAnalysis();

  static void addEventFilterModel(EventFilter* filter);
  static void addEventFilterAnalysis(EventFilter* filter);
  static void addParticleFilterModel(ParticleFilter* filter);
  static void addParticleFilterAnalysis(ParticleFilter* filter);

  static void addEventFiltersModel(vector<EventFilter*>  filters);
  static void addEventFiltersAnalysis(vector<EventFilter*>  filters);
  static void addParticleFiltersModel(vector<ParticleFilter*>  filters);
  static void addParticleFiltersAnalysis(vector<ParticleFilter*>  filters);


  static vector<EventFilter*> & getEventFiltersModel();
  static vector<EventFilter*> & getEventFiltersAnalysis();
  static vector<ParticleFilter*> & getParticleFiltersModel();
  static vector<ParticleFilter*> &  getParticleFiltersAnalysis();

protected:

  static vector<EventFilter*>    * eventFiltersModel;
  static vector<ParticleFilter*> * particleFiltersModel;
  static vector<EventFilter*>    * eventFiltersAnalysis;
  static vector<ParticleFilter*> * particleFiltersAnalysis;


  ClassDef(FilterCreator,0)
};

}

#endif /* CAP_FilterCreator */


