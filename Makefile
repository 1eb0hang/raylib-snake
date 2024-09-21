
LIBS= -lraylib
LIB_DIR = "-Llibs/raylib-cpp-master/build/_deps/raylib-build/raylib/"
INCLUDES = "-Ilibs/raylib-cpp-master/build/_deps/raylib-build/raylib/include/"

OBJECTS = `ls src | grep cpp | sed "s/.*cpp/build\/&.o/" | sed "s/.cpp//"`

all:main

clean:
	rm -rf build
	mkdir build

build/main.o : main.cpp
	g++ -c -o ./build/main.o ${INCLUDES} main.cpp

main : build/main.o
	g++ -o ./build/main ./build/main.o ${LIB_DIR} ${LIBS}

run:
	make
	./build/main
