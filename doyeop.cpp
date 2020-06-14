#include "doyeop.h"
#include <bits/stdc++.h>
#define rep(i, x, y) for (unsigned int i = x; i < (unsigned int)y; i++)
#define repinclude(i, x, y) for (int i = x; i <= y; i++)
using namespace std;

void DoYeop::Split() {
    vector<string> tmp(shortreads);
    shortreads.clear();
    assert(tmp[0].size() >= K_MER);
    for (int t = 0; t < tmp.size(); t++) {
        string s = tmp[t];
        string shortread;
        for (int i = K_MER - 1; i < s.size(); i++) {
            if (i == K_MER - 1) {
                for (int j = 0; j < K_MER; j++)
                    shortread.push_back(s[j]);
            } else {
                shortread.erase(shortread.begin());
                shortread.push_back(s[i]);
            }
            shortreads.push_back(shortread);
        }
    }
}

void DoYeop::Insert() {
    rep(i, 0, shortreads.size()) {
        string s = shortreads[i];
        // gen prefix
        s.pop_back();
        ac->insert(s, Node(i, true));
        // gen suffix
        s.erase(s.begin());
        s.push_back(shortreads[i].back());
        ac->insert(s, Node(i, false));
    }
}

void DoYeop::Connect() {
    queue<AhoCorasick<Node>*> Q;
    Q.push(ac);
    G.resize(shortreads.size());
    while (!Q.empty()) { // Search Tree
        AhoCorasick<Node> * cur = Q.front();
        Q.pop();
        if (cur->EndNode()) {
            const vector<Node> &v = cur->GetIdentifier();
            rep(i, 0, v.size() - 1) rep(j, i + 1, v.size()) {
                if (v[i].y && !v[j].y) { // v[i] is prefix
                    G[v[j].x].push_back(v[i].x);
                } else if (!v[i].y && v[j].y) { // v[i] is suffix
                    G[v[i].x].push_back(v[j].x);
                }
            }
        }
        rep(i, 0, 4) {
            if (cur->GetChild(i) != nullptr) {
                Q.push(cur->GetChild(i));
            }
        }
    }
    // for (int i = 0; i < (int)G.size(); i++) {
    //    cout << shortreads[i] << " : ";
    //    for (int j = 0; j < G[i].size(); j++)
    //        cout << shortreads[G[i][j]] << ' ';
    //    cout << endl;
    // }
    // cout << endl;
}

string DoYeop::FindEulerPath() {
    Euler euler(G);
    //
    //for (int i = 0; i < euler.G.size(); i++) {
    //    cout << shortreads[i] << " : ";
    //    for (int j = 0; j < euler.G[i].size(); j++)
    //        cout << shortreads[euler.G[i][j]->to] << ' ';
    //    cout << endl;
    //}
    //return "";
    //
    vector<int> result = euler.find();
    string ret(shortreads[result[0]]);
    rep(i, 1, result.size()) {
        ret.push_back(shortreads[result[i]].back());
    }
    return ret;
}

DoYeop::DoYeop(const char * REFER_FILE, const char * SHORT_FILE, const int MISMATCH, int K_mer) : FileManager(REFER_FILE, SHORT_FILE, MISMATCH) {
    ac = new AhoCorasick<Node>();
    K_MER = K_mer;
}

DoYeop::~DoYeop() {
    delete ac;
}

std::string DoYeop::Solve() {
    auto echo = [=](int x, int y) {
        cout.precision(4);
        cout << fixed;
        cout << '\r' << double(x) * 100.0 / y << "\t% complete";
    };
    Split();
    echo(1, 4);
    Insert();
    echo(2, 4);
    Connect();
    echo(3, 4);
    string ret = FindEulerPath();
    echo(4, 4);
    cout << endl;
    return ret;
}