
INCLUDES = -I/home/wethinkcode/Dev/cpp/raylib/snake/libs/raylib/build/raylib/include
LIB_DIR = -L/home/wethinkcode/Dev/cpp/raylib/snake/libs/raylib/build/raylib/
LIBS = -lraylib

clean:
	rm -rf build
	mkdir build

build/main.o : main.cpp
	cd build && g++ -c -o main.o ${INCLUDES} ../main.cpp

main : build/main.o
	cd build && g++ -o main main.o ${LIB_DIR} ${LIBS}
