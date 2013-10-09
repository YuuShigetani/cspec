#!/bin/sh

sudo make uninstall
sudo make clean
./autogen.sh
./configure
./remake.sh
