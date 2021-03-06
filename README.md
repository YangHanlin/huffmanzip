# Huffmanzip

[![Issues](https://img.shields.io/github/issues/YangHanlin/huffmanzip.svg)](https://github.com/YangHanlin/huffmanzip/issues) [![Pull requests](https://img.shields.io/github/issues-pr/YangHanlin/huffmanzip.svg)](https://github.com/YangHanlin/huffmanzip/pulls) [![License](https://img.shields.io/github/license/YangHanlin/huffmanzip.svg)](LICENSE)

> **Notice:** While the [first beta version (`v0.10-beta`)](https://github.com/YangHanlin/huffmanzip/releases/tag/v0.10-beta) has been released, I am still working on the documentation. Please wait for a while.

Huffmanzip is a single-file, command-line (toy) compressor & decompressor, using Huffman coding to reduce the size of the file being compressed.

Huffmanzip is:

- **simple**: the code is simple enough to illustrate the application of Huffman coding and Huffman trees; actually, it is one of the homework of my college course *Data Structures & Algorithms*;
- **modular**: the program is divided into several separate modules between which they communicate with unified interfaces;
- **cross-platform**: the program is written in C++ and only depends on the standard libraries of C++ delivered with the compiler;
- **designed for general purposes**: the program is designed for general binary files, rather than limited to plain-text files, even ASCII files.

## Usage

The usage of Huffmanzip is inspired by [GNU Gzip](https://www.gnu.org/software/gzip/), therefore most of the features and usages may be similar with it. A reference can be accessed [here](https://github.com/YangHanlin/huffmanzip/wiki/Usage-of-Huffmanzip) in the wiki.

### TL;DR

Here are some examples illustrating the usage of Huffmanzip.

- To compress `example.txt` into `example.txt.huffmanzip`:

  ```bash
  huffmanzip example.txt
  ```

- To compress `example.txt` into `example`:

  ```bash
  huffmanzip example.txt -o example # use -o or --output
  ```

- To decompress `example.txt.huffmanzip` into `example.txt`:

  ```bash
  huffmanzip example.txt.huffmanzip # judging from the suffix
  ```

- To decompress `example` into `example.txt`:

  ```bash
  huffmanzip example -o example.txt -d
  ```

  > If the compressed file does not end with `.huffmanzip`, you must explicitly specify the output file (with `-o` or `--output`) and set to decompression mode (with `-d` or `--decompress`).

## Building from source

### Dependencies

- A C++ compiler **with support of C++17**, along with a build system
- CMake 3.10 (or later version)

### How to build

#### From command line

Use CMake to generate configuration files and build the executable:

```shell
cmake .
cmake --build .
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

> **Note:** Depending on the generator CMake chooses to use, the executable may not be built in the current directory, so a simple `./huffmanzip -V` (or `.\huffmanzip.exe -V`) may not work. In this case, replace `huffmanzip` with the actual path to the built executable, e.g. `Build/huffmanzip`.

#### In an IDE

If you are using an IDE the building may be easier. Add the source files to create a project and select `Build` or similar actions. Find the built executable in the corresponding directory.

> **Note**: If you are experiencing some strange problems while building, try excluding `BinaryTree.ipp` from your project and force it to build again. This may be caused by the IDE not recognizing the `.ipp` files as headers.

## Contributing

This is only a toy project and may contain many problems owing to my poor programming skills. If you are happy to help me improve Huffmanzip, just be free to fork it and create a pull request. Issues are welcomed as well :-)

## License

Contents in this repository are licensed under the [GNU General Public License v3.0 (GPL v3)](LICENSE).
