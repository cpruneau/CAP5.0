
using VectorString      = std::vector<  TString    >;

class Configuration
{
  //friend TextParser;

  struct Parameter
  {
    TString      keyword;
    TString      value;
  };

public:
  Configuration();
  Configuration(const Configuration & _configuration);
  virtual ~Configuration();
  Configuration & operator=(const Configuration & _configuration);

  TString       getParameter(const char* aKeyword)  const;
  int     getNParameters() const;
  bool    getValueBool(const char* aKeyword) const;
  int     getValueInt(const char* aKeyword) const;
  long    getValueLong(const char* aKeyword) const;
  double  getValueDouble(const char* aKeyword) const;
  TString       getValueString  (const char* aKeyword) const;


  TString       standardize(   const char * path, const char* aKeyword) const;
  bool    getValueBool(  const char * path, const char* aKeyword) const;
  int     getValueInt (  const char * path, const char* aKeyword) const;
  long    getValueLong(  const char * path, const char* aKeyword) const;
  double  getValueDouble(const char * path, const char* aKeyword) const;
  TString       getValueString  (const char * path, const char* aKeyword) const;


  void addParameters(const Configuration & configuration);
  void addParameter(Parameter& aPar);
  void addParameter(const char * name, bool value);
  void addParameter(const char * name, int value);
  void addParameter(const char * name, long value);
  void addParameter(const char * name, double value);
  void addParameter(const char * name, const char * value);
  void addParameter(const char * name, const    TString      & value);
  void addParameter(const char * path, const char * name, bool value);
  void addParameter(const char * path, const char * name, int value);
  void addParameter(const char * path, const char * name, long value);
  void addParameter(const char * path, const char * name, double value);
  void addParameter(const char * path, const char * name, const char * value);
  void addParameter(const char * path, const char * name, const    TString      & value);
  bool hasEndColon(const char * path) const;
  void clear();
  bool isBool(const char * name) const;
  bool isInt(const char * name) const;
  bool isLong(const char * name) const;
  bool isDouble(const char * name) const;
  bool isString  (const char * name) const;
  bool isFound(const char * name) const;
  //  void readFromFile(const char * _inputPath,
  //                    const char * _inputFileName,
  //                    const char * _extension=".ini",
  //                    MessageLogger::Severity severity=MessageLogger::Info);
  //  void writeToFile(const char * outputFileName);
  int  printConfiguration(ostream & output);

  void sanityCheck(const char * name);


  //!
  //!Generates and stores in the configuration of this task a list of key,value parameters based on the given parameters.value
  //!The keys generated have the form keyBaseName## where keyBaseName is the base name of the keys and ## is an integer k
  //!from 0 to nKeysToGenerate-1 (inclusively)
  //!
  //!@param keyBaseName base name of the keys
  //!@param defaultValue default value given for all key,value pairs
  //!@param nKeysToGenerate number of key,value pairs to generate and add to this task configuration.
  //!
  void generateKeyValuePairs(const char *  keyBaseName, const char *  defaultValue, int nKeysToGenerate);

  void generateKeyValuePairs(const char *  path, const char *  keyBaseName, const char *  defaultValue, int nKeysToGenerate);

  //!
  //!Parse the configuration associated with task to find the key,value pairs that DO NOT feature the defaultValue
  //!
  //!@param keyBaseName base name of the keys
  //!@param defaultValue default value that is selected against
  //!
  VectorString      getSelectedValues(const char *  keyBaseName, const char *  defaultValue) const;

  VectorString      getSelectedValues(const char *  path, const char *  keyBaseName, const char *  defaultValue) const;

  //!
  //!Get  the number of key,value pairs with the given key base name  that DO NOT feature the defaultValue
  //!
  //!@param keyBaseName base name of the keys to be tested against.
  //!@param defaultValue default value that is selected against
  //!
  int getNSelectedValues(const char *  keyBaseName, const char *  defaultValue)  const;

  int getNSelectedValues(const char *  path, const char *  keyBaseName, const char *  defaultValue) const
  {
    TString      sPath = path;
    TString      sKeyBaseName = keyBaseName;
    return getNSelectedValues(sPath+  TString    (":")+sKeyBaseName, defaultValue);
  }

  int getNPossibleValues(const char *  keyBaseName) const;

  int getNPossibleValues(const char *  path, const char *  keyBaseName) const;

  //!
  //!Add key,value pairs with the given key base name  and values provided in the selectedValues array.
  //!
  //!@param keyBaseName base name of the keys to be used
  //!@param defaultValue default value that is selected against
  //!@param selectedValues  number of key,value pairs to be checked
  //!
  void addSelectedValues(const char *  keyBaseName, const char *  defaultValue, const VectorString      & selectedValues);

  void addSelectedValues(const char * path, const char * keyBaseName, const char * defaultValue, const VectorString      & selectedValues)
  {
    TString      sPath = path;
    TString      sKeyBaseName = keyBaseName;
    addSelectedValues(sPath+  TString    (":")+sKeyBaseName, defaultValue, selectedValues);
  }

protected:
  std::vector<Parameter> parameters;

  ClassDef(Configuration,0)

};


Configuration::Configuration()
{
  parameters.clear();
}

Configuration::Configuration(const Configuration & _configuration)
{
  parameters = _configuration.parameters;
}

Configuration & Configuration::operator=(const Configuration & _configuration)
{
  if (this!= &_configuration)
  {
    parameters = _configuration.parameters;
  }
  return *this;
}


Configuration::~Configuration()
{
  parameters.clear();
}


TString     Configuration::getParameter(const char* aKeyword)  const
{
  vector<Parameter>::const_iterator iter;
  //cout << " size: " << parameters.size() << endl;
  for (iter = parameters.begin(); iter != parameters.end(); iter++)
  {
    //cout << "keyword:" << iter->keyword << "   " << iter->value << endl;
    if (iter->keyword.EndsWith(aKeyword))
    {
      return iter->value;
    }
  }
  cout << "BUG 1" << endl; exit(1);
}

TString      Configuration::standardize(const char * path, const char* aKeyword) const
{
  TString      keyword = path;
  if (keyword.EndsWith(":")) keyword += aKeyword;
  else
  {
    keyword += ":";
    keyword += aKeyword;
  }
  return keyword;
}


bool    Configuration::getValueBool(  const char * path, const char* aKeyword) const
{
  return getValueBool(standardize(path,aKeyword));
}

int     Configuration::getValueInt (  const char * path, const char* aKeyword) const
{
  return getValueInt(standardize(path,aKeyword));
}

long    Configuration::getValueLong(  const char * path, const char* aKeyword) const
{
  return getValueLong(standardize(path,aKeyword));
}

double  Configuration::getValueDouble(const char * path, const char* aKeyword) const
{
  return getValueDouble(standardize(path,aKeyword));
}

TString      Configuration::getValueString  (const char * path, const char* aKeyword) const
{
  return getValueString  (standardize(path,aKeyword));
}

bool  Configuration::getValueBool(const char* aKeyword) const
{
  TString      v = getParameter(aKeyword);
  v.ToUpper();
  //cout << " Configuration::getValueBool(const char* aKeyword) for keyword: " << aKeyword << " finds:" << v << endl;
  if (v.EqualTo("0") || v.EqualTo("FALSE") || v.EqualTo("YES") ) return false;
  else if (v.EqualTo("1") || v.EqualTo("TRUE")  || v.EqualTo("NO")  ) return true;
  else if (v.IsDec())
  {
    int vv = v.Atoi();
    return vv>0;
  }
  return false;
}


int Configuration::getValueInt(const char* aKeyword) const
{
  TString      v = getParameter(aKeyword);
  if (!v.IsDec())
  {
    return -99999;
  }
  return v.Atoi();
}

long Configuration::getValueLong(const char* aKeyword) const
{
  TString      v = getParameter(aKeyword);
  if (!v.IsDec())
  {
    return -99999;
  }
  return v.Atoll();
}

double Configuration::getValueDouble (const char* aKeyword) const
{
  TString      v = getParameter(aKeyword);
  if (!v.IsFloat())
  {
    return -1.0E100;
  }
  return v.Atof();
}


TString   Configuration::getValueString   (const char* aKeyword) const
{
  return getParameter(aKeyword);
}


int Configuration::getNParameters() const
{
  return parameters.size();
}

void Configuration::addParameters(const Configuration & source)
{
  vector<Parameter>::const_iterator iter;
  //cout << "======== Initial: " << parameters.size() << endl;
  //cout << "======== Adding: " << source.getNParameters() << endl;
  for (iter = source.parameters.begin(); iter != source.parameters.end(); iter++)
  {
    //cout << "======== Adding parameter.keyword = " << iter->keyword << " value   = " << iter->value << endl;
    Parameter  parameter;
    parameter.keyword = iter->keyword;
    parameter.value   = iter->value;
    addParameter(parameter);
    int index = -1 + parameters.size();
    //cout << "======== Added parameter.keyword = " << parameters[index].keyword << " value   = " << parameters[index].value << endl;
  }
  //cout << "======== Final:  " << parameters.size() << endl;
}


void Configuration::addParameter(Parameter& parameter)
{
  vector<Parameter>::iterator iter;
  bool stop = false;

  //  if (parameter.keyword.Contains("EventsAnalyze"))
  //    {
  //    cout << "Searching for EventsAnalyze " << endl;
  //    stop = true;
  //    }
  TString      keySearched = parameter.keyword;
  //cout << "======== Configuration::addParameter(" << keySearched << ")" << endl;
  for (iter = parameters.begin(); iter != parameters.end(); iter++)
  {
    TString      keyCompared = iter->keyword;
    if (keyCompared.EqualTo(keySearched.Data()))
    {
      iter->value = parameter.value;
      return;
    }
  }
  parameters.push_back(parameter);
}

void Configuration::addParameter(const char * name, bool value)
{
  Parameter p;
  p.keyword = name;
  p.value   = "";
  p.value   += value;
  addParameter(p);
}

//!
//! Add an int parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * name, int value)
{
  Parameter p;
  p.keyword = name;
  p.value   = "";
  p.value   += value;
  addParameter(p);
}


//!
//! Add an int parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * name, long value)
{
  Parameter p;
  p.keyword = name;
  p.value   = "";
  p.value   += value;
  addParameter(p);
}

//!
//! Add a double parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * name, double value)
{
  Parameter p;
  p.keyword = name;
  p.value   = "";
  p.value   += value;
  addParameter(p);
}

//!
//! Add a string parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * keyword, const char * value)
{
  Parameter p;
  p.keyword = keyword;
  p.value   = value;
  addParameter(p);
}

//!
//! Add a string parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * keyword, const    TString      & value)
{
  Parameter p;
  p.keyword = keyword;
  p.value   = value;
  addParameter(p);
}

//!
//! Add a bool parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * path, const char * keyword, bool value)
{
  addParameter(standardize(path,keyword),value);
}

//!
//! Add an int parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * path, const char * keyword, int value)
{
  addParameter(standardize(path,keyword),value);
}

//!
//! Add an int parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * path, const char * keyword, long value)
{
  addParameter(standardize(path,keyword),value);
}

//!
//! Add a double parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * path, const char * keyword, double value)
{
  addParameter(standardize(path,keyword),value);
}

//!
//! Add a const char *  parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * path, const char * keyword, const char * value)
{
  addParameter(standardize(path,keyword),value);
}

//!
//! Add a string parameter to the configuration with the given name and value
//!
void Configuration::addParameter(const char * path, const char * keyword, const    TString      & value)
{
  addParameter(standardize(path,keyword),value);
}



bool Configuration::hasEndColon(const char * path) const
{
  TString      s = path;
  int last = s.Last(':');
  int size = s.Length() - 1;
  return (last>0 && last == size);
}

int Configuration::printConfiguration(ostream & output)
{
  vector<Parameter>::iterator iter;
  for (iter = parameters.begin(); iter != parameters.end(); iter++)
  {
    output <<  left << setw(50) << setfill('.')<< iter->keyword << ": " << iter->value<< endl;
  }
  output << setfill(' ')<< endl;
  //    output << "\tKeyword: " << iter->keyword << "\tValue: " << iter->value<< endl;
  return 0;
}

bool Configuration::isBool(const char * keyword) const
{
  bool found = isFound(keyword);
  if (found)
  {
    TString      v = getParameter(keyword);
    v.ToUpper();
    if (v.EqualTo("0")    || v.EqualTo("1") )     return true;
    if (v.EqualTo("TRUE") || v.EqualTo("FALSE") ) return true;
    if (v.EqualTo("YES")  || v.EqualTo("NO") )    return true;
    return false;
  }
  else
    return false;
}


bool Configuration::isInt(const char * keyword) const
{
  TString      v = getParameter(keyword);
  if (!v.IsDec())
  {
    return false;
  }
  return true;
}


bool Configuration::isLong(const char * keyword) const
{
  TString      v = getParameter(keyword);
  if (!v.IsDec())
  {
    return false;
  }
  return true;
}

bool Configuration::isDouble(const char * keyword) const
{
  TString      v = getParameter(keyword);
  if (v.IsFloat()) return true;
  return false;
}

bool Configuration::isString  (const char * keyword) const
{
  TString      v = getParameter(keyword);
  return true;
}

bool Configuration::isFound(const char * keyword) const
{
  vector<Parameter>::const_iterator iter;
  for (iter = parameters.begin(); iter != parameters.end(); iter++)
    if (iter->keyword == keyword)
    {
      //cout << "<Configuration::getParameter>\tReturning value " << Iter->value << " for keyword " << Iter->keyword << endl;
      return true;
    }
  return false;
}



void Configuration::generateKeyValuePairs(const char *  keyBaseName, const char *  defaultValue, int nKeysToGenerate)
{
  TString      key;
  for (int k=0; k<nKeysToGenerate; k++)
  {
    key = keyBaseName; key += k;
    addParameter(key,defaultValue);
  }
}

void Configuration::generateKeyValuePairs(const char *  path, const char *  keyBaseName, const char *  defaultValue, int nKeysToGenerate)
{
  TString      sPath = path;
  TString      sKeyBaseName = keyBaseName;
  if (sPath.EndsWith(":"))
    generateKeyValuePairs(sPath+sKeyBaseName, defaultValue, nKeysToGenerate);
  else
    generateKeyValuePairs(sPath+  TString  (":")+sKeyBaseName, defaultValue, nKeysToGenerate);
}

vector<  TString  > Configuration::getSelectedValues(const char *  keyBaseName, const char *  defaultValue) const
{
  TString      sKeyBaseName = keyBaseName;
  vector<  TString  > selectedValues;
  vector<Parameter>::const_iterator iter;
  for (iter = parameters.begin(); iter != parameters.end(); iter++)
  {
    if (iter->keyword.Contains(keyBaseName) && !iter->value.Contains(defaultValue) ) selectedValues.push_back(iter->value);
  }
  return selectedValues;
}

vector<  TString  > Configuration::getSelectedValues(const char *  path, const char *  keyBaseName, const char *  defaultValue) const
{
  TString      sPath = path;
  TString      sKeyBaseName = keyBaseName;
  if (sPath.EndsWith(":"))
    return getSelectedValues(sPath+sKeyBaseName, defaultValue);
  else
    return getSelectedValues(sPath+  TString  (":")+sKeyBaseName, defaultValue);
}


int Configuration::getNPossibleValues(const char *  keyBaseName)  const
{
  int nPossible = 0;
  TString      sKeyBaseName = keyBaseName;
  vector<Parameter>::const_iterator iter;
  for (iter = parameters.begin(); iter != parameters.end(); iter++)
  {
    if (iter->keyword.Contains(sKeyBaseName) ) nPossible++;
  }
  return nPossible;
}

int Configuration::getNPossibleValues(const char *  path, const char *  keyBaseName) const
{
  TString      sPath = path;
  TString      sKeyBaseName = keyBaseName;
  if (sPath.EndsWith(":"))
    return getNPossibleValues(sPath+sKeyBaseName);
  else
    return getNPossibleValues(sPath+  TString  (":")+sKeyBaseName);
}


int Configuration::getNSelectedValues(const char *  keyBaseName, const char *  defaultValue)  const
{
  int nSelected = 0;
  TString      sKeyBaseName = keyBaseName;
  vector<Parameter>::const_iterator iter;
  for (iter = parameters.begin(); iter != parameters.end(); iter++)
  {
    if (iter->keyword.Contains(sKeyBaseName) && !iter->value.Contains(defaultValue) ) nSelected++;
  }
  return nSelected;
}


void Configuration::addSelectedValues(const char *  keyBaseName, const char *  defaultValue, const vector<  TString  > & selectedValues)
{
  TString      key;
  int nSelected = getNSelectedValues(keyBaseName,defaultValue);
  for (unsigned int k=0; k<selectedValues.size(); k++)
  {
    TString      key = keyBaseName;
    int index = nSelected + k;
    key += index;
    addParameter(key,selectedValues[k]);
  }
}

void Configuration::clear()
{
  parameters.clear();
}

//void Configuration::readFromFile(const char * _inputPath,
//                                      const char * _inputFileName,
//                                      const char * _extension,
//                                      MessageLogger::Severity severity)
//{
//  TextParser parser(severity);
//  parser.read(*this,_inputPath,_inputFileName,_extension);
//}
//
//void Configuration::writeToFile(const char * outputFileName __attribute__((unused)))
//{
//// to be implemented....
//}

void Configuration::sanityCheck(const char * keyword)
{
  int count = 0;
  vector<Parameter>::const_iterator iter;
  for (iter = parameters.begin(); iter != parameters.end(); iter++)
  {
    if (iter->keyword.Contains(keyword))
    {
      cout << "sanityCheck("<< keyword<< ") found " << iter->keyword << " with value:" << iter->value << endl;
      count++;
    }
  }
  cout << "sanityCheck("<< keyword<< ") COUNT=" << count << endl;
}




//!
//! Convenience class designed to facilitate the setting of root windows
//!
class CanvasConfiguration: public Configuration
{
public:

  enum CanvasFormat   { PortraitTight, Portrait, PortraitWide, SquareTight, Square, SquareWide, LandscapeTight, Landscape, LandscapeWide, LandscapeXtop };
  enum CanvasAxes     { Linear, LogX, LogY, LogZ, LogXY, LogXZ, LogYZ, LogXYZ  };

  //!
  //! Default CTOR
  //!
  CanvasConfiguration();

  //!
  //!CTOR
  //!Set the aspect ratio and the axes
  //!
  CanvasConfiguration(CanvasFormat format, CanvasAxes axes);

  //!
  //!Copy CTOR
  //!
  CanvasConfiguration(const Configuration & config);

  //!
  //!Copy operator
  //!
  CanvasConfiguration &  operator=(const Configuration & config);

  //!
  //!DOTR
  //!
  virtual ~CanvasConfiguration();

  //!
  //!Set canvas parameters to their default value
  //!
  virtual void setDefaultConfiguration();

  //!
  //!Set the format
  //!
  virtual void setFormat(CanvasFormat format=Square);

  //!
  //!Set the axis style
  //!
  virtual void setAxes(CanvasAxes format=Linear);

  //!
  //!Set margine sizes
  //!
  virtual void setMargins(float leftMargin, float topMargin, float rightMargin, float bottomMargin);

  //!
  //!Set the window size
  //!
  virtual void setSize(int width, int height);

  //!
  //!Set the nominal window position
  //!
  virtual void setPosition(int x, int y);

  ClassDef(CanvasConfiguration,0)

};


CanvasConfiguration::CanvasConfiguration()
:
Configuration()
{
  setDefaultConfiguration();
}



CanvasConfiguration::CanvasConfiguration(CanvasFormat format, CanvasAxes axes)
:
Configuration()
{
  setDefaultConfiguration();
  // chose the aspect ratio and the margin style (tight, regular, wide)
  setFormat(format);
  // chose the axes settings
  setAxes(axes);
}


//!
//! Copy CTOR
//!
CanvasConfiguration::CanvasConfiguration(const Configuration & config)
:
Configuration(config)
{}

////////////////////////////////////////////////////
// Assignment operator
////////////////////////////////////////////////////
CanvasConfiguration & CanvasConfiguration::operator=(const Configuration & config)
{
  if (this!=&config) Configuration::operator=(config);
  return *this;
}

CanvasConfiguration::~CanvasConfiguration()
{
}

void CanvasConfiguration::setDefaultConfiguration()
{
  addParameter("windowXPosition",     20);
  addParameter("windowYPosition",     20);
  addParameter("windowWidth",        700);
  addParameter("windowHeight",       700);
  addParameter("windowLeftMargin",  0.15);
  addParameter("windowTopMargin",   0.03);
  addParameter("windowRightMargin", 0.03);
  addParameter("windowBottomMargin",0.15);
  addParameter("windowLogX", false);
  addParameter("windowLogY", false);
  addParameter("windowLogZ", false);
  addParameter("windowTheta", 35.0);
  addParameter("windowPhi",   25.0);

  addParameter("windowFillColor", kWhite);
  addParameter("windowFillStyle", 1001);
  addParameter("windowBorderSize",0);
  addParameter("windowBorderMode",0);
}


void CanvasConfiguration::setFormat(CanvasFormat format)
{
  switch (format)
  {
    case PortraitTight:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        500);
      addParameter("windowHeight",       800);
      addParameter("windowLeftMargin",  0.10);
      addParameter("windowTopMargin",   0.03);
      addParameter("windowRightMargin", 0.03);
      addParameter("windowBottomMargin",0.10);
      break;

    case Portrait:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        500);
      addParameter("windowHeight",       800);
      addParameter("windowLeftMargin",  0.15);
      addParameter("windowTopMargin",   0.05);
      addParameter("windowRightMargin", 0.05);
      addParameter("windowBottomMargin",0.15);
      break;

    case PortraitWide:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        500);
      addParameter("windowHeight",       800);
      addParameter("windowLeftMargin",  0.20);
      addParameter("windowTopMargin",   0.10);
      addParameter("windowRightMargin", 0.10);
      addParameter("windowBottomMargin",0.20);
      break;

    case SquareTight:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        700);
      addParameter("windowHeight",       700);
      addParameter("windowLeftMargin",  0.10);
      addParameter("windowTopMargin",   0.03);
      addParameter("windowRightMargin", 0.03);
      addParameter("windowBottomMargin",0.10);
      break;

    case Square:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        700);
      addParameter("windowHeight",       700);
      addParameter("windowLeftMargin",  0.15);
      addParameter("windowTopMargin",   0.05);
      addParameter("windowRightMargin", 0.05);
      addParameter("windowBottomMargin",0.15);
      break;

    case SquareWide:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        700);
      addParameter("windowHeight",       700);
      addParameter("windowLeftMargin",  0.20);
      addParameter("windowTopMargin",   0.05);
      addParameter("windowRightMargin", 0.10);
      addParameter("windowBottomMargin",0.20);
      break;

    case LandscapeTight:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        800);
      addParameter("windowHeight",       500);
      addParameter("windowLeftMargin",  0.10);
      addParameter("windowTopMargin",   0.03);
      addParameter("windowRightMargin", 0.03);
      addParameter("windowBottomMargin",0.10);
      break;

    case Landscape:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        800);
      addParameter("windowHeight",       500);
      addParameter("windowLeftMargin",  0.15);
      addParameter("windowTopMargin",   0.05);
      addParameter("windowRightMargin", 0.10);
      addParameter("windowBottomMargin",0.15);
      break;

    case LandscapeWide:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        800);
      addParameter("windowHeight",       500);
      addParameter("windowLeftMargin",  0.20);
      addParameter("windowTopMargin",   0.05);
      addParameter("windowRightMargin", 0.15);
      addParameter("windowBottomMargin",0.15);
      break;

    case LandscapeXtop:
      addParameter("windowXPosition",     20);
      addParameter("windowYPosition",     20);
      addParameter("windowWidth",        800);
      addParameter("windowHeight",       600);
      addParameter("windowLeftMargin",  0.20);
      addParameter("windowTopMargin",   0.20);
      addParameter("windowRightMargin", 0.05);
      addParameter("windowBottomMargin",0.15);
      break;

  };
}


void CanvasConfiguration::setAxes(CanvasAxes axes)
{
  switch (axes)
  {
    case Linear:
      addParameter("windowLogX", false);
      addParameter("windowLogY", false);
      addParameter("windowLogZ", false);
      break;

    case LogX:
      addParameter("windowLogX", true);
      addParameter("windowLogY", false);
      addParameter("windowLogZ", false);
      break;

    case LogY:
      addParameter("windowLogX", false);
      addParameter("windowLogY", true);
      addParameter("windowLogZ", false);
      break;

    case LogZ:
      addParameter("windowLogX", false);
      addParameter("windowLogY", false);
      addParameter("windowLogZ", true);
      break;

    case LogXY:
      addParameter("windowLogX", true);
      addParameter("windowLogY", true);
      addParameter("windowLogZ", false);
      break;

    case LogXZ:
      addParameter("windowLogX", true);
      addParameter("windowLogY", false);
      addParameter("windowLogZ", true);
      break;

    case LogYZ:
      addParameter("windowLogX", false);
      addParameter("windowLogY", true);
      addParameter("windowLogZ", true);
      break;

    case LogXYZ:
      addParameter("windowLogX", true);
      addParameter("windowLogY", true);
      addParameter("windowLogZ", true);
      break;
  };
}

void CanvasConfiguration::setMargins(float left, float top, float right, float bottom)
{
  addParameter("windowLeftMargin",  left);
  addParameter("windowTopMargin",   top);
  addParameter("windowRightMargin", right);
  addParameter("windowBottomMargin",bottom);
}

void CanvasConfiguration::setSize(int width, int heigh)
{
  addParameter("windowWidth",        width);
  addParameter("windowHeight",       heigh);
}

void CanvasConfiguration::setPosition(int x, int y)
{
  addParameter("windowXPosition",x);
  addParameter("windowYPosition",y);
}


TCanvas * createCanvas(const TString & canvasName,
                       const CanvasConfiguration & configuration, int inc=200)
{
  int xInc = inc;
  TCanvas * canvas = new TCanvas(canvasName,
                                 canvasName,
                                 xInc+configuration.getValueInt("windowXPosition"),
                                 configuration.getValueInt("windowYPosition"),
                                 configuration.getValueInt("windowWidth"),
                                 configuration.getValueInt("windowHeight") );
  canvas->SetLogx(        configuration.getValueBool("windowLogX") );
  canvas->SetLogy(        configuration.getValueBool("windowLogY") );
  canvas->SetLogz(        configuration.getValueBool("windowLogZ") );
  canvas->SetRightMargin( configuration.getValueDouble("windowRightMargin") );
  canvas->SetLeftMargin(  configuration.getValueDouble("windowLeftMargin") );
  canvas->SetBottomMargin(configuration.getValueDouble("windowBottomMargin") );
  canvas->SetTopMargin(   configuration.getValueDouble("windowTopMargin") );
  //  canvas->SetTheta(       configuration.getValueDouble("windowTheta") );
  //  canvas->SetPhi(         configuration.getValueDouble("windowPhi") );
  //
  //  canvas->SetFillColor(  configuration.getValueInt("windowFillColor") );
  //  canvas->SetFillStyle(  configuration.getValueInt("windowFillStyle") );
  //  canvas->SetBorderSize( configuration.getValueInt("windowBorderSize") );
  //  canvas->SetBorderMode( configuration.getValueInt("windowBorderMode") );
  return canvas;
}




//!
//! Class encapsulates the plotting properties or attributes of a graph or histograms.
//! This class is designed to work with other CAP graphics classes to set the plotting
//! attributes of graphs (TGraph), histograms (TH1*), and data graphs (DataGraph) displaying
//! data values, statistical error bars, and systematic error bars.
//!
//! Lines are used to draw connections between points as well as  (statistical) error bars.
//! Markers are used to represent the data point position/value
//! Systs are used to represent the systematic error bars or bounds.
//!
class GraphConfiguration : public Configuration
{
public:

  //!
  //!Default CTOR
  //!
  GraphConfiguration();

  GraphConfiguration(int d, int type=1);

  //!
  //!Copy CTOR
  //!
  GraphConfiguration(GraphConfiguration & source);

  //!
  //!DTOR
  //!
  virtual ~GraphConfiguration(){}

  //!
  //!Assignment operator (COPY)
  //!
  GraphConfiguration & operator=(GraphConfiguration & source);

  //!
  //! Set the default graph configuration
  //!
  virtual void setDefaultConfiguration();

  //!
  //! Set the graph parameter for dim =1 or  =2 and according to the type.
  //!
  void addParametersWith(int dim, int type);

  //!
  //! Create a graph configuration palette.
  //!
  static vector<GraphConfiguration*> createConfigurationPalette(unsigned int n, int dimension);

  ClassDef(GraphConfiguration,0)
};

GraphConfiguration::GraphConfiguration()
{
  setDefaultConfiguration();
}

GraphConfiguration::GraphConfiguration(int dim, int type)
:
Configuration()
{
  setDefaultConfiguration();
  addParametersWith(dim,type);
}

void GraphConfiguration::setDefaultConfiguration()
{
  addParameter("npx", 100);
  addParameter("npy", 100);
  addParameter("lineColor", 1);
  addParameter("lineStyle", 1);
  addParameter("lineWidth", 1);
  addParameter("markerColor",   1);
  addParameter("markerStyle",  20);
  addParameter("markerSize",  1.1);
  addParameter("systsColor", 1);
  addParameter("systsStyle", 3003);
  addParameter("systsWidth", 1);
  addParameter("nXDivisions", 5);
  addParameter("xTitleSize", 0.06);
  addParameter("xTitleOffset", 1.1);
  addParameter("xLabelSize",  0.05);
  addParameter("xLabelOffset", 0.01);
  addParameter("xTitle",         TString    ("x"));
  addParameter("nYDivisions",     5);
  addParameter("yTitleSize",   0.06);
  addParameter("yTitleOffset",  1.2);
  addParameter("yLabelSize",   0.05);
  addParameter("yLabelOffset", 0.01);
  addParameter("yTitle",          TString    ("y"));
  addParameter("nZDivisions",     5);
  addParameter("zTitleSize",   0.06);
  addParameter("zTitleOffset",  1.5);
  addParameter("zLabelSize",   0.05);
  addParameter("zLabelOffset", 0.01);
  addParameter("zLabelOffset", 0.01);
  addParameter("zTitle",          TString    ("z"));
  addParameter("PlotOption",      TString    ("E0"));

  addParameter("systsColor",1);
  addParameter("systsStyle",1001);
  addParameter("systsWidth",1);
}

void GraphConfiguration::addParametersWith(int dim, int type)
{
  if (dim==1 || dim==0)
  {

    switch (type)
    {
      default:

      case  0:
        addParameter("lineColor",   kBlack);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kBlack);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kBlack);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  1:
        addParameter("lineColor",   kRed);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kRed);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kRed);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  2:
        addParameter("lineColor",   kGreen);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kGreen);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kGreen);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  3:
        addParameter("lineColor",   kMagenta);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kMagenta);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kMagenta);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  4:
        addParameter("lineColor",   kBlue);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kBlue);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kBlue);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  5:
        addParameter("lineColor",   kYellow);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kYellow);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kYellow);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  6:
        addParameter("lineColor",   kPink);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kPink);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kPink);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  7:
        addParameter("lineColor",   kBlue+2);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kBlue+2);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kBlue+2);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  8:
        addParameter("lineColor",   kRed+2);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kRed+2);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kRed+2);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  9:
        addParameter("lineColor",   kGreen+2);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kGreen+2);
        addParameter("markerStyle", kFullSquare);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kGreen+2);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;


      case  10:
        addParameter("lineColor",   kBlack);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kBlack);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kBlack);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  11:
        addParameter("lineColor",   kRed);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kRed);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kRed);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  12:
        addParameter("lineColor",   kGreen);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kGreen);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kGreen);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  13:
        addParameter("lineColor",   kMagenta);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kMagenta);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kMagenta);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  14:
        addParameter("lineColor",   kBlue);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kBlue);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kBlue);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  15:
        addParameter("lineColor",   kYellow);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kYellow);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kYellow);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  16:
        addParameter("lineColor",   kPink);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kPink);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kPink);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  17:
        addParameter("lineColor",   kBlue+2);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kBlue+2);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kBlue+2);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  18:
        addParameter("lineColor",   kRed+2);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kRed+2);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kRed+2);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  19:
        addParameter("lineColor",   kGreen+2);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kGreen+2);
        addParameter("markerStyle", kFullCircle);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kGreen+2);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  20:
        addParameter("lineColor",   kBlack);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kBlack);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kBlack);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  21:
        addParameter("lineColor",   kRed);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kRed);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kRed);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  22:
        addParameter("lineColor",   kGreen);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kGreen);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kGreen);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  23:
        addParameter("lineColor",   kMagenta);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kMagenta);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kMagenta);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  24:
        addParameter("lineColor",   kBlue);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kBlue);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kBlue);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  25:
        addParameter("lineColor",   kYellow);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kYellow);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kYellow);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  26:
        addParameter("lineColor",   kPink);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kPink);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kPink);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  27:
        addParameter("lineColor",   kBlue+2);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kBlue+2);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kBlue+2);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  28:
        addParameter("lineColor",   kRed+2);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kRed+2);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kRed+2);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

      case  29:
        addParameter("lineColor",   kGreen+2);
        addParameter("lineStyle",   kSolid);
        addParameter("lineWidth",   2);
        addParameter("markerColor", kGreen+2);
        addParameter("markerStyle", kFullDiamond);
        addParameter("markerSize",  1.1);
        addParameter("systsColor",  kGreen+2);
        addParameter("systsStyle",  3003);
        addParameter("systsWidth",  1);
        break;

    }
  }
  else if (dim==2)
  {
    addParameter("nXDivisions", 5);
    addParameter("xTitleSize", 0.05);
    addParameter("xTitleOffset", 1.3);
    addParameter("xLabelSize",  0.05);
    addParameter("xLabelOffset", 0.002);
    addParameter("xTitle",          TString    ("x"));
    addParameter("nYDivisions",     5);
    addParameter("yTitleSize",   0.05);
    addParameter("yTitleOffset",  1.5);
    addParameter("yLabelSize",   0.05);
    addParameter("yLabelOffset", 0.05);
    addParameter("yTitle",          TString    ("y"));
    addParameter("nZDivisions",     5);
    addParameter("zTitleSize",   0.05);
    addParameter("zTitleOffset",  1.5);
    addParameter("zLabelSize",   0.05);
    addParameter("zLabelOffset",0.005);
    addParameter("zTitle",          TString    ("z"));
    addParameter("PlotOption",  TString    ("SURF3"));
  }
}

GraphConfiguration::GraphConfiguration(GraphConfiguration & source)
:
Configuration(source)
{

}


GraphConfiguration & GraphConfiguration::operator=(GraphConfiguration & source)
{
  if (this!=&source)
  {
    Configuration::operator=(source);
  }
  return *this;
}



vector<GraphConfiguration*> GraphConfiguration::createConfigurationPalette(unsigned int n, int dimension)
{
  vector<GraphConfiguration*> configs;

  for (unsigned int k=0; k<n; k++)
  {
    GraphConfiguration * c = new GraphConfiguration(dimension, k);
    configs.push_back( c );
  }
  return configs;
}



////////////////////////////////////////////////////////////////////////
// Setting Histogram Properties
////////////////////////////////////////////////////////////////////////
void setProperties(TH1 * h, const GraphConfiguration & graphConfiguration)
{

    cout << "Setting properties of histo: " << h->GetName() << endl;
    h->SetLineColor(graphConfiguration.getValueInt("lineColor"));
    h->SetLineStyle(graphConfiguration.getValueInt("lineStyle"));
    h->SetLineWidth(graphConfiguration.getValueInt("lineWidth"));
    h->SetMarkerColor(graphConfiguration.getValueInt("markerColor"));
    h->SetMarkerStyle(graphConfiguration.getValueInt("markerStyle"));
    h->SetMarkerSize (graphConfiguration.getValueDouble("markerSize"));
    TAxis * xAxis = (TAxis *) h->GetXaxis();
    xAxis->SetNdivisions(graphConfiguration.getValueInt("nXDivisions"));
    xAxis->SetTitleSize(graphConfiguration.getValueDouble("xTitleSize"));
    xAxis->SetTitleOffset(graphConfiguration.getValueDouble("xTitleOffset"));
    xAxis->SetLabelSize(graphConfiguration.getValueDouble("xLabelSize"));
    xAxis->SetLabelOffset(graphConfiguration.getValueDouble("xLabelOffset"));
    TAxis * yAxis = (TAxis *) h->GetYaxis();
    yAxis->SetNdivisions(graphConfiguration.getValueInt("nYDivisions"));
    yAxis->SetTitleSize(graphConfiguration.getValueDouble("yTitleSize"));
    yAxis->SetTitleOffset(graphConfiguration.getValueDouble("yTitleOffset"));
    yAxis->SetLabelSize(graphConfiguration.getValueDouble("yLabelSize"));
    yAxis->SetLabelOffset(graphConfiguration.getValueDouble("yLabelOffset"));
    if (h->IsA() == TH2::Class()  || h->IsA() == TH2F::Class() || h->IsA() == TH2F::Class() )
    {
      cout << "Setting properties as 2D histo: " << h->GetTitle() << endl;
      TAxis * zAxis = (TAxis *) h->GetZaxis();
      zAxis->SetNdivisions(graphConfiguration.getValueInt("nZDivisions"));
      zAxis->SetTitleSize(graphConfiguration.getValueDouble("zTitleSize"));
      zAxis->SetTitleOffset(graphConfiguration.getValueDouble("zTitleOffset"));
      zAxis->SetLabelSize(graphConfiguration.getValueDouble("zLabelSize"));
      zAxis->SetLabelOffset(graphConfiguration.getValueDouble("zLabelOffset"));
    }
}

void setProperties(TH1 * h, const GraphConfiguration & graphConfiguration,
                   const    TString      & xTitle, const    TString      & yTitle, const    TString      & zTitle)
{

    cout << "Setting properties of histo: " << h->GetTitle() << endl;

  setProperties(h, graphConfiguration);
  TAxis * xAxis = (TAxis *) h->GetXaxis();
  xAxis->SetTitle(xTitle);
  TAxis * yAxis = (TAxis *) h->GetYaxis();
  yAxis->SetTitle(yTitle);
  if (h->IsA() == TH2::Class()  || h->IsA() == TH2F::Class() || h->IsA() == TH2F::Class() )
  {
    TAxis * zAxis = (TAxis *) h->GetZaxis();
    zAxis->SetTitle(zTitle);
  }
}



int Plot()
{
  //Name of the canvas
  TString     canvasName = "MyCanvas";
  double yMin = -1.0;
  double yMax =  10.0;

  //Configuration of the canvas
  // use this for a linear plot
  //CanvasConfiguration  canvasConfiguration(CanvasConfiguration::Portrait,CanvasConfiguration::Linear);
  // use this for a log plot
  CanvasConfiguration  canvasConfiguration(CanvasConfiguration::Portrait,CanvasConfiguration::LogY);

  //Configuration of the histogram
  GraphConfiguration   graphConfiguration;

  // Create one canvas
  TCanvas * canvas = createCanvas(canvasName,canvasConfiguration);
  canvas->SetTicky(1);
  canvas->SetTickx(1);

  // Create one histogram and fill it with random numbers.
  TH1 * h = new TH1D("example"," ",100,-1.0, 99.0);
  for (int k=0; k<10000; k++)
  {
    h->Fill( gRandom->Gaus(50.0, 10.0));
  }

  // Plot the histogram

  graphConfiguration.addParameter("lineColor", kBlue);


  setProperties(h,graphConfiguration);
  h->GetXaxis()->SetTitle("x");
  h->GetYaxis()->SetTitle("y");
//  h->SetMinimum(yMin);
//  h->SetMaximum(yMax);
  h->Draw();
  canvas->Print(canvasName+".pdf");

  return 0;
}
