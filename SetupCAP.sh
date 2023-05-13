#!/bin/bash

####################################################################################################
#
# Source this script to define CAP environment variables used in the build and running of CAP5.0 with root.
# This script assumes the following environment variables are already defined
#
# ROOTSYS             : path to your root installation
# LD_LIBRARY_PATH     : path to dynamic load librairies (including root)
# SHLIB_PATH          : path to shared libraries (including root's)
# LIBPATH             : path to root, pythia and other required libraries
# PYTHONPATH          : path to PYTHON stuff used by root
# CMAKE_PREFIX_PATH   : path to cmake stuff setup by root
# PYTHIA8             : path to the PYTHIA8 install
# PYTHIA8_DIR         : path to the PYTHIA8 install
# PYTHIA8_INCLUDE_DIR : path to the PYTHIA8 install
#
# DataInputPath       : path to the location where large event files will be read from
# DataOutputPath      : path to the location where large event or histogram files will be written to
#
#  The following directory structure is assumed/build
#
#  'pwd'                      : Current directory (where from this script is sourced)
#  'pwd'/build                : Where cmake & make will compile&build APPs
#  'pwd'/documentation        : documentation output (DOXYGEN)
#  'pwd'/src                  : Source code main directory
#  'pwd'/src/AMPT             : Code to read AMPT events.
#  'pwd'/src/Base             : Base classes of the CAP framework.
#  'pwd'/src/BasicGen         : Basic MC generators
#  'pwd'/src/CAPPythia        : Interface to read/write/generate PYTHIA8 events
#  'pwd'/src/Epos             : Code to read EPOS events.
#  'pwd'/src/Exec             : High level analysis (steering) functions.
#  'pwd'/src/Garbage          : Where all ends eventually
#  'pwd'/src/Hijing           : Code to read HIJING events.
#  'pwd'/src/Macros           : Most macros used in CAP
#  'pwd'/src/Math             : Basic math functions.
#  'pwd'/src/NuDyn            : Nudynamics analysis.
#  'pwd'/src/ParticlePair     : (Differential) Particle pair analysis, R2, P2, G2, balance functions, etc.
#  'pwd'/src/ParticleSingle   : (Differential) single particle spectra analysis
#  'pwd'/src/Particles        : All tools relevant to describe particles, events, and analyze them
#  'pwd'/src/Performance      : MC generators to (fast) simulate the performance of detectors
#  'pwd'/src/Plotting         : High level plotting tools and functions
#  'pwd'/src/PtFluc           : Pt fluctuations analysis (in development)
#  'pwd'/src/SubSample        : Basic tools for subsample analysis
#  'pwd'/src/ThermalGas       : Code to carry out hadron gas calculation and event generation.
#  'pwd'/src/Therminator      : CAP implementation of therminator 2
#  'pwd'/src/Tools            : Code to carry various stat studies.
#  'pwd'/src/Urqmd            : Code to read UrQMD events.
#
#  'pwd'/Clusters             : Scripts to launch "cluster" (grid) jobs
#  'pwd'/Clusters/WSUGrid     : Scripts to launch slurm jobs on the Wayne State grid
#  'pwd'/Db                   : Master CAP database directory
#  'pwd'/Db/ParticleData      : Particle speices and decay DB
#  'pwd'/Db/Therminator       : multiplicity files used and produced by therminator
#  'pwd'/projects             : configuration files (*.ini) used in various projects.
#
#   Notes:
#
# The build and run CAP5.0, you need to have the following tools
#
#   cmake    :  available (free) from: https://cmake.org/download/
#   make     :  indigenous to all LINUX, UNIX, and MacOS platforms
#   root     :  available from the CERN root distribution or from various sources
#   PYTHIA8  :  optional, available from https://pythia.org
#
# To build and run the code, you will need a version root that works on your machine. Given root uses
# dynamic load libraries, it is sufficient (usually) to get a recent binary of root for your
# platform. Alternatively, you can also use a version built from the source. Note: EG libraries
# are no longer required with CAP5.0.
#
# The cmake code assumes root is located at $ROOTSYS and
# that the $LD_LIBRARY_PATH, $SHLIB_PATH, $PYTHONPATH,
#
# To build the code after download
#    cd  CAP5.0          : i.e., whereever you have located your download version of CAP5.0
#    rm  -r -f build     : to start with a clean slate
#    source SetupCAP.sh  : source this file to configure the environment variables.
#    cd build            : swith to the build dir
#    cmake ../src        : to configure the build with cmake
#    make -j# install    : to build the code. # is a number corresponding to the number of
#                        : of CPU cores dedicated to the build -- more cores means a faster build
#
# See the src/Macros subdirectory for a list of instructions and commands to run high level
# analyses.
#
#
####################################################################################################
echo " "
echo " "
echo "========================================================================================"
echo " SetupCAP starting!"
echo "========================================================================================"
echo " "
echo " Creating build, lib, and bin folders (if needed)."
echo "========================================================================================"
if [[ ! (-d build) ]]
then
  mkdir build;
fi
if [[ ! (-d lib) ]]
then
  mkdir lib;
fi
if [[ ! (-d bin) ]]
then
  mkdir bin;
fi

echo " "
echo " Defining environment variables"
echo "========================================================================================"
export CAP_ROOT=`pwd`
export CAP_SRC="$CAP_ROOT/src/"
export CAP_BIN="$CAP_ROOT/bin/"
export CAP_LIB="$CAP_ROOT/lib/"
export CAP_INPUT_DATA="$DataInputPath"
export CAP_OUTPUT_DATA="$DataInputPath"
export CAP_INPUT_HISTOS="$DataInputPath"
export CAP_OUTPUT_HISTOS="$DataInputPath"
export CAP_CONFIG="$CAP_ROOT/projects/"
export CAP_DATABASE="$CAP_ROOT/DB/"
export CAP_GRID="$CAP_ROOT/Grid/"
export CAP_GRID_WSU="$CAP_ROOT/Grid/WSU/"
export CAP_MACROS="$CAP_SRC/Macros/"
export PATH="$CAP_BIN:$PATH"
export DYLD_LIBRARY_PATH="$CAP_LIB:$DYLD_LIBRARY_PATH"
export LD_LIBRARY_PATH="$CAP_LIB:$LD_LIBRARY_PATH"

echo " "
echo " Source code                    : " $CAP_SRC
echo " CAP Database                   : " $CAP_DATABASE
echo " Job configuration files (.ini) : " $CAP_CONFIG
echo " Scripts (.sh) grid files       : " $CAP_GRID
echo " root Macros                    : " $CAP_MACROS
echo " Default data input path        : " $CAP_INPUT_DATA
echo " Default data output path       : " $CAP_OUTPUT_DATA
echo " Default histogram input path   : " $CAP_INPUT_HISTOS
echo " Default histogram output path  : " $CAP_OUTPUT_HISTOS
echo " "
echo " Build instructions"
echo "========================================================================================"
echo " To build CAP5.0, execute the following commands"
echo " cd build"
echo " cmake ../src"
echo " make -j8 install"
echo " "
echo " Run instructions"
echo "========================================================================================"
echo " To run CAP5.0, call root with one the macros in " $CAP_MACROS
echo " "
echo "========================================================================================"
echo " Setup_CAP completed!"
echo "========================================================================================"
