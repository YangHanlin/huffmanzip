// huffmanzip.cpp

#include "Settings.h"
#include "Util.h"

// #include <iostream>
#include <stdexcept>

// using std::cerr;
// using std::endl;
using std::exception;

int main(int argc, char *argv[]) {
    // argc = 1;
    // char *argvCandidate[] = {
    //     "huffmanzip.exe"
    // };
    // argv = argvCandidate;
    // cout << "Original:" << endl
    //      << "globalSettings.compressorIdentifier = \"" << string(globalSettings.compressorIdentifier, globalSettings.compressorIdentifier + GlobalSettings::COMPRESSOR_IDENTIFIER_SIZE) << "\"" << endl
    //      << "globalSettings.compressorVersion = " << globalSettings.compressorVersion << endl
    //      << "globalSettings.compressorVersionStr = \"" << globalSettings.compressorVersionStr << "\"" << endl
    //      << "globalSettings.fileSignature = " << globalSettings.fileSignature << endl
    //      << "sessionSettings.programName = \"" << sessionSettings.programName << "\"" << endl
    //      << "sessionSettings.showHelp = " << sessionSettings.showHelp << endl
    //      << "sessionSettings.showVersion = " << sessionSettings.showVersion << endl
    //      << "sessionSettings.compress = " << sessionSettings.compress << endl
    //      << "sessionSettings.verboseMode = " << sessionSettings.verboseMode << endl
    //      << "sessionSettings.keepOriginalFile = " << sessionSettings.keepOriginalFile << endl
    //      << "sessionSettings.useStdin = " << sessionSettings.useStdin << endl
    //      << "sessionSettings.useStdout = " << sessionSettings.useStdout << endl
    //      << "sessionSettings.inFilePath = \"" << sessionSettings.inFilePath << "\"" << endl
    //      << "sessionSettings.outFilePath = \"" << sessionSettings.outFilePath << "\"" << endl;
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
        sendMessage(MSG_WARNING, "the feature has not been implemented; please wait");
        return 0;
    } catch (const exception &e) {
        sendMessage(MSG_INFO, "program terminated due to an error");
    }
    // cout << "Parsed:" << endl
    //      << "globalSettings.compressorIdentifier = \"" << string(globalSettings.compressorIdentifier, globalSettings.compressorIdentifier + GlobalSettings::COMPRESSOR_IDENTIFIER_SIZE) << "\"" << endl
    //      << "globalSettings.compressorVersion = " << globalSettings.compressorVersion << endl
    //      << "globalSettings.compressorVersionStr = \"" << globalSettings.compressorVersionStr << "\"" << endl
    //      << "globalSettings.fileSignature = " << globalSettings.fileSignature << endl
    //      << "sessionSettings.programName = \"" << sessionSettings.programName << "\"" << endl
    //      << "sessionSettings.showHelp = " << sessionSettings.showHelp << endl
    //      << "sessionSettings.showVersion = " << sessionSettings.showVersion << endl
    //      << "sessionSettings.compress = " << sessionSettings.compress << endl
    //      << "sessionSettings.verboseMode = " << sessionSettings.verboseMode << endl
    //      << "sessionSettings.keepOriginalFile = " << sessionSettings.keepOriginalFile << endl
    //      << "sessionSettings.useStdin = " << sessionSettings.useStdin << endl
    //      << "sessionSettings.useStdout = " << sessionSettings.useStdout << endl
    //      << "sessionSettings.inFilePath = \"" << sessionSettings.inFilePath << "\"" << endl
    //      << "sessionSettings.outFilePath = \"" << sessionSettings.outFilePath << "\"" << endl;
    // showHelp();
    // showVersion();
    // system("pause");
}
