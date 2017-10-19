#!/bin/bash
# My first script

echo "Compling Files...."
g++ main.cpp -isystem /usr/include/boost -L/usr/include/ -lboost_system -std=gnu++11 -pthread -o test
echo "Running ..."
./test
