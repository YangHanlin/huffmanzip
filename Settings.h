// Settings.h

#ifndef DBGGING
#define DBGGING

#include <string>

struct GlobalSettings {
    static const int COMPRESSOR_IDENTIFIER_SIZE = 7;
    std::string programName;
    char compressorIdentifier[COMPRESSOR_IDENTIFIER_SIZE];
    unsigned compressorVersion;
    unsigned fileSignature;
    GlobalSettings();
};

struct SessionSettings {
    bool showHelp;
    bool showVersion;
    bool verboseMode;
    bool keepOriginalFile;
    bool useStdin;
    bool useStdout;
    bool inFilePath;
    bool outFilePath;
};

extern GlobalSettings globalSettings;
extern SessionSettings sessionSettings;

#endif
