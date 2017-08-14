# Merlin `cmake`

This is the `cmake` branch of Merlin. An eclipse orientated branch also exists. Both branches should share the same Merlin library files (in the directory `Merlin`)

## Merlin Documentation

You can find `doxygen` generated documentation for Merlin by running `doxygen Merlin.Doxyfile` in the `doxygen` directory, and opening the webpage `doxygen/generated-docs/html/index.html`.  

## Building with `cmake`

Create a build directory, and `cd` into it.

To configure, run:

    cmake -DCMAKE_BUILD_TYPE=Release $PATH_TO_MERLIN_DIR

For example if you created the build directory inside the Merlin directory:

    cmake -DCMAKE_BUILD_TYPE=Release ..

To interactively configure, run:

    ccmake $PATH_TO_MERLIN_DIR

To build run `make` or, to build with multiple threads (e.g. 4 threads)

    make -j4


The `libmerlin.so` library will be built in the build directory.

## Running Tests

Enable tests with

    cmake -DBUILD_TESTING=ON
    make
    make test

## Source Code to investigate

~~~~~~~~~~~~~~~~~~~~~~
cd merlin-cmake/Merlin
grep -rnohl "TO DO" 
./SMPStdIntegrators.cpp
./TransRFIntegrator.cpp
./SMPBunch.cpp

grep -rnohl "TODO" 
./HollowELensProcess.cpp
./TransRFfield.h
./ProtonBunch.cpp
./InterpolatedApertures.h
./LinearParticleMap.cpp
./MatrixMaps.cpp
./ApertureConfiguration.cpp
./ParticleBunch.cpp

grep -rnohl "to do" 
./Collimator.cpp
./CrabMarker.cpp
./PatchFrame.h
./Marker.cpp
./TMatrixLib.h
./ModelElement.h
./ProtonBunch.cpp
./Bunch.h
./Drift.cpp
./SMPBunch.cpp
./Klystron.h
./BunchFilter.cpp
./HollowElectronLens.cpp
./EMField.cpp
./MagnetMover.cpp
./CollimateParticleProcess.cpp

grep -rnohl "FIX" 
./ScatteringModelsMerlin.cpp
./Marker.cpp
./MADInterface.cpp
./ProtonBunch.cpp
./Marker.h
./RMap.h

grep -rnohl "fix" 
./CollimateParticleProcess.h
./ScatteringModelsMerlin.cpp
./PSmoments.h
./XTFFInterface.cpp
./EquilibriumDistribution.cpp
./SymplecticIntegrators.cpp
./MonitorProcess.h
./TransferMatrix.cpp
./OPFormat.h
./StdIntegrators.cpp
./TransportIntegrators.cpp
./LatticeFunctions.cpp
./MADInterface.cpp
./ProtonBunch.cpp
./Range.h
./ApertureConfiguration.cpp
./MultiNormal.h
./MonitorProcess.cpp
./MADInterface.h
./MVCMatrix.h
./ScatteringModelsMerlin.h
./CollimateParticleProcess.cpp
./ParticleBunch.cpp
./DiffractiveScatter.cpp
./TrackingOutputAV.cpp

~~~~~~~~~~~~~~~~~~~~~~
