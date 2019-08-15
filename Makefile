# Makefile

# This Makefile is capable to identify different operating systems (Windows,
# Linux and macOS) and take corresponding measures (specify different names of
# executables and the remove commands).

# This variable specifies the name of the C++ compiler.
# The compiler specified must be compatitble with G++-style arguments.
CC = g++

# This variable specifies additional flags (arguments) passed to the compiler.
# Do not remove the default arg '-std=c++17' which specifies the required C++
# 17 standard.
ADDITIONAL_FLAGS = -std=c++17

# This variable specifies the name of the program.
PROGRAM = huffmanzip

# This variable specifies the default OS if Make is not able to detect it, or
# if the OS detected is not Windows, Linux or macOS.
OS_TYPE = UNKNOWN

# The following section detects the type of the operating system by checking
# the built-in variable OS by Make. If the OS is not Windows, check the output
# of 'uname -s' to further tell it is Linux or macOS.
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

# Assign to the variable OS_TYPE in the following line if you would like to
# force it to adopt Windows, Linux or macOS.
# OS_TYPE = WIN32 or LINUX or OSX

# The following section speicfies the name of the executable based on the name
# of the program. On Windows, it is '<Program Name>.exe' and otherwise it is
# '<Program Name>'.
ifeq ($(OS_TYPE), WIN32)
	EXECUTABLE = $(PROGRAM).exe
else
	EXECUTABLE = $(PROGRAM)
endif

# The following section specifies the remove command. On Windows, it is 'del'
# and on other platforms it is 'rm'.
ifeq ($(OS_TYPE), WIN32)
	REMOVE = del
else
	REMOVE = rm
endif

# The following section defines the targets, dependencies and the commands to
# build the targets respectively.

# Targets:
# <Executable Name>(Default):   Build Huffmanzip
# clean:                        Clean all temporary files (object files)
# clean-target:                 Clean the built executable of Huffmanzip

$(EXECUTABLE): CompressCore.o huffmanzip.o Settings.o Util.o
	$(CC) -o $@ $^ $(ADDITIONAL_FLAGS)

CompressCore.o: CompressCore.cpp CompressCore.h BinaryTree.h BinaryTree.ipp \
                Settings.h Util.h
	$(CC) -o $@ CompressCore.cpp -c $(ADDITIONAL_FLAGS)

huffmanzip.o: huffmanzip.cpp Settings.h Util.h CompressCore.h BinaryTree.h \
              BinaryTree.ipp
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
