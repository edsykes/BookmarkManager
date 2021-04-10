#!/bin/bash

make.exe clean -j400
echo start qmake
qmake ./BookmarkManager.pro -spec win32-g++ "CONFIG+=release" "CONFIG+=qml_release"
echo create make file
make.exe -n -j4
ls
cd debug
echo debug dir contents
ls
cd ../release
pwd
echo release dir contents
ls