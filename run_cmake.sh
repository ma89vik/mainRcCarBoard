#!/bin/bash

export TOOLCHAIN_PATH="/c/Program Files (x86)/GNU Arm Embedded Toolchain/9 2020-q2-update"
export APP_SIGN_PRIVATE_KEY=$(cat src/private.pem)


rm -rf build
mkdir build

pip3 install -r requirements.txt
cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake ..
cmake --build . 