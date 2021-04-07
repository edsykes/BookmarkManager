#!/bin/bash

make.exe clean -j400
pwd
cd ..
pwd
ls
cd BookmarkManager
ls
qmake ./BookmarkManager.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"
ls
make.exe -f ./Makefile qmake_all
echo make command is $(MAKE) -f $(MAKEFILE).Debug
echo starting the final build
cd D:/a/BookmarkManager/BookmarkManager
cat Makefile
make.exe -j4

