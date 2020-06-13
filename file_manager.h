#pragma once
#include <string>

class FileManager {
protected:
    std::string referDNA;
    std::string shortread;
public:
    FileManager(const char * REFER_FILE, const char * SHORT_FILE);
};