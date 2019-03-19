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


TEST_CASE( "1. FillSeries Test", "[CW2]" ) {

    // Expected error messages
    std::string errmsg = "Invalid number of values, must choose between 1 and "
                         "100000. i.e. between 1b and 800kb worth of data.";

    // Test arrays to fill
    unsigned long int valsmin[0];
    unsigned long int valsmax[100001];
    unsigned long int vals[2] = {100, 100};

    SECTION("Test that we correctly handle min list sizes") {
        bool thrown = false;
        try {
            ccmpi::FillSeries(valsmin, 0);
        } catch(const std::exception &e) {
            REQUIRE(std::string(e.what()) == errmsg);
            thrown = true;
        }
        REQUIRE(thrown);
    }

    SECTION("Test that we correctly handle max list sizes") {
        bool thrown = false;
        try {
            ccmpi::FillSeries(valsmax, 100001);
        } catch(const std::exception &e) {
            REQUIRE(std::string(e.what()) == errmsg);
            thrown = true;
        }
        REQUIRE(thrown);
    }

    SECTION("Test that we can correctly fill an acceptable array") {
        for (int i=0; i<2; i++) {
            ccmpi::FillSeries(vals, 2);
            REQUIRE(vals[i] == i);
        }
    }

}

TEST_CASE( "2. SumSeries Test", "[CW2]" ) {
}

TEST_CASE( "3. EvaluateGregoryLeibnizSeries Test", "[CW2]" ) {
}
