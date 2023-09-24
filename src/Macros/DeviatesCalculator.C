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

void printPerm(vector<TString> & perm)
{
  int n = perm.size();
  for (int i=0;i<n;i++)
    {
    cout << perm[i];
    if (i<n-1) cout << ",  ";
    }
    cout << endl;
}


void printPerms(vector<vector<TString>> & perms)
{
  for (int i=0;i<perms.size();i++)
    {
    printPerm(perms[i]);
    }
  cout << endl;
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

TString create_qin(int index, TString & exp, bool withIs=true, bool noExp=false)
{
  TString body = "q";
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
    output += exp;
    output += "}";
    }
  return output;
}



TString create_Qn(TString & index)
{
  TString body   = "Q";
  TString output = "";
  output += body;
  output += "_{";
  output += index;
  output += "}";
  return output;
}

TString create_qnProd(vector<TString> perm, bool avg=true, bool withIs=true, bool noExp=false)
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

TString create_QnProd(vector<TString> perm, bool avg=true)
{
  TString output = "";
  if (avg) output += "\\llangle ";
  int n = perm.size();
  for (int k=0; k<n; k++) output += create_Qn(perm[k]);
  if (avg) output += "\\rrangle ";
  return output;
}


bool isIn(TString & target, vector<TString> & perm)
{
  int n = perm.size();
  if (n<1) return false;
  for (int i=0; i<n; i++)
    {
    if (target.EqualTo(perm[i]) ) return true;
    }
  return false;
}

bool isEquivalent(vector<TString> & target, vector<TString> & perm)
{
  int n = target.size();
  if (n!=perm.size()) return false;
  for (int i=0; i<n; i++)
    {
    if (!isIn(target[i],perm)) return false;
    }
  return true;
}

bool isFoundIn(vector<TString> & target,  vector<vector<TString>>& perms)
{
  for (int i=0; i<perms.size(); i++)
    {
    vector<TString> & perm = perms[i];
    if (isEquivalent(target,perm)) return true;
    }
  return false;
}


vector<TString>  generateN(vector<TString> & list)
{
  int n = list.size();
  vector<TString> perm;
  TString term = "";
  for (int i=0;i<n;i++)
    {
    term += list[i];
    if (i<n-1) term += TString("+");
    }
  perm.push_back(term);
  return perm;
}


vector<TString>  generate11(vector<TString> & list)
{
  int n = list.size();
  vector<TString> perm;
  for (int i=0;i<n;i++)
    {
    perm.push_back(list[i]);
    }
  return perm;
}

vector<vector<TString>>  generate21(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (int i1=0;i1<n; i1++)
    {
    for (int i2=i1+1;i2<n;i2++)
      {
      for (int i3=0;i3<n;i3++)
        {
        if (i3!=i1 && i3!=i2)
          {
          perm.push_back(list[i1]+TString("+")+list[i2]);
          perm.push_back(list[i3]);
          perms.push_back(perm);
          perm.clear();
          break;
          }
        }
      }
    }
  return perms;
}

vector<vector<TString>>  generate211(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
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
            perm.push_back(list[i1]+TString("+")+list[i2]);
            perm.push_back(list[i3]);
            perm.push_back(list[i4]);
            perms.push_back(perm);
            perm.clear();
            break;
            }
          }
        }
      }
    }
  return perms;
}



vector<vector<TString>> generate2111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
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
              perm.push_back(list[i1]+TString("+")+list[i2]);
              perm.push_back(list[i3]);
              perm.push_back(list[i4]);
              perm.push_back(list[i5]);
              perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
  return perms;
}

vector<vector<TString>>  generate21111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
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
                perm.push_back(list[i1]+TString("+")+list[i2]);
                perm.push_back(list[i3]);
                perm.push_back(list[i4]);
                perm.push_back(list[i5]);
                perm.push_back(list[i6]);
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
  return perms;
}

vector<vector<TString>> generate211111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]);
                  perm.push_back(list[i3]);
                  perm.push_back(list[i4]);
                  perm.push_back(list[i5]);
                  perm.push_back(list[i6]);
                  perm.push_back(list[i7]);
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
  return perms;
}

vector<vector<TString>> generate2111111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]);
                    perm.push_back(list[i3]);
                    perm.push_back(list[i4]);
                    perm.push_back(list[i5]);
                    perm.push_back(list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate22(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
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
            perm.push_back(list[i1]+TString("+")+list[i2]);
            perm.push_back(list[i3]+TString("+")+list[i4]);
            if (!isFoundIn(perm, perms)) perms.push_back(perm);
            perm.clear();
            break;
            }
          }
        }
      }
    }
  return perms;
}

vector<vector<TString>> generate221(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
              perm.push_back(list[i1]+TString("+")+list[i2]);
              perm.push_back(list[i3]+TString("+")+list[i4]);
              perm.push_back(list[i5]);
              //            perm.push_back(list[i6]);
              //            perm.push_back(list[i7]);
              //            perm.push_back(list[i8]);

              if (!isFoundIn(perm, perms)) perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
  return perms;
}

vector<vector<TString>> generate2211(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                perm.push_back(list[i1]+TString("+")+list[i2]);
                perm.push_back(list[i3]+TString("+")+list[i4]);
                perm.push_back(list[i5]);
                perm.push_back(list[i6]);
                //            perm.push_back(list[i7]);
                //            perm.push_back(list[i8]);

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
  return perms;
}

vector<vector<TString>> generate22111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]);
                  perm.push_back(list[i3]+TString("+")+list[i4]);
                  perm.push_back(list[i5]);
                  perm.push_back(list[i6]);
                  perm.push_back(list[i7]);
                  //            perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate221111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]);
                    perm.push_back(list[i3]+TString("+")+list[i4]);
                    perm.push_back(list[i5]);
                    perm.push_back(list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate222(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                perm.push_back(list[i1]+TString("+")+list[i2]);
                perm.push_back(list[i3]+TString("+")+list[i4]);
                perm.push_back(list[i5]+TString("+")+list[i6]);
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
  return perms;
}

vector<vector<TString>> generate2221(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]);
                  perm.push_back(list[i3]+TString("+")+list[i4]);
                  perm.push_back(list[i5]+TString("+")+list[i6]);
                  perm.push_back(list[i7]);
                  //                perm.push_back(list[i8]);

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
  return perms;
}

vector<vector<TString>> generate22211(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]);
                    perm.push_back(list[i3]+TString("+")+list[i4]);
                    perm.push_back(list[i5]+TString("+")+list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate2222(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]);
                    perm.push_back(list[i3]+TString("+")+list[i4]);
                    perm.push_back(list[i5]+TString("+")+list[i6]);
                    perm.push_back(list[i7]+TString("+")+list[i8]);
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
  return perms;
}

vector<vector<TString>>  generate31(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
            perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
            perm.push_back(list[i4]);
            perms.push_back(perm);
            perm.clear();
            break;
            }
          }
        }
      }
    }
  return perms;
}

void generate311(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
              perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
              perm.push_back(list[i4]);
              perm.push_back(list[i5]);

              perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
  return perms;
}

void generate3111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                perm.push_back(list[i4]);
                perm.push_back(list[i5]);
                perm.push_back(list[i6]);

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
  return perms;
}

void generate31111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                  perm.push_back(list[i4]);
                  perm.push_back(list[i5]);
                  perm.push_back(list[i6]);
                  perm.push_back(list[i7]);

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
  return perms;
}

vector<vector<TString>>  generate311111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                    perm.push_back(list[i4]);
                    perm.push_back(list[i5]);
                    perm.push_back(list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>>  generate32(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
              perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
              perm.push_back(list[i4]+TString("+")+list[i5]);
 //             perm.push_back(list[i5]);

              perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
  return perms;
}

vector<vector<TString>>  generate321(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
 vector<TString> perm;
  TString term = "";
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
                perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                perm.push_back(list[i4]+TString("+")+list[i5]);
                perm.push_back(list[i6]);

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
  return perms;
}

vector<vector<TString>>  generate3211(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                  perm.push_back(list[i4]+TString("+")+list[i5]);
                  perm.push_back(list[i6]);
                  perm.push_back(list[i7]);
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
  return perms;

}

vector<vector<TString>>  generate32111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                    perm.push_back(list[i4]+TString("+")+list[i5]);
                    perm.push_back(list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;

}

vector<vector<TString>>  generate322(vector<TString> & list)
{
  int n = list.size();
  vector<TString> perm;
  vector<vector<TString>> perms;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                  perm.push_back(list[i4]+TString("+")+list[i5]);
                  perm.push_back(list[i6]+TString("+")+list[i7]);
//                  perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate3221(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                    perm.push_back(list[i4]+TString("+")+list[i5]);
                    perm.push_back(list[i6]+TString("+")+list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate33(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                perm.push_back(list[i4]+TString("+")+list[i5]+TString("+")+list[i6]);
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
  return perms;
}

vector<vector<TString>> generate331(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                  perm.push_back(list[i4]+TString("+")+list[i5]+TString("+")+list[i6]);
                  perm.push_back(list[i7]);
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
  return perms;
}

vector<vector<TString>>  generate3311(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                    perm.push_back(list[i4]+TString("+")+list[i5]+TString("+")+list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);

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
  return perms;
}

vector<vector<TString>> generate332(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                    perm.push_back(list[i4]+TString("+")+list[i5]+TString("+")+list[i6]);
                    perm.push_back(list[i7]+TString("+")+list[i5]+TString("+")+list[i8]);
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
  return perms;
}

vector<vector<TString>> generate41(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
              perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
              perm.push_back(list[i5]);
              perms.push_back(perm);
              perm.clear();
              break;
              }
            }
          }
        }
      }
    }
  return perms;
}

vector<vector<TString>> generate411(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
                perm.push_back(list[i5]);
                perm.push_back(list[i6]);
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
  return perms;
}

vector<vector<TString>> generate4111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
                  perm.push_back(list[i5]);
                  perm.push_back(list[i6]);
                  perm.push_back(list[i7]);

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
  return perms;
}

vector<vector<TString>> generate41111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
                    perm.push_back(list[i5]);
                    perm.push_back(list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate42(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
                perm.push_back(list[i5]+TString("+")+list[i6]);
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
  return perms;
}

vector<vector<TString>> generate421(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
                  perm.push_back(list[i5]+TString("+")+list[i6]);
                  perm.push_back(list[i7]);
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
  return perms;
}

vector<vector<TString>> generate4211(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
                    perm.push_back(list[i5]+TString("+")+list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate43(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
                  perm.push_back(list[i5]+TString("+")+list[i6]+TString("+")+list[i7]);
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
  return perms;
}

vector<vector<TString>> generate431(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
                    perm.push_back(list[i5]+TString("+")+list[i6]+TString("+")+list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate44(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]);
                    perm.push_back(list[i5]+TString("+")+list[i6]+TString("+")+list[i7]+TString("+")+list[i8]);
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
  return perms;
}

vector<vector<TString>> generate51(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]);
                perm.push_back(list[i6]);
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
  return perms;
}

vector<vector<TString>> generate511(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]);
                  perm.push_back(list[i6]);
                  perm.push_back(list[i7]);
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
  return perms;
}

vector<vector<TString>> generate5111(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]);
                    perm.push_back(list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate52(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]);
                  perm.push_back(list[i6]+TString("+")+list[i7]);
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
  return perms;
}

vector<vector<TString>> generate521(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]);
                    perm.push_back(list[i6]+TString("+")+list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

vector<vector<TString>> generate53(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]);
                    perm.push_back(list[i6]+TString("+")+list[i7]+TString("+")+list[i8]);
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
  return perms;
}

vector<vector<TString>> generate61(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
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
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]+TString("+")+list[i6]);
                  perm.push_back(list[i7]);
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
  return perms;
}

vector<vector<TString>> generate611(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]+TString("+")+list[i6]);
                    perm.push_back(list[i7]);
                    perm.push_back(list[i8]);

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
  return perms;
}

vector<vector<TString>> generate62(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]+TString("+")+list[i6]);
                    perm.push_back(list[i7]+TString("+")+list[i8]);
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
  return perms;
}

vector<vector<TString>> generate71(vector<TString> & list)
{
  int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
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
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]+TString("+")+list[i4]+TString("+")+list[i5]+TString("+")+list[i6]+TString("+")+list[i7]);
                    perm.push_back(list[i8]);
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
  return perms;
}

//TString create_Q2(vector<TString> & list, bool avg=true)
//{
//  vector<vector<TString>>  perms;
//  TString output = "";
//
//  // lhs
//  generate11(list,perms);
//  output += create_QnProd(perms[0],avg);
//  perms.clear();
//  output += " =& ";
//
//  // rhs
//  generateN(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  output += " + ";
//
//  generate11(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  return output;
//}
//
//
//TString create_Q3(vector<TString> & list, bool avg=true)
//{
//  vector<vector<TString>>  perms;
//  TString output = "";
//
//  // lhs
//  generate11(list,perms);
//  output += create_QnProd(perms[0],avg);
//  perms.clear();
//  output += " =& ";
//
//  // rhs
//  generateN(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  output += " + ";
//
//  generate21(list,perms);
//  int nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate11(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  return output;
//}
//
//
//TString create_Q4(vector<TString> & list, bool avg=true)
//{
//  vector<vector<TString>>  perms;
//  TString output = "";
//
//  // lhs
//  generate11(list,perms);
//  output += create_QnProd(perms[0],avg);
//  perms.clear();
//  output += " =& ";
//
//  // rhs
//  generateN(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  output += " + ";
//
//  generate31(list,perms);
//  int nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate22(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate211(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate11(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  return output;
//}
//
//TString create_Q5(vector<TString> & list, bool avg=true)
//{
//  vector<vector<TString>>  perms;
//  TString output = "";
//
//  // lhs
//  generate11(list,perms);
//  output += create_QnProd(perms[0],avg);
//  perms.clear();
//  output += " =& ";
//
//  // rhs
//  generateN(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  output += " + ";
//
//  generate41(list,perms);
//  int nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate32(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate311(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate22(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate211(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate11(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  return output;
//}
//
//TString create_Q6(vector<TString> & list, bool avg=true)
//{
//  vector<vector<TString>>  perms;
//  TString output = "";
//
//  // lhs
//  generate11(list,perms);
//  output += create_QnProd(perms[0],avg);
//  perms.clear();
//  output += " =& ";
//
//  // rhs
//  generateN(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  output += " + ";
//
//  generate51(list,perms);
//  int nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate42(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate411(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate33(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate321(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate3111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate222(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate2211(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate21111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate11(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  return output;
//}
//
//TString create_Q7(vector<TString> & list, bool avg=true)
//{
//  vector<vector<TString>>  perms;
//  TString output = "";
//
//  // lhs
//  generate11(list,perms);
//  create_QnProd(perms[0],avg);
//  perms.clear();
//  output += " =& ";
//
//  // rhs
//  generateN(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  output += " + ";
//
//  generate61(list,perms);
//  int nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate52(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate511(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate43(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate421(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate4111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate331(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate3211(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate31111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate211111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate11(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  return output;
//}
//
//TString create_Q8(vector<TString> & list, bool avg=true)
//{
//  vector<vector<TString>>  perms;
//  TString output = "";
//
//  // lhs
//  generate11(list,perms);
//  create_QnProd(perms[0],avg);
//  perms.clear();
//  output += " =& ";
//
//  // rhs
//  generateN(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  output += " + ";
//
//  generate71(list,perms);
//  int nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate62(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate611(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate53(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate521(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//  // output += " + ";
//
//  generate5111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate44(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate431(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate4211(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate41111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate332(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate3311(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate32111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate311111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate2222(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate22211(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate221111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate2111111(list,perms);
//  nn = perms.size();
//  for (int i=0;i<nn;i++)
//    {
//    output += create_qnProd(perms[i],avg);
//    output += " + ";
//    }
//  perms.clear();
//
//  generate11(list,perms);
//  output += create_qnProd(perms[0],avg);
//  perms.clear();
//  return output;
//}

TString create_q2Avg(vector<TString> & list,
                     bool avg=true,
                     bool paren=false,
                     bool lhs=false)
{
  TString output = "";

  // lhs
  if (lhs)
    {
    create_qnProd(list,avg);
    output += " =& ";
    }

  // rhs
  if (paren) output += "\\left( ";
  output += create_QnProd(list,avg);
  output += " - ";
  output += create_QnProd(generateN(list),avg);
  if (paren) output += "\\right)";
 return output;
}

TString create_q3Avg(vector<TString> & list,
                     bool avg=true, bool paren=false, bool lhs=true)
{
  TString output = "";

   if (lhs)
    {
    output += create_qnProd(list,avg);
    output += " =& ";
    }

  // rhs
  bool longVersion = false;
  if (longVersion)
    {
    if (paren) output += "\\left[ ";
    output += create_QnProd(list,avg);
    if (paren) output += "\\right.";
    output += "\\\\ \\nonumber ";

    vector<vector<TString>> perms21 = generate21(list);
    int n21 = perms21.size();
    for (int i=0;i<n21; i++)
      {
      output += "& -";
      output += create_q2Avg(perms21[i],1,1,0);
      output += "\\\\ \\nonumber";
      }
    output += "& - ";
    if (paren) output += "\\left.";
    output += create_QnProd(generateN(list),avg);
    if (paren) output += "\\right] \\\\ \\nonumber";
  }
  else // short version
    {
    if (paren) output += "\\left[ ";
    output += create_QnProd(list,avg);
    if (paren) output += "\\right.";
    output += "\\\\ \\nonumber ";

    vector<vector<TString>> perms21 = generate21(list);
    int n21 = perms21.size();
    output += "& -";
    output += create_QnProd(perms21[0],avg);
    output += "& -";
    output += create_QnProd(perms21[1],avg);
    output += "& -";
    output += create_QnProd(perms21[2],avg);
    if (paren) output += "\\left.";
    output += "& +2 ";
    output += create_QnProd(generateN(list),avg);
    if (paren) output += "\\right] \\\\ \\nonumber";
    }
  return output;
}

TString create_q4Avg(vector<TString> & list,
                     bool avg=true, bool paren=false, bool lhs=true)
{
  TString output = "";

   if (lhs)
    {
    output += create_qnProd(list,avg);
    output += " =& ";
    }

  // rhs
  if (paren) output += "\\left[ ";
  output += create_QnProd(list,avg);
  if (paren) output += "\\right.";
  output += "\\\\ \\nonumber ";

  vector<vector<TString>> perms31 = generate31(list);
  int n31 = perms31.size();

  for (int i=0;i<n31; i++)
    {
    output += "& -";
    output += create_q2Avg(perms31[i],1,1,0);
    output += "\\\\ \\nonumber";
    }

  vector<vector<TString>> perms22 = generate22(list);
  int n22 = perms22.size();
  for (int i=0;i<n22; i++)
    {
    output += "& -";
    output += create_q2Avg(perms22[i],1,1,0);
    output += "\\\\ \\nonumber";
    }

  vector<vector<TString>> perms211 = generate211(list);
  int n211 = perms211.size();
  for (int i=0;i<n211; i++)
    {
    output += "& -";
    output += create_q3Avg(perms211[i],1,1,0);
    output += "\\\\ \\nonumber";
    }

  output += "& - ";
  if (paren) output += "\\left.";
  output += create_QnProd(generateN(list),avg);
  if (paren) output += "\\right] \\\\ \\nonumber";
  return output;
}

TString create_q5Avg(vector<TString> & list,
                     bool avg=true, bool paren=false, bool lhs=true)
{
  TString output = "";

  if (lhs)
    {
    output += create_qnProd(list,avg);
    output += " =& ";
    }

  // rhs
  if (paren) output += "\\left[ ";
  output += create_QnProd(list,avg);
  if (paren) output += "\\right.";
  output += "\\\\ \\nonumber ";

  vector<vector<TString>> perms41 = generate41(list);
  int n41 = perms41.size();

  for (int i=0;i<n41; i++)
    {
    output += "& -";
    output += create_q2Avg(perms41[i],1,1,0);
    output += "\\\\ \\nonumber";
    }

  vector<vector<TString>> perms32 = generate32(list);
  int n32 = perms32.size();
  for (int i=0;i<n32; i++)
    {
    output += "& -";
    output += create_q2Avg(perms32[i],1,1,0);
    output += "\\\\ \\nonumber";
    }

  vector<vector<TString>> perms221 = generate221(list);
  int n221 = perms221.size();
  for (int i=0;i<n221; i++)
    {
    output += "& -";
    output += create_q3Avg(perms221[i],1,1,0);
    output += "\\\\ \\nonumber";
    }

  vector<vector<TString>> perms2111 = generate2111(list);
  int n2111 = perms2111.size();
  for (int i=0;i<n2111; i++)
    {
    output += "& -";
    output += create_q4Avg(perms2111[i],1,1,0);
    output += "\\\\ \\nonumber";
    }

  output += "& - ";
  if (paren) output += "\\left.";
  output += create_QnProd(generateN(list),avg);
  if (paren) output += "\\right] \\\\ \\nonumber";
  return output;
}



void printList(vector<TString> & list)
{
  for (int i=0; i<list.size(); i++)
    {
    cout << " i: " << list[i] << endl;
    }
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

TString createFactor(vector<TString> & factor)
{
  TString output;
  output = "(";
  int nt = factor.size();
  for (int k=0;k<nt;k++)
    {
    output += factor[k];
    }
  output += ")";
  return output;
}

TString createExpression(vector<vector<TString>> & expression)
{
  TString output;
  int nt = expression.size();
  for (int k=0;k<nt;k++)
  {
  output += createFactor(expression[k]);
  }
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
  int     exponent;

  VarToken()
  :
  name(""),
  exponent(0)
  { }

  VarToken(TString _name, int _exponent)
  :
  name(_name),
  exponent(_exponent)
  { }

  VarToken(const VarToken & token)
  :
  name(token.name),
  exponent(token.exponent)
  { }

  VarToken & operator=(const VarToken & rhs)
  {
  if (this!=&rhs)
    {
    name = rhs.name;
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
  bool ans = name.EqualTo(s);
  return ans;
  }

  bool sameNameAs(const VarToken & token)
  {
  return name.EqualTo(token.name);
  }

  bool sameExpAs(const VarToken & token)
  {
  return exponent==token.exponent;
  }

  bool sameAs(const VarToken & token)
  {
  return sameNameAs(token) && sameExpAs(token);
  }

  TString createLatex()
  {
  TString output;
  if (exponent==0) return output;
  output = name;
  if (exponent!=1)
    {
    output += "^{";
    output += exponent;
    output += "}";
    }
  return output;
  }

  void addToExponent(int n)
  {
  exponent += n;
  }

  VarToken multiply(VarToken & token)
  {
  VarToken newToken(name,exponent+token.exponent);
  return newToken;
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

  Term(float _coefficient, TString _name, int _exp)
  :
  coefficient(_coefficient),
  varTokens()
  {
  varTokens.push_back(VarToken(_name,_exp));
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
    varTokens = rhs.varTokens;
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
  if (varTokens.size()!=aTerm.varTokens.size()) false;
  bool same = true;
  for (int k=0;k<varTokens.size();k++)
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

  for (int k1=0;k1<tokens.size();k1++)
    {
    //cout << " simplify() k1:" << k1 << " keep: " << keep[k1] << endl;
    if (keep[k1])
      {
      VarToken & t1 = tokens[k1];
      for (int k2=k1+1;k2<tokens.size();k2++)
        {
        VarToken & t2 = tokens[k2];
        if (t1.sameNameAs(t2))
          {
          keep[k2]=false;
          t1.exponent += t2.exponent;
          }
        }
      varTokens.push_back(t1);
      }
    }

  // fix sequences in q_.
  int count = 1;
  for (int k1=0;k1<varTokens.size();k1++)
    {
    VarToken & t = varTokens[k1];
    if (t.name.Contains("q_"))
      {
      t.name = "q_";
      t.name += count;
      count++;
      }
    }

  // fix sequences in p_.
  count = 1;
  for (int k1=0;k1<varTokens.size();k1++)
    {
    VarToken & t = varTokens[k1];
    if (t.name.Contains("p_"))
      {
      t.name = "p_";
      t.name += count;
      count++;
      }
    }

  // fix sequences in r_.
  count = 1;
  for (int k1=0;k1<varTokens.size();k1++)
    {
    VarToken & t = varTokens[k1];
    if (t.name.Contains("r_"))
      {
      t.name = "r_";
      t.name += count;
      count++;
      }
    }

  // fix sequences in s_.
  count = 1;
  for (int k1=0;k1<varTokens.size();k1++)
    {
    VarToken & t = varTokens[k1];
    if (t.name.Contains("s_"))
      {
      t.name = "s_";
      t.name += count;
      count++;
      }
    }
  //cout << " simplify() after: " << createLatex() << endl;
  }

  Term multiply(const Term & rhs)
  {
  Term newTerm;
  newTerm.coefficient = coefficient * rhs.coefficient;
  vector<VarToken> lhsTokens = varTokens;
  vector<VarToken> rhsTokens = rhs.varTokens;
  vector<bool> copyRhs(rhsTokens.size(),true);
  for (int k1=0;k1<lhsTokens.size();k1++)
    {
    VarToken lhsToken = lhsTokens[k1];
    for (int k2=0;k2<rhsTokens.size();k2++)
      {
      VarToken & rhsToken = rhsTokens[k2];
      if (lhsToken.sameNameAs(rhsToken))
        {
        lhsToken.addToExponent(rhsToken.exponent);
        copyRhs[k2] = false;
        }
      }
    newTerm.addVarToken(lhsToken);
    }
  for (int k2=0;k2<rhsTokens.size();k2++)
    {
    if (copyRhs[k2]) newTerm.addVarToken(rhsTokens[k2]);
    //newTerm.addVarToken(rhsTokens[k2]);
    }
  //cout << "Term::multiply(const Term & rhs) newTerm:" << newTerm.createLatex() << endl;
  return newTerm;
  }

  // substitute occurences of s1 by s2
  void substitute(TString s1, TString s2)
  {
  for (int k=0;k<varTokens.size();k++)
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
    for (int k=1;k<varTokens.size();k++)
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
  for (int k=0;k<varTokens.size();k++)
    {
    if (varTokens[k].name.Contains("_"))  nCount++;
    }
  if (nCount==1)
    {
    for (int k=0;k<varTokens.size();k++)
      {
      if (varTokens[k].name.Contains(s1))  varTokens[k].name = s2;
      }
    }
  }

  TString createLatex(bool withAvg=false)
  {
  TString output = " ";
  if (coefficient==0) return output;
  if (coefficient>0)
    {
    output += "+";
    if (coefficient!=1) output += coefficient;
    }
  if (coefficient<0)
    {
    output += "-";
    if (fabs(coefficient)!=1) output += fabs(coefficient);
    }

  if (!withAvg)
    {
    int n = varTokens.size();
    for (int k=0;k<n;k++)
      {
        output += varTokens[k].createLatex();
      }
    }
  else
    {
    bool inserted  = false;
    int n = varTokens.size();
    for (int k=0;k<n;k++)
      {
      if (varTokens[k].name.Contains("llangle"))
        {
        output += varTokens[k].createLatex();
        }
      else
        {
        if (k<n-1)
          {
          if (!inserted)
            {
            inserted = true;
            output  += "\\llangle ";
            output  += varTokens[k].createLatex();
            }
          else
            {
            output  += varTokens[k].createLatex();
            }
          }
        else
          {
          output  += varTokens[k].createLatex();
          }
        }
      }
    if (inserted) output  += "\\rrangle ";
    }

  return output;
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

  Sum multiply(const Sum & rhs)
  {
  Sum newTerms;
  for (int k1=0;k1<terms.size();k1++)
    {
    Term lhsTerm = terms[k1];
    for (int k2=0;k2<rhs.terms.size();k2++)
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
  for (int k=0;k<terms.size();k++)
    terms[k].substitute(s1,s2);
  }

  // bring VarToken with s at the beginning
  void collect(TString s)
  {
  for (int k=0;k<terms.size();k++)
    terms[k].collect(s);
  }

  void replaceSingles(const TString s1, const TString s2)
  {
  for (int k=0;k<terms.size();k++)
    terms[k].replaceSingles(s1,s2);
  }

  // change sequences q_1q2q_4 to q_1q_2_q3, etc.
  void simplify()
  {

  }


  void regroup()
  {
  vector<Term> allTerms = terms;
  terms.clear();
  vector<bool> keep(allTerms.size(),true);

  for (int k1=0;k1<allTerms.size();k1++)
    {
    if (keep[k1])
      {
      Term & t1 = allTerms[k1];
      for (int k2=k1+1;k2<allTerms.size();k2++)
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

  TString createLatex(bool withAvg=false)
  {
  TString output;
  int n = terms.size();
  output = "(";
  for (int k=0;k<n;k++)
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
  for (int k=0;k<factors.size();k++)
    factors[k].substitute(s1,s2);
  }

  // bring VarToken with s at the beginning
  void collect(TString s)
  {
  for (int k=0;k<factors.size();k++)
    factors[k].collect(s);
  }

  void replaceSingles(const TString s1, const TString s2)
  {
  for (int k=0;k<factors.size();k++)
    factors[k].replaceSingles(s1,s2);
  }

  void regroup()
  {
  for (int k=0;k<factors.size();k++)
    factors[k].regroup();
  }


  TString createLatex(bool withAvg=false)
  {
  TString output;
  int n = factors.size();
  output = "(";
  for (int k=0;k<n;k++)
    {
    output += factors[k].createLatex(withAvg);
    }
  output += ")";
  return output;
  }

};



//
//
//
//TString multinomialOld(int nq, int np, int nr, int ns)
//{
//  TString qAvg = "qa";
//  TString pAvg = "pa";
//  TString rAvg = "ra";
//  TString sAvg = "sa";
//  TString term;
//
//  vector<TString> factor;
//  vector<vector<TString>> expression;
//  for (int k=0; k<nq; k++)
//    {
//    term = "+q";
//    term += k+1;
//    term += " ";
//    factor.push_back(term);
//    term = "-qa ";
//    factor.push_back(term);
//    expression.push_back(factor);
//    factor.clear();
//    }
//  for (int k=0; k<np; k++)
//    {
//    term = "+p";
//    term += k+1;
//    term += " ";
//    factor.push_back(term);
//    term = "-pa ";
//    factor.push_back(term);
//    expression.push_back(factor);
//    factor.clear();
//    }
//  for (int k=0; k<nr; k++)
//    {
//    term = "+r";
//    term += k+1;
//    term += " ";
//    factor.push_back(term);
//    term = "-ra ";
//    factor.push_back(term);
//    expression.push_back(factor);
//    factor.clear();
//    }
//  for (int k=0; k<ns; k++)
//    {
//    term = "+s";
//    term += k+1;
//    term += " ";
//    factor.push_back(term);
//    term = "-sa";
//    factor.push_back(term);
//    expression.push_back(factor);
//    factor.clear();
//    }
//
//  while (expression.size()>1)
//    {
//    cout << createExpression(expression) << endl;
//    int n = expression.size();
//    vector<TString> factor2 = expression[n-1];
//    vector<TString> factor1 = expression[n-2];
//    expression.pop_back();
//    expression.pop_back();
//    expression.push_back(multiply(factor1, factor2));
//    }
//  return createExpression(expression);
//}


TString multinomial(int nq, int np, int nr, int ns)
{
  Product expression;
  Sum sum;
  Term term;

  for (int k=0; k<nq; k++)
    {
    Sum sum;
    TString name = "q";
    name += "_";
    name += k+1;
    sum.addTerm(Term(1.0, name, 1));
    sum.addTerm(Term(-1.0, "qa", 1));
    expression.addFactor(sum);
    }
  for (int k=0; k<np; k++)
    {
    Sum sum;
    TString name = "p";
    name += "_";
    name += k+1;
    sum.addTerm(Term(1.0, name, 1));
    sum.addTerm(Term(-1.0, "pa", 1));
    expression.addFactor(sum);
    }
  for (int k=0; k<nr; k++)
    {
    Sum sum;
    TString name = "r";
    name += "_";
    name += k+1;
    sum.addTerm(Term(1.0, name, 1));
    sum.addTerm(Term(-1.0, "ra", 1));
    expression.addFactor(sum);
    }
  for (int k=0; k<ns; k++)
    {
    Sum sum;
    TString name = "s";
    name += "_";
    name += k+1;
    sum.addTerm(Term(1.0, name, 1));
    sum.addTerm(Term(-1.0, "sa", 1));
    expression.addFactor(sum);
    }

  cout << endl << endl << expression.createLatex(false) << endl << endl;

  while (expression.size()>1)
    {
    int n = expression.size();
    Sum factor2 = expression.factors[n-1];
    Sum factor1 = expression.factors[n-2];
    expression.popBack();
    expression.popBack();
    expression.addFactor(factor1.multiply(factor2));
    }
  cout << endl << endl << expression.createLatex() << endl << endl;
  expression.replaceSingles("q_","qa");
  expression.replaceSingles("p_","pa");
  expression.replaceSingles("r_","ra");
  expression.replaceSingles("s_","sa");
 // cout << endl << endl << expression.createLatex(false) << endl << endl;
  expression.collect("qa");
  expression.collect("pa");
  expression.collect("ra");
  expression.collect("sa");
//  cout << endl << endl << "qa and pa collected:" << expression.createLatex(false) << endl << endl;
  expression.regroup();
  cout << endl << endl << "regrouped:" << expression.createLatex() << endl << endl;
//  return expression.createLatex();

  expression.substitute("qa"," \\llangle q\\rrangle ");
  expression.substitute("pa"," \\llangle p\\rrangle ");
  expression.substitute("ra"," \\llangle r\\rrangle ");
  expression.substitute("sa"," \\llangle s\\rrangle ");
  return expression.createLatex(true);

}



void MomentMethod(int nq=2, int np=0, int nr=0, int ns=0)
{
  cout << multinomial(nq,np,nr,ns);
  cout << endl;
}

//  vector<TString>  list;
//  list.push_back(create_subindex("n",1));
//  list.push_back(create_subindex("n",2));
//  list.push_back(create_subindex("n",3));
//  list.push_back(create_subindex("n",4));
////  list.push_back(create_subindex("n",5));
////
//  cout << insertPageBreaks(create_q3Avg(list,true,true));
//  cout << endl<< endl<< endl;
//  cout << create_q2Avg(perms31[1],true);
//  cout << endl<< endl<< endl;
//  cout << create_q2Avg(perms31[2],true);
//  cout << endl<< endl<< endl;
//
//  cout << create_q4Avg(list,true);
//  cout << endl<< endl<< endl;

//  TString sum1 = list[0];
//  sum1 += "+";
//  sum1 += list[1];
//  sum1 += "+";
//  sum1 += list[2];
//  sum1 += "+";
//  sum1 += list[3];
//  cout << sum1 << endl;
//
//  TString sum2 = list[0];
//  sum2 += "+";
//  sum2 += list[2];
//  sum2 += "+";
//  sum2 += list[1];
//  sum2 += "+";
//  sum2 += list[3];
//  cout << sum2 << endl;
//
//
//  TString tok;
//  Ssiz_t from = 0;
//  vector<TString> tokens1;
//  vector<TString> tokens2;
//
//  while (sum1.Tokenize(tok, from, "+"))
//    {
//    tokens1.push_back(tok);
//  }
//  for (int i=0;i<tokens1.size();i++)
//    {
//    cout << tokens1[i] << endl;
//    }
//
//  cout << "sum2" << endl;
//  from = 0;
//  while (sum2.Tokenize(tok, from, "+"))
//    {
//    tokens2.push_back(tok);
//    }
//  for (int i=0;i<tokens2.size();i++)
//    {
//    cout << tokens2[i] << endl;
//    }
//  cout << isEquivalent(tokens1, tokens2) << endl;

//  list.push_back(create_subindex("n",3));
//  generate11(list,perms11);
//  cout << "11" << endl;
//  printPerms(perms11);
//  cout << "N" << endl;
//  generateN(list,permsN);
//  printPerms(permsN);
//  generate21(list,perms21);
//  cout << "21" << endl;
//  printPerms(perms21);
//
//
//  cout << create_q3Avg(perms11,perms21,permsN,true);
//  cout << endl<< endl<< endl;
//
//  cout << create_q2Avg(perms21,permsN,true);
//
//  cout << endl<< endl<< endl;
//
//
//
//  perms11.clear();
//  permsN.clear();
////
//  list.push_back(create_subindex("n",4));
//
//  generate11(list,perms11);
//  cout << "11" << endl;
//  printPerms(perms11);
//  cout << "N" << endl;
//  generateN(list,permsN);
//  printPerms(permsN);
//  generate31(list,perms31);
//  cout << "31" << endl;
//  printPerms(perms31);
//  generate22(list,perms22);
//  cout << "22" << endl;
//  printPerms(perms22);
//  generate211(list,perms211);
//  cout << "211" << endl;
//  printPerms(perms211);
//  perms11.clear();
//  permsN.clear();

  //  cout << endl;

