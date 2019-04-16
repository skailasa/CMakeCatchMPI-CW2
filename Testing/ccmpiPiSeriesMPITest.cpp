/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "ccmpiCatchMain.h"
#include "ccmpiMyFunctions.h"
#include <iostream>
#include <mpi.h>


TEST_CASE( "5. MPI Pi Test", "[CW2]" ) {

  int rank = 0;
  int size = 0;
  double sum = 0;
  double pi = 0;
  int N = 1000;
  unsigned long int indexes[2];

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  std::vector<std::pair<unsigned long int, unsigned long int> > v
          = ccmpi::GetVectorOfSeriesIndexPairs(size, N);

  /////////////////////////////////////////////////////////////////////////////
  // Start of your code
  /////////////////////////////////////////////////////////////////////////////

  // Calculate Gregory-Leibniz Series terms
  sum = ccmpi::EvaluateGregoryLeibnizSeries(v[rank].first, v[rank].second);

  MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  /////////////////////////////////////////////////////////////////////////////
  // End of your code
  /////////////////////////////////////////////////////////////////////////////

  // The EvaluateGregoryLeibnizSeries calculates pi/4.0.
  pi *= 4.0;

  std::cout << "Process " << rank << ", computed sum=" << sum << ", pi=" << pi << std::endl;
  if (rank == 0)
  {
    // Check that we get convergence to within 1% of value
    REQUIRE(pi == Approx(3.14159).epsilon(0.01));
  }
  else
  {
    // i.e. non-root nodes won't have the correct answer.
    REQUIRE(pi == Approx(0.0));
  }
}
