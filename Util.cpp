// Util.cpp

#include "Util.h"
#include "Settings.h"

#include <iostream>
#include <string>
#include <stdexcept>

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::runtime_error;

void sendMessage(MessageType type, const string &msg) {
    switch (type) {
        case MSG_INFO:
            cout << sessionSettings.programName << ": info: " << msg << endl;
            break;
        case MSG_WARNING:
            cerr << sessionSettings.programName << ": warning: " << msg << endl;
            break;
        case MSG_ERROR:
            cerr << sessionSettings.programName << ": error: " << msg << endl;
            break;
        default:
            throw runtime_error("Invalid MessageType (enum) value in sendMessage()");
            break;
    }
}

void showHelp() {
    cout << "Usage: " << sessionSettings.programName << " [OPTION]... [FILE]..." << endl
         << "Compress/decompress single files using Huffman coding." << endl
         << endl
         << "-c, --stdout     write on standard output" << endl
         << "-d, --decompress decompress (implied when input filename ends with .huffmanzip)" << endl
         << "-h, --help       display help information and exit" << endl
         << "-k, --no-keep    do not keep (delete) the original file" << endl
         << "-v, --verbose    verbose mode (display more information)" << endl
         << "-V, --version    display version information and exit" << endl
         << endl
         << "With no FILE given, or when FILE is -, read standard input." << endl;
}

void showVersion() {
    cout << sessionSettings.programName << " version " << globalSettings.compressorVersionStr << " (" << globalSettings.compressorVersion << ")" << endl
         << "Last built at " << __TIME__ << " on " << __DATE__ << endl;
}
