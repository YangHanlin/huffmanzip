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
            cout << globalSettings.programName << ": info: " << msg << endl;
        case MSG_WARNING:
            cerr << globalSettings.programName << ": warning: " << msg << endl;
        case MSG_ERROR:
            cerr << globalSettings.programName << ": error: " << msg << endl;
        default:
            throw runtime_error("Invalid MessageType (enum) value in sendMessage()");
    }
}
