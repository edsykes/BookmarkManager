#!/bin/bash

mkdir deployment-$1
echo $BUILD_NUMBER
windeployqt release/BookmarkManager.exe --dir deployment-$1
cp release/BookmarkManager.exe deployment-$1