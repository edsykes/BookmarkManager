#!/bin/bash

make.exe clean -j400
echo start qmake
qmake ./BookmarkManager.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"
echo create make file
make.exe -n -j4

