#!/bin/sh

make
sudo make install
cd examples/sample
cspec
cd ../skip
cspec
