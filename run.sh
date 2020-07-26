#!/bin/bash

cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake ..
cmake --build . 