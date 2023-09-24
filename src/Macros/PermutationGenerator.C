//PermutationGenerator

bool isIn(const TString & target, const vector<TString> & perm)
{
  unsigned  int n = perm.size();
  if (n<1) return false;
  for (unsigned   int i=0; i<n; i++)
    {
    if (target.EqualTo(perm[i]) ) return true;
    }
  return false;
}

bool isEquivalent(const vector<TString> & target, const vector<TString> & perm)
{
  unsigned  int n = target.size();
  if (n!=perm.size()) return false;
  for (unsigned   int i=0; i<n; i++)
    {
    if (!isIn(target[i],perm)) return false;
    }
  return true;
}

bool isFoundIn(const vector<TString> & target,  vector<vector<TString>>& perms)
{
  for (unsigned   int i=0; i<perms.size(); i++)
    {
    vector<TString> & perm = perms[i];
    if (isEquivalent(target,perm)) return true;
    }
  return false;
}


vector<TString>  genVar(const TString & name, int n)
{
  vector<TString> vars;
  for (int k=0; k<n; k++) vars.push_back(name);
  return vars;
}


vector<TString>  generateN(const vector<TString> & list)
{
  unsigned  int n = list.size();
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i=0;i<n;i++)
    {
    term += list[i];
    if (i<n-1) term += TString("+");
    }
  perm.push_back(term);
  return perm;
}


vector<vector<TString>>  generate21(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
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

vector<vector<TString>>  generate211(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
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



vector<vector<TString>> generate2111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
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

vector<vector<TString>>  generate21111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
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

vector<vector<TString>> generate211111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
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

vector<vector<TString>> generate2111111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate22(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          if (i3!=i1 && i3!=i2 &&
              i4!=i1 && i4!=i2)
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

vector<vector<TString>> generate221(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
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

vector<vector<TString>> generate2211(const vector<TString> & list)
{
  unsigned  int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
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

vector<vector<TString>> generate22111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
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

vector<vector<TString>> generate221111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate222(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
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

vector<vector<TString>> generate2221(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
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

vector<vector<TString>> generate22211(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate2222(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=0;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>>  generate31(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
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

vector<vector<TString>>   generate311(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            if (i4!=i1 && i4!=i2 && i4!=i3  &&
                i5!=i1 && i5!=i2 && i5!=i3)
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

vector<vector<TString>>  generate3111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
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

vector<vector<TString>>  generate31111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
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

vector<vector<TString>>  generate311111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>>  generate32(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            if (i4!=i1 && i4!=i2 && i4!=i3  &&
                i5!=i1 && i5!=i2 && i5!=i3)
              {
              perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
              perm.push_back(list[i4]+TString("+")+list[i5]);
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

vector<vector<TString>>  generate321(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
 vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
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

vector<vector<TString>>  generate3211(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                if (i4!=i1  && i4!=i2 && i4!=i3  &&
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

vector<vector<TString>>  generate32111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>>  generate322(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<TString> perm;
  vector<vector<TString>> perms;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                if (i4!=i1  && i4!=i2 && i4!=i3   &&
                    i5!=i1  && i5!=i2 && i5!=i3  &&
                    i6!=i1  && i6!=i2 && i6!=i3  && i6!=i4 && i6!=i5 &&
                    i7!=i1  && i7!=i2 && i7!=i3  && i7!=i4 && i7!=i5 )
                  {
                  perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                  perm.push_back(list[i4]+TString("+")+list[i5]);
                  perm.push_back(list[i6]+TString("+")+list[i7]);
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

vector<vector<TString>> generate3221(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=0;i8<n;i8++)
                  {
                  if (i4!=i1  && i4!=i2 && i4!=i3  &&
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

vector<vector<TString>> generate33(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<1; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              if (i4!=i1 && i4!=i2 && i4!=i3  &&
                  i5!=i1 && i5!=i2 && i5!=i3  &&
                  i6!=i1 && i6!=i2 && i6!=i3 )
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

vector<vector<TString>> generate331(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>> perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<1; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
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

vector<vector<TString>>  generate3311(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<1; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate332(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=0;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
                  {
                  if (i4!=i1 && i4!=i2 && i4!=i3 &&
                      i5!=i1 && i5!=i2 && i5!=i3 &&
                      i6!=i1 && i6!=i2 && i6!=i3 &&
                      i7!=i1 && i7!=i2 && i7!=i3 && i7!=i4 && i7!=i5 && i7!=i6 &&
                      i8!=i1 && i8!=i2 && i8!=i3 && i8!=i4 && i8!=i5 && i8!=i6  )
                    {
                    perm.push_back(list[i1]+TString("+")+list[i2]+TString("+")+list[i3]);
                    perm.push_back(list[i4]+TString("+")+list[i5]+TString("+")+list[i6]);
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

vector<vector<TString>> generate41(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
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

vector<vector<TString>> generate411(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
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

vector<vector<TString>> generate4111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
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

vector<vector<TString>> generate41111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate42(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
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

vector<vector<TString>> generate421(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
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

vector<vector<TString>> generate4211(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate43(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
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

vector<vector<TString>> generate431(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=0;i8<n;i8++)
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

vector<vector<TString>> generate44(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<1; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=0;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate51(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
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

vector<vector<TString>> generate511(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
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

vector<vector<TString>> generate5111(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate52(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
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

vector<vector<TString>> generate521(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
  vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=0;i8<n;i8++)
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

vector<vector<TString>> generate53(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=0;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate61(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
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

vector<vector<TString>> generate611(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate62(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=0;i7<n;i7++)
                {
                for (unsigned  int i8=i7+1;i8<n;i8++)
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

vector<vector<TString>> generate71(const vector<TString> & list)
{
  unsigned int n = list.size();
  vector<vector<TString>>  perms;
 vector<TString> perm;
  TString term = "";
  for (unsigned  int i1=0;i1<n; i1++)
    {
    for (unsigned  int i2=i1+1;i2<n;i2++)
      {
      for (unsigned  int i3=i2+1;i3<n;i3++)
        {
        for (unsigned  int i4=i3+1;i4<n;i4++)
          {
          for (unsigned  int i5=i4+1;i5<n;i5++)
            {
            for (unsigned  int i6=i5+1;i6<n;i6++)
              {
              for (unsigned  int i7=i6+1;i7<n;i7++)
                {
                for (unsigned  int i8=0;i8<n;i8++)
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
