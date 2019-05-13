// Settings.cpp

#include "Settings.h"
#include "Util.h"

#include <string>
#include <algorithm>

using std::string;
using std::copy;

const char defaultCompressorIdentifier[GlobalSettings::COMPRESSOR_IDENTIFIER_SIZE] = {'H', 'U', 'F', 'M', 'A', 'N', 'Z'};
const unsigned defaultCompressorVersion = 0U;
const string defaultCompressorVersionStr = "0.0";
const unsigned defaultFileSignature = 0xaabbccddU;

const string defaultProgramName = "huffmanzip";
const bool defaultShowHelp = false;
const bool defaultShowVersion = true;
const bool defaultCompress = true;
const bool defaultVerboseMode = false;
const bool defaultKeepOriginalFile = true;
const bool defaultUseStdin = true;
const bool defaultUseStdout = false;
const string defaultInFilePath = "";
const string defaultOutFilePath = "";

GlobalSettings globalSettings;
SessionSettings sessionSettings;

GlobalSettings::GlobalSettings() :
    compressorVersion(defaultCompressorVersion),
    compressorVersionStr(defaultCompressorVersionStr),
    fileSignature(defaultFileSignature) {
    copy(defaultCompressorIdentifier, defaultCompressorIdentifier + COMPRESSOR_IDENTIFIER_SIZE, compressorIdentifier);
}

SessionSettings::SessionSettings() :
    programName(defaultProgramName),
    showHelp(defaultShowHelp),
    showVersion(defaultShowVersion),
    compress(defaultCompress),
    verboseMode(defaultVerboseMode),
    keepOriginalFile(defaultKeepOriginalFile),
    useStdin(defaultUseStdin),
    useStdout(defaultUseStdout),
    inFilePath(defaultInFilePath),
    outFilePath(defaultOutFilePath) {}
    

void parseArgs(int argc, char *argv[]) {
    // ....
}
