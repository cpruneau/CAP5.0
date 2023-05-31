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

void fillArray(vector<double> * array, int  n, double v)
{
  vector<double> internal;
  for (int k=0; k<n; k++)
    {
    internal.push_back(v);
    }
  (*array) = internal;
}



int TestArray()
{
  vector<double> myArray;

  fillArray(&myArray,10,2.0);

  int n = myArray.size();
  cout << "myArray.size() :" <<  n << endl;

  for (int k=0; k<n; k++)
    {
    cout << "k:" << k << "  " << myArray[k] << endl;
    }
  return 0;
}
