#!/bin/sh

cmake CMakeLists.txt
make

./Output1char
echo
./Output1charLF
echo
./Output1Line
echo
./Output1LineLF
echo
./OutputAll
echo
./OutputAllLF
echo
./OutputBinary
echo
./Input1char
echo
./Input1Line
echo
./InputAll
echo
./InputBinary
