#!/bin/bash

make.exe clean -j400
echo print current directory
pwd
echo go to parent
cd ..
echo print parent
pwd
ls
echo go to BookmarkManager and print
cd BookmarkManager
ls
echo start qmake
qmake ./BookmarkManager.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"
echo list files post qmake
ls
echo create make file
make.exe -n -f ./Makefile qmake_all
echo make command is $(MAKE) 
echo starting the final build
cd D:/a/BookmarkManager/BookmarkManager
echo cat the debug make file
cat Makefile.Debug
pwd
ls
echo start make
C:/ProgramData/Chocolatey/lib/mingw/tools/install/mingw64/bin/mingw32-make -n -f Makefile.Debug

#make.exe -n -j4

