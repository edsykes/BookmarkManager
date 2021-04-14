#!/bin/bash

mkdir deployment
echo $BUILD_NUMBER
windeployqt release/BookmarkManager.exe --dir deployment
cp release/BookmarkManager.exe deployment