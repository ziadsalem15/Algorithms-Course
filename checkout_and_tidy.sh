#!/bin/bash

# This script will call the local tidy.sh script, do a git checkout,  
# and then call refrehs.sh. You need to pass the exercise name
#
# Usage example: ./checkout_and_tidy.sh ex2
#
# The purpose of the script is to help keep your directory tidy between
# exercises. You can, of course, do all of this stuff manually yourself. 
#
# Author: Giles Reger

if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <exercise name>" 
  exit 1
fi

# A cheap test to check that you commit before changing branch
# Note that this won't detect all weird states you can get your
# repository into!
<<<<<<< HEAD
if [ -z "$(git status -uno --porcelain)" ];
=======
if [ -n "$(git status -uno --porcelain)" ];
>>>>>>> Add scripts and README
then
    echo "Getting $1"
    ./tidy.sh
    git checkout $1
    ./refresh.sh
else
    echo "Commit your changes first!"
<<<<<<< HEAD
    git status
=======
    echo git status
>>>>>>> Add scripts and README
fi



