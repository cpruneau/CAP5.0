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
#ifndef CAP__TaskIterator
#define CAP__TaskIterator
#include "Task.hpp"

namespace CAP {

//!
//! This class implements a task iterator task, i.e., a task that repeated calls other tasks (subtasks) to carry out the same operation(s) on a sequence of events (event stream).
//!  Use the 'run' method to execute the job on all selected events. Internally, 'run' calls the 'execute' method repeatedly on each event in the event stream.
//!  Do not call the 'execute' method of this class directly unless you know what you are doing..
//!
//!  Optionally, the iterator may call a subsampleAnalysis method to carry out a sub-sample analysis of all the sub tasks operated by this iterator.
//!
class TaskIterator : public Task
{
public:
  
  //!
  //! Detailed CTOR
  //!
  //! @param _name Name given to task instance
  //! @param _configuration Configuration used to run this task
  //! @param _reportLevel Message log level to be used by this task.
  //!
  TaskIterator(const String & _name, const Configuration & _configuration);

  //!
  //! DTOR
  //!
  virtual ~TaskIterator() {}
  
  //!
  //! Sets the default  values of the configuration parameters used by this task
  //!
  virtual void setDefaultConfiguration();

  //!
  //! Initialize the subtasks
  //!
  virtual void configure();

  virtual void partial(const String & outputPathBase);
  //!
  //! Execute the subtasks
  //!
  virtual void execute();

  //!
  //! Finalize the subtasks
  //!
  virtual void finalize();

protected:

  bool    isGrid;
  long    nEventsPerSubbunch;
  int     nSubbunchesPerBunch;
  int     nBunches;
  long    nEventsRequested;
  long    nEventsReport;
  String  bunchLabel;
  String  subbunchLabel;
  long    iEvent;
  int     iSubBunch;
  int     iBunch;

  ClassDef(TaskIterator,0)
};

}
#endif /* CAP__TaskIterator */
