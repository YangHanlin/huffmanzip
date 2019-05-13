// Util.h

#include <string>

enum MessageType {
    MSG_INFO,
    MSG_WARNING,
    MSG_ERROR
};

void sendMessage(MessageType type, const std::string &msg);
