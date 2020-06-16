#include "doyeop.h"
#include <assert.h>
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <map>
#include <vector>
#define rep(i, x, y) for (unsigned int i = x; i < (unsigned int)y; i++)
#define repinclude(i, x, y) for (int i = x; i <= y; i++)
using namespace std;

void DoYeop::Split() {
    vector<string> tmp(shortreads);
    vector<string> candidate;
    shortreads.clear();
    assert(tmp[0].size() >= K_MER);
    for (int t = 0; t < tmp.size(); t++) {
        string s = tmp[t];
        string shortread;
        for (int i = K_MER - 1; i < s.size(); i++) {
            if (i == K_MER - 1) {
                for (int j = 0; j < K_MER; j++)
                    shortread.push_back(s[j]);
                candidate.push_back(shortread);
            } else {
                shortread.erase(shortread.begin());
                shortread.push_back(s[i]);
            }
            shortreads.push_back(shortread);
        }
    }
    sort(shortreads.begin(), shortreads.end());
    shortreads.erase(unique(shortreads.begin(), shortreads.end()), shortreads.end());
    for (int try_ = 0; try_ < 2; try_++) {
        for (int i = 0; i < candidate.size(); i++) {
            int counter = 0;
            for (int t = 0; t < 4; t++) {
                char c = "ATGC"[t];
                string s = candidate[i];
                s.pop_back();
                s.insert(s.begin(), c);
                auto it = lower_bound(shortreads.begin(), shortreads.end(), s);
                if (it == shortreads.end() || *it != s) {
                    counter++;
                }
            }
            if (counter == 4 - try_) {
                starting.push_back(lower_bound(shortreads.begin(), shortreads.end(), candidate[i]) - shortreads.begin());
            }
        }
        if (starting.size()) break;
    }
    sort(starting.begin(), starting.end());
    starting.erase(unique(starting.begin(), starting.end()), starting.end());
}

void DoYeop::Insert() {
    vector<string> k_mer;
    map<string, int> counter;
    rep(i, 0, shortreads.size()) {
        string s = shortreads[i];
        // gen prefix
        s.pop_back();
        ac->insert(s, Node(i, true));
        k_mer.push_back(s);
        counter[s]++;
        // gen suffix
        s.erase(s.begin());
        s.push_back(shortreads[i].back());
        ac->insert(s, Node(i, false));
        k_mer.push_back(s);
        //counter[s]++;
    }
    sort(k_mer.begin(), k_mer.end());
    k_mer.erase(unique(k_mer.begin(), k_mer.end()), k_mer.end());
    shortread_counter.resize(shortreads.size());
    for (auto it = counter.begin(); it != counter.end(); it++) {
        shortread_counter[lower_bound(shortreads.begin(), shortreads.end(), it->first) - shortreads.begin()] = it->second;
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

vector<string> DoYeop::FindEulerPath() {
    Traversal traversal(G, shortread_counter);
    //// code
    if (starting.empty()) starting = vector<int>({-1});
    vector<string> contigs;
    rep(k, 0, starting.size()) {
        int start = starting[k];
        //cout << "START : " << start << ':' << (start == -1 ? "" : shortreads[start]) << '\n';
        vector<int> result = traversal.find(start);
        traversal.reset();
        string res(shortreads[result[0]]);
        rep(i, 1, result.size()) {
            res.push_back(shortreads[result[i]].back());
        }
        contigs.push_back(res);
    }
    return contigs;
}

DoYeop::DoYeop(const char * REFER_FILE, const char * SHORT_FILE, const int MISMATCH, unsigned long K_mer) : FileManager(REFER_FILE, SHORT_FILE, MISMATCH) {
    ac = new AhoCorasick<Node>();
    auto get_k_mer_k = [=](unsigned long x) {
        if (x <= 30) return (x + 1) / 2;
        //if (x <= 70 && shortreads.size() >= x * 2) return x / 3;
        //if (x <= 200) return x / 4;
        return (unsigned long)21;
    };
    K_MER = min(K_mer, get_k_mer_k(shortreads[0].size()));
}

DoYeop::~DoYeop() {
    delete ac;
}
// 99382
std::vector<std::string> DoYeop::Solve() {
    auto echo = [=](int x, int y) {
        cout.precision(6);
        cout << '\r' << double(x) * 100.0 / y << "\t% complete";
    };
    echo(0, 4);
    Split();
    echo(1, 4);
    Insert();
    echo(2, 4);
    Connect();
    echo(3, 4);
    vector<string> ret = FindEulerPath();
    echo(4, 4);
    cout << endl << endl;
    return ret;
}