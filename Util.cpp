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
    cout << "Usage: " << sessionSettings.programName << " [OPTION]... [FILE}..." << endl
         << "Compress/decompress single files using Huffman coding." << endl
         << endl
         << "(N/A yet)" << endl;
}

void showVersion() {
    cout << sessionSettings.programName << " version " << globalSettings.compressorVersionStr << " (" << globalSettings.compressorVersion << ")" << endl
         << "Last built at " << __TIME__ << " on " << __DATE__ << endl;
}
