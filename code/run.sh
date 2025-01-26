#!/bin/bash

mkdir build &> /dev/null

cd build || exit 1

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release .. >> /dev/null
if [ $? -ne 0 ]; then
    echo "CMake configuration failed."
    exit 1
fi

ninja

if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

cd .. || exit 1

./build/bin/indproj
