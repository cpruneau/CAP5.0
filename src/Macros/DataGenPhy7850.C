
void loadBase(const TString & includeBasePath);

void DataGenPhy7850()
{
  TString includeBasePath = getenv("CAP_SRC");
  loadBase(includeBasePath);

  ofstream out("data.txt");

  out << "Set 1" << endl;
  for (int k=0; k<10; k++)
    {
    double mu = 101.55;
    double sigma = 5.0;
    double v = gRandom->Gaus(mu,sigma);
    out << k << " " << v << endl;
    }
  out << endl << endl << endl << endl ;

  out << "Set 2" << endl;
  for (int k=0; k<100; k++)
    {
    double mu = 101.55;
    double sigma = 5.0;
    double v = gRandom->Gaus(mu,sigma);
    out << k << " " << v << endl;
    }
  out << endl << endl << endl << endl ;

  out << "Set 3" << endl;
  for (int k=0; k<1000; k++)
    {
    double mu = 101.55;
    double sigma = 5.0;
    double v = gRandom->Gaus(mu,sigma);
    out << k << " " << v << endl;
    }
}


void loadBase(const TString & includeBasePath)
{
  TString includePath = includeBasePath + "/Base/";
  gSystem->Load(includePath+"Exceptions.hpp");
//  gSystem->Load(includePath+"Timer.hpp");
//  gSystem->Load(includePath+"MessageLogger.hpp");
//  gSystem->Load(includePath+"Task.hpp");
//  gSystem->Load(includePath+"Collection.hpp");
//  gSystem->Load(includePath+"HistogramCollection.hpp");
//  gSystem->Load(includePath+"HistogramGroup.hpp");
 // gSystem->Load("libBase.so");
///

  //gSystem->Load("libBase.dylib");
}
