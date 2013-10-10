#!/bin/sh

make
sudo make install
cspec -I./inc
