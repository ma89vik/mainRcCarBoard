#!/bin/bash

rm -rf build
mkdir build

export TOOLCHAIN_PATH=/home/marius/gcc-arm-none-eabi-9-2020-q2-update/
pip3 install -r requirements.txt
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake ..
cmake --build . 