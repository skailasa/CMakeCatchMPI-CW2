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

TEST_CASE( "4. OpenMP Pi Test", "[CW2]" ) {

    // Expected error messages
    std::string errmsg = "Must select a positive number of elements";

    SECTION("Check that we can handle invalid number of terms") {
        bool thrown = false;
        try {
            ccmpi::EvaluatePiUsingOpenMP(0);
        } catch(std::exception &e) {
            REQUIRE(std::string(e.what()) == errmsg);
            thrown=true;
        }
        REQUIRE(thrown);
    }

    SECTION("Check that we get convergence to pi") {
        double expected = 3.14159; // pi to 5 dp
        double res = ccmpi::EvaluatePiUsingOpenMP(1000);

        // Check for convergence with error of 1%
        REQUIRE(res == Approx(expected).epsilon(0.01));
    }
}


