// CompressCore.cpp

#include "CompressCore.h"
#include "Settings.h"
#include "Util.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

using std::cin;
using std::cout;
using std::istream;
using std::ostream;
using std::ostringstream;
using std::fstream;
using std::string;
using std::copy;
using std::ios;
using std::istream_iterator;
using std::ostream_iterator;
using std::runtime_error;

void test();

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

ostream &copyStream(istream &is, ostream &os) {
    char tmp;
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
    if (sessionSettings.compress) {
        sendMessage(MSG_WARNING, "Compressing is not available for now; the following is a test");
        test();
    } else {
        sendMessage(MSG_WARNING, "Decompressing is not available for now");
    }
    if (sessionSettings.useStdout) {
        fstream tmpFileStream;
        TempFile::open(tmpFileStream, sessionSettings.outFilePath, ios::in);
        copyStream(tmpFileStream, cout);
    }
    if (sessionSettings.useStdin)
        TempFile::remove(sessionSettings.inFilePath);
    if (sessionSettings.useStdout) {
        delete tmpOutFile;
        tmpOutFile = NULL;
    }
}

void test() {
    fstream fin(sessionSettings.inFilePath.c_str(), ios::in|ios::binary), fout(sessionSettings.outFilePath.c_str(), ios::out|ios::binary);
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
