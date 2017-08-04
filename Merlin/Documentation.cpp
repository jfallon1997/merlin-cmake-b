/*! \mainpage Merlin Index
 *
* \section intro_sec Introduction
*
* MERLIN is a C++ accelerator physics library, which has been extended to be
* used for large scale proton collimation simulations, with the aim of providing
* an accurate simulation of the Large Hadron Collider (LHC) collimation system.
* MERLIN is used to simulate the nominal optics at 7 TeV of the LHC in order to
* generate loss maps, using a thick lens tracking model. 
*
* \section install_sec Installation
*
* ## Building with `cmake`
* 
* Create a build directory, and `cd` into it.
* 
* To configure, run:
* 
*     cmake -DCMAKE_BUILD_TYPE=Release $PATH_TO_MERLIN_DIR
* 
* For example if you created the build directory inside the Merlin directory:
* 
*     cmake -DCMAKE_BUILD_TYPE=Release ..
* 
* To interactively configure, run:
* 
*     ccmake $PATH_TO_MERLIN_DIR
* 
* To build run `make` or, to build with multiple threads (e.g. 4 threads)
* `make -j4`
* 
* 
* The `libmerlin.so` library will be built in the build directory.
* 
* ## Running Tests
* 
* Enable tests with
* 
*     cmake -DBUILD_TESTING=ON
*     make
*     make test
* 
* **Warning, the OS specific instructions are probably out of date and unlikely
* to work**
*
* ## Linux
*
* The current method is to use `cmake` to build makefiles for Merlin
*
* 1. Make a `build` folder outside the folder where Merlin was extracted.
* 
* 2. run `cmake /path/to/merlin/folder`
*
* 3. run `ccmake /path/to/buildfolder`
*
* 4. Pick the options you wish to use.
*
* 5. run `make -j < ncpu >`
*
* 6. This will make the merlin library
*
* ## Windows
* Needs to be updated.
*
* ## OSX
* The optimal way to use Merlin on OSX is to get cmake to generate build files for Xcode.
* This of course requires that xcode is installed.
* By default cmake will generate unix makefiles.
* To generate Xcode files the appropriate generator must be specified when using cmake as:
*
*     cmake -G Xcode`
*
* One can then run:
*
*     xcodebuild
*
* which will compile merlin.
* Other options exist such as `xcodebuild clean`, which will clear out built files.
*
* ## About
*
* \author Nick Walker
* \author Dirk Kruecker
* \author Andy Wolski
* \author Roger Barlow
* \author Adina Toader
* \author James Molson
* \author Haroon Rafique
* \author Sam Tygier
* \version 5.02
* \date 2001-2017
*/
