#!/bin/sh

cmake CMakeLists.txt
make

./Accuracy       
echo
./Arithmetic     
echo
./Bitwise        
echo
./Factorization  
echo
./Mod            
echo
./Mathematics    
echo
./Variance
