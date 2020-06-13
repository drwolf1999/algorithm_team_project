#include "utils.h"
#include "file_manager.h"

class DoYeop : public FileManager {
    AhoCorasick *ac;

    public:
    DoYeop(const char * REFER_FILE, const char * SHORT_FILE);
    ~DoYeop();
    std::string Solve();
};