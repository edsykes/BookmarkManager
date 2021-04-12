#!/bin/bash

mkdir deployment
windeployqt release/BookmarkManager.exe --dir deployment
cp release/BookmarkManager.exe deployment