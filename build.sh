#!/bin/sh
#------------------------------------------------------------------------------------
# The scope of this script is to interface with the build system to build the project
# This scripts accepts two optinal arguments: 1. The build directory 2. The source directory
# Written by James Little <james@jameslittle.org>
#------------------------------------------------------------------------------------

###################################
# Default Variables
###################################
DEFAULT_BUILD_DIR="build"
DEFAULT_SRC_DIR="src"

###################################
# Input Arguments
###################################
BUILD_DIR=$1
SRC_DIR=$2
THIS_DIR="${PWD}"

###################################
# Functions
###################################
function now() {
  echo `date '+%m-%d-%Y %H:%M:%S'`
}

function println() {
	echo "[$(now)]: $1"
}

#------------------------------------------------------------------------------------
echo "****** STARTING BUILD SCRIPT ******"
println "Current Working Directory: $THIS_DIR"
println "Additional CFLAGS: $ANY_CFLAGS"
println "\t=> Additional CFLAGS can be set by exporting ANY_CFLAGS='your flags here'"
println "Additional MAKE Flags: $ANY_MAKE_FLAGS"
println "\t=> Additional MAKE Flags can be set by exporting ANY_MAKE_FLAGS='your flags here'"

###################################
# Setting up Build DIR
###################################


if [ -z "$BUILD_DIR" ]; then
	println "No build directory given, assuming $THIS_DIR/$DEFAULT_BUILD_DIR/"
	BUILD_DIR=$DEFAULT_BUILD_DIR
fi	

b_dir="$THIS_DIR/$BUILD_DIR/"
println "Using build directory $b_dir"

mkdir -p $b_dir #create dir if not exists

###################################
# Getting up Source DIR
###################################

if [ -z "$SRC_DIR" ]; then
	println "No source directory given, assuming $THIS_DIR/$DEFAULT_SRC_DIR/"
	SRC_DIR=$DEFAULT_SRC_DIR
fi	
s_dir="$THIS_DIR/$SRC_DIR/"
println "Using source directory $s_dir"

# might want to check if the source directory exists, if not stop here?

###################################
# Running CMAKE
###################################
println "Running CMake"
if [ -z "$ANY_CFLAGS" ]; then
	println "\t=> No additional CFLAGS given"
	cmake -B$b_dir -S$s_dir
else
	cmake -B$b_dir -S$s_dir "$ANY_CFLAGS"
fi

cmake_r=$?

if [ $cmake_r -ne 0 ]; then
	println "CMake Failed. Status Code: $cmake_r"
	exit $cmake_r
fi

###################################
# Running MAKE
###################################
println "Running Make"

cd $BUILD_DIR
make $ANY_MAKEFLAGS
make_r=$?

if [ $make_r -ne 0 ]; then
	println "Failed to Compile. Status Code: $make_r"
	exit $make_r
fi

println "Build Finished!"