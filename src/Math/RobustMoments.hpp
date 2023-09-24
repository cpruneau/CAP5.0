#ifndef CAP_MathBasicStatistics
#define CAP_MathBasicStatistics
#include <iostream>
#include <vector>
#include <cmath>
#include "MathBasicFunctions.hpp"

using namespace std;

namespace CAP
{
namespace Math
{

//!
//! Arithmetic Mean
//! I.e., the regular mean of data sample
//!
template <typename T, typename Iterator> T arithmeticMean(Iterator first, Iterator last);
template <typename T, typename Iterator, typename WeightIterator> T arithmeticMean(Iterator first, Iterator last, WeightIterator wfirst);
template <typename T> T arithmeticMean(long n, const T *a, const double *w=0);
template <typename T> T arithmeticMean(std::vector<T> values);
template <typename T> T arithmeticMean(std::vector<T> values, std::vector<T> weights);


template <typename T, typename Iterator> T arithmeticMean(Iterator first, Iterator last)
{
  T sum  = 0;
  T sumw = 0;
  while ( first != last )
    {
    sum  += *first;
    sumw += 1;
    first++;
    }
  return sum/sumw;
}

//!
//!Compute moments of order up to n using robust updating formula
//!
template<typename T, int n=2>
class RobustMoments
{
protected:

  long entries;
  std:array<T,n> moments;

public:

  RobustMoments()
  {
  moments.clear(n, 0);
  }


  void fill(T value)
  {
  entries++;
  T deviate = value - moments[0];
  moments[0] += value;
  if (n>=1) moments[1] += value*value;
  if (n>=2) moments[2] += value*value*value;
  moments[3] += value*value*value*value;
  }

  template<typename Iterator>
  void fill(Iterator first, Iterator last)
  {
  Iterator iter = first;
  while (iter!=last) fill(*iter);
  }


  T


  moments[0] ++;  // entries
  T n = moments[0];
  moments[1] += deviate/moments[0];
  T oldM2 = moments[2];
  T nn = n/n-1;
  moments[2] = nn*(oldM2 + deviate*deviate/n/n);

  T mean() const { return moments[1]; }
  T meanUncertainty() const { return rms()/sqrt(n); }
  T var() const { return moments[2]; }
  T rms() const { return sqrt(moments[2]); }





};

} // namespace Math

} // namespace CAP

#endif
