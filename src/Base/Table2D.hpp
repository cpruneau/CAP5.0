#ifndef TableParser_h
#define TableParser_h
#include <string>
#include <vector>
#include "Parser.hpp"
using namespace std;

namespace CAP
{

class TableParser : public Parser
{
public:

  TableParser();
  virtual ~TableParser() {}

  virtual int  read(const String  & _inputPath,
                    const String  & _inputFileName,
                    const String  & _extension = ".dat");
  virtual int  write(const String & _outputPath,
                     const String & _outputFileName,
                     const String & _extension = ".dat",
                     const String & _option="RECREATE");

  vector<double> stringToDoubles(string str);
  ClassDef(TableParser,0)
};


};

} // namespace CAP


#endif

