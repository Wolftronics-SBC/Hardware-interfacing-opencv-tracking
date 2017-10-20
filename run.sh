#!/bin/bash
#Compile and Run main.cpp

echo "Compiling Files...."
g++ main.cpp -isystem /usr/include/boost -L/usr/include/ -lboost_system -std=gnu++11 -pthread -o test
echo "Just created executable test ...."
echo "Running ..."
./test
