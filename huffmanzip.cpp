// huffmanzip.cpp

#include "Settings.h"
#include "Util.h"

#include <iostream>
#include <stdexcept>

using std::cerr;
using std::endl;
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
    } catch (const exception &e) {
        cerr << "Process terminated due to an error." << endl;
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
    return 0;
}
