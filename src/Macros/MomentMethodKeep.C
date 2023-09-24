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
#include <TROOT.h>

using namespace std;


void printPerms(vector<vector<vector<int>> >& perms)
{
  for (int i=0;i<perms.size();i++)
    {
    vector<vector<int>> & perm = perms[i];
    cout << i << "   ::: ";
    for (int j=0;j<perm.size();j++)
      {
      vector<int> & term = perm[j];
      cout << "(";
      int n = term.size();
      for (int k=0;k<n;k++)
        {
        cout << term[k];
        if (k<n-1)  cout << ",";
        }
      cout << ")  ";
      }
    cout << endl;
    }
}

TString create_subindex(const TString & label, int index)
{
  TString output = "";
  output += label;
  output += "_{";
  output += index;
  output += "}";
  return output;
}

TString create_superindex(const TString & label, int index)
{
  TString output = "";
  output += label;
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
  int nn = indexMax-indexMin+1;
  for (int k=0;k<nn;k++)
    {
    create_subindex(label, indexMin+k);
    if (k<nn-1) output +=  "\\ne ";
    }
  output +=  "} ";
  return output;
}

TString create_qin(int index, vector<int> & ns, bool withIs=true, bool noExp=false)
{
  TString body = "q";
  TString exp  = "n";
  TString ind  = "i";
  TString output = "";
  output += body;
  if (withIs)
    {
    output += "_{";
    output += create_subindex(ind,index);
    output += "}";
    }
  else
    {
    output += "_{";
    output += index;
    output += "}";
    }
  if (!noExp)
    {
    output += "^{";
    int nn = ns.size();
    for (int i=0;i<nn;i++)
      {
      output += create_subindex(exp,ns[i]);
      if (i<nn-1) output += "+";
      }
    output += "}";
    }
  return output;
}



TString create_Qn(vector<int> & ns)
{
  TString body   = "Q";
  TString ind    = "n";
  TString output = "";
  output += body;
  output += "_{";
  int nn = ns.size();
  for (int i=0;i<nn;i++)
    {
    output += create_subindex(ind,ns[i]);
    if (i<nn-1) output += "+";
    }
  output += "}";
  return output;
}

TString create_qnProd(vector<vector<int>>& perm, bool avg=true, bool withIs=true, bool noExp=false)
{
  TString output = "";
  int nFac = perm.size();
  if (avg)
    {
    output += create_Navg(nFac);
    output += "\\llangle ";
    }
  else
    output += create_SumNE(1,nFac);
  int n = perm.size();
  for (int k=0; k<n; k++)  output += create_qin(k+1,perm[k],withIs,noExp);
  if (avg) output += "\\rrangle ";
  return output;
}


TString create_QnProd(vector<vector<int>>& perm, bool avg=true)
{
  TString output = "";
  if (avg) output += "\\llangle ";
  int n = perm.size();
  for (int k=0; k<n; k++) output += create_Qn(perm[k]);
  if (avg) output += "\\rrangle ";
  return output;
}

bool isEqual(vector<int> & target, vector<int> & reference)
{
  int n1 = target.size();
  int n2 = reference.size();
  if (n1!=n2) return false;
  for (int i=0;i<n1; i++)
    {
    if (target[i]!=reference[i]) return false;
    }
  return true;
}

bool isIn(vector<int> & target, vector<vector<int>> & perm)
{
  int n = perm.size();
  if (n<1) return false;
  for (int i=0; i<n; i++)
    {
    vector<int> & term = perm[i];
    if (isEqual(target,term)) return true;
    }
  return false;
}

bool isEquivalent(vector<vector<int>> & target, vector<vector<int>> & perm)
{

  int n = target.size();
  if (n!=perm.size()) return false;
  for (int i=0; i<n; i++)
    {
    vector<int> & term = target[i];
    if (!isIn(term,perm)) return false;
    }
  return true;
}

bool isFoundIn(vector<vector<int>> & target,  vector<vector<vector<int>> >& perms)
{
  for (int i=0; i<perms.size(); i++)
    {
    vector<vector<int>> & perm = perms[i];
    if (isEquivalent(target,perm)) return true;
    }
  return false;
}


void generateN(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i=0;i<n;i++)
    {
    term.push_back(list[i]);
    }
  perm.push_back(term);
  perms.push_back(perm);
}


void generate11(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i=0;i<n;i++)
    {
    term.push_back(list[i]);
    perm.push_back(term);
    term.clear();
    }
  perms.push_back(perm);
}

void generate21(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        if (i3!=i1 && i3!=i2)
          {
          term.push_back(list[i1]);
          term.push_back(list[i2]);
          perm.push_back(term);
          term.clear();
          term.push_back(list[i3]);
          perm.push_back(term);
          perms.push_back(perm);
          term.clear();
          perm.clear();
          break;
          }
        }
      }
    }
}

void generate211(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          if (i3!=i1 && i3!=i2 && i4!=i1 && i4!=i2)
            {
            term.push_back(list[i1]);
            term.push_back(list[i2]);
            perm.push_back(term);
            term.clear();
            term.push_back(list[i3]);
            perm.push_back(term);
            term.clear();
            term.push_back(list[i4]);
            perm.push_back(term);
            term.clear();
            perms.push_back(perm);
            perm.clear();
            break;
            }
          }
        }
      }
    }
}



void generate2111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            if (i3!=i1 && i3!=i2 &&
                i4!=i1 && i4!=i2 &&
                i5!=i1 && i5!=i2 )
              {
              term.push_back(list[i1]);
              term.push_back(list[i2]);
              perm.push_back(term);
              term.clear();
              term.push_back(list[i3]);
              perm.push_back(term);
              term.clear();
              term.push_back(list[i4]);
              perm.push_back(term);
              term.clear();
              term.push_back(list[i5]);
              perm.push_back(term);
              term.clear();
              perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
}

void generate21111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              if (i3!=i1 && i3!=i2 &&
                  i4!=i1 && i4!=i2 &&
                  i5!=i1 && i5!=i2 &&
                  i6!=i1 && i6!=i2)
                {
                term.push_back(list[i1]);
                term.push_back(list[i2]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i3]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i4]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i5]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i6]);
                perm.push_back(term);
                term.clear();
                perms.push_back(perm);
                perm.clear();
                break;
                }
              }
            }
          }
        }
      }
    }
}

void generate211111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                if (i3!=i1 && i3!=i2 &&
                    i4!=i1 && i4!=i2 &&
                    i5!=i1 && i5!=i2 &&
                    i6!=i1 && i6!=i2 &&
                    i7!=i1 && i7!=i2)
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i3]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i4]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i5]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate2111111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i3!=i1 && i3!=i2 &&
                      i4!=i1 && i4!=i2 &&
                      i5!=i1 && i5!=i2 &&
                      i6!=i1 && i6!=i2 &&
                      i7!=i1 && i7!=i2 &&
                      i8!=i1 && i8!=i2)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i3]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i4]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i5]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate22(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i1+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          if (i3!=i2 && i4!=i1 && i4!=i2 && i4!=i3)
            {
            term.push_back(list[i1]);
            term.push_back(list[i2]);
            perm.push_back(term);
            term.clear();
            term.push_back(list[i3]);
            term.push_back(list[i4]);
            perm.push_back(term);
            term.clear();
            if (!isFoundIn(perm, perms)) perms.push_back(perm);
            perm.clear();
            break;
            }
          }
        }
      }
    }
}

void generate221(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            if (i3!=i1 && i3!=i2 &&
                i4!=i1 && i4!=i2 &&
                i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4)
              {
              term.push_back(list[i1]);
              term.push_back(list[i2]);
              perm.push_back(term);
              term.clear();
              term.push_back(list[i3]);
              term.push_back(list[i4]);
              perm.push_back(term);
              term.clear();
              term.push_back(list[i5]);
              perm.push_back(term);
              term.clear();
              if (!isFoundIn(perm, perms)) perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
}

void generate2211(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              if (i3!=i1 && i3!=i2 &&
                  i4!=i1 && i4!=i2 &&
                  i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4 &&
                  i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4)
                {
                term.push_back(list[i1]);
                term.push_back(list[i2]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i3]);
                term.push_back(list[i4]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i5]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i6]);
                perm.push_back(term);
                term.clear();
                if (!isFoundIn(perm, perms)) perms.push_back(perm);
                perm.clear();
                break;
                }
              }
            }
          }
        }
      }
    }
}

void generate22111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                if (i3!=i1 && i3!=i2 &&
                    i4!=i1 && i4!=i2 &&
                    i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4 &&
                    i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 &&
                    i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4)
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i3]);
                  term.push_back(list[i4]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i5]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  if (!isFoundIn(perm, perms)) perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate221111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i3!=i1 && i3!=i2 &&
                      i4!=i1 && i4!=i2 &&
                      i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4 &&
                      i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i5]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    if (!isFoundIn(perm, perms)) perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate222(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              if (i3!=i1 && i3!=i2 &&
                  i4!=i1 && i4!=i2 &&
                  i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4 &&
                  i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4)
                {
                term.push_back(list[i1]);
                term.push_back(list[i2]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i3]);
                term.push_back(list[i4]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i5]);
                term.push_back(list[i6]);
                perm.push_back(term);
                term.clear();
                if (!isFoundIn(perm, perms)) perms.push_back(perm);
                perm.clear();
                break;
                }
              }
            }
          }
        }
      }
    }
}

void generate2221(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                if (i3!=i1 && i3!=i2 &&
                    i4!=i1 && i4!=i2 &&
                    i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4 &&
                    i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 &&
                    i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 && i7!=i6)
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i3]);
                  term.push_back(list[i4]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i5]);
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  if (!isFoundIn(perm, perms)) perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate22211(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i3!=i1 && i3!=i2 &&
                      i4!=i1 && i4!=i2 &&
                      i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4 &&
                      i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 && i7!=i6 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 && i8!=i6)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    if (!isFoundIn(perm, perms)) perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate2222(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i3!=i1 && i3!=i2 &&
                      i4!=i1 && i4!=i2 &&
                      i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4 &&
                      i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 && i7!=i6 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 && i8!=i6)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    if (!isFoundIn(perm, perms)) perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate31(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          if (i4!=i1 && i4!=i2 && i4!=i3)
            {
            term.push_back(list[i1]);
            term.push_back(list[i2]);
            term.push_back(list[i3]);
            perm.push_back(term);
            term.clear();
            term.push_back(list[i4]);
            perm.push_back(term);
            term.clear();
            perms.push_back(perm);
            perm.clear();
            break;
            }
          }
        }
      }
    }
}

void generate311(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            if (i4!=i1 && i4!=i2 && i4!=i3  && i5!=i1  && i5!=i2 && i5!=i3)
              {
              term.push_back(list[i1]);
              term.push_back(list[i2]);
              term.push_back(list[i3]);
              perm.push_back(term);
              term.clear();
              term.push_back(list[i4]);
              perm.push_back(term);
              term.clear();
              term.push_back(list[i5]);
              perm.push_back(term);
              term.clear();
              perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
}

void generate3111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              if (i4!=i1 && i4!=i2 && i4!=i3  &&
                  i5!=i1 && i5!=i2 && i5!=i3  &&
                  i6!=i1 && i6!=i2 && i6!=i3)
                {
                term.push_back(list[i1]);
                term.push_back(list[i2]);
                term.push_back(list[i3]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i4]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i5]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i6]);
                perm.push_back(term);
                term.clear();
                perms.push_back(perm);
                perm.clear();
                break;
                }
              }
            }
          }
        }
      }
    }
}

void generate31111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                if (i4!=i1 && i4!=i2 && i4!=i3  &&
                    i5!=i1 && i5!=i2 && i5!=i3  &&
                    i6!=i1 && i6!=i2 && i6!=i3  &&
                    i7!=i1 && i7!=i2 && i7!=i3)
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i4]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i5]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate311111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i4!=i1 && i4!=i2 && i4!=i3  &&
                      i5!=i1 && i5!=i2 && i5!=i3  &&
                      i6!=i1 && i6!=i2 && i6!=i3  &&
                      i7!=i1 && i7!=i2 && i7!=i3  &&
                      i8!=i1 && i8!=i2 && i8!=i3)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i4]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i5]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate32(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            if (i4!=i1 && i4!=i2 && i4!=i3  && i5!=i1  && i5!=i2 && i5!=i3)
              {
              term.push_back(list[i1]);
              term.push_back(list[i2]);
              term.push_back(list[i3]);
              perm.push_back(term);
              term.clear();
              term.push_back(list[i4]);
              term.push_back(list[i5]);
              perm.push_back(term);
              term.clear();
              perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
}

void generate321(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              if (i4!=i1  && i4!=i2 && i4!=i3  &&
                  i5!=i1  && i5!=i2 && i5!=i3  &&
                  i6!=i1  && i6!=i2 && i6!=i3  && i6!=i4 && i6!=i5)
                {
                term.push_back(list[i1]);
                term.push_back(list[i2]);
                term.push_back(list[i3]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i4]);
                term.push_back(list[i5]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i6]);
                perm.push_back(term);
                term.clear();
                perms.push_back(perm);
                perm.clear();
                break;
                }
              }
            }
          }
        }
      }
    }
}

void generate3211(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                if (i4!=i1  && i4!=i2 && i4!=i3   &&
                    i5!=i1  && i5!=i2 && i5!=i3  &&
                    i6!=i1  && i6!=i2 && i6!=i3  && i6!=i4 && i6!=i5 &&
                    i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4 && i7!=i5 )
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i4]);
                  term.push_back(list[i5]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate32111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i4!=i1  && i4!=i2 && i4!=i3  &&
                      i5!=i1  && i5!=i2 && i5!=i3  &&
                      i6!=i1  && i6!=i2 && i6!=i3  && i6!=i4 && i6!=i5 &&
                      i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4 && i7!=i5 &&
                      i8!=i1  && i8!=i2 && i8!=i3  && i8!=i4 && i8!=i5 )
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate322(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                if (i4!=i1  && i4!=i2 && i4!=i3   &&
                    i5!=i1  && i5!=i2 && i5!=i3  &&
                    i6!=i1  && i6!=i2 && i6!=i3  && i6!=i4 && i6!=i5 &&
                    i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4 && i7!=i5 )
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i4]);
                  term.push_back(list[i5]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i6]);
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  perms.push_back(perm);
                  if (!isFoundIn(perm, perms))  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate3221(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=0;i8<n;i8++)
                  {
                  if (i4!=i1  && i4!=i2 && i4!=i3   &&
                      i5!=i1  && i5!=i2 && i5!=i3  &&
                      i6!=i1  && i6!=i2 && i6!=i3  && i6!=i4 && i6!=i5 &&
                      i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4 && i7!=i5 &&
                      i8!=i1  && i8!=i2 && i8!=i3  && i8!=i4 && i8!=i5 && i8!=i6 && i8!=i7)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i6]);
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    if (!isFoundIn(perm, perms))  perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate33(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<1; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              if (i4!=i1 && i4!=i2 && i4!=i3   &&
                  i5!=i1  && i5!=i2 && i5!=i3  &&
                  i6!=i1  && i6!=i2 && i6!=i3 )
                {
                term.push_back(list[i1]);
                term.push_back(list[i2]);
                term.push_back(list[i3]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i4]);
                term.push_back(list[i5]);
                term.push_back(list[i6]);
                perm.push_back(term);
                term.clear();
                if (!isFoundIn(perm, perms))  perms.push_back(perm);
                perm.clear();
                break;
                }
              }
            }
          }
        }
      }
    }
}

void generate331(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<1; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                if (i4!=i1  && i4!=i2 && i4!=i3  &&
                    i5!=i1  && i5!=i2 && i5!=i3  &&
                    i6!=i1  && i6!=i2 && i6!=i3  &&
                    i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4  && i7!=i5 && i7!=i6)
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i4]);
                  term.push_back(list[i5]);
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  if (!isFoundIn(perm, perms))  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate3311(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<1; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i4!=i1  && i4!=i2 && i4!=i3  &&
                      i5!=i1  && i5!=i2 && i5!=i3  &&
                      i6!=i1  && i6!=i2 && i6!=i3  &&
                      i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4  && i7!=i5 && i7!=i6 &&
                      i8!=i1  && i8!=i2 && i8!=i3  && i8!=i4  && i8!=i5 && i8!=i6)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    if (!isFoundIn(perm, perms))  perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate332(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=0;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i4!=i1 && i4!=i2 && i4!=i3 &&
                      i5!=i1 && i5!=i2 && i5!=i3 &&
                      i6!=i1 && i6!=i2 && i6!=i3 &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 && i7!=i6 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 && i8!=i6  )
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    if (!isFoundIn(perm, perms)) perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate41(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            if (i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4)
              {
              term.push_back(list[i1]);
              term.push_back(list[i2]);
              term.push_back(list[i3]);
              term.push_back(list[i4]);
              perm.push_back(term);
              term.clear();
              term.push_back(list[i5]);
              perm.push_back(term);
              term.clear();
              perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
}

void generate411(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              if (i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4  &&
                  i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4)
                {
                term.push_back(list[i1]);
                term.push_back(list[i2]);
                term.push_back(list[i3]);
                term.push_back(list[i4]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i5]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i6]);
                perm.push_back(term);
                term.clear();
                if (!isFoundIn(perm, perms)) perms.push_back(perm);
                perm.clear();
                break;
                }
              }
            }
          }
        }
      }
    }
}

void generate4111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                if (i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4  &&
                    i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4  &&
                    i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4)
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  term.push_back(list[i4]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i5]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  if (!isFoundIn(perm, perms)) perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate41111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4  &&
                      i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4  &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4  &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i5]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    if (!isFoundIn(perm, perms)) perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate42(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              if (i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4  &&
                  i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4)
                {
                term.push_back(list[i1]);
                term.push_back(list[i2]);
                term.push_back(list[i3]);
                term.push_back(list[i4]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i5]);
                term.push_back(list[i6]);
                perm.push_back(term);
                term.clear();
                perms.push_back(perm);
                perm.clear();
                break;
                }
              }
            }
          }
        }
      }
    }
}

void generate421(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                if (i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4  &&
                    i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4  &&
                    i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4  && i7!=i5 && i7!=i6)
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  term.push_back(list[i4]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i5]);
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate4211(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i5!=i1 && i5!=i2 && i5!=i3 && i5!=i4  &&
                      i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4  &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4  && i7!=i5 && i7!=i6 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4  && i8!=i5 && i8!=i6)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate43(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                if (i5!=i1  && i5!=i2 && i5!=i3  && i5!=i4  &&
                    i6!=i1  && i6!=i2 && i6!=i3  && i6!=i4  &&
                    i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4 )
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  term.push_back(list[i4]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i5]);
                  term.push_back(list[i6]);
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate431(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=0;i8<n;i8++)
                  {
                  if (i5!=i1  && i5!=i2 && i5!=i3  && i5!=i4  &&
                      i6!=i1  && i6!=i2 && i6!=i3  && i6!=i4  &&
                      i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4  &&
                      i8!=i1  && i8!=i2 && i8!=i3  && i8!=i4  && i8!=i5 && i8!=i6  && i8!=i7)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate44(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<1; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=0;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i5!=i1  && i5!=i2 && i5!=i3  && i5!=i4  &&
                      i6!=i1  && i6!=i2 && i6!=i3  && i6!=i4  &&
                      i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4  &&
                      i8!=i1  && i8!=i2 && i8!=i3  && i8!=i4)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    term.push_back(list[i7]);
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    if (!isFoundIn(perm, perms)) perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate51(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              if (i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 && i6!=i5)
                {
                term.push_back(list[i1]);
                term.push_back(list[i2]);
                term.push_back(list[i3]);
                term.push_back(list[i4]);
                term.push_back(list[i5]);
                perm.push_back(term);
                term.clear();
                term.push_back(list[i6]);
                perm.push_back(term);
                term.clear();
                perms.push_back(perm);
                perm.clear();
                break;
                }
              }
            }
          }
        }
      }
    }
}

void generate511(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                if (i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 && i6!=i5 &&
                    i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 )
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  term.push_back(list[i4]);
                  term.push_back(list[i5]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate5111(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 && i6!=i5 &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 )
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate52(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                if (i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 && i6!=i5 &&
                    i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 )
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  term.push_back(list[i4]);
                  term.push_back(list[i5]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i6]);
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate521(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=0;i8<n;i8++)
                  {
                  if (i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 && i6!=i5 &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 && i8!=i6 && i8!=i7)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i6]);
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate53(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=0;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i6!=i1 && i6!=i2 && i6!=i3 && i6!=i4 && i6!=i5 &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 )
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i6]);
                    term.push_back(list[i7]);
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate61(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                if (i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 && i7!=i6)
                  {
                  term.push_back(list[i1]);
                  term.push_back(list[i2]);
                  term.push_back(list[i3]);
                  term.push_back(list[i4]);
                  term.push_back(list[i5]);
                  term.push_back(list[i6]);
                  perm.push_back(term);
                  term.clear();
                  term.push_back(list[i7]);
                  perm.push_back(term);
                  term.clear();
                  perms.push_back(perm);
                  perm.clear();
                  break;
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate611(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 && i7!=i6 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 && i8!=i6)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate62(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=0;i7<n;i7++)
                {
                for (int i8=i7+1;i8<n;i8++)
                  {
                  if (i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 && i7!=i6 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 && i8!=i6)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i7]);
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

void generate71(vector<int> & list, vector<vector<vector<int>> >& perms)
{
  int n = list.size();
  vector<vector<int>> perm;
  vector<int> term;
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=i2+1;i3<n;i3++)
        {
        for (int i4=i3+1;i4<n;i4++)
          {
          for (int i5=i4+1;i5<n;i5++)
            {
            for (int i6=i5+1;i6<n;i6++)
              {
              for (int i7=i6+1;i7<n;i7++)
                {
                for (int i8=0;i8<n;i8++)
                  {
                  if (i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 && i8!=i6 && i8!=i7)
                    {
                    term.push_back(list[i1]);
                    term.push_back(list[i2]);
                    term.push_back(list[i3]);
                    term.push_back(list[i4]);
                    term.push_back(list[i5]);
                    term.push_back(list[i6]);
                    term.push_back(list[i7]);
                    perm.push_back(term);
                    term.clear();
                    term.push_back(list[i8]);
                    perm.push_back(term);
                    term.clear();
                    perms.push_back(perm);
                    perm.clear();
                    break;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
}

TString create_Q2(vector<int> & list, bool avg=true)
{
  vector<vector<vector<int>>> perms;
  TString output = "";

  // lhs
  generate11(list,perms);
  output += create_QnProd(perms[0],avg);
  perms.clear();
  output += " =& ";

  // rhs
  generateN(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  output += " + ";

  generate11(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  return output;
}


TString create_Q3(vector<int> & list, bool avg=true)
{
  vector<vector<vector<int>>> perms;
  TString output = "";

  // lhs
  generate11(list,perms);
  output += create_QnProd(perms[0],avg);
  perms.clear();
  output += " =& ";

  // rhs
  generateN(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  output += " + ";

  generate21(list,perms);
  int nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate11(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  return output;
}


TString create_Q4(vector<int> & list, bool avg=true)
{
  vector<vector<vector<int>>> perms;
  TString output = "";

  // lhs
  generate11(list,perms);
  output += create_QnProd(perms[0],avg);
  perms.clear();
  output += " =& ";

  // rhs
  generateN(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  output += " + ";

  generate31(list,perms);
  int nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate22(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate211(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate11(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  return output;
}

TString create_Q5(vector<int> & list, bool avg=true)
{
  vector<vector<vector<int>>> perms;
  TString output = "";

  // lhs
  generate11(list,perms);
  output += create_QnProd(perms[0],avg);
  perms.clear();
  output += " =& ";

  // rhs
  generateN(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  output += " + ";

  generate41(list,perms);
  int nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate32(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate311(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate22(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate211(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate11(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  return output;
}

TString create_Q6(vector<int> & list, bool avg=true)
{
  vector<vector<vector<int>>> perms;
  TString output = "";

  // lhs
  generate11(list,perms);
  output += create_QnProd(perms[0],avg);
  perms.clear();
  output += " =& ";

  // rhs
  generateN(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  output += " + ";

  generate51(list,perms);
  int nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate42(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate411(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate33(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate321(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate3111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate222(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate2211(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate21111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate11(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  return output;
}

TString create_Q7(vector<int> & list, bool avg=true)
{
  vector<vector<vector<int>>> perms;
  TString output = "";

  // lhs
  generate11(list,perms);
  create_QnProd(perms[0],avg);
  perms.clear();
  output += " =& ";

  // rhs
  generateN(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  output += " + ";

  generate61(list,perms);
  int nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate52(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate511(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate43(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate421(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate4111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate331(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate3211(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate31111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate211111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate11(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  return output;
}

TString create_Q8(vector<int> & list, bool avg=true)
{
  vector<vector<vector<int>>> perms;
  TString output = "";

  // lhs
  generate11(list,perms);
  create_QnProd(perms[0],avg);
  perms.clear();
  output += " =& ";

  // rhs
  generateN(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  output += " + ";

  generate71(list,perms);
  int nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate62(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate611(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate53(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate521(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();
  // output += " + ";

  generate5111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate44(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate431(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate4211(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate41111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate332(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate3311(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate32111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate311111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate2222(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate22211(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate221111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate2111111(list,perms);
  nn = perms.size();
  for (int i=0;i<nn;i++)
    {
    output += create_qnProd(perms[i],avg);
    output += " + ";
    }
  perms.clear();

  generate11(list,perms);
  output += create_qnProd(perms[0],avg);
  perms.clear();
  return output;
}

TString create_q2Avg(vector<vector<vector<int>>> & perms11,
                     vector<vector<vector<int>>> & permsN,
                     bool avg=true, bool lhs=false)
{
  TString output = "";

  // lhs
  if (lhs)
    {
    create_qnProd(perms11[0],avg);
    output += " =& ";
    }

  // rhs
  output += create_QnProd(perms11[0],avg);
  output += " - ";
  output += create_QnProd(permsN[0],avg);
  return output;
}

TString create_q3Avg(vector<vector<vector<int>>> & perms11,
                     vector<vector<vector<int>>> & perms21,
                     vector<vector<vector<int>>> & permsN,
                     bool avg=true, bool lhs=true)
{
  TString output = "";

   if (lhs)
    {
    output += create_qnProd(perms11[0],avg);
    output += " =& ";
    }

  // rhs
  output += create_QnProd(perms11[0],avg);
  output += " - ";

  int nn = perms21.size();
  for (int i=0;i<nn;i++)
    {
    output += create_QnProd(perms21[i],avg);
    if (i<nn-1) output += " - ";
    }
  output += " +2 ";
  output += create_QnProd(permsN[0],avg);
  return output;
}

TString create_q4Avg(vector<vector<vector<int>>> & perms11,
                     vector<vector<vector<int>>> & perms31,
                     vector<vector<vector<int>>> & perms22,
                     vector<vector<vector<int>>> & perms211,
                     vector<vector<vector<int>>> & permsN,
                     bool avg=true, bool lhs=true)
{
  TString output = "";

   if (lhs)
    {
    output += create_qnProd(perms11[0],avg);
    output += " =& ";
    }

  // rhs
  output += create_QnProd(perms11[0],avg);
  output += " - ";
  output += create_QnProd(permsN[0],avg);
  output += " - ";
  output += " \\[ ";
  int nn = perms31.size();
  for (int i=0;i<nn;i++)
    {
    output += create_QnProd(perms31[i],avg);
    output += " - ";
    output += create_QnProd(permsN[0],avg);
    if (i<nn-1) output += " + ";
    }
  output += " \\] ";
  output += " - ";
  output += " \\[ ";
  nn = perms22.size();
  for (int i=0;i<nn;i++)
    {
    output += create_QnProd(perms22[i],avg);
    output += " - ";
    output += create_QnProd(permsN[0],avg);
    if (i<nn-1) output += " + ";
    }
  output += " \\] ";
  output += " - ";
  output += " \\[ ";
  nn = perms211.size();
  for (int i=0;i<nn;i++)
    {
    output += create_QnProd(perms11[0],avg);
    output += " - ";
    output += create_QnProd(perms211[0],avg);
    if (i<nn-1) output += " + ";
    }
  output += " \\] ";


  output += create_QnProd(permsN[0],avg);
  return output;
}




void MomentMethod()
{
  vector<int>  list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  list.push_back(4);

  vector<vector<vector<int>>> perms11;
  vector<vector<vector<int>>> perms21;
  vector<vector<vector<int>>> perms31;
  vector<vector<vector<int>>> perms22;
  vector<vector<vector<int>>> perms211;
  vector<vector<vector<int>>> permsN;
  generate11(list,perms11);
  generate21(list,perms21);
  generate31(list,perms31);
  generate22(list,perms22);
  generate211(list,perms211);
  generateN(list,permsN);


//  list.push_back(4);
//  list.push_back(5);
//  list.push_back(6);
//  list.push_back(7);
  //list.push_back(8);
//  vector< vector<vector<int> > > perms;
//  generate21111(list,perms);
  printPerms(perms31);
  cout << endl;
  cout << create_q3Avg(perms211,perms211,permsN,true);
  cout << endl;
}

