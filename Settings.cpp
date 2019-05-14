// Settings.cpp

#include "Settings.h"
#include "Util.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdexcept>

using std::string;
using std::ostringstream;
using std::copy;
using std::find;
using std::vector;
using std::runtime_error;

struct OptionChange {
    bool &target;
    bool targetStatus;
    OptionChange(bool &target, bool targetStatus);
};

const char defaultCompressorIdentifier[GlobalSettings::COMPRESSOR_IDENTIFIER_SIZE] = {'H', 'U', 'F', 'M', 'A', 'N', 'Z'};
const unsigned defaultCompressorVersion = 0U;
const string defaultCompressorVersionStr = "0.0";
const unsigned defaultFileSignature = 0xaabbccddU;

const string defaultProgramName = "huffmanzip";
const bool defaultShowHelp = false;
const bool defaultShowVersion = false;
const bool defaultCompress = true;
const bool defaultVerboseMode = false;
const bool defaultKeepOriginalFile = true;
const bool defaultUseStdin = true;
const bool defaultUseStdout = false;
const string defaultInFilePath = "";
const string defaultOutFilePath = "";

const vector<char> shortArgs = {'c', 'd', 'h', 'k', 'v', 'V'};
const vector<string> longArgs = {
    "stdout",
    "decompress",
    "help",
    "no-keep",
    "verbose",
    "version"
};
const vector<OptionChange> optionChanges = {
    OptionChange(sessionSettings.useStdout, true),
    OptionChange(sessionSettings.compress, false),
    OptionChange(sessionSettings.showHelp, true),
    OptionChange(sessionSettings.keepOriginalFile, false),
    OptionChange(sessionSettings.verboseMode, true),
    OptionChange(sessionSettings.showVersion, true)
};

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

OptionChange::OptionChange(bool &target, bool targetStatus) : target(target), targetStatus(targetStatus) {}

void parseArgs(int argc, char *argv[]) {
    string programName = argv[0];
    string::size_type pos = programName.find_last_of('/'),
                      backslashPos = programName.find_last_of('\\');
    if (backslashPos != string::npos && pos < backslashPos)
        pos = backslashPos;
    if (pos != string::npos)
        programName = programName.substr(pos + 1);
    if (!programName.empty())
        sessionSettings.programName = programName;
    bool needFurtherPath = false;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            if (needFurtherPath) {
                sessionSettings.outFilePath = argv[i];
                needFurtherPath = false;
            } else {
                sessionSettings.inFilePath = argv[i];
            }
        } else if (argv[i][1] != '-') {
            for (int j = 1; argv[i][j] != '\0'; ++j) {
                if (argv[i][j] == 'o') {
                    sessionSettings.useStdin = false;
                    needFurtherPath = true;
                } else {
                    vector<char>::const_iterator iter = find(shortArgs.begin(), shortArgs.end(), argv[i][j]);
                    if (iter == shortArgs.end()) {
                        ostringstream errMsg;
                        errMsg << "unrecognized option -" << argv[i][j];
                        sendMessage(MSG_ERROR, errMsg.str());
                        throw runtime_error(errMsg.str());
                    } else {
                        vector<OptionChange>::const_iterator optionChangeIter = optionChanges.begin() + (iter - shortArgs.begin());
                        optionChangeIter->target = optionChangeIter->targetStatus;
                    }
                }
            }
        } else {
            string option = argv[i] + 2;
            if (option == "output") {
                sessionSettings.useStdin = false;
                needFurtherPath = true;
            } else {
                vector<string>::const_iterator iter = find(longArgs.begin(), longArgs.end(), argv[i] + 2);
                if (iter == longArgs.end()) {
                    ostringstream errMsg;
                    errMsg << "unrecognized option " << argv[i];
                    sendMessage(MSG_ERROR, errMsg.str());
                    throw runtime_error(errMsg.str());
                } else {
                    vector<OptionChange>::const_iterator optionChangeIter = optionChanges.begin() + (iter - longArgs.begin());
                    optionChangeIter->target = optionChangeIter->targetStatus;
                }
            }
        }
    }
}
