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
#include <math.h>

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
    GetFirstAndLastIndex(numberOfThreads,
                         i,
                         elementsPerThread,
                         numberOfElements,
                         first,
                         last);
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
    std::string errmsg1 = "Invalid number of values, must pre-allocate an array"
                          "with at least 1 element";

    std::string errmsg2 = "Too many values! Must pass in array with between 1"
                          "and 2^32 values";

    unsigned long int  largestInt = 4294967295; // 2^32

    // Check whether array has been pre-allocated (>0 elements)
    if (numberOfValues <= 0) {
        throw std::runtime_error(errmsg1);
    }
    // Check whether array size will result in integer overflow of index values
    // At least from most devices.
    if (numberOfValues >= largestInt) {
        throw std::runtime_error(errmsg2);
    }
    else {
        for (unsigned int i = 0; i < numberOfValues; i++) {
            values[i] = i+1;
        }
    }
}


//-----------------------------------------------------------------------------
unsigned long int SumSeries(const unsigned long int* const values,
                            unsigned long int const & numberOfValues)
{
    std::string errmsg1 = "Invalid number of values, must pre-allocate an array"
                          "with at least 1 element";

    std::string errmsg2 = "Sum total too high, integer overflow!";

    // Check whether array has been pre-allocated (>0 elements)
    if (numberOfValues <= 0) {
        throw std::runtime_error(errmsg1);
    } else {

        unsigned long int  largestInt = 4294967295; // 2^32
        bool evaluated = false;
        int i = 0;
        unsigned long int sum = 0;

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
    // Error messages
    std::string errmsg1 = "Must choose positive starting & finishing term"
                          "numbers!";

    std::string errmsg2 = "Must choose a finishingTermNumber >= "
                          "startingTermNumber";


    if (startingTermNumber <= 0 || finishingTermNumber <= 0) {
        throw std::runtime_error(errmsg1);
    } if (startingTermNumber > finishingTermNumber) {
        throw std::runtime_error(errmsg2);
    } if (startingTermNumber == finishingTermNumber) {
        unsigned long int k = startingTermNumber - 1;
        double res = pow(-1., k) / (2 * k + 1);

        return res;

    } else {
        double res = 0;
        for (unsigned long int k = startingTermNumber - 1;
             k < finishingTermNumber;
             k++) {

            res += pow(-1., k) / (2 * k + 1);
        }
        return res;
    }
}


//-----------------------------------------------------------------------------
double EvaluatePiUsingOpenMP(unsigned long int numberOfElements)
{
    std::string errmsg = "Must select a positive number of elements";

    if (numberOfElements <= 0) {
        throw std::runtime_error(errmsg);
    } else {
        int k;
        double res = 0;

        #pragma omp parallel private(k), reduction(+:res)
        {
            #pragma omp for
            for (k = 0; k < numberOfElements; k++) {
                res += pow(-1., k) / (2 * k + 1);
            }
        }

        return res*4;
    }
}

} // end namespace

