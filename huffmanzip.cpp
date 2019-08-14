// huffmanzip.cpp

// #define DIRECT_DEBUG
// #define EXPOSE_CRASH

#include "Settings.h"
#include "Util.h"
#include "CompressCore.h"

#include <stdexcept>

using std::exception;

int main(int argc, char *argv[]) {
    #ifdef DIRECT_DEBUG
    char *argvCandidate[] = {
        ".\\huffmanzip.exe"
    };
    argc = sizeof(argvCandidate) / sizeof(argvCandidate[0]);
    argv = argvCandidate;
    #endif
    #ifndef EXPOSE_CRASH
    try {
    #endif
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
    #ifndef EXPOSE_CRASH
    } catch (const exception &e) {
        sendMessage(MSG_INFO, "Program terminated due to an error");
        return 1;
    }
    #endif
}
