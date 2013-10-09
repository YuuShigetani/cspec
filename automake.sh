#!/bin/sh

make clean
./configure
make
sudo cp src/libcspec.a /usr/local/lib
sudo cp inc/* /usr/local/include
cd examples/sample
./sample
