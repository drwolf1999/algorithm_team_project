#include "file_manager.h"
#include <fstream>

FileManager::FileManager(const char * REFER_FILE, const char * SHORT_FILE, const int MISMATCH) {
    std::ifstream refer_file(REFER_FILE), short_file(SHORT_FILE);
    refer_file >> referDNA;
    while (!short_file.eof()) {
        std::string s;
        short_file >> s;
        shortreads.push_back(s);
    }
    refer_file.close();
    short_file.close();
    mismatch = MISMATCH;
}

int FileManager::GetMismatch() { return mismatch; }