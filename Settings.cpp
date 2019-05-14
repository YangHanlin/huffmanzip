// Settings.cpp

#include "Settings.h"
#include "Util.h"

#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <stdexcept>

using std::string;
using std::ostringstream;
using std::copy;
using std::map;
using std::runtime_error;

struct Arg {
    char shortArg;
    string longArg;
    Arg(char shortArg, const string &longArg);
    Arg(char shortArg);
    Arg(const string &longArg);
};

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

const map<Arg, OptionChange> argOptionMap = {
    {Arg('c', "stdout"), OptionChange(sessionSettings.useStdout, true)},
    {Arg('d', "decompress"), OptionChange(sessionSettings.compress, false)},
    {Arg('h', "help"), OptionChange(sessionSettings.showHelp, true)},
    {Arg('k', "no-keep"), OptionChange(sessionSettings.keepOriginalFile, false)},
    {Arg('v', "verbose"), OptionChange(sessionSettings.verboseMode, true)},
    {Arg('V', "version"), OptionChange(sessionSettings.showVersion, true)}
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

Arg::Arg(char shortArg, const string &longArg) : shortArg(shortArg), longArg(longArg) {}

Arg::Arg(char shortArg) : shortArg(shortArg), longArg("") {}

Arg::Arg(const string &longArg) : shortArg('\0'), longArg(longArg) {}

OptionChange::OptionChange(bool &target, bool targetStatus) : target(target), targetStatus(targetStatus) {}

bool operator<(const Arg &lhs, const Arg &rhs) {
    return lhs.shortArg < rhs.shortArg;
}

bool operator==(const Arg &lhs, const Arg &rhs) {
    return lhs.shortArg == rhs.shortArg || lhs.longArg == rhs.longArg;
}

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
                    map<Arg, OptionChange>::const_iterator iter = argOptionMap.find(Arg(argv[i][j]));
                    if (iter == argOptionMap.end()) {
                        ostringstream errMsg;
                        errMsg << "unrecognized option -" << argv[i][j];
                        sendMessage(MSG_ERROR, errMsg.str());
                        throw runtime_error(errMsg.str());
                    } else {
                        iter->second.target = iter->second.targetStatus;
                    }
                }
            }
        } else {
            string option = argv[i] + 2;
            // sendMessage(MSG_INFO, "<dbg> current option: " + option);
            // sendMessage(MSG_INFO, "<dbg> current capsuled option: " + Arg(option).longArg);
            if (option == "output") {
                sessionSettings.useStdin = false;
                needFurtherPath = true;
            } else {
                map<Arg, OptionChange>::const_iterator iter = argOptionMap.find(Arg(option));
                if (iter == argOptionMap.end()) {
                    ostringstream errMsg;
                    errMsg << "unrecognized option " << argv[i];
                    sendMessage(MSG_ERROR, errMsg.str());
                    throw runtime_error(errMsg.str());
                } else {
                    iter->second.target = iter->second.targetStatus;
                }
            }
        }
    }
}
