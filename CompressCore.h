// CompressCore.h

#ifndef COMPRESS_CORE
#define COMRPESS_CORE

#include "BinaryTree.h"

#include <string>
#include <fstream>
#include <iostream>

class TempFile {
public:
    TempFile(std::ios::openmode openMode = std::ios::in | std::ios::out, bool autoRemove = true);
    ~TempFile();
    std::string path() const;
    std::fstream &stream();
    void remove() const;
    static void open(std::fstream &fileStream, const std::string &filePath, std::ios::openmode openMode);
    static void remove(const std::string &filePath);
private:
    std::string filePath;
    std::fstream fileStream;
    bool autoRemove;
};

struct HuffmanNode {
    unsigned char byte;
    unsigned weight;
    HuffmanNode(unsigned char byte = '\0', unsigned weight = 0U);
};

class HuffmanNodeCompare {
public:
    bool operator()(const BinaryTree<HuffmanNode> *lhs, const BinaryTree<HuffmanNode> *rhs) const;
};

std::ostream &copyStream(std::istream &is, std::ostream &os);

void compressCore();

#endif
