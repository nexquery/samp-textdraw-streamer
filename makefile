GPP = g++
GCC = gcc
OUTPUT = "TextdrawStreamer.so"
CC_PARAMS = -std=c++11 -c -m32 -fPIC -O3 -w -DLINUX -I ./SDK/amx/

all:
	$(GCC) $(CC_PARAMS) ./SDK/amx/*.h
	$(GPP) $(CC_PARAMS) ./SDK/*.cpp
	$(GPP) $(CC_PARAMS) ./*.cpp
	$(GPP) -m32 -O2 -fshort-wchar -shared -o $(OUTPUT) *.o
	-rm -f *.o
