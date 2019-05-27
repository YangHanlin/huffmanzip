// CompressCore.cpp

#include "CompressCore.h"
#include "Settings.h"
#include "Util.h"
#include "BinaryTree.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::ostringstream;
using std::fstream;
using std::string;
using std::priority_queue;
using std::vector;
using std::map;
using std::copy;
using std::ios;
using std::istream_iterator;
using std::ostream_iterator;
using std::runtime_error;

#include <iomanip>
using std::setbase;
const size_t BYTE_SIZE = 256;

void test();
ostream &print(ostream &os, const unsigned *arr);
string toBinary(unsigned num);
void genHuffmanCode(const BinaryTree<HuffmanNode> *tree, unsigned *arr);
void genHuffmanCode(const BinaryTree<HuffmanNode>::ConstIterator &iter, unsigned *arr, unsigned code);

TempFile::TempFile(ios::openmode openMode, bool autoRemove) :
    filePath(tmpnam(NULL) + sessionSettings.programName + ".tmp"),
    autoRemove(autoRemove) {
    open(fileStream, filePath, openMode);
}

TempFile::~TempFile() {
    fileStream.close();
    if (autoRemove)
        remove();
}

string TempFile::path() const {
    return filePath;
}

fstream &TempFile::stream() {
    return fileStream;
}

void TempFile::remove() const {
    remove(filePath);
}

void TempFile::open(fstream &fileStream, const string &filePath, std::ios::openmode openMode) {
    fileStream.open(filePath.c_str(), openMode);
    if (!fileStream) {
        ostringstream errMsg;
        errMsg << "Unable to open temporary file " << filePath;
        sendMessage(MSG_ERROR, errMsg.str());
        throw runtime_error(errMsg.str());
    }
}

void TempFile::remove(const string &filePath) {
    if (::remove(filePath.c_str())) {
        ostringstream errMsg;
        errMsg << "Unable to delete temporary file " << filePath << "; you may delete it yourself";
        sendMessage(MSG_ERROR, errMsg.str());
    }
}

HuffmanNode::HuffmanNode(unsigned char byte, unsigned weight) : byte(byte), weight(weight) {}

bool HuffmanNodeCompare::operator()(const BinaryTree<HuffmanNode> *lhs, const BinaryTree<HuffmanNode> *rhs) const {
    return lhs->root()->weight > rhs->root()->weight;
}

ostream &copyStream(istream &is, ostream &os) {
    char tmp = '\0';
    while (is.get(tmp))
        os << tmp;
    return os;
}

void compressCore() {
    if (sessionSettings.verboseMode) {
        ostringstream infoMsg;
        infoMsg << (sessionSettings.compress ? "Compressing" : "Decompressing") << " from "
                << (sessionSettings.useStdin ? "standard input" : sessionSettings.inFilePath)
                << " to "
                << (sessionSettings.useStdout ? "standard output" : sessionSettings.outFilePath);
        sendMessage(MSG_INFO, infoMsg.str());
    }
    if (sessionSettings.useStdin) {
        TempFile tmpFile(ios::out, false);
        sessionSettings.inFilePath = tmpFile.path();
        copyStream(cin, tmpFile.stream());
    }
    TempFile *tmpOutFile = NULL;
    if (sessionSettings.useStdout) {
        tmpOutFile = new TempFile(ios::out);
        sessionSettings.outFilePath = tmpOutFile->path();
    }
    fstream inFileStream(sessionSettings.inFilePath.c_str(), ios::in | ios::binary);
    if (!inFileStream) {
        ostringstream errMsg;
        errMsg << "Unable to open " << (sessionSettings.useStdin ? "temporary file" : "input") << " " << sessionSettings.inFilePath;
        sendMessage(MSG_ERROR, errMsg.str());
        throw runtime_error(errMsg.str());
    }
    if (!sessionSettings.useStdout) {
        fstream testOutFileStream(sessionSettings.outFilePath.c_str(), ios::in | ios::binary);
        if (testOutFileStream) {
            ostringstream warningMsg;
            warningMsg << "The output file " << sessionSettings.outFilePath << " already exists; its content will be cleared";
            sendMessage(MSG_WARNING, warningMsg.str());
            testOutFileStream.close();
        }
    }
    clock_t clockBefore = 0L, clockAfter = 0L;
    fstream outFileStream(sessionSettings.outFilePath.c_str(), ios::out | ios::binary);
    if (!outFileStream) {
        ostringstream errMsg;
        errMsg << "Unable to open " << (sessionSettings.useStdout ? "temporary file" : "output") << " " << sessionSettings.outFilePath;
        sendMessage(MSG_ERROR, errMsg.str());
        throw runtime_error(errMsg.str());
    }
    if (sessionSettings.compress) {
        clockBefore = clock();
        unsigned byteFrequencies[BYTE_SIZE] = {0U};
        unsigned long long originalSize = 0ULL;
        unsigned char tmp = '\0';
        while (inFileStream.read(reinterpret_cast<char*>(&tmp), sizeof(tmp))) {
            ++byteFrequencies[tmp];
            ++originalSize;
        }
        // print(cout, byteFrequencies);
        priority_queue<BinaryTree<HuffmanNode>*, vector<BinaryTree<HuffmanNode>*>, HuffmanNodeCompare> nodeQueue;
        for (size_t i = 0ULL; i < BYTE_SIZE; ++i)
            if (byteFrequencies[i] > 0)
                nodeQueue.push(new BinaryTree(HuffmanNode(i, byteFrequencies[i])));
        while (nodeQueue.size() > 1) {
            BinaryTree<HuffmanNode> *tree1 = nodeQueue.top();
            nodeQueue.pop();
            BinaryTree<HuffmanNode> *tree2 = nodeQueue.top();
            nodeQueue.pop();
            BinaryTree<HuffmanNode> *treeCombined = new BinaryTree(HuffmanNode('\0', tree1->root()->weight + tree2->root()->weight));
            // cout << tree1->root()->weight << " + " << tree2->root()->weight << " = " << treeCombined->root()->weight << "\n";
            treeCombined->move(treeCombined->root().lchild(), tree1->root());
            treeCombined->move(treeCombined->root().rchild(), tree2->root());
            nodeQueue.push(treeCombined);
        }
        // cout << "Huffman tree has been constructed\n";
        BinaryTree<HuffmanNode> *huffmanTree = NULL;
        if (!nodeQueue.empty()) {
            huffmanTree = nodeQueue.top();
            nodeQueue.pop();
        } else {
            huffmanTree = new BinaryTree<HuffmanNode>;
        }
        if (huffmanTree->root().lchild().null() && huffmanTree->root().rchild().null()) {
            BinaryTree<HuffmanNode> *tmpHuffmanTree = new BinaryTree(HuffmanNode('\0', huffmanTree->root()->weight));
            tmpHuffmanTree->move(tmpHuffmanTree->root().lchild(), huffmanTree->root());
            huffmanTree = tmpHuffmanTree;
        }
        unsigned huffmanCodes[BYTE_SIZE] = {0U};
        genHuffmanCode(huffmanTree, huffmanCodes);
        // for (size_t i = 0ULL; i < BYTE_SIZE; ++i)
        //     if (huffmanCodes[i] != 0)
        //         cout << i << ": " << toBinary(huffmanCodes[i]) << "\n";
        outFileStream.write(reinterpret_cast<char*>(&globalSettings.fileSignature), sizeof(globalSettings.fileSignature));
        outFileStream.write(reinterpret_cast<char*>(&globalSettings.compressorIdentifier), sizeof(globalSettings.compressorIdentifier));
        outFileStream.write(reinterpret_cast<char*>(&globalSettings.compressorVersion), sizeof(globalSettings.compressorVersion));
        unsigned long long ullPlaceHolder = 0U; unsigned char ucPlaceHolder = '\0';
        outFileStream.write(reinterpret_cast<char*>(&ullPlaceHolder), sizeof(ullPlaceHolder));
        outFileStream.write(reinterpret_cast<char*>(&ullPlaceHolder), sizeof(ullPlaceHolder));
        outFileStream.write(reinterpret_cast<char*>(&ucPlaceHolder), sizeof(ucPlaceHolder));
        unsigned long long huffmanTableSize = 0ULL;
        for (size_t i = 0ULL; i < BYTE_SIZE; ++i)
            if (huffmanCodes[i] != 0U) {
                unsigned char ci = i;
                outFileStream.write(reinterpret_cast<char*>(&ci), sizeof(ci));
                outFileStream.write(reinterpret_cast<char*>(&huffmanCodes[i]), sizeof(huffmanCodes[i]));
                huffmanTableSize += sizeof(ci) + sizeof(huffmanCodes[i]);
            }
        inFileStream.clear();
        inFileStream.seekg(ios::beg);
        unsigned char outTmp = '\0';
        unsigned long long compressedSize = 0ULL;
        unsigned char currentByte = 0U, currentMask = 0U;
        // TODO: Use bitwise operations to simply code (and speed up?)
        while (inFileStream.read(reinterpret_cast<char*>(&outTmp), sizeof(outTmp))) {
            vector<bool> bits;
            unsigned huffmanCode = huffmanCodes[outTmp];
            while (huffmanCode != 0U) {
                bits.push_back(huffmanCode & 0x1U);
                huffmanCode >>= 1;
            }
            for (vector<bool>::reverse_iterator iter = bits.rbegin() + 1; iter != bits.rend(); ++iter) {
                currentByte = (currentByte << 1) + *iter;
                currentMask = (currentMask << 1) + 1;
                if (currentMask == 0xffU) {
                    outFileStream.write(reinterpret_cast<char*>(&currentByte), sizeof(currentByte));
                    currentByte = 0U;
                    currentMask = 0U;
                    ++compressedSize;
                }
            }
        }
        if (currentMask == 0x0U) {
            currentMask = 0xffU;
        } else {
            ++compressedSize;
            for (unsigned char i = currentMask; i != 0xffU; i = (i << 1) + 1, currentByte <<= 1, currentMask <<= 1);
            outFileStream.write(reinterpret_cast<char*>(&currentByte), sizeof(currentByte));
        }
        int huffmanTableSizeOffset = sizeof(globalSettings.fileSignature) + sizeof(globalSettings.compressorIdentifier) + sizeof(globalSettings.compressorVersion),
            compressedSizeOffset = huffmanTableSizeOffset + sizeof(ullPlaceHolder),
            lastByteMaskOffset = compressedSizeOffset + sizeof(ullPlaceHolder);
        outFileStream.seekp(huffmanTableSizeOffset, ios::beg).write(reinterpret_cast<char*>(&huffmanTableSize), sizeof(huffmanTableSize));
        outFileStream.seekp(compressedSizeOffset, ios::beg).write(reinterpret_cast<char*>(&compressedSize), sizeof(compressedSize));
        outFileStream.seekp(lastByteMaskOffset, ios::beg).write(reinterpret_cast<char*>(&currentMask), sizeof(currentMask));
        clockAfter = clock();
        if (sessionSettings.verboseMode) {
            sendMessage(MSG_INFO, "Compression completed");
            unsigned long long totalCompressedSize = lastByteMaskOffset + sizeof(currentMask) + huffmanTableSize + compressedSize;
            ostringstream infoMsg;
            infoMsg << "Compression rate = " << static_cast<double>(totalCompressedSize) / static_cast<double>(originalSize) * 100.0 << "%, time consumed = ~" << static_cast<double>(clockAfter - clockBefore) / static_cast<double>(CLOCKS_PER_SEC) << "s";
            sendMessage(MSG_INFO, infoMsg.str());
        }
        delete huffmanTree;
    } else {
        clockBefore = clock();
        unsigned int actualFileSignature = 0U;
        inFileStream.read(reinterpret_cast<char*>(&actualFileSignature), sizeof(actualFileSignature));
        if (actualFileSignature != globalSettings.fileSignature) {
            string errMsgStr = "The file signature does not match; it may be in wrong format or broken";
            sendMessage(MSG_ERROR, errMsgStr);
            throw runtime_error(errMsgStr);
        }
        char actualCompressorIdentifier[globalSettings.COMPRESSOR_IDENTIFIER_SIZE] = {'\0'};
        inFileStream.read(reinterpret_cast<char*>(actualCompressorIdentifier), sizeof(actualCompressorIdentifier));
        // Ignore the compressor identifier
        unsigned int actualCompressorVersion = 0U;
        inFileStream.read(reinterpret_cast<char*>(&actualCompressorVersion), sizeof(actualCompressorVersion));
        if (actualCompressorVersion > globalSettings.compressorVersion) {
            ostringstream errMsg;
            errMsg << "The compressed file is created with a newer version of Huffmanzip; update Huffmanzip to decompress it";
            sendMessage(MSG_ERROR, errMsg.str());
            throw runtime_error(errMsg.str());
        }
        unsigned long long actualHuffmanTableSize = 0ULL, actualCompressedSize = 0ULL;
        unsigned char actualLastByteMask = '\0';
        inFileStream.read(reinterpret_cast<char*>(&actualHuffmanTableSize), sizeof(actualHuffmanTableSize))
                    .read(reinterpret_cast<char*>(&actualCompressedSize), sizeof(actualCompressedSize))
                    .read(reinterpret_cast<char*>(&actualLastByteMask), sizeof(actualLastByteMask));
        map<unsigned, unsigned char> codeByteMap;
        for (unsigned long long i = 0ULL; i < actualHuffmanTableSize; i += sizeof(unsigned) + sizeof(unsigned char)) {
            unsigned char tmpByte = '\0';
            unsigned tmpCode = 0U;
            if (inFileStream.read(reinterpret_cast<char*>(&tmpByte), sizeof(tmpByte)).read(reinterpret_cast<char*>(&tmpCode), sizeof(tmpCode))) {
                codeByteMap[tmpCode] = tmpByte;
            } else {
                string errMsgStr = "Failed to load complete Huffman table; the file may be broken";
                sendMessage(MSG_ERROR, errMsgStr);
                throw runtime_error(errMsgStr);
            }
        }
        unsigned long long measuredCompressedSize = 0ULL;
        unsigned char currentByte = '\0', prevByte = '\0';
        unsigned int currentCode = 1U;
        if (inFileStream.read(reinterpret_cast<char*>(&prevByte), sizeof(prevByte))) {
            ++measuredCompressedSize;
            while (inFileStream.read(reinterpret_cast<char*>(&currentByte), sizeof(currentByte))) {
                ++measuredCompressedSize;
                for (int i = 0; i < 8; ++i) {
                    currentCode = (currentCode << 1) + ((prevByte >> (7 - i)) & 0x1U);
                    map<unsigned, unsigned char>::iterator iter = codeByteMap.find(currentCode);
                    if (iter != codeByteMap.end()) {
                        outFileStream.write(reinterpret_cast<char*>(&iter->second), sizeof(iter->second));
                        currentCode = 1U;
                    }
                }
                prevByte = currentByte;
            } 
            // For robustness considerations, it is NOT required that the "dirty bits" in the last byte have to be all 0.
            for (int i = 0; i < 8; ++i)
                if ((actualLastByteMask >> (7 - i)) & 0x1U) {
                    currentCode = (currentCode << 1) + ((prevByte >> (7 - i)) & 0x1U);
                    map<unsigned, unsigned char>::iterator iter = codeByteMap.find(currentCode);
                    if (iter != codeByteMap.end()) {
                        outFileStream.write(reinterpret_cast<char*>(&iter->second), sizeof(iter->second));
                        currentCode = 1U;
                    }
                }
        }
        clockAfter = clock();
        if (actualCompressedSize != measuredCompressedSize)
            sendMessage(MSG_WARNING, "Claimed and measured compressed data size does not match; the file may have been broken");
        if (sessionSettings.verboseMode) {
            sendMessage(MSG_INFO, "Decompression completed");
            ostringstream infoMsg;
            infoMsg << "Time consumed = " << static_cast<double>(clockAfter - clockBefore) / static_cast<double>(CLOCKS_PER_SEC) << "s";
            sendMessage(MSG_INFO, infoMsg.str());
        }
    }
    outFileStream.close();
    inFileStream.close();
    if (sessionSettings.useStdout) {
        fstream tmpFileStream;
        TempFile::open(tmpFileStream, sessionSettings.outFilePath, ios::in);
        copyStream(tmpFileStream, cout);
    }
    if (sessionSettings.useStdin) {
        TempFile::remove(sessionSettings.inFilePath);
    } else if (!sessionSettings.keepOriginalFile) {
        if (remove(sessionSettings.inFilePath.c_str())) {
            ostringstream warningMsg;
            warningMsg << "Unable to delete input file " << sessionSettings.inFilePath << "; you may delete it yourself";
            sendMessage(MSG_WARNING, warningMsg.str());
            throw runtime_error(warningMsg.str());
        }
    }
    if (sessionSettings.useStdout) {
        delete tmpOutFile;
        tmpOutFile = NULL;
    }
}

void test() {
    fstream fin(sessionSettings.inFilePath.c_str(), ios::in | ios::binary), fout(sessionSettings.outFilePath.c_str(), ios::out | ios::binary);
    if (!fin) {
        ostringstream errMsg;
        errMsg << "Unable to open input file " << sessionSettings.inFilePath;
        sendMessage(MSG_ERROR, errMsg.str());
        throw runtime_error(errMsg.str());
    }
    if (!fout) {
        ostringstream errMsg;
        errMsg << "Unable to open output file " << sessionSettings.outFilePath;
        sendMessage(MSG_ERROR, errMsg.str());
        throw runtime_error(errMsg.str());
    }
    copyStream(fin, fout);
}

ostream &print(ostream &os, const unsigned *arr) {
    for (size_t i = 0ULL; i < BYTE_SIZE; ++i)
        if (arr[i] != 0U)
            os << setbase(16) << (int)i << "("
               << setbase(10) << i << "): "
               << arr[i] << "\n";
    return os;
}

string toBinary(unsigned num) {
    if (num == 0U)
        return "";
    return toBinary(num / 2U) + (num % 2U ? "1" : "0");
}

void genHuffmanCode(const BinaryTree<HuffmanNode> *tree, unsigned *arr) {
    genHuffmanCode(tree->root(), arr, 1U);
}

void genHuffmanCode(const BinaryTree<HuffmanNode>::ConstIterator &iter, unsigned *arr, unsigned code) {
    if (iter.null())
        return;
    if (iter.lchild().null() && iter.rchild().null())
        arr[iter->byte] = code;
    genHuffmanCode(iter.lchild(), arr, code << 1);
    genHuffmanCode(iter.rchild(), arr, (code << 1) + 1);
}
