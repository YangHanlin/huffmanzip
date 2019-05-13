// Settings.h

#ifndef SETTING_H
#define SETTING_H

#include <string>

struct GlobalSettings {
    static const int COMPRESSOR_IDENTIFIER_SIZE = 7;
    char compressorIdentifier[COMPRESSOR_IDENTIFIER_SIZE];
    unsigned compressorVersion;
    unsigned fileSignature;
    GlobalSettings();
};

struct SessionSettings {
    std::string programName;
    bool showHelp;
    bool showVersion;
    bool verboseMode;
    bool keepOriginalFile;
    bool useStdin;
    bool useStdout;
    std::string inFilePath;
    std::string outFilePath;
    SessionSettings();
};

extern GlobalSettings globalSettings;
extern SessionSettings sessionSettings;

void parseArgs(int argc, char *argv[]);

#endif
