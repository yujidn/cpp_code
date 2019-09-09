#!/bin/sh

cmake CMakeLists.txt
make

./Reference
echo
./STLAddress
echo
./STLEmplace
echo
./STLEmplaceBack
echo
./STLErase
echo
./STLInsert
echo
./STLIteration
echo
./STLPushBack
echo
./STLPushFront
echo
./STLSearch
echo
./STLsizeof
echo
./STLSort
echo
./STLStable_sort

