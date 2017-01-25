all:
	git submodule update --init --recursive
	mkdir -p build
	cd build && cmake .. && make -j 4 && make package
