
Merlin cmake
------------

This is the cmake branch of Merlin. An eclipse orientated branch also exists. Both branches should share the same Merlin library files (in the directory `Merlin`)

Merlin Documentation
====================

You can find `doxygen` generated documentation for Merlin at the webpage [https://github.com/jfallon1997/merlin-cmake-b/doxygen/generated-docs/html](https://github.com/jfallon1997/merlin-cmake-b/doxygen/generated-docs/html)


Building with cmake
===================

Create a build directory, and cd into it.

To configure, run:
cmake -DCMAKE_BUILD_TYPE=Release $PATH_TO_MERLIN_DIR
for example if you created the build directory inside the Merlin directory,
cmake -DCMAKE_BUILD_TYPE=Release ..

To interactivly configure, run:
ccmake $PATH_TO_MERLIN_DIR

To build run:
make
or, to build with multiple threads, e.g. 4 threads
make -j4


The libmerlin.so library will be built in the build directory.

Running Tests
=============

Enable tests with
cmake -DBUILD_TESTING=ON

Then run:
make
make test








