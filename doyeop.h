#ifndef __doyeop__

#define __doyeop__ 1
#include "utils.h"
#include "file_manager.h"

typedef Pair<int, bool> Node;

/**
 * This Algorithm is based by string matching (Aho-Corasick)
 * 1. Insert S[1..k-1](prefix) and S[2..k](suffix) into prefix, souffix Aho-Corasick for k-mer S
 * 2. Connect Edge when S.prefix == T.suffix or S.suffix == T.prefix for k-mer S, T
 * 3. Find Euler Path
 * 4. End Algorithm
*/

class DoYeop : public FileManager {
    AhoCorasick<Node> *ac;
    std::vector<std::vector<int>> G;
    void Insert();
    void Connect();
    string FindEulerPath();
    public:
    DoYeop(const char * REFER_FILE, const char * SHORT_FILE, const int MISMATCH);
    ~DoYeop();
    std::string Solve();
};

#endif // !__doyeop__