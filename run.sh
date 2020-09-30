#!/bin/bash

rm -rf build
mkdir build

export TOOLCHAIN_PATH=/home/marius/toolchains/gcc-arm-none-eabi-9-2020-q2-update
export APP_SIGN_PRIVATE_KEY=$(cat src/private.pem)

pip3 install -r requirements.txt
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake ..
cmake --build . 