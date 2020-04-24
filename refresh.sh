#!/bin/bash

# This script will ensure the starting files are up-to-date in the current branch 
# 
# It does this by fetching the upstream repository (the one we control) and rebasing
# on top of it. If you have already modified these starting files then you may need
# to resolve some conflicts. If you do need to resolve conflicts you will need to
# force push afterwards.
#
# You should run this script at the start of an exercise and if told to do so. 
#
<<<<<<< HEAD
# This script can now be used to refresh a single file e.g.
# ./refresh.sh refresh.sh
# will update this script
#
=======
>>>>>>> Add scripts and README
# Author: Giles Reger

# find tag name
BRANCH=$(git branch | grep "\*" | cut -d ' ' -f 2)

<<<<<<< HEAD
# In case upstream was previously added wrongly, just delete and re-add 
git remote remove upstream
git remote add upstream https://gitlab.cs.man.ac.uk/mbaxjgr2/comp26120_base.git
=======
# The remote upstream should already be added in your repository but if it is
# not there you can add it by running
# git remote add upstream https://gitlab.cs.man.ac.uk/mbaxjgr2/comp26120-base
>>>>>>> Add scripts and README

# Get any upstream changes
git fetch upstream

<<<<<<< HEAD
# If no file given just merge full branch 
if [ -z $1 ]; then
  git merge upstream/"${BRANCH}"
else
  git checkout upstream/"${BRANCH}" $1
fi
=======
# Rebase on top of them (apply them before any local changes)
git rebase upstream/"${BRANCH}"

# This will diverge from origin so force push
git push -f origin "${BRANCH}"
>>>>>>> Add scripts and README
