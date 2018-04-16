#!/bin/bash
#Compile and Run harry.cpp
./find.sh
echo "Compiling Files...."
g++ harry.cpp -isystem /usr/include/boost -L/usr/include/ -lboost_system `pkg-config --cflags --libs opencv` -std=gnu++11 -pthread -o test
echo "Just created executable test ...."
echo "Running ..."
./test
