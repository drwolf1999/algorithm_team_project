#ifndef __filemanager__
#define __filemanager__ 1
#include <string>
#include <vector>

class FileManager {
    int mismatch;
protected:
    std::string referDNA;
    std::vector<std::string> shortreads;
public:
    FileManager(const char * REFER_FILE, const char * SHORT_FILE, const int MISMATCH);
    int GetMismatch();
};

#endif // !__filemanager__