/* **********************************************************************
 * Copyright (C) 2019-2023, Claude Pruneau, Victor Gonzalez, Sumit Basu
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
#include <TROOT.h>
#include "PermutationGenerator.C"
using namespace std;


void printStringVector(vector<TString> & sVector, int option=0)
{
  int n = sVector.size();
  for (int i=0;i<n;i++)
    {
    switch (option)
      {
        case 0: // concatenate strings separated by commas
        cout << sVector[i];
        if (i<n-1) cout << ",  ";
        break;

        case 1: // bulletted list
        cout << sVector[i] << endl;
        break;

        case 2: // numbered list
        cout << i << " : " << sVector[i] << endl;
        break;
      }
    }
  cout << endl;
}


void printStringVectors(vector<vector<TString>> & perms)
{
  for (unsigned int i=0;i<perms.size();i++)
    {
    printStringVector(perms[i]);
    }
  cout << endl;
}


TString insertPageBreaks(const TString & input, int nBreak=45)
{
  TString output;
  TString tok;
  Ssiz_t from = 0;
  output += "\\begin{align} ";

  int n = 0;
  while (input.Tokenize(tok, from, "&"))
    {
    n++;
    if (n==nBreak)
      {
      n=0;
      output += " \\end{align}";
      output += " \\begin{align}";
      output += " {\\rm cont'd} & ";
      output += tok;
      }
    else
      {
      output += " & ";
      output += tok;
      }
    }
  output += "\\end{align} ";

  return output;
}

TString create_subindex(const TString & s, int index)
{
  TString output = "";
  output += s;
  output += "_{";
  output += index;
  output += "}";
  return output;
}

TString create_subindex(const TString & s, const TString & index)
{
  TString output = "";
  output += s;
  output += "_{";
  output += index;
  output += "}";
  return output;
}


TString create_superindex(const TString & s, int index)
{
  TString output = "";
  output += s;
  output += "^{";
  output += index;
  output += "}";
  return output;
}

TString create_superindex(const TString & s, const TString & index)
{
  TString output = "";
  output += s;
  output += "^{";
  output += index;
  output += "}";
  return output;
}


TString create_Navg(int n)
{
  TString output = "";
  output += "\\langle ";
  output += "N";
  if (n>1)
    {
    for (int i=1; i<n; i++)
      {
      output += "\\left(N-";
      output += i;
      output += "\\right)";
      }
    }
  output += "\\rangle ";
  return output;
}

TString create_SumNE(int indexMin, int indexMax)
{
  const TString label = "i";
  TString output = "";
  output += "\\sum_{";
  unsigned int nn = indexMax-indexMin+1;
  for (unsigned int k=0;k<nn;k++)
    {
    create_subindex(label, indexMin+k);
    if (k<nn-1) output +=  "\\ne ";
    }
  output +=  "} ";
  return output;
}



// put brackets aroung the given string
// option : brackets
//   0    : \langle \rangle
//   1    : \llangle \rrangle
//   2    : \left(  \right)
//   3    : \left[  \right]
//   4    : \left{  \right}
//
TString bracketize(const TString & s, int option=0)
{
  TString left;
  TString right;
  TString output;
  switch (option)
    {
      case 0: left = "\\langle ";  right = "\\rangle ";   break;
      case 1: left = "\\llangle "; right = "\\rrangle ";  break;
      case 2: left = "\\left( ";   right = "\\right) ";   break;
      case 3: left = "\\left[ ";   right = "\\right] ";   break;
      case 4: left = "\\left\\{ "; right = "\\right\\} "; break;
    }
  output = left+s+right;
  return output;
}


TString multiply(TString s1, TString s2)
{
  TString output;
  int sign1 = 1;
  int sign2 = 1;
  if (s1.BeginsWith("-"))
    {
    sign1 = -1;
    s1.Remove(0,1);
    }
  else if (s1.BeginsWith("+"))
    {
    sign1 = 1;
    s1.Remove(0,1);
    }
  if (s2.BeginsWith("-"))
    {
    sign2 = -1;
    s2.Remove(0,1);
    }
  else if (s2.BeginsWith("+"))
    {
    sign2 = 1;
    s2.Remove(0,1);
    }
  int sign = sign1*sign2;
  //  cout << " sign1: " << sign1 << " s1: " << s1 << endl;
  //  cout << " sign2: " << sign2 << " s2: " << s2 << endl;
  //  cout << " sign : " << sign << endl;
  if (sign>0)
    {
    output = "+";
    output += s1+s2;
    }
  else
    {
    output = "-";
    output += s1;
    output += s2;
    }
  return output;
}

vector<TString> multiply(vector<TString> fac1, vector<TString> fac2)
{
  int n1 = fac1.size();
  int n2 = fac2.size();
  vector<TString> expression;
  TString result;
  for (int k1=0; k1<n1; k1++)
    {
    for (int k2=0; k2<n2; k2++)
      {
      result = multiply(fac1[k1],fac2[k2]);
      expression.push_back(result);
      }
    }
  return expression;
}

class VarToken
{
public:
  TString name;
  TString exponent;
  TString index;

  VarToken()
  :
  name(""),
  index(""),
  exponent("")
  { }

  VarToken(const TString & _name, const TString & _index, const TString & _exponent)
  :
  name(_name),
  index(_index),
  exponent(_exponent)
  { }

  VarToken(const VarToken & token)
  :
  name(token.name),
  index(token.index),
  exponent(token.exponent)
  { }

  VarToken & operator=(const VarToken & rhs)
  {
  if (this!=&rhs)
    {
    name     = rhs.name;
    index    = rhs.index;
    exponent = rhs.exponent;
    }
  return *this;
  }

  virtual ~VarToken()
  {  }

  bool isEmpty()
  {
  return 0==name.Length();
  }

  bool isNamed(const TString & s)
  {
  return name.EqualTo(s);
  }

  bool sameNameAs(const VarToken & token)
  {
  return name.EqualTo(token.name);
  }

  bool sameExpAs(const VarToken & token)
  {
  return exponent.EqualTo(token.exponent);
  }

  bool sameIndexAs(const VarToken & token)
  {
  return index.EqualTo(token.index);
  }

  bool sameAs(const VarToken & token)
  {
  return sameNameAs(token) && sameExpAs(token) && sameIndexAs(token);
  }

  TString createLatex() const
  {
  TString output = name;
  if (index.Length()>0) output = create_subindex(output,index);
  if (exponent.Length()>0)
    return create_superindex(output,exponent);
  else
    return output;
  }

  VarToken multiply(VarToken & token)
  {
  VarToken newToken(name,index,exponent+token.exponent);
  return newToken;
  }

  void addToExponent(const TString & expo)
  {
  if (exponent.Length()>0)
    {
    if (expo.Length()>0)
      {
      exponent += "+";
      exponent += expo;
      }
    }
  else
    {
    if (expo.Length()>0)
      {
      exponent = expo;
      }
    }
  }

  void fixIndices()
  {
  TString s = index;
  TString tok;
  Ssiz_t from = 0;
  vector<TString> tokens;
  while (s.Tokenize(tok, from, "+"))
    {
    tokens.push_back(tok);
    }
  if (tokens.size()<1) return;
  bool swap = false;
  bool done = false;
  while (!done)
    {
    swap = false;
    for (unsigned int k=1;k<tokens.size();k++)
      {
      if (tokens[k].CompareTo(tokens[k-1])<1)
        {
        TString t1 = tokens[k-1];
        TString t2 = tokens[k];
        tokens[k-1] = t2;
        tokens[k] = t1;
        swap = true;
        }
      }
    if (!swap) done = true;
    }
  index = tokens[0];
  for (unsigned int k=1;k<tokens.size();k++)
    {
    index += "+";
    index += tokens[k];
    }
  }

  void setIndices()
  {
  TString s = index;
  TString tok;
  Ssiz_t from = 0;
  vector<TString> tokens;
  while (s.Tokenize(tok, from, "+"))
    {
    tokens.push_back(tok);
    }
  index = "";
  index += tokens.size();
  }

  // substitute occurences of s1 by s2
  void substitute(TString s1, TString s2)
  {
  if (name.EqualTo(s1)) name = s2;
  }


};

class Term
{
public:
  float coefficient;
  vector<VarToken> varTokens;

  Term()
  :
  coefficient(1.0),
  varTokens()
  {   }

  Term(float _coefficient, const TString & _name, const TString & _index, const TString & _exp)
  :
  coefficient(_coefficient),
  varTokens()
  {
  varTokens.push_back(VarToken(_name,_index,_exp));
  }

  Term(float _coefficient, vector<VarToken> & _varTokens)
  :
  coefficient(_coefficient),
  varTokens(_varTokens)
  {   }

  Term & operator=(const Term & rhs)
  {
  if (this!=&rhs)
    {
    coefficient = rhs.coefficient;
    varTokens   = rhs.varTokens;
    }
  return *this;
  }

  virtual ~Term()
  { }

  void setCoefficient(float _coefficient)
  {
  coefficient = _coefficient;
  }

  void addVarToken(VarToken token)
  {
  varTokens.push_back(token);
  }

  bool sameAs(const Term & aTerm)
  {
  if (varTokens.size()!=aTerm.varTokens.size()) return false;
  bool same = true;
  for (unsigned int k=0;k<varTokens.size();k++)
    {
    if (!varTokens[k].sameAs(aTerm.varTokens[k]))
      {
      same = false;
      break;
      }
    }
  return same;
  }

  // merge tokens with identical names
  // change indices to be in a 1, 2, 3 sequence
  void simplify()
  {
  vector<VarToken> tokens = varTokens;
  //cout << " simplify() before: " << createLatex() << endl;
  //cout << " simplify()   size: " << tokens.size() << endl;
  varTokens.clear();
  vector<bool> keep(tokens.size(),true);

  // merge identical tokens
  //cout << " examining term: " << createLatex(1) << endl;
  for (unsigned int k1=0;k1<tokens.size();k1++)
    {
    //cout << " simplify() k1:" << k1 << " keep: " << keep[k1] << endl;
    if (keep[k1])
      {
      VarToken & t1 = tokens[k1];
      for (unsigned int k2=k1+1;k2<tokens.size();k2++)
        {
        VarToken & t2 = tokens[k2];
        //cout << "token1:" << t1.createLatex() << endl;
        //cout << "token2:" << t2.createLatex() << endl;
        if (t1.sameNameAs(t2) && t1.sameIndexAs(t2))
          {
          keep[k2]=false;
          int lt1 = t1.exponent.Length();
          int lt2 = t2.exponent.Length();
          if (lt1>0 && lt2>0)
            {
            t1.exponent += "+";
            t1.exponent += t2.exponent;
            }
          else if (lt1>0 && lt2==0)
            t1.exponent += "+1";
          else if (lt1==0 && lt2>0)
            {
            t1.exponent = t2.exponent;
            t1.exponent += "+1";
            }
          else
            {
            t1.exponent += "2";
            }
          //cout << "Merging exponents" << t1.exponent << endl;
          }
        }
      varTokens.push_back(t1);
      }
    }
  }

  Term multiply(const Term & rhs)
  {
  Term newTerm;

  cout << "lhs:" << createLatex() << endl;
  cout << "rhs:" << rhs.createLatex() << endl;

  newTerm.coefficient = coefficient * rhs.coefficient;
  vector<VarToken> lhsTokens = varTokens;
  vector<VarToken> rhsTokens = rhs.varTokens;
  vector<bool> copyRhs(rhsTokens.size(),true);
  for (unsigned int k1=0;k1<lhsTokens.size();k1++)
    {
    VarToken lhsToken = lhsTokens[k1];
//    for (unsigned int k2=0;k2<rhsTokens.size();k2++)
//      {
//      VarToken & rhsToken = rhsTokens[k2];
//      if (lhsToken.sameNameAs(rhsToken))
//        {
//        lhsToken.addToExponent(rhsToken.exponent);
//        copyRhs[k2] = false;
//        }
//      }
    newTerm.addVarToken(lhsToken);
    }
  for (unsigned int k2=0;k2<rhsTokens.size();k2++)
    {
    //if (copyRhs[k2]) newTerm.addVarToken(rhsTokens[k2]);
    newTerm.addVarToken(rhsTokens[k2]);

    }
  cout << "new:" << newTerm.createLatex() << endl;

  //cout << "Term::multiply(const Term & rhs) newTerm:" << newTerm.createLatex() << endl;
  return newTerm;
  }

  // substitute occurences of s1 by s2
  void substitute(TString s1, TString s2)
  {
  for (unsigned int k=0;k<varTokens.size();k++)
    varTokens[k].substitute(s1,s2);
  }

  // bring VarToken with s at the beginning
  void collect(TString s)
  {
  simplify();
  bool swap = false;
  bool done = false;
  while (!done)
    {
    for (unsigned int k=1;k<varTokens.size();k++)
      {
      if (varTokens[k].isNamed(s))
        {
        VarToken t1 = varTokens[k-1];
        VarToken t2 = varTokens[k];
        varTokens[k-1] = t2;
        varTokens[k] = t1;
        if (k-1==0) done = true;
        swap = true;
        }
      }
    if (!swap) done = true;
    }

  }

  void replaceSingles(const TString s1, const TString s2)
  {
  int nCount = 0;
  for (unsigned int k=0;k<varTokens.size();k++)
    {
    if (varTokens[k].name.Contains("_"))  nCount++;
    }
  if (nCount==1)
    {
    for (unsigned int k=0;k<varTokens.size();k++)
      {
      if (varTokens[k].name.Contains(s1))  varTokens[k].name = s2;
      }
    }
  }

  void fixIndices()
  {
  for (unsigned int k=0;k<varTokens.size();k++)
    {
    varTokens[k].fixIndices();
    }
  }

  void setIndices()
  {
  for (unsigned int k=0;k<varTokens.size();k++)
    {
    varTokens[k].setIndices();
    }
  }


  TString createLatex(bool withAvg=false) const
  {
  TString coeff;
  TString output;
  if (coefficient==0) return output;
  if (coefficient>0)
    {
    coeff += "+";
    if (coefficient!=1)
      {
      coeff += coefficient;
      coeff += " ";
      }
    }
  if (coefficient<0)
    {
    coeff += "-";
    if (fabs(coefficient)!=1)
      {
      coeff += fabs(coefficient);
      coeff += " ";
      }
    }

  unsigned int n = varTokens.size();
  for (unsigned int k=0;k<n;k++)
    {
    output += varTokens[k].createLatex();
    }
  if (withAvg) output =  bracketize(output,1);
  return coeff + output;
  }
};


class Sum
{
public:
  vector<Term> terms;
  Sum()
  { }

  Sum(const vector<Term> & _terms)
  {
  terms = _terms;
  }

  Sum(const Sum & lhs)
  {
  terms = lhs.terms;
  }

  Sum & operator=(const Sum & rhs)
  {
  if (this!=&rhs)
    {
    terms = rhs.terms;
    }
  return *this;
  }

  void addTerm(Term term)
  {
  terms.push_back(term);
  }

  void addSum(float coeff,  Sum sum)
  {
  vector<Term> & newTerms = sum.terms;
  for (unsigned int k=0; k<newTerms.size(); k++)
    {
    newTerms[k].coefficient *= coeff;
    addTerm(newTerms[k]);
    }
  }

  Sum multiply(const Sum & rhs)
  {
  Sum newTerms;
  for (unsigned int k1=0;k1<terms.size();k1++)
    {
    Term lhsTerm = terms[k1];
    for (unsigned int k2=0;k2<rhs.terms.size();k2++)
      {
      Term rhsTerm = rhs.terms[k2];
      Term newTerm = lhsTerm.multiply(rhsTerm);
      newTerms.addTerm(newTerm);
      }
    }
  return newTerms;
  }

  // substitute occurences of s1 by s2
  void substitute(TString s1, TString s2)
  {
  for (unsigned int k=0;k<terms.size();k++)
    terms[k].substitute(s1,s2);
  }

  // bring VarToken with s at the beginning
  void collect(TString s)
  {
  for (unsigned int k=0;k<terms.size();k++)
    terms[k].collect(s);
  }

  void replaceSingles(const TString s1, const TString s2)
  {
  for (unsigned int k=0;k<terms.size();k++)
    terms[k].replaceSingles(s1,s2);
  }

  void regroup(int option)
  {
  vector<Term> allTerms = terms;
  terms.clear();
  vector<bool> keep(allTerms.size(),true);



  switch (option)
    {
      case 1:
      for (unsigned int k1=0;k1<allTerms.size();k1++)
        {
        allTerms[k1].fixIndices();
        }
      break;

      case 2:
      for (unsigned int k1=0;k1<allTerms.size();k1++)
        {
        allTerms[k1].setIndices();
        allTerms[k1].simplify();
        }
    }


  for (unsigned int k1=0;k1<allTerms.size();k1++)
    {
    if (keep[k1])
      {
      Term & t1 = allTerms[k1];
      for (unsigned int k2=k1+1;k2<allTerms.size();k2++)
        {
        Term & t2 = allTerms[k2];
        if (t1.sameAs(t2))
          {
          keep[k2]=false;
          t1.coefficient += t2.coefficient;
          }
        }
      terms.push_back(t1);
      }
    }
  }

  TString createLatex(bool withAvg=false) const
  {
  TString output;
  output = "(";
  for (unsigned int k=0;k<terms.size();k++)
    {
    output += terms[k].createLatex(withAvg);
    }
  output += ")";
  return output;
  }

};


class Product
{
public:
  vector<Sum> factors;
  Product()
  { }

  Product(const vector<Sum> & _factors)
  {
  factors = _factors;
  }

  Product & operator=(const Product & rhs)
  {
  if (this!=&rhs)
    {
    factors = rhs.factors;
    }
  return *this;
  }

  int size()
  {
  return factors.size();
  }

  void addFactor(Sum sum)
  {
  factors.push_back(sum);
  }

  void popBack()
  {
  factors.pop_back();
  }

  // substitute occurences of s1 by s2
  void substitute(TString s1, TString s2)
  {
  for (unsigned int k=0;k<factors.size();k++)
    factors[k].substitute(s1,s2);
  }

  // bring VarToken with s at the beginning
  void collect(TString s)
  {
  for (unsigned int k=0;k<factors.size();k++)
    factors[k].collect(s);
  }

  void replaceSingles(const TString s1, const TString s2)
  {
  for (unsigned int k=0;k<factors.size();k++)
    factors[k].replaceSingles(s1,s2);
  }

  void regroup(int option)
  {
  for (unsigned int k=0;k<factors.size();k++)
    factors[k].regroup(option);
  }


  TString createLatex(bool withAvg=false) const
  {
  TString output;
  output = "(";
  for (unsigned int k=0;k<factors.size();k++)
    {
    output += factors[k].createLatex(withAvg);
    }
  output += ")";
  return output;
  }

};


class QGenerators
{
public:

  static TString emptyString;
  static TString nString;
  static TString mString;
  static TString oString;

  QGenerators()
  { }

  ~QGenerators()
  { }

  VarToken createVar(const TString & var, const TString & index, const TString & exponent);
  Term createVarProd(float coefficient, const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents);

  Sum calculate_qAAvg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option=1);
  Sum calculate_q1Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option=1);
  Sum calculate_q2Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option=1);
  Sum calculate_q3Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option=1);
  Sum calculate_q4Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option=1);
  Sum calculate_q5Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option=1);
  Sum calculate_q6Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option=1);
  Sum calculate_q7Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option=1);
  Sum calculate_q8Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option=1);

  Sum calculate_q1p1Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option);
  Sum calculate_q2p1Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option);
  Sum calculate_q3p1Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option);
  Sum calculate_q3p2Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option);
  Sum calculate_q3p3Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option);
  Sum calculate_qn(int nq, int np, int nr, int option=2);
};

TString QGenerators::emptyString = TString();
TString QGenerators::nString = TString("n");
TString QGenerators::mString = TString("m");
TString QGenerators::oString = TString("o");

VarToken QGenerators::createVar(const TString & var, const TString & index, const TString & exponent)
{
  return VarToken(var, index, exponent);
}

Term QGenerators::createVarProd(float coefficient, const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents)
{
  Term result;
  result.setCoefficient(coefficient);
  for (unsigned int k=0; k<vars.size(); k++)
    {
    result.addVarToken(VarToken(vars[k],indices[k],exponents[k]));
    }
  return result;
}

Sum QGenerators::calculate_q1Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option)
{
  Sum result;
  result.addTerm(createVarProd(1.0,genVar(vars[0],1),generateN(indices),exponents));
  return result;
}

Sum QGenerators::calculate_qAAvg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option)
{
  Sum result;
  result.addTerm(createVarProd(1.0,genVar(vars[0],indices.size()),indices,exponents));
  return result;
}


Sum QGenerators::calculate_q2Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option)
{
  Sum result;
  result.addSum(-1.0, calculate_q1Avg(vars,generateN(indices),exponents));
  result.addSum(1.0,calculate_qAAvg(vars,indices,exponents));
  if (option>0) result.regroup(option);
  return result;
}

Sum QGenerators::calculate_q3Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option)
{
  Sum result;
  result.addSum(-1.0,  calculate_q1Avg(vars,generateN(indices),exponents));
  vector<vector<TString>> perms = generate21(indices);
  for (unsigned int k=0; k<perms.size();k++) result.addSum(-1.0, calculate_q2Avg(vars,perms[k],exponents));
  result.addSum(1.0,calculate_qAAvg(vars,indices,exponents));
  if (option>0) result.regroup(option);
  return result;
}


Sum QGenerators::calculate_q4Avg(const vector<TString> & vars, const vector<TString> & indices, const vector<TString> & exponents, int option)
{
  Sum result;
  result.addSum(-1.0,  calculate_q1Avg(vars,generateN(indices),exponents));
  vector<vector<TString>> perms = generate31(indices);
  for (unsigned int k=0; k<perms.size();k++) result.addSum(-1.0, calculate_q2Avg(vars,perms[k],exponents));
  perms = generate22(indices);
  for (unsigned int k=0; k<perms.size();k++) result.addSum(-1.0, calculate_q2Avg(vars,perms[k],exponents));
  perms = generate211(indices);
  for (unsigned int k=0; k<perms.size();k++) result.addSum(-1.0, calculate_q3Avg(vars,perms[k],exponents));
  result.addSum(1.0,calculate_qAAvg(vars,indices,exponents));
  if (option>0) result.regroup(option);
  return result;
}


Sum QGenerators::calculate_q1p1Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option)
{
  Sum result;
  Term term1 = createVarProd(1.0,genVar(vars[0],1),generateN(qIndices),exponents);
  Term term2 = createVarProd(1.0,genVar(vars[1],1),generateN(pIndices),exponents);
  Term p = term1.multiply(term2);
  result.addTerm(p);
  if (option>0) result.regroup(option);
  return result;
}

Sum QGenerators::calculate_q2p1Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option)
{
  vector<TString> varsq;
  vector<TString> varsp;
  varsq.push_back(vars[0]);
  varsp.push_back(vars[1]);
  Sum r1 = calculate_q2Avg(varsq, qIndices, exponents);
  Sum r2 = calculate_q1Avg(varsp, pIndices, exponents);
  Sum result = r1.multiply(r2);
  if (option>0) result.regroup(option);
  return result;
}

Sum QGenerators::calculate_q3p1Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option)
{
  vector<TString> varsq;
  vector<TString> varsp;
  varsq.push_back(vars[0]);
  varsp.push_back(vars[1]);
  Sum r1 = calculate_q3Avg(varsq, qIndices, exponents);
  Sum r2 = calculate_q1Avg(varsp, pIndices, exponents);
  Sum result = r1.multiply(r2);

  if (option>0) result.regroup(option);
  return result;
}

Sum QGenerators::calculate_q3p2Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option)
{
  vector<TString> varsq;
  vector<TString> varsp;
  varsq.push_back(vars[0]);
  varsp.push_back(vars[1]);
  Sum r1 = calculate_q3Avg(varsq, qIndices, exponents);
  Sum r2 = calculate_q2Avg(varsp, pIndices, exponents);
  Sum result = r1.multiply(r2);

  if (option>0) result.regroup(option);
  return result;
}

Sum QGenerators::calculate_q3p3Avg(const vector<TString> & vars, const vector<TString> & qIndices, const vector<TString> & pIndices, const vector<TString> & exponents, int option)
{
  vector<TString> varsq;
  vector<TString> varsp;
  varsq.push_back(vars[0]);
  varsp.push_back(vars[1]);
  Sum r1 = calculate_q3Avg(varsq, qIndices, exponents);
  Sum r2 = calculate_q3Avg(varsp, pIndices, exponents);
  Sum result = r1.multiply(r2);

  if (option>0) result.regroup(option);
  return result;
}



Sum QGenerators::calculate_qn(int nq, int np, int nr, int option)
{
  vector<TString>  qIndices;
  vector<TString>  pIndices;
  vector<TString>  rIndices;
  vector<TString>  vars;
  vector<TString>  exponents;
  TString s;
  for (unsigned int k=0; k< uint(nq); k++)
    {
    s = nString; s += k+1;
    qIndices.push_back(s);
    exponents.push_back(emptyString);
    }
  for (unsigned int k=0; k< uint(np); k++)
    {
    s = mString; s += k+1;
    pIndices.push_back(s);
    exponents.push_back(emptyString);
    }
  for (unsigned int k=0; k< uint(nr); k++)
    {
    s = oString; s += k+1;
    rIndices.push_back(s);
    exponents.push_back(emptyString);
    }
  vars.push_back("Q");
  if (np>0) vars.push_back("P");
  if (nr>0) vars.push_back("R");
  int choice = 100*nq+10*np+nr;
  switch (choice)
    {
      default:
      cout << "Invalid value of choice: " << choice << endl;
      break;
      case 200: return calculate_q2Avg(vars, qIndices, exponents, option); break;
      case 300: return calculate_q3Avg(vars, qIndices, exponents, option); break;
      case 400: return calculate_q4Avg(vars, qIndices, exponents, option); break;
      case 110: return calculate_q1p1Avg(vars, qIndices, pIndices, exponents, option); break;
      case 210: return calculate_q2p1Avg(vars, qIndices, pIndices, exponents, option); break;
      case 310: return calculate_q3p1Avg(vars, qIndices, pIndices, exponents, option); break;
      case 320: return calculate_q3p2Avg(vars, qIndices, pIndices, exponents, option); break;
      case 330: return calculate_q3p3Avg(vars, qIndices, pIndices, exponents, option); break;
    }
  return Sum();
}


void CrossMomentCalculator(int nq=3, int np=3, int nr=0, int option=2)
{
  QGenerators gen;
  Sum result = gen.calculate_qn(nq, np, nr, option);
  cout << result.createLatex(true);
  cout << endl;
}


