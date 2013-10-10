#!/bin/sh

sudo make uninstall
sudo make clean
./bootstrap
./configure
./remake.sh
