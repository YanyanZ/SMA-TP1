#! /bin/bash

cd src/market/server
./server 8080 &
cd ../../..
./simulation
killall server