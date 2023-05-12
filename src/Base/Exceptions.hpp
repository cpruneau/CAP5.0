#ifndef CAP_Exceptions
#define CAP_Exceptions
#include <iostream>
#include "Aliases.hpp"
namespace CAP
{

class Exception
{
public:
  Exception(const TString   & _message, const TString  & _source);
  virtual ~Exception() {}
  virtual void print();

protected:
  const TString  source;
  const TString  message;
};

class MemoryException : public Exception
{
public:
  MemoryException(const TString  & _message, const TString  & _source);
  virtual ~MemoryException() {}
  virtual void print();
};

class FactoryException : public Exception
{
public:
  FactoryException(long _currentSize,
                   long _requestedSize,
                   const TString  & _message,
                   const TString  & _source);
  virtual ~FactoryException() {}
  virtual void print();
protected:
  long currentSize;
  long requestedSize;
};

class TaskException : public Exception
{
public:
  TaskException(const TString  & _message, const TString  & _source);
  virtual ~TaskException() {}
  virtual void print();
};

class MathException : public Exception
{
public:
  MathException(const TString  & _message, const TString  & _source);
  virtual ~MathException() {}
  virtual void print();
};

class FileException : public Exception
{
public:
  FileException(const TString  & _fileName, const TString  & _message, const TString  & _source);
  FileException(const TString  & _pathName, const TString  & _fileName, const TString  & _message, const TString  & _source);
  virtual ~FileException() {}
  virtual void print();
protected:
  const TString  pathName;
  const TString  fileName;
};


class HistogramException : public Exception
{
public:
  HistogramException(const TString  & _histogramName, const TString  & _message, const TString  & _source);
  virtual ~HistogramException() {}
  virtual void print();
protected:
  const TString  histogramName;
};




} // namespace CAP

#endif
