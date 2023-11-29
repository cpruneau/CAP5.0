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
#include <fstream>
#include <TStyle.h>
#include <TROOT.h>
void loadBase(const TString & includeBasePath);
void loadIdentity(const TString & includeBasePath);

//!
//! Run generic data analysis based on the configuration listed in 'configFile'
//!
//! configFile     :  configuration file (.ini) describing the task(s) to be done
//! outputPath   :  output path used for all files created
//! seed            :  provided by slurm (grid job engine) or directly by user
//! isGrid          :   must be true for jobs running on grid
//! nEventsPerSubbunch : number of events to run per bunch  (actual on grid or simulated on a single node)
//! nSubbunchesPerBunch : number of sub-bunches  (must be 1 on grid)
//! nBunches :  number of bunches  (must be 1 on grid)
//!
int RunId()
{
  TString includeBasePath = getenv("CAP_SRC");
  cout << " includeBasePath: " << includeBasePath << endl;
  loadBase(includeBasePath);
  loadIdentity(includeBasePath);

  try
  {
  CAP::Configuration configuration;
  //TString configurationPath = getenv("CAP_PROJECTS");
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  cout << "RunId()"  << endl;
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  cout << "------------------------------------------------------------------------------------------------------" << endl;


  CAP::LineShape * analysis = new CAP::LineShape("LineShape", configuration);
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  cout << "Configure" << endl;
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  analysis->configure();
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  cout << "Execute RunAnalysis" << endl;
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  analysis->createHistograms();
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  cout << "RunAnalysis completed successfully" << endl;
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  return 1;
  }
  catch (CAP::TaskException exception)
  {
  exception.print();
  //exit(1);
  }
  catch (CAP::FileException exception)
  {
  exception.print();
  //exit(1);
  }
  catch (CAP::MathException exception)
  {
  exception.print();
  // exit(1);
  }
  catch (CAP::Exception exception)
  {
  exception.print();
  //exit(1);
  }
  cout << "------------------------------------------------------------------------------------------------------" << endl;
  cout << " RunAnalysis NOT completed." << endl;
  cout << "------------------------------------------------------------------------------------------------------" << endl;

return 0;
}

void loadBase(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Base/";
  gSystem->Load(includePath+"Configuration.hpp");
  gSystem->Load(includePath+"Timer.hpp");
  gSystem->Load(includePath+"MessageLogger.hpp");
  gSystem->Load(includePath+"Task.hpp");
  gSystem->Load(includePath+"TaskIterator.hpp");
  gSystem->Load(includePath+"Collection.hpp");
  gSystem->Load(includePath+"HistogramCollection.hpp");
  //gSystem->Load(includePath+"Histograms.hpp");
  gSystem->Load(includePath+"DerivedHistoIterator.hpp");
  gSystem->Load("libBase.dylib");
}

void loadIdentity(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Identity/";
  gSystem->Load(includePath+"LineShape.hpp");
  gSystem->Load("libIdentity.dylib");
}


