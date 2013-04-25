#!/bin/sh

make clean
make
sudo cp src/libcspec.a /usr/local/lib
sudo cp inc/* /usr/local/include
