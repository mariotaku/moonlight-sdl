#!/bin/bash

TOPDIR=$(git rev-parse --show-toplevel)

if [ $TOPDIR != $PWD ]; then
    echo "Please invoke this script in project root directory"
    return 1
fi

echo "Update submodules"
git submodule update --init --recursive

echo "Setup environment"
. /opt/webos-sdk-x86_64/1.0.g/environment-setup-armv7a-neon-webos-linux-gnueabi

echo "Project configuration"
if [ ! -d build ]; then
    mkdir build
fi

cd build
cmake .. -DTARGET_WEBOS=ON -DCMAKE_BUILD_TYPE=Debug

echo "Start build"
cmake --install .
cmake --build . --target webos-package-moonlight