CMakeCatchMPI - CW2
-------------------

[![Build Status](https://travis-ci.org/MattClarkson/CMakeCatchMPI.svg?branch=master)](https://travis-ci.org/MattClarkson/CMakeCatchMPI)
[![Build Status](https://ci.appveyor.com/api/projects/status/5pm89ej732c1ekf0/branch/master)](https://ci.appveyor.com/project/MattClarkson/cmakecatchmpi)


Purpose
-------

In this coursework we demonstrate the usage of OpenMP/MPI through some toy
examples.


Build
-----

Out of source build, with both OpenMP and OpenMPI.

##### Linux

```bash
# create build directory and generate build files
mkdir ../build && cd ../build
ccmake ../CMakeCatchMPI-CW2

make

```

##### MacOs

Ensure that you have downloaded OpenMP and MPI

```bash
# create build directory
mkdir ../build && cd ../build

# generate build files, ensure that you are using correct compiler flags
ccmake ../CMakeCatchMPI-CW2/ -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang

make
```


Run MPI tests
-------------

To run tests that use MPI use the following command

```bash
mpiexec -n <number_of_cores> <test_binary>

# for example
mpiexec -n 2 ./ccmpiTriangleNumberSeriesMPITest 

```

