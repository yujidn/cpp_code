#!/bin/sh

cmake CMakeLists.txt
make

./MatMulti
echo
./MatMultiNotAligned
echo
g++ -O2 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mfma MatMulti.cpp -o MatMulti-opt2
g++ -O2 -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mfma MatMultiNotAligned.cpp -o MatMultiNotAligned-opt2
echo
./MatMulti-opt2
echo
./MatMultiNotAligned-opt2
echo
./SIMDalignedByAllocator
echo
./SIMDArithmetic
echo
./SIMDArray
echo
./SIMDSample
echo
./SIMDsegmentationFault
echo
./SIMDUnion
echo
