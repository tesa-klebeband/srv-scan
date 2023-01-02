CPP = g++
LINKER = -lpthread

all: prep srv-scan

prep:
	mkdir -p build

srv-scan: src/*.cpp
	$(CPP) $^ $(LINKER) -O1 -o build/$@
