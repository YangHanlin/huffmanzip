// Settings.cpp

#include "Settings.h"

#include <string>
#include <algorithm>

using std::string;
using std::copy;

const string defaultProgramName = "huffmanzip";
const char defaultCompressorIdentifier[GlobalSettings::COMPRESSOR_IDENTIFIER_SIZE] = {'H', 'U', 'F', 'M', 'A', 'N', 'Z'};
const unsigned defaultCompressorVersion = 0U;
const unsigned defaultFileSignature = 0xaabbccddU;

GlobalSettings globalSettings;
SessionSettings sessionSettings;

GlobalSettings::GlobalSettings() : programName(defaultProgramName), compressorVersion(defaultCompressorVersion), fileSignature(defaultFileSignature) {
    copy(defaultCompressorIdentifier, defaultCompressorIdentifier + COMPRESSOR_IDENTIFIER_SIZE, compressorIdentifier);
}
