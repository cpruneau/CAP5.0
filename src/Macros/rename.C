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
#include <vector>
#include <TStyle.h>
#include <TROOT.h>
#include <TSystem.h>
#include "TClass.h"
#include "TParameter.h"
#include "TFile.h"
using std::vector;
using std::iostream;
using std::cout;
using std::endl;

vector<TString> listFilesInDir(const TString & pathname,
                                    const TString & ext,
                                    bool prependPath,
                                    bool verbose,
                                    int  maximumDepth,
                                    int  currentDepth)
{
  TString dirname = pathname;
  int depth = currentDepth;
  if (!dirname.EndsWith("/")) dirname += "/";
  if (verbose) cout << " Searching................: " << dirname << endl;
  if (verbose) cout << " maximumDepth.............: " << maximumDepth << endl;
  if (verbose) cout << " currentDepth.............: " << depth << endl;
  TSystemDirectory dir(dirname, dirname);
  TList *files = dir.GetListOfFiles();
  vector<TString>  fileNames;
  vector<TString>  subdirs;

  if (files)
    {
    TSystemFile *file;
    TString fname;
    TIter next(files);
    while ((file=(TSystemFile*)next()))
      {
      fname = file->GetName();
      if (file->IsDirectory() &&  !fname.BeginsWith(".") )
        {
        subdirs.push_back(fname);
        }
      else if (fname.EndsWith(ext))
        {
        if (prependPath)
          fileNames.push_back(dirname+fname);
        else
          fileNames.push_back(fname);
        //cout << fname.Data() << endl;
        if (verbose) cout << fname << endl;
        }
      }
    }
  int nSubdirs = subdirs.size();
  if (verbose) cout << " Number of subdir found...: " << nSubdirs << endl;
  ++depth;

  if (nSubdirs>0 && depth<=maximumDepth)
    {

    for (int iDir=0; iDir<nSubdirs; iDir++)
      {
      vector<TString> additionalFiles;
      TString  subdirname = dirname;
      subdirname += "/";
      subdirname += subdirs[iDir];
      subdirname += "/";
      additionalFiles = listFilesInDir(subdirname,ext,prependPath,verbose,maximumDepth,depth);
      int nAdditionalfiles = additionalFiles.size();
      for (int iFile=0;iFile<nAdditionalfiles;iFile++)
        fileNames.push_back(additionalFiles[iFile]);
      }
    }
  if (verbose) cout << " Number of files  found...: " << fileNames.size() << endl;
  if (verbose) cout << " Returning up one level.... " <<  endl;

  return fileNames;
}

int rename(TString pathname="/Volumes/ClaudeDisc4/OutputFiles/Therminator/BW/OUT202305231524/")
{
  vector<TString>  names = listFilesInDir(pathname,TString(".root"), 1, 1, 3, 0);

  int nFiles = names.size();
  std::ofstream script("test.sh");

  for (int iFile=0; iFile<nFiles; iFile++)
    {
    cout << names[iFile] << endl;
    TString source = names[iFile];
    TString target = names[iFile];
    target.ReplaceAll("single","SingleGen");
    target.ReplaceAll("pair","PairGen");
    cout << target << endl;
    script << " mv " << source << "   " << target << endl;
    }
  script.close();
  return 0;

}
