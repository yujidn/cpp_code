#!/bin/sh

cmake CMakeLists.txt
make

./MatMulti
echo
./MatMultiNotAligned
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
