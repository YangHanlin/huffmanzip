// huffmanzip.cpp

#include "Settings.h"
#include "Util.h"
#include "CompressCore.h"

#include <stdexcept>

using std::exception;

int main(int argc, char *argv[]) {
    try {
        parseArgs(argc, argv);
        if (sessionSettings.showHelp) {
            showHelp();
            return 0;
        }
        if (sessionSettings.showVersion) {
            showVersion();
            return 0;
        }
        compressCore();
        return 0;
    } catch (const exception &e) {
        sendMessage(MSG_INFO, "Program terminated due to an error");
        return 1;
    }
}
