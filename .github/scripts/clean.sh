#!/bin/bash

make.exe clean -j400
pwd
ls
qmake BookmarkManager.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"
ls
make.exe -f Makefile qmake_all
make.exe -j4

