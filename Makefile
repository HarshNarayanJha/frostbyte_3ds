.PHONY: all clean prepare build

all: clean prepare build

clean:
	rm -rf build

prepare:
	cmake -DCMAKE_TOOLCHAIN_FILE=DevkitArm3DS.cmake -S . -B build

build:
	cmake --build build
