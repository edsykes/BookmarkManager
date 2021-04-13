#!/bin/bash

mkdir deployment
windeployqt release/BookmarkManager.exe --dir deployment-$BUILD_NUMBER
cp release/BookmarkManager.exe deployment-BUILD_NUMBER