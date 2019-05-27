# Huffmanzip

[![Issues](https://img.shields.io/github/issues/YangHanlin/huffmanzip.svg)](https://github.com/YangHanlin/huffmanzip/issues) [![Pull requests](https://img.shields.io/github/issues-pr/YangHanlin/huffmanzip.svg)](https://github.com/YangHanlin/huffmanzip/pulls) [![License](https://img.shields.io/github/license/YangHanlin/huffmanzip.svg)](https://github.com/YangHanlin/huffmanzip/blob/master/LICENSE)

> **Notice:** While the [first version (v0.9-alpha)](https://github.com/YangHanlin/huffmanzip/releases/tag/v0.9-alpha) has been released, I am still working on the documentation. Please wait for a while.

**Important**: The developer is still working on this project; it will not be ready until after some time. Current status:

```
Completed (almost) all parts of huffmanzip; working on documentation.
```

Huffmanzip is a single-file, command-line (toy) compressor & decompressor, using Huffman coding to reduce the size of the file being compressed.

Huffmanzip is:

- **simple**: the code is simple enough to illustrate the application of Huffman coding and Huffman trees; actually, it is one of the homework of my college course *Data Structures & Algorithms*;
- **modular**: the program is divided into several separate modules between which they communicate with unified interfaces;
- **cross-platform**: the program is written in C++ and only depends on the standard libraries of C++ delivered with the compiler;
- **designed for general purposes**: the program is designed for general binary files, rather than limited to plain-text files, even ASCII files.

## Usage

The usage of Huffmanzip is inspired by [GNU Gzip](https://www.gnu.org/software/gzip/), therefore most of the features and usages may be similar with it.

> [WIP] A reference can be accessed [here](https://github.com/YangHanlin/huffmanzip/wiki/Usage-of-Huffmanzip) in the wiki. A more friendly usage (`Quick Start` or `TL;DR`) will be available here in this README later.

## Building from source

### Dependencies

None but a C++ compiler. There are many excellent C++ compilers available, including MSVC (through [Visual Studio](https://visualstudio.microsoft.com/vs/)), G++ (through [GCC, the GNU Compiler Collection](https://gcc.gnu.org/)), Clang++ (through [Clang](http://clang.llvm.org/)), etc.

### How to build

#### From command line

The main source file is `huffmanzip.cpp`, and the other files are all `#include`d, either directly or indirectly, in this file. So it only requires compilation of `huffmanzip.cpp` to build the whole program.

Take G++ and Linux shell as an example:

```shell
# Compile the main source file
g++ huffmanzip.cpp -o huffmanzip
```

then run

```shell
# Show help info to insure it is built
./huffmanzip --help
```

Building with other compilers and/or in other environments are similar with above.

### In an IDE

If you are using an IDE the building may be easier. Add the source files to create a project and select `Build` or similar actions. Find the built executable in the corresponding directory.

> **Note**: If you are experiencing some strange problems while building, try only adding `huffmanzip.cpp` into your project and force it to build again. This may be caused by the IDE not recognizing the `.ipp` files as headers, and due to the special structure of this program, only adding `huffmanzip.cpp` works as well.

## Contributing

This is only a toy project and may contain many problems owing to my poor programming skills. If you are happy to help me improve Huffmanzip, just be free to fork it and create a pull request. Issues are welcomed as well :-)

## License

[GPL v3](https://github.com/YangHanlin/huffmanzip/blob/master/LICENSE)
