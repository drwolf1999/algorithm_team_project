#include "doyeop.h"
#include <bits/stdc++.h>
#define rep(i, x, y) for (int i = x; i < y; i++)
#define repinclude(i, x, y) for (int i = x; i <= y; i++)
using namespace std;

void DoYeop::Insert() {
    rep(i, 0, shortreads.size()) {
        string s = shortreads[i];
        // gen prefix
        s.pop_back();
        ac->insert(s, Node(i, true));
        // gen suffix
        s.erase(s.begin());
        ac->insert(s, Node(i, false));
    }
}

void DoYeop::Connect() {
    queue<AhoCorasick<Node>*> Q;
    Q.push(ac);
}

string DoYeop::FindEulerPath() {
    return "test";
}

DoYeop::DoYeop(const char * REFER_FILE, const char * SHORT_FILE, const int MISMATCH) : FileManager(REFER_FILE, SHORT_FILE, MISMATCH) {
    ac = new AhoCorasick<Node>();
}

DoYeop::~DoYeop() {
    delete ac;
}

std::string DoYeop::Solve() {
    Insert();
    Connect();
    return FindEulerPath();
}