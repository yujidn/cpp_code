#!/bin/sh

cmake CMakeLists.txt
make

./GetterSetter
echo 
./LoopStyle
g++ LoopStyle.cpp -o loopstyle_no_opt
./loopstyle_no_opt
echo 
./Reference
echo 

