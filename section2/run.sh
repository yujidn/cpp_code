#!/bin/sh

cmake CMakeLists.txt
make

./memory       
echo
./pipline     
