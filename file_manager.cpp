#include "file_manager.h"
#include <fstream>

FileManager::FileManager(const char * REFER_FILE, const char * SHORT_FILE) {
    std::ifstream refer_file(REFER_FILE), short_file(SHORT_FILE);
    refer_file >> referDNA;
    short_file >> shortread;
    refer_file.close();
    short_file.close();
}