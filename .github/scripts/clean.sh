#!/bin/bash

make.exe clean -j400
pwd
qmake BookmarkManager\BookmarkManager.pro -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"