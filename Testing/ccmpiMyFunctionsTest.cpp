/*=============================================================================

  CMAKECATCHMPI: A software package to demo MPI with CMake, CTest and Catch.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include <iostream>
#include "catch.hpp"
#include "ccmpiCatchMain.h"
#include "ccmpiMyFunctions.h"

using namespace std;

TEST_CASE( "1. FillSeries Test", "[CW2]" ) {
    // Expected error messages
    std::string errmsg1 = "Invalid number of values, must pre-allocate an array"
                          "with at least 1 element";

    std::string errmsg2 = "Too many values! Must pass in array with between 1"
                          "and 2^32 values";


    SECTION("Check that we can handle empty arrays") {
        unsigned long int vals[0];
        bool thrown = false;
        try {
            ccmpi::FillSeries(vals, 0);
        } catch (const std::exception &e) {
            REQUIRE(std::string(e.what()) == errmsg1);
            thrown=true;
        }
        REQUIRE(thrown);
    }

    SECTION("Check that we can handle arrays that are too long") {
       // Mock array, can't allocate int arr[4294967296] on most machines
       // N.B. 2^(32) + 1 = 4294967296
       unsigned long int vals[0];
       bool thrown = false;
        try {
            ccmpi::FillSeries(vals, 4294967296);
        } catch (const std::exception &e) {
            REQUIRE(std::string(e.what()) == errmsg2);
            thrown=true;
        }
        REQUIRE(thrown);
    }

    SECTION("Check that we can handle arrays of acceptable length") {
        unsigned long int vals[3] = {10, 11, 12};
        ccmpi::FillSeries(vals, 3);

        for (int i=0; i<3; i++) {
            REQUIRE(vals[i] == i);
        }
    }
}


TEST_CASE( "2. SumSeries Test", "[CW2]" ) {

    // Expected error messages
    std::string errmsg1 = "Invalid number of values, must pre-allocate an array"
                          "with at least 1 element";

    std::string errmsg2 = "Sum total too high, integer overflow!";


    SECTION("Check that we can handle empty arrays") {
        unsigned long int vals[0];
        bool thrown = false;
        try {
            ccmpi::SumSeries(vals, 0);
        } catch (const std::exception &e) {
            REQUIRE(std::string(e.what()) == errmsg1);
            thrown=true;
        }
        REQUIRE(thrown);
    }

    SECTION("Check that we can handle sums that result in numerical overflow") {
        unsigned long int vals[2]={1, 4294967295};
        bool thrown = false;
        try {
            ccmpi::SumSeries(vals, 2);
        } catch (const std::exception &e) {
            REQUIRE(std::string(e.what()) == errmsg2);
            thrown=true;
        }
    }

    SECTION("Check that we can handle arrays which will not overflow") {
        unsigned long int expected = 10;
        unsigned long int vals[4]={1, 2, 3, 4};
        auto res = ccmpi::SumSeries(vals, 4);

        REQUIRE(res == expected);
    }
}


TEST_CASE( "3. EvaluateGregoryLeibnizSeries Test", "[CW2]" ) {
}
