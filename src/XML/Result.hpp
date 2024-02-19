/* **********************************************************************
 * Copyright (C) 2019-2022, Claude Pruneau
 * All rights reserved.
 *
 * Based on the ROOT package and environment
 *
 * For the licensing terms see LICENSE.
 *
 * Author: Claude Pruneau,   02/27/2023
 *
 * *********************************************************************/

#ifndef CAP__Result
#define CAP__Result

#include "Aliases.hpp"
#include "Factory.hpp"
#include "ResultType.hpp"
#include "ResultDb.hpp"

using namespace std;

namespace CAP
{

//!
//!
//!
class ScholarlyWork
{
public:
  enum ScholarlyWorkTypes {Letter, Regular, Review, Proceeding, PublicNote, PrivateNote, Book, Chapter, Unpublished, Unknown};

  String inspireEntryCode;  // e.g., Pruneau:2006gj
  String title;
  String collaboration;
  String editors;
  String authors;
  String bookName;
  String journalName;
  String journalVolume;
  String journalNumber;
  String journalPages;
  String journalMonth;
  String journalYear;
  String journalUrl;


  String doi;
  String archiveSubmitted;
  String archiveModified;
  String archiveName;  // e.g., arXiv
  String archiveClass; // e.g., nucl-th
  String archiveNumber; // 1612.05634


  ScholarlyWorkTypes workType;

  String appendWithA(const String & s1, const String & s2)
  {
  String result;
  result = s1;
  result = " =  \"";
  result += s2;
  result += "\",";
  return result;
  }

  String appendWithAB(const String & s1, const String & s2)
  {
  String result;
  result = s1;
  result = " =  \"{";
  result += s2;
  result += "\"},\n";
  return result;
  }

  String generateArticleBibEntry()
  {
  String bibEntry;
  bibEntry = "@article{";
  if (inspireEntryCode.Length()>0)
    bibEntry += inspireEntryCode;
  else if (doi.Length()>0)
    bibEntry += doi;
  else
    bibEntry += "uncodedEntry";
  bibEntry += ",\n";
  bibEntry += appendWithAB("author",authors);
  bibEntry += appendWithAB("title",title);
  bibEntry += appendWithAB("journal",journalName);
  bibEntry += appendWithAB("volume",journalVolume);
  bibEntry += appendWithAB("number",journalNumber);
  bibEntry += appendWithAB("pages",journalPages);
  bibEntry += appendWithAB("month",journalMonth);
  bibEntry += appendWithAB("year", journalYear);
  bibEntry += appendWithAB("doi",  doi);
  bibEntry += appendWithAB("URL",  journalUrl);
  bibEntry += appendWithAB("eprint",  archiveName+archiveClass+archiveNumber);
  bibEntry += "}";
      }

  return bibEntry;
  }

  String generateBibEntry()
  {
  String bibEntry;
  switch (workType)
    {
      case Letter:   bibEntry = generateArticleBibEntry();
      case Regular:bibEntry = generateArticleBibEntry();
      case Review:bibEntry = generateArticleBibEntry();
      case Proceeding:bibEntry = generateArticleBibEntry();
      case PublicNote:bibEntry = generateArticleBibEntry();
      case PrivateNote:bibEntry = generateArticleBibEntry();
      case Book:bibEntry = generateBookBibEntry();
      case Chapter:bibEntry = generateArticleBibEntry();
      case Unpublished:bibEntry = generateArticleBibEntry();
      case Unknown:bibEntry = generateArticleBibEntry();
    }
  }
};

//!
//!
//!
class Result
{
public:
  
  //!
  //! CTOR
  //!
  Result();

  //!
  //! DTOR
  //!
  virtual ~Result(){}
  
  //!
  //! Copy CTOR
  //!
  Result(const Result& other);

  //!
  //!Assignment operator. The properties of "other" are shallowed copied into the properties of
  //!this particle.
  //!
  Result & operator=(const Result & other);

  //!
  //!Print the properties of this particle on the given output stream. The output properties do not
  //!include decay properties.
  //!
  void printProperties(ostream & output=cout);

  //!
  //! Clear all variables held by this particle
  //!
  void clear();
  
  //!
  //! Reset this particle
  //!
  void reset();

  //!
  //! Set the ResultType of this particle.
  //!
  void setType(ResultType * _type) { type = _type;   }
  
  
  //!
  //! Get the ResultType of this particle.
  //!
  ResultType & getType() const     { return *type;   }

  ResultType * getTypePtr() const     { return type;   }

  

  //! @param live: whether the particle is considered "live" or "dead" (decayed)
  //!
  void set(ResultType * type,
           double p_x, double p_y, double p_z, double p_e,
           double x,   double y,   double z,   double t,
           bool live=true);


  //!
  //!Get the name of this particle (object)
  //!
  String getName()
  {
  if (type)
    return type->getName();
  else
    return "UnknownType";
  }


protected:

  HepDb hepDbRef;
  Paper paper;  //!< 4-momentum of the particle
  vector<TH1*> histograms;
  vector<Graph*> graphs;

  Date created;
  Date modified;
  version

  enum ResultSource {ExpData, Theory};

  String collisionSystemName;
  String collisionSystemTitle;
  enum    CollisionType {Fixedtarget, Collider};
  String  collaborationName;
  String  collaborationTitle;

  String  aBeamName;
  String  bBeamName;
  String  aBeamTitle;
  String  bBeamTitle;
  float   sqrtS;
  String  collisionClassName;
  String  collisionClassTitle;
  vector<String> selectionCriteriaName;
  vector<String> selectionCriteriaTitle;
  vector<String> variableNames;  // x, y, z, t, w, etc
  vector<String> variableTitles;

  


  ClassDef(Result,0)

};

} // namespace CAP

#endif /* CAP__Result */
