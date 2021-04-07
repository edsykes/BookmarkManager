#!/bin/bash

make.exe clean -j400
pwd
ls
qmake BookmarkManager.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"
ls
make.exe -f Qt_5_15_2_MinGW_64_bit-Debug/Makefile qmake_all

