#!/usr/bin/zsh

cd ./ServiceProvider
make clean
make

cd ../Application
make clean
make
