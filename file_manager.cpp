#include "file_manager.h"
#include <fstream>
#include <iostream>

FileManager::FileManager(const char * REFER_FILE, const char * SHORT_FILE, const int MISMATCH) {
    std::ifstream refer_file(REFER_FILE), short_file(SHORT_FILE);
    if (!refer_file.is_open()) {
        std::cout << "reference file is not exist\n";
        exit(0);
    }
    if (!short_file.is_open()) {
        std::cout << "short read file is not exist\n";
        exit(0);
    }
    refer_file >> referDNA;
    while (!short_file.eof()) {
        std::string s;
        short_file >> s;
        shortreads.push_back(s);
    }
    refer_file.close();
    short_file.close();
    mismatch = MISMATCH;
    std::cout << "Length of Original : " << referDNA.size() << "\nNumber of Shortreads : " << shortreads.size() << "\nLength of Shortread : " << shortreads[0].size() << "\n\n";
}

int FileManager::GetMismatch() { return mismatch; }