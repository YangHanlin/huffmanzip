# Huffmanzip

[![Issues](https://img.shields.io/github/issues/YangHanlin/huffmanzip.svg)](https://github.com/YangHanlin/huffmanzip/issues) [![Pull requests](https://img.shields.io/github/issues-pr/YangHanlin/huffmanzip.svg)](https://github.com/YangHanlin/huffmanzip/pulls) [![License](https://img.shields.io/github/license/YangHanlin/huffmanzip.svg)](https://github.com/YangHanlin/huffmanzip/blob/master/LICENSE)

> **Notice:** While the [first version (v0.9-alpha)](https://github.com/YangHanlin/huffmanzip/releases/tag/v0.9-alpha) has been released, I am still working on the documentation. Please wait for a while.

**Important**: The developer is still working on this project; it will not be ready until after some time. Current status:

```
Completed the core part of compressing & decompressing; working on some polishment of the code.
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

- A C++ compiler **with C++ 17 support**
- Make

> If you would like to build with the attached `Makefile` without any modification, please use GCC or Clang with a compiler named `g++` available and compatible with the syntax of G++.

### How to build

#### From command line

Make the default target to build Huffmanzip:

```shell
make
```

then run the following command to make sure it is built:

```shell
./huffmanzip -V # on Windows, use '.\huffmanzip.exe -V' instead
```

Huffmanzip should display the version information as follows:

```
huffmanzip version 0.10-beta (2)
Last built at 16:07:19 on May 29 2019
```

You can dig into the attached `Makefile` for more options.

### In an IDE

If you are using an IDE the building may be easier. Add the source files to create a project and select `Build` or similar actions. Find the built executable in the corresponding directory.

> **Note**: If you are experiencing some strange problems while building, try excluding `BinaryTree.ipp` from your project and force it to build again. This may be caused by the IDE not recognizing the `.ipp` files as headers.

## Contributing

This is only a toy project and may contain many problems owing to my poor programming skills. If you are happy to help me improve Huffmanzip, just be free to fork it and create a pull request. Issues are welcomed as well :-)

## License

[GPL v3](https://github.com/YangHanlin/huffmanzip/blob/master/LICENSE)