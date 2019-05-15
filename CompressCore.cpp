// CompressCore.cpp

#include "CompressCore.h"
#include "Settings.h"
#include "Util.h"

#include <sstream>

using std::ostringstream;

void compress() {
    if (sessionSettings.verboseMode) {
        ostringstream infoMsg;
        infoMsg << "Compressing from "
                << (sessionSettings.useStdin ? "standard input" : sessionSettings.inFilePath)
                << " to "
                << (sessionSettings.useStdout ? "standard output" : sessionSettings.outFilePath);
        sendMessage(MSG_INFO, infoMsg.str());
    }
    sendMessage(MSG_WARNING, "Compressing is not avalable for now");
}

void decompress() {
    if (sessionSettings.verboseMode) {
        ostringstream infoMsg;
        infoMsg << "Decompressing from "
                << (sessionSettings.useStdin ? "standard input" : sessionSettings.inFilePath)
                << " to "
                << (sessionSettings.useStdout ? "standard output" : sessionSettings.outFilePath);
        sendMessage(MSG_INFO, infoMsg.str());
    }
    sendMessage(MSG_WARNING, "Decompressing is not available for now");
}
