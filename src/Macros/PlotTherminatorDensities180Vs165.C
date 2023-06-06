
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
void loadParticles(const TString & includeBasePath);
void loadPythia(const TString & includeBasePath);
void loadPerformance(const TString & includeBasePath);
void loadAmpt(const TString & includeBasePath);
void loadEpos(const TString & includeBasePath);
void loadHijing(const TString & includeBasePath);
void loadHerwig(const TString & includeBasePath);
void loadUrqmd(const TString & includeBasePath);
void loadBasicGen(const TString & includeBasePath);
void loadGlobal(const TString & includeBasePath);
void loadParticle(const TString & includeBasePath);
void loadPair(const TString & includeBasePath);
void loadNuDyn(const TString & includeBasePath);
void loadSubSample(const TString & includeBasePath);
void loadExec(const TString & includeBasePath);
void loadTherminator(const TString & includeBasePath);


TH1 * getProjectionX(TFile * inputFile, const TString & histoName2D)
{
  TH2 * h2 = (TH2*) inputFile->Get(histoName2D);
  if (!h2)
    {
    cout << "Histogram named " << histoName2D << " not found - abort" << endl;
    return nullptr;
    }
  TH1 * proj = h2->ProjectionX();
  return proj;
}

double scaleAndGetIntegral(TH1 * h)
{
  double binWidth = h->GetXaxis()->GetBinWidth(1);
  double scale = 1.0/binWidth;
  h->Scale(scale);
  double integral = h->Integral("WIDTH");
  cout << "Integral of " << h->GetName() << "  :   " << integral  << endl;
  return integral;
}

TH1 * computeRatio(TH1 * num, TH1* dem)
{
  TH1 * clone = (TH1*) num->Clone();
  clone->Divide(dem);
  return clone;
}


ifstream & openInputAsciiFile(const TString  & inputPath, const TString  & fileName, const TString  & extension, const TString  & ioOption="")
{
  TString  inputFileName = inputPath;
  // make sure that if an inputPath is given, it ends with '/'
  int slash = inputFileName.First('/');
  int len = inputFileName.Length();
  //  cout << slash << endl;
  //  cout << len << endl;
  if (len>0 && (len-1)!=slash) inputFileName += "/";
  inputFileName += fileName;
  if (!inputFileName.EndsWith(extension)) inputFileName += extension;
  cout << "Attempting to open input file named: " << inputFileName << " in mode: " << ioOption << endl;
  ios_base::openmode mode = ios_base::in;
  cout << "Opening file: " << inputFileName << " with option: " << ioOption << endl;
  ifstream * inputFile = new ifstream(inputFileName.Data(),mode);
  if (!inputFile || !inputFile->is_open())
    {
    cout << "File not open" << endl;
    exit(2);
    }
  cout << "File: " << inputFileName << " successfully opened." << endl;
  return *inputFile;
}

CAP::ParticleDb * importParticleDb()
{
  TString particleDbImportPath = "/Users/aa7526/Documents/GitHub/CAP5.0/DB/ParticleData/";
  TString particleDbImportFile = "particles.data";
  ifstream & inputFile = openInputAsciiFile(particleDbImportPath,particleDbImportFile,".data");
  CAP::ParticleDb   * particleDb = new CAP::ParticleDb();
  CAP::ParticleType * particleType;
  char   buff[300];
  char   name[20];
  double mass, width, spin, isospin, isospin3, Nq, Ns, Naq, Nas, Nc, Nac, pdgCode;
  int    index = 0;
  try
  {
  while (!inputFile.eof())
    {
    inputFile.getline(buff,300);
    if (!(*buff) || (*buff == '#'))
      {
      //      cout << "Buffer:" << buff << endl;
      //      cout << "Skip comment" << endl;
      continue;
      }
    istringstream * iss = new istringstream(buff);
    (*iss) >> name >> mass >> width >> spin >> isospin >> isospin3 >> Nq >> Ns >> Naq >> Nas >> Nc >> Nac >> pdgCode;
    index++;
    //    if (reportDebug(__FUNCTION__))
    //      {
    //      cout << '\t'<<index<<" "<<name<<" "<<mass<<" "<<width<<" "<<spin<<" "<<isospin<<" "<<isospin3<<" "<<Nq<<" "<<Naq<<" "<<Ns<<" "<<Nas<<" "<<Nc<<" "<<Nac<<" "<<pdgCode << endl;
    //      }
    particleType = new CAP::ParticleType();
    particleType->setIndex(index);
    particleType->setName(name);
    particleType->setTitle(name);
    particleType->setMass(mass);
    particleType->setWidth(width);
    particleType->setSpin(spin);
    particleType->setIsospin(isospin);
    particleType->setIsospin3(isospin3);
    particleType->setNumberQ(static_cast<int>  (Nq));
    particleType->setNumberAQ(static_cast<int> (Naq));
    particleType->setNumberS(static_cast<int>  (Ns));
    particleType->setNumberAS(static_cast<int> (Nas));
    particleType->setNumberC(static_cast<int>  (Nc));
    particleType->setNumberAC(static_cast<int> (Nac));
    particleType->setNumberB(static_cast<int>  (0));
    particleType->setNumberAB(static_cast<int> (0));
    double netS   = Nas - Ns;
    double netC   = Nc  - Nac;
    double baryon = (Nq + Ns + Nc)/3.0 - (Naq + Nas + Nac)/3.0;
    double charge = isospin3 +(baryon +netS)/2.0;
    particleType->setCharge( static_cast<int> ( charge ));
    particleType->setBaryonNumber( static_cast<int> ( baryon ));
    particleType->setStrangessNumber(static_cast<int> ( netS   ));
    particleType->setCharmNumber(  static_cast<int> ( netC   ));
    particleType->setBottomNumber( 0 );
    particleType->setPdgCode(static_cast<int> ( pdgCode));
    particleDb->addParticleType(particleType);
    delete iss;
    }
  }
  catch (...)
  {
  cout << "error reading particle database." << endl;
  exit(1);
  }
  inputFile.close();
  return particleDb;
}



int PlotTherminatorDensities180Vs165()
{
  TString includeBasePath = getenv("CAP_SRC");
  loadBase(includeBasePath);
  loadParticles(includeBasePath);

  using CAP::Configuration;
  using CAP::CanvasConfiguration;
  using CAP::GraphConfiguration;
  using CAP::Plotter;
  using CAP::Particle;
  using CAP::ParticleType;



  try
  {
  CAP::ParticleDb * particleDb = importParticleDb();
  if (!particleDb)
    {
    cout << "No ParticleDb!!! Why???" << endl;
    exit(1);
    }


  bool printGif = 0;
  bool printPdf = 1;
  bool printSvg = 0;
  bool printC   = 1;
  bool useColor = true;
  //CanvasConfiguration landscapeLinear(CanvasConfiguration::LandscapeWide,CanvasConfiguration::Linear);
  CanvasConfiguration landscapeLinear(CanvasConfiguration::Landscape,CanvasConfiguration::Linear);
  CanvasConfiguration landscapeLinearTight(CanvasConfiguration::LandscapeTight,CanvasConfiguration::Linear);
  CanvasConfiguration landscapeLogY(CanvasConfiguration::LandscapeWide,CanvasConfiguration::LogY);
  vector<GraphConfiguration*>  graphConfigurations1D = GraphConfiguration::createConfigurationPalette(10,1);
  vector<GraphConfiguration*>  graphConfigurations2D = GraphConfiguration::createConfigurationPalette(10,2);
  //landscapeLinear.addParameter("windowHeight", 300);
  for (unsigned int iGraph=0; iGraph<8; iGraph++)
    {
    graphConfigurations1D[iGraph]->addParameter("yTitleOffset",  0.9);
    graphConfigurations1D[iGraph]->addParameter("xTitleSize",   0.08);
    graphConfigurations1D[iGraph]->addParameter("xTitleOffset", 0.8);
    graphConfigurations1D[iGraph]->addParameter("xLabelSize",   0.06);
    graphConfigurations1D[iGraph]->addParameter("xLabelOffset", 0.01);
    graphConfigurations1D[iGraph]->addParameter("yTitleSize",   0.08);
    graphConfigurations1D[iGraph]->addParameter("yTitleOffset", 0.7);
    graphConfigurations1D[iGraph]->addParameter("yLabelSize",   0.06);
    graphConfigurations1D[iGraph]->addParameter("yLabelOffset", 0.01);
    graphConfigurations1D[iGraph]->addParameter("markerSize",   0.5);
    graphConfigurations1D[iGraph]->addParameter("markerStyle",  20);
    if (iGraph<4)
      graphConfigurations1D[iGraph]->addParameter("markerStyle",  kFullSquare);
    else
      graphConfigurations1D[iGraph]->addParameter("markerStyle",  kOpenSquare);
    }
  graphConfigurations1D[0]->addParameter("markerColor", kBlack);
  graphConfigurations1D[0]->addParameter("lineColor",   kBlack);
  graphConfigurations1D[1]->addParameter("markerColor", kBlue);
  graphConfigurations1D[1]->addParameter("lineColor",   kBlue);
  graphConfigurations1D[2]->addParameter("markerColor", kRed);
  graphConfigurations1D[2]->addParameter("lineColor",   kRed);
  graphConfigurations1D[3]->addParameter("markerColor", kGreen);
  graphConfigurations1D[3]->addParameter("lineColor",   kGreen);
  graphConfigurations1D[4+0]->addParameter("markerColor", kBlack);
  graphConfigurations1D[4+0]->addParameter("lineColor",   kBlack);
  graphConfigurations1D[4+1]->addParameter("markerColor", kBlue);
  graphConfigurations1D[4+1]->addParameter("lineColor",   kBlue);
  graphConfigurations1D[4+2]->addParameter("markerColor", kRed);
  graphConfigurations1D[4+2]->addParameter("lineColor",   kRed);
  graphConfigurations1D[4+3]->addParameter("markerColor", kGreen);
  graphConfigurations1D[4+3]->addParameter("lineColor",   kGreen);


  TString inputPath1  = "/Volumes/ClaudeDisc4/OutputFiles/Therminator/BW/T165.6/";
  TString inputPath2  = "/Volumes/ClaudeDisc4/OutputFiles/Therminator/BW/T180/";
  TString outputPath  = "/Volumes/ClaudeDisc4/OutputFiles/Therminator/BW/T180VsT165/";

  //vector<TH2*>    histos2D;
  vector<TH1*>    histosPt;
  //vector<TH1*>    histosY;
  vector<TString> titles;

  Configuration taskConfig;
  Plotter * plotter = new Plotter("Plotter",taskConfig);
  plotter->setDefaultOptions(useColor);

  TFile & file1 =  plotter->openRootFile(inputPath1,"SingleGen.root","OLD");
  TFile & file2 =  plotter->openRootFile(inputPath2,"SingleGen.root","OLD");

  int nTypes = particleDb->getNumberOfTypes();
  cout << "particleDb::nTypes" << nTypes << endl;

  TString histoBase = "SingleGen_All_";
  TString ptSuffix  = "_n1_ptXS";
  TString histoName;

  for (int k=nTypes-11; k<nTypes-1; k++)
    {
    ParticleType * particleType = particleDb->getParticleType(k);
    if (!particleType)
      {
      cout << "!particleType" << endl;
      exit(1);
      }
    int pdgCode = particleType->getPdgCode();
    TString particleName    = particleType->getName();
    TString particleTitle   = particleType->getTitle();
    histoName = histoBase;
    histoName += particleName;
    histoName += ptSuffix;

    TH1 * h2  = (TH1*) file2.Get(histoName);
    if (!h2)
      {
      cout << " File 2: Histograms not found: " << histoName <<   endl;
      return -1;
      }

    TH1 * h1  = (TH1*) file1.Get(histoName);
    if (!h1)
    {
    cout << " File 1: Histograms not found: " << histoName <<   endl;
    return -1;
    }

    histosPt.push_back(h1);
    histosPt.push_back(h2);
    titles.push_back(particleName+" 165");
    titles.push_back(particleName+" 180");
    }

  TString plotNameBase = "TherminatorDensities180Vs165_";
  TString plotName;

  vector<TH1*>    histosSet;
  //vector<TH1*>    histosY;
  vector<TString> titlesSet;

  for (int iSet=0;iSet<10;iSet++)
    {
    plotName = plotNameBase;
    plotName += iSet;
    histosSet.clear();
    titlesSet.clear();
    for (int iHisto=0;iHisto<2;iHisto++)
      {
      int index = iSet*2 + iHisto;
      histosSet.push_back(histosPt[index]);
      titlesSet.push_back(titles[index]);
      }
    plotter->plot(histosSet,graphConfigurations1D,titlesSet,plotName,landscapeLogY,TString("pT"), 0.0, 5.0,TString("#rho_{1}(pT)"),1.0E-7, 1.0E3,
                0.50, 0.6, 0.65, 0.9, 0.04);
    }

  plotter->printAllCanvas(outputPath, printGif, printPdf, printSvg, 0, printC);
  }
  catch (CAP::TaskException exception)
  {
  exception.print();
  exit(1);
  }
  catch (CAP::FileException exception)
  {
  exception.print();
  exit(1);
  }
  catch (CAP::MathException exception)
  {
  exception.print();
  exit(1);
  }
  catch (CAP::Exception exception)
  {
  exception.print();
  exit(1);
  }

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

void loadParticles(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Particles/";
  gSystem->Load(includePath+"Particle.hpp");
  gSystem->Load(includePath+"ParticleType.hpp");
  gSystem->Load(includePath+"ParticleDecayMode.hpp");
  gSystem->Load(includePath+"ParticleDb.hpp");
  gSystem->Load("libParticles.dylib");
}


void loadPythia(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/CAPPythia/";
  gSystem->Load(includePath+"PythiaEventGenerator.hpp");
  gSystem->Load(includePath+"PythiaEventReader.hpp");
  gSystem->Load("libCAPPythia.dylib");
}

void loadPerformance(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Performance/";
  gSystem->Load(includePath+"ClosureCalculator.hpp");
  gSystem->Load(includePath+"ClosureIterator.hpp");
  gSystem->Load(includePath+"MeasurementPerformanceSimulator.hpp");
  gSystem->Load(includePath+"ParticlePerformanceSimulator.hpp");
  gSystem->Load(includePath+"ParticlePerformanceAnalyzer.hpp");
  gSystem->Load(includePath+"ParticlePerformanceHistos.hpp");
  gSystem->Load("libPerformance.dylib");
}

void loadAmpt(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Ampt/";
  gSystem->Load(includePath+"AmptEventReader.hpp");
  gSystem->Load("libAmpt.dylib");
}

void loadEpos(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Epos/";
  gSystem->Load(includePath+"EposEventReader.hpp");
  gSystem->Load("libEpos.dylib");
}

void loadHijing(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Hijing/";
  gSystem->Load(includePath+"HijingEventReader.hpp");
  gSystem->Load("libHijing.dylib");
}

void loadHerwig(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Herwig/";
  gSystem->Load(includePath+"HerwigEventReader.hpp");
  gSystem->Load("libHerwig.dylib");
}

void loadUrqmd(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Urqmd/";
  gSystem->Load(includePath+"UrqmdEventReader.hpp");
  gSystem->Load("libUrqmd.dylib");
}


void loadBasicGen(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/BasicGen/";
  gSystem->Load(includePath+"GaussianGeneratorTask.hpp");
  gSystem->Load(includePath+"RadialBoostHistos.hpp");
  gSystem->Load(includePath+"RadialBoostTask.hpp");
  gSystem->Load(includePath+"RapidityGenerator.hpp");
  gSystem->Load("libBasicGen.dylib");
}

void loadGlobal(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Global/";
  gSystem->Load(includePath+"GlobalAnalyzer.hpp");
  gSystem->Load(includePath+"GlobalHistos.hpp");
  gSystem->Load(includePath+"TransverseSpherocityHistos.hpp");
  gSystem->Load(includePath+"TransverseSpherocityAnalyzer.hpp");
  gSystem->Load("libBasicGen.dylib");
}

void loadParticle(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/ParticleSingle/";
  gSystem->Load(includePath+"ParticleSingleHistos.hpp");
  gSystem->Load(includePath+"ParticleSingleDerivedHistos.hpp");
  gSystem->Load(includePath+"ParticleSingleAnalyzer.hpp");
  gSystem->Load("libParticleSingle.dylib");
}

void loadPair(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/ParticlePair/";
  gSystem->Load(includePath+"ParticlePairAnalyzer.hpp");
  gSystem->Load(includePath+"ParticlePairHistos.hpp");
  gSystem->Load(includePath+"ParticlePairDerivedHistos.hpp");
  gSystem->Load(includePath+"BalanceFunctionCalculator.hpp");
  gSystem->Load("libParticlePair.dylib");
}

void loadNuDyn(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/NuDyn/";
  gSystem->Load(includePath+"NuDynAnalyzer.hpp");
  gSystem->Load(includePath+"NuDynDerivedHistos.hpp");
  gSystem->Load(includePath+"NuDynHistos.hpp");
  gSystem->Load("libNuDyn.dylib");
}

void loadSubSample(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/SubSample/";
  gSystem->Load(includePath+"SubSampleStatCalculator.hpp");
  gSystem->Load("libSubSample.dylib");
}

void loadExec(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Exec/";
  gSystem->Load(includePath+"RunAnalysis.hpp");
  gSystem->Load("libExec.dylib");
}

void loadTherminator(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Therminator/";
  gSystem->Load(includePath+"Model.hpp");
  gSystem->Load("libTherminator.dylib");
}
