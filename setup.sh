#! /bin/bash 

if [[ ! -d libs/raylib-cpp/build ]] 
then
    mkdir libs/raylib-cpp/build
    cd libs/raylib-cpp/build 
    $(bash -c cmake ..) || pkill bash
    make
    cd ../../..
fi

if [[ ! -f libs/raylib-cpp/build/_deps/raylib-build/raylib/libraylib.a ]]
then
    cd libs/raylib-cpp/build 
    $(bash -c cmake ..) || pkill bash
    make
    cd ../../..
fi

