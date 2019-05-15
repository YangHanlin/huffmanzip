// CompressCore.h

#ifndef COMPRESS_CORE
#define COMRPESS_CORE

#include <string>
#include <fstream>

class TempFile {
public:
    TempFile(std::ios::openmode openMode = std::ios::in | std::ios::out, bool autoRemove = true);
    ~TempFile();
    std::string path() const;
    std::fstream &stream();
    void remove() const;
    static void open(fstream &fileStream, const string &filePath, std::ios::openmode openMode);
    static void remove(const std::string &filePath);
private:
    std::string filePath;
    std::fstream fileStream;
    bool autoRemove;
};

void compressCore();

#endif
