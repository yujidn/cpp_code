#!/bin/sh

cmake CMakeLists.txt
make

./MaxMin
echo
./Memory
echo
./Reference
echo
./RepeatCalc
g++ -O2 RepeatCalc.cpp -o RepeatCalcOpt2
./RepeatCalcOpt2
echo
./RepeatNew
echo
./Terminate

