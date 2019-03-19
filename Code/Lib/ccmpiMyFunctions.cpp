/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "ccmpiMyFunctions.h"
#include <iostream>
#include <omp.h>

namespace ccmpi {

//-----------------------------------------------------------------------------
void GetFirstAndLastIndex(const int& numberOfThreads,
                          const unsigned long int& i,
                          const double& elementsPerThread,
                          const unsigned long int& numberOfElements,
                          unsigned long int& first,
                          unsigned long int& last)
{
  first = i * elementsPerThread + 1;
  last = ((i + 1) * elementsPerThread + 1) - 1;
  if (last < first) last = first;
  if (last > numberOfElements) last = numberOfElements;
  if (i + 1 == numberOfThreads) last = numberOfElements;
}


//-----------------------------------------------------------------------------
std::vector<std::pair<unsigned long int, unsigned long int> >
GetVectorOfSeriesIndexPairs(const unsigned int& numberOfThreads,
                            const unsigned long int& numberOfElements
                           )
{

  double elementsPerThread = static_cast<double>(numberOfElements)
                           / static_cast<double>(numberOfThreads);

  std::vector<std::pair<unsigned long int, unsigned long int> > v;
  for (int i = 0; i < numberOfThreads; i++)
  {
    unsigned long int first = 0;
    unsigned long int last = 0;
    GetFirstAndLastIndex(numberOfThreads, i, elementsPerThread, numberOfElements, first, last);
    v.push_back(std::pair<unsigned long int, unsigned long int>(first, last));

    std::cout << "For " << numberOfElements << " elements, "
              << " spread over " << numberOfThreads << " processes/threads, "
              << " the i=" << i << " block "
              << " started at " << first
              << " and finished at " << last << std::endl;
  }
  return v;
}


//-----------------------------------------------------------------------------
void FillSeries(unsigned long int* const values,
                unsigned long int const& numberOfValues)
{
    std::string errmsg = "Invalid number of values, must choose between 1 and "
                         "100000. i.e. between 1b and 800kb worth of data.";

    // Check whether array has been pre-allocated (>0b) or whether length of
    // array leads to segfaults on many compilers/OSs (800kb or 100000 unsigned
    // long ints).
    if (numberOfValues <= 0 || numberOfValues > 100000) {
        throw std::runtime_error(errmsg);
    } else {
        for (unsigned int i = 0; i < numberOfValues; i++) {
            values[i] = i;
        }
    }
}


//-----------------------------------------------------------------------------
unsigned long int SumSeries(const unsigned long int* const values,
                            unsigned long int const & numberOfValues)
{
    std::string errmsg1 = "Invalid number of values, must choose between 1 and "
                         "100000. i.e. between 1b and 800kb worth of data.";
    std::string errmsg2 = "Sum total too high, integer overflow!";

    // Check whether array has been pre-allocated (>0b) or whether length of
    // array leads to segfaults on many compilers/OSs (800kb or 100000 unsigned
    // long ints).
    if (numberOfValues <= 0 || numberOfValues > 100000) {
        throw std::runtime_error(errmsg1);
    } else {

        bool evaluated = false;
        int i = 0;
        unsigned long int sum = 0;
        unsigned long int  largestInt = 4294967295; // 2^32

        while (!evaluated) {
            if (sum <= largestInt - values[i]) {
                sum += values[i];
                i+=1;
                if (i == numberOfValues) {
                    evaluated = true;
                }
            } else {
                // Check that the sum hasn't overflowed, against the maximum
                // integer size we can expect from most devices.
                throw std::runtime_error(errmsg2);
            }
        }
        return sum;
    }
}


//-----------------------------------------------------------------------------
double EvaluateGregoryLeibnizSeries(unsigned long int startingTermNumber,
                                    unsigned long int finishingTermNumber
                                   )
{
  return 0.0;
}


//-----------------------------------------------------------------------------
double EvaluatePiUsingOpenMP(unsigned long int numberOfElements)
{
  return 0.0;
}

} // end namespace
