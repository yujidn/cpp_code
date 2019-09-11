#!/bin/sh

cmake CMakeLists.txt
make

./memory       
echo
./pipline     
echo
g++ -mavx analined.cpp -o analined
./analined

