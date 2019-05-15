// CompressCore.cpp

#include "CompressCore.h"
#include "Settings.h"
#include "Util.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

using std::ostringstream;
using std::cin;
using std::ofstream;
using std::runtime_error;

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
        sessionSettings.inFilePath = tmpnam(NULL) + sessionSettings.programName + ".tmp";
        ofstream tmpFile(sessionSettings.inFilePath);
        if (!tmpFile) {
            ostringstream errMsg;
            errMsg << "Unable to open temporary file " << sessionSettings.inFilePath;
            sendMessage(MSG_ERROR, errMsg.str());
            throw runtime_error(errMsg.str());
        }
        char tmp = '\0';
        while (cin.get(tmp))
            tmpFile << tmp;
        tmpFile.close();
    }
    if (sessionSettings.compress) {
        sendMessage(MSG_WARNING, "Compressing is not available for now");
    } else {
        sendMessage(MSG_WARNING, "Decompressing is not available for now");
    }
    if (sessionSettings.useStdin && remove(sessionSettings.inFilePath.c_str())) {
        ostringstream warningMsg;
        warningMsg << "Unable to delete temporary file " << sessionSettings.inFilePath << "; you may yourself";
        sendMessage(MSG_WARNING, warningMsg.str());
    }
}
