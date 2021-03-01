#!/bin/bash          

#delete old result
rm power_output.txt

#compile
echo Compiling..
gcc rev_pow.c -o rev_pow
echo done.

#run
echo Running C program..
./rev_pow 

#test script
echo Running test..
python power_test.py 
