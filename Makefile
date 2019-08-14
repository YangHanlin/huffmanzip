# This Makefile will automatically detect OS and take appropriate measures.

CC = g++
ADDITIONAL_FLAGS = -std=c++17

PROGRAM = huffmanzip
OS_TYPE = UNKNOWN

ifeq ($(OS), Windows_NT)
	OS_TYPE = WIN32
else
	UNAME = $(shell uname -s)
	ifeq ($(UNAME), Linux)
		OS_TYPE = LINUX
	endif
	ifeq ($(UNAME), Darwin)
		OS_TYPE = OSX
	endif
endif

ifeq ($(OS_TYPE), WIN32)
	EXECUTABLE = $(PROGRAM).exe
else
	EXECUTABLE = $(PROGRAM)
endif

ifeq ($(OS_TYPE), WIN32)
	REMOVE = del
else
	REMOVE = rm
endif

$(EXECUTABLE): CompressCore.o huffmanzip.o Settings.o Util.o
	$(CC) -o $@ $^ $(ADDITIONAL_FLAGS)

CompressCore.o: CompressCore.cpp CompressCore.h BinaryTree.h BinaryTree.ipp Settings.h Util.h
	$(CC) -o $@ CompressCore.cpp -c $(ADDITIONAL_FLAGS)

huffmanzip.o: huffmanzip.cpp Settings.h Util.h CompressCore.h BinaryTree.h BinaryTree.ipp
	$(CC) -o $@ huffmanzip.cpp -c $(ADDITIONAL_FLAGS)

Settings.o: Settings.cpp Settings.h Util.h
	$(CC) -o $@ Settings.cpp -c $(ADDITIONAL_FLAGS)

Util.o: Util.cpp Util.h Settings.h
	$(CC) -o $@ Util.cpp -c $(ADDITIONAL_FLAGS)

.PHONY: clean clean-target

clean:
	-$(REMOVE) CompressCore.o huffmanzip.o Settings.o Util.o

clean-target:
	-$(REMOVE) $(EXECUTABLE)
