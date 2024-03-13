
void loadBase(const TString & includeBasePath);

void generateConstantValue(double mu, double sigma, int n1, int n2, int n3, ofstream & out)
{
  out << "Set 1" << endl;
  double v;
  for (int k=0; k<n1; k++)
    {
    v = gRandom->Gaus(mu,sigma);
    out << k << " " << v << endl;
    }
  out << endl << endl << endl << endl ;
  out << "Set 2" << endl;
  for (int k=0; k<n2; k++)
    {
    v = gRandom->Gaus(mu,sigma);
    out << k << " " << v << endl;
    }
  out << endl << endl << endl << endl ;
  out << "Set 3" << endl;
  for (int k=0; k<n3; k++)
    {
    double v = gRandom->Gaus(mu,sigma);
    out << k << " " << v << endl;
    }
}

void generateLinearValue(double a0, double a1, double sigma, int n1, int n2, int n3, ofstream & out)
{
  double x, y, v, e;
  double xMin = -5.0;
  double xMax = 15.0;
  double xWidth = xMax - xMin;
  double xBin;

  out << "Set 1" << endl;
  xBin = xWidth/double(n1);
  for (int k=0; k<n1; k++)
    {
    x = xMin +  double(k)*xBin;
    y = a0 + a1*x;
    e = sigma*sqrt(a1*double(k+1)*xBin);
    v = gRandom->Gaus(y,e);
    out << k << " " << x << " " << y << " " << e << endl;
    }
  out << endl << endl << endl << endl ;

  out << "Set 2" << endl;
  xBin = xWidth/double(n2);
  for (int k=0; k<n2; k++)
    {
    x = xMin +  double(k)*xBin;
    y = a0 + a1*x;
    e = sigma*sqrt(a1*double(k+1)*xBin);
    v = gRandom->Gaus(y,e);
    out << k << " " << x << " " << y << " " << e << endl;
    }
  out << endl << endl << endl << endl ;

  out << "Set 3" << endl;
  xBin = xWidth/double(n3);
  for (int k=0; k<n3; k++)
    {
    x = xMin +  double(k)*xBin;
    y = a0 + a1*x;
    e = sigma*sqrt(a1*double(k+1)*xBin);
    v = gRandom->Gaus(y,e);
    out << k << " " << x << " " << y << " " << e << endl;
    }
  out << endl << endl << endl << endl ;

  out << "Set 4" << endl;
  xBin = xWidth/double(n3);
  for (int k=0; k<n3; k++)
    {
    x = xMin +  double(k)*xBin;
    y = a0 + a1*x;
    e = 0.1*sigma*sqrt(a1*double(k+1)*xBin);
    v = gRandom->Gaus(y,e);
    out << k << " " << x << " " << y << " " << e << endl;
    }
  out << endl << endl << endl << endl ;
}

void generateCubicValue(double a0, double a1, double a2, double a3, double sigma, int n1, int n2, int n3, ofstream & out)
{
  double x, y, v, e;
  double xMin = -5.0;
  double xMax = 15.0;
  double xWidth = xMax - xMin;
  double xBin;

  out << "Set 1" << endl;
  xBin = xWidth/double(n1);
  for (int k=0; k<n1; k++)
    {
    x = xMin +  double(k)*xBin;
    y = a0 + x*(a1 + x*(a2 + x*a3));
    e = sigma*sqrt(a1*double(k+1)*xBin);
    v = gRandom->Gaus(y,e);
    out << k << " " << x << " " << y << " " << e << endl;
    }
  out << endl << endl << endl << endl ;

  out << "Set 2" << endl;
  xBin = xWidth/double(n2);
  for (int k=0; k<n2; k++)
    {
    x = xMin +  double(k)*xBin;
    y = a0 + x*(a1 + x*(a2 + x*a3));
    e = sigma*sqrt(a1*double(k+1)*xBin);
    v = gRandom->Gaus(y,e);
    out << k << " " << x << " " << y << " " << e << endl;
    }
  out << endl << endl << endl << endl ;

  out << "Set 3" << endl;
  xBin = xWidth/double(n3);
  for (int k=0; k<n3; k++)
    {
    x = xMin +  double(k)*xBin;
    y = a0 + x*(a1 + x*(a2 + x*a3));
    e = sigma*sqrt(a1*double(k+1)*xBin);
    v = gRandom->Gaus(y,e);
    out << k << " " << x << " " << y << " " << e << endl;
    }
  out << endl << endl << endl << endl ;

  out << "Set 4" << endl;
  xBin = xWidth/double(n3);
  for (int k=0; k<n3; k++)
    {
    x = xMin +  double(k)*xBin;
    y = a0 + x*(a1 + x*(a2 + x*a3));
    e = 0.1*sigma*sqrt(a1*double(k+1)*xBin);
    v = gRandom->Gaus(y,e);
    out << k << " " << x << " " << y << " " << e << endl;
    }
  out << endl << endl << endl << endl ;
}

void DataGenPhy7850(int option=3, const TString & outputFileName="cube.txt")
{
  TString includeBasePath = getenv("CAP_SRC");
  loadBase(includeBasePath);

  ofstream out(outputFileName);
  switch (option)
    {
      case 0:
      {
      cout << "Generate constant values" << endl;
      double mu = 101.55;
      double sigma = 5.0;
      int    n1 = 10;
      int    n2 = 100;
      int    n3 = 1000;
      generateConstantValue(mu, sigma, n1, n2, n3, out);
      break;
      }

      case 1:
      {
      cout << "Generate straight values" << endl;
      double a0 = 10.0;
      double a1 = 5.0;
      double sigma = 0.15;
      int    n1 = 10;
      int    n2 = 100;
      int    n3 = 1000;
      generateLinearValue(a0, a1, sigma, n1, n2,n3, out);
      break;
      }

      case 3:
      {
      cout << "Generate cubic values" << endl;
      double a0 = 10.0;
      double a1 = 5.0;
      double a2 = 1.0;
      double a3 = 0.5;
      double sigma = 0.15;
      int    n1 = 10;
      int    n2 = 100;
      int    n3 = 1000;
      generateCubicValue(a0, a1, a2, a3, sigma, n1, n2,n3, out);
      break;
      }
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
