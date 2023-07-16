clean:
	rm -rf build
	rm -rf CMakeFiles
	rm -rf _deps
	mkdir build

init:
	test -d build || mkdir build
	cmake -S . -B build
	cmake --build build

build:
	cmake --build build

run:
	cmake --build build
	./build/pizone
