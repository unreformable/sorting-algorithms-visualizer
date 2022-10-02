#!/bin/bash
# Bash script for quick compile and run executable

cd ..
mkdir build
cd build/
cmake ..
make
./sorting-algorithms-visualizer