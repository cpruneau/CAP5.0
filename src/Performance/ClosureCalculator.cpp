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
//#include "HistogramCollection.hpp"
#include "ClosureCalculator.hpp"
using CAP::ClosureCalculator;

ClassImp(ClosureCalculator);

ClosureCalculator::ClosureCalculator(const String & _name,
                                     const Configuration & _configuration)
:
Task(_name, _configuration)
{
  appendClassName("ClosureCalculator");
}

void ClosureCalculator::setDefaultConfiguration()
{
  Task::setDefaultConfiguration();
  addParameter("HistogramsCreate",        true);
  addParameter("HistogramsExport",        true);
  addParameter("SelectedMethod",          0);
}

void ClosureCalculator::execute()
{
  String histosGeneratorFileName ="";
  String histosDetectorFileName  ="";
  String histosClosureFileName  ="";
  int selectedMethod = 0;
  // this needs to be fixed...

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("Starting closure test calculation");
    printItem("HistoInputPath",histosImportPath);
    printItem("HistoGeneratorFileName",histosGeneratorFileName);
    printItem("HistoDetectorFileName",histosDetectorFileName);
    printItem("HistogramsExportPath",histosExportPath);
    printItem("HistogramsClosureFileName",histosClosureFileName);
    switch (selectedMethod)
      {
        case 0: printItem("SelectedMethod","Difference"); break;
        case 1: printItem("SelectedMethod","Ratio"); break;
      }
    }
  String option = "NEW";
  if (histosForceRewrite) option = "RECREATE";
  TFile & generatorFile = *openRootFile("", histosGeneratorFileName, "READ");
  TFile & detectorFile  = *openRootFile("", histosDetectorFileName,  "READ");
  TFile & closureFile   = *openRootFile("", histosClosureFileName,option);
  HistogramCollection * generatorCollection = new HistogramCollection("GeneratorLevel",getSeverityLevel());
  HistogramCollection * detectorCollection  = new HistogramCollection("DetectorLevel", getSeverityLevel());
  HistogramCollection * closureCollection   = new HistogramCollection("Closure",       getSeverityLevel());
  generatorCollection->loadCollection(generatorFile);
  detectorCollection->loadCollection(detectorFile);
  generatorCollection->setOwnership(false);
  detectorCollection->setOwnership(false);
  closureCollection->setOwnership(false);
  switch (selectedMethod)
    {
      case 0: closureCollection->differenceCollection(*detectorCollection,*generatorCollection,true); break;
      case 1: closureCollection->ratioCollection(*detectorCollection,*generatorCollection,true); break;
    }
  closureCollection->exportHistograms(closureFile);
  generatorFile.Close();
  detectorFile.Close();
  closureFile.Close();
  delete generatorCollection;
  delete detectorCollection;
  delete closureCollection;
  if (reportInfo (__FUNCTION__)) cout << "Closure Test Completed." << endl;
}

