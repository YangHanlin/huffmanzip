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
const unsigned defaultCompressorVersion = 2U;
const string defaultCompressorVersionStr = "0.10-beta";
const unsigned defaultFileSignature = 0xaabbccddU;
const string defaultFileSuffix = ".huffmanzip";

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
    fileSignature(defaultFileSignature),
    fileSuffix(defaultFileSuffix) {
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
    if (pos == string::npos || (backslashPos != string::npos && pos < backslashPos))
        pos = backslashPos;
    if (pos != string::npos)
        programName = programName.substr(pos + 1);
    string::size_type dotPos = programName.find_last_of('.');
    if (dotPos != string::npos)
        programName = programName.substr(0, dotPos);
    if (!programName.empty())
        sessionSettings.programName = programName;
    bool needFurtherPath = false;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            if (needFurtherPath) {
                sessionSettings.outFilePath = argv[i];
                needFurtherPath = false;
            } else {
                sessionSettings.useStdin = false;
                sessionSettings.inFilePath = argv[i];
            }
        } else if (argv[i][1] != '-') {
            for (int j = 1; argv[i][j] != '\0'; ++j) {
                if (argv[i][j] == 'o') {
                    sessionSettings.useStdout = false;
                    needFurtherPath = true;
                } else {
                    vector<char>::const_iterator iter = find(shortArgs.begin(), shortArgs.end(), argv[i][j]);
                    if (iter == shortArgs.end()) {
                        ostringstream errMsg;
                        errMsg << "Unrecognized option -" << argv[i][j];
                        sendMessage(MSG_ERROR, errMsg.str() + "; use -h/--help to get help");
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
                sessionSettings.useStdout = false;
                needFurtherPath = true;
            } else {
                vector<string>::const_iterator iter = find(longArgs.begin(), longArgs.end(), argv[i] + 2);
                if (iter == longArgs.end()) {
                    ostringstream errMsg;
                    errMsg << "Unrecognized option " << argv[i];
                    sendMessage(MSG_ERROR, errMsg.str() + "; use -h/--help to get help");
                    throw runtime_error(errMsg.str());
                } else {
                    vector<OptionChange>::const_iterator optionChangeIter = optionChanges.begin() + (iter - longArgs.begin());
                    optionChangeIter->target = optionChangeIter->targetStatus;
                }
            }
        }
    }
    if (sessionSettings.showHelp || sessionSettings.showVersion)
        return;
    if (!sessionSettings.useStdin) {
        string::size_type suffixPos = sessionSettings.inFilePath.rfind(globalSettings.fileSuffix);
        bool endsWithSuffix;
        if (suffixPos + globalSettings.fileSuffix.size() == sessionSettings.inFilePath.size()) {
            endsWithSuffix = true;
            sessionSettings.compress = false;
        }
        if (!sessionSettings.useStdout && sessionSettings.outFilePath.empty())
            sessionSettings.outFilePath = sessionSettings.compress ? sessionSettings.inFilePath + globalSettings.fileSuffix : (endsWithSuffix ? sessionSettings.inFilePath.substr(0, suffixPos) : "");
    }
    if (!sessionSettings.useStdin && sessionSettings.inFilePath.empty()) {
        sendMessage(MSG_ERROR, "Missing input file; use -h/--help to get help");
        throw runtime_error("Missing input file");
    }
    if (!sessionSettings.useStdout && sessionSettings.outFilePath.empty()) {
        sendMessage(MSG_ERROR, "Missing output file; use -h/--help to get help");
        throw runtime_error("Missing output file");
    }
}
