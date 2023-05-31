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
#include "DerivedHistoIterator.hpp"
using CAP::DerivedHistoIterator;
using CAP::Configuration;
using CAP::String;
using CAP::VectorString;

ClassImp(CAP::DerivedHistoIterator);

namespace CAP
{

DerivedHistoIterator::DerivedHistoIterator(const String & _name,
                                           const Configuration & _configuration)
:
Task(_name,_configuration)
{
  appendClassName("DerivedHistoIterator");
}

void DerivedHistoIterator::setDefaultConfiguration()
{
  Task::setDefaultConfiguration();
  String none  = "none";
  addParameter("HistogramsCreate",         true);
  addParameter("HistogramsImport",         true);
  addParameter("HistogramsExport",         true);
  addParameter("AppendedString",           TString("_Derived"));
  generateKeyValuePairs("IncludedPattern", none,20);
  generateKeyValuePairs("ExcludedPattern", none,20);
}

void DerivedHistoIterator::configure()
{
  Task::configure();
  setSeverity();
  nEventFilters = 0;
  if (reportInfo(__FUNCTION__)) cout << "Configuring task:" << getName() << endl;
  histosForceRewrite  = getValueBool(  "HistogramsForceRewrite");
  histosImport        = getValueString("HistogramsImport");
  histosImportPath    = getValueString("HistogramsImportPath");
  histosExport        = getValueBool(  "HistogramsExport");
  histosExportPath    = getValueString("HistogramsExportPath");
  histosExportFile    = getName();
  appendedString      = getValueString("AppendedString");
  maximumDepth        = 2; //getValueInt(   "MaximumDepth");
  defaultGroupSize    = 20; //getValueInt(   "DefaultGroupSize");

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem("HistogramsImport",    histosImport);
    printItem("HistogramsImportPath",histosImportPath);
    printItem("HistogramsExport",    histosExport);
    printItem("HistogramsExportPath",histosExportPath);
    printItem("HistogramsExportFile",histosExportFile);
    printItem("DefaultGroupSize",    defaultGroupSize);
    printItem("AppendedString",      appendedString);
    printItem("MaximumDepth",        maximumDepth);
    cout << endl;
    }
}

void DerivedHistoIterator::initialize()
{
  initializeTaskExecuted();
  //initializeFilters();
  //initializeParticleDbLink();
}


void DerivedHistoIterator::execute()
{
  String none("none");
  String analyzerName;
  unsigned int nSubTasks = subTasks.size();

  if (reportInfo(__FUNCTION__))
    {
    cout << endl;
    printItem(" SubTasks Count",int(nSubTasks));
//    for (unsigned int k=0; k<includedPatterns.size(); k++)
//      {
//      cout << " Included.................: " << includedPatterns[k]     << endl;
//      }
//    for (unsigned int k=0; k<excludedPatterns.size(); k++)
//      {
//      cout << " Excluded.................: " << excludedPatterns[k]     << endl;
//      }
    }

  for (unsigned int iTask=0; iTask<nSubTasks; iTask++)
    {
    CAP::Task & subTask = *subTasks[iTask];
    analyzerName = subTask.getName();
    VectorString  includePatterns = getSelectedValues("IncludedPattern", "none");
    VectorString  excludePatterns = getSelectedValues("ExcludedPattern", "none");
    includePatterns.push_back(analyzerName);
    bool isReco = analyzerName.Contains("Reco");
    if (isReco)  includePatterns.push_back(TString("Reco"));
    if (!isReco) excludePatterns.push_back(TString("Reco"));
    excludePatterns.push_back(TString("Derived"));

    if (reportInfo(__FUNCTION__))
      {
      cout << endl;
      cout << "===========================================================" << endl;
      printItem("SubTask#", int(iTask));
      printItem("SubTask Name",analyzerName);
      printItem("HistogramsImportPath",histosImportPath);
      printItem("HistogramsExportPath",histosExportPath);
      for (int k=0; k<includePatterns.size(); k++)
        printItem("Include Pattern",includePatterns[k]);
      for (int k=0; k<excludePatterns.size(); k++)
        printItem("Exclude Pattern",excludePatterns[k]);
      cout << "===========================================================" << endl;
      }
     bool prependPath = true;
    bool verbose = false;
    int  maximumDepth = 1;
    VectorString  allFilesToProcess = listFilesInDir(histosImportPath,includePatterns,excludePatterns, prependPath, verbose, maximumDepth,0);
    
    int nFiles = allFilesToProcess.size();
    if (nFiles<1)
      {
      if (reportError(__FUNCTION__))
        {
        cout << endl;
        cout << "X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#"  << endl;
        cout << "X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#"  << endl;
        cout << "  Attempting to execute derived histo analysis with no selected files." << endl;
        cout << "                         Check your code!!!!!!! " <<  endl;
        cout << "X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#"  << endl;
        cout << "X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#X#"  << endl;
        }
      return;
      }
    if (reportInfo(__FUNCTION__))
      {
      cout << endl;
      cout << " nFiles................: " << nFiles << endl;
      }
    for (int iFile=0; iFile<nFiles; iFile++)
      {
      histosImportFile  = allFilesToProcess[iFile];
      histosExportFile  = removeRootExtension(histosImportFile);
      histosExportFile += appendedString;
      if (reportInfo(__FUNCTION__))
        {
        cout << endl;
        cout << " nFiles................: " << nFiles << endl;
        cout << " iFile.................: " << iFile  << endl;
        cout << " Input file............: " << histosImportFile << endl;
        cout << " Output file...........: " << histosExportFile << endl;
        }
      String nullString = "";
      subTask.setHistosCreate(false);
      subTask.setHistosImport(true);
      subTask.setHistosImportPath(nullString);
      subTask.setHistosImportFile(histosImportFile);
      subTask.setHistosImportDerived(false);
      subTask.setHistosCreateDerived(true);
      subTask.setHistosExport(true);
      subTask.setHistosExportPath(nullString);
      subTask.setHistosExportFile(histosExportFile);
      subTask.setHistosReset(false);
      subTask.setHistosClear(true);
      subTask.setHistosPlot(false);
      subTask.setHistosPrint(false);
      subTask.setHistosScale(false);
      subTask.setHistosForceRewrite(true);
      subTask.initialize();
      subTask.calculateDerivedHistograms();
      subTask.finalize();
      subTask.clear();
      }
    }
  if (reportEnd(__FUNCTION__))
    ;
}

} // namespace CAP
