# CYS-bonds
Uses GEMS/GMML to figure out which CYS residues should be bonded to each other based on distance, then writes tleap bonds commands.

## Prerequisites

You'll need GEMS and GMML. See here for installation instructions: http://glycam.org/docs/gems/download-and-install/.

2017-06-28 you'll need the gmml-dev branch:

git clone -b gmml-dev https://github.com/GLYCAM-Web/gmml.git gmml

### Installation of CYS-bonds
export GEMSHOME=<Your Path To Gems > # eg: export GEMSHOME=/home/oliver/Programs/gems

qmake

make

### Usage

You must provide a protein 3D structure

./CYS-bonds protein.pdb

### Warning

Crashes out if your input file does not exist or you do not provide one, but if you've read this far that shouldn't be happening..
