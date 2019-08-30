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
echo
./RepeatNew
echo
./Terminate

