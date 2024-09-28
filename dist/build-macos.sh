#!/bin/sh

cd ..

git submodule update --init

mkdir build
cd build

cmake .. -DCMAKE_INSTALL_PREFIX=. -DCMAKE_BUILD_TYPE=Release

cmake --build . -j --target install

cd ..

mkdir app
mkdir app/licenses

cp ./build/bex-app/* ./app
cp LICENSE ./app/licenses/bex-license.txt
cp deps/googletest/LICENSE ./app/licenses/googletest-license.txt
