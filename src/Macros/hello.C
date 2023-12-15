
void loadBase(const TString & includeBasePath);

void hello()
{
  TString includeBasePath = getenv("CAP_SRC");
  loadBase(includeBasePath);

  cout << "Hello World" << endl;
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
