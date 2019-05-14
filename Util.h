// Util.h

#ifndef UTIL_H
#define UTIL_H

#include <string>

enum MessageType {
    MSG_INFO,
    MSG_WARNING,
    MSG_ERROR
};

void sendMessage(MessageType type, const std::string &msg);

void showHelp();
void showVersion();

#endif
