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
    map<string, int> counter;
    rep(i, 0, shortreads.size()) {
        string s = shortreads[i];
        counter[s]++;
        // gen prefix
        s.pop_back();
        ac->insert(s, Node(i, true));
        // gen suffix
        s.erase(s.begin());
        s.push_back(shortreads[i].back());
        ac->insert(s, Node(i, false));
    }
    shortread_counter.resize(shortreads.size());
    for (auto it = counter.begin(); it != counter.end(); it++) {
        shortread_counter[lower_bound(shortreads.begin(), shortreads.end(), it->first) - shortreads.begin()] = it->second;
    }
}

void DoYeop::Connect() {
    queue<AhoCorasick<Node>*> Q;
    Q.push(ac);
    G.resize(shortreads.size());
    auto comp = [](string l, string r) {
        return l.substr(1, l.size() - 1) == r.substr(0, r.size() - 1);
    };
    while (!Q.empty()) { // Search Tree
        AhoCorasick<Node> * cur = Q.front();
        Q.pop();
        if (cur->EndNode()) {
            const vector<Node> &v = cur->GetIdentifier();
            rep(i, 0, v.size() - 1) rep(j, i + 1, v.size()) {
                if (v[i].y && !v[j].y) { // v[i] is prefix
                    G[v[j].x].push_back(v[i].x);
                    //cout << shortreads[v[j].x] << ' ' << shortreads[v[i].x] << '\n';
                    assert(comp(shortreads[v[j].x], shortreads[v[i].x]));
                } else if (!v[i].y && v[j].y) { // v[i] is suffix
                    G[v[i].x].push_back(v[j].x);
                    //cout << shortreads[v[i].x] << ' ' << shortreads[v[j].x] << '\n';
                    assert(comp(shortreads[v[i].x], shortreads[v[j].x]));
                }
            }
            //cout << "\n";
        }
        rep(i, 0, 4) {
            if (cur->GetChild(i) != nullptr) {
                Q.push(cur->GetChild(i));
            }
        }
    }
}

vector<string> DoYeop::FindContigs() {
    Traversal traversal(G, shortread_counter);
    //// code
    if (starting.empty()) starting = vector<int>({-1});
    vector<string> contigs;
    rep(k, 0, starting.size()) {
        int start = starting[k];
        vector<int> result = traversal.find(start);
        traversal.reset();
        string res(shortreads[result[0]]);
        rep(i, 1, result.size()) {
            //assert(result[i] < shortreads.size());
            //if (i > result.size() - 20) cout << shortreads[result[i]] << '\n';
            res.push_back(shortreads[result[i]].back());
        }
        //cout << endl;
        contigs.push_back(res);
    }
    return contigs;
}

DoYeop::DoYeop(const char * REFER_FILE, const char * SHORT_FILE, const int MISMATCH, unsigned long K_mer) : FileManager(REFER_FILE, SHORT_FILE, MISMATCH) {
    ac = new AhoCorasick<Node>();
    auto get_k_mer_k = [=](unsigned long x) {
        if (x <= 10) return (x + 1) / 2;
        else if (x <= 40) return (x + 4) / 5;
        return (unsigned long)21;
    };
    K_MER = min(K_mer, get_k_mer_k(shortreads[0].size()));
}

DoYeop::~DoYeop() {
    delete ac;
}

std::vector<std::string> DoYeop::Solve() {
    auto echo = [=](int x, int y) {
        cout.precision(6);
        cout << "\rprocessing " << double(x) * 100.0 / y << "\t% complete";
    };
    echo(0, 4);
    Split();
    echo(1, 4);
    Insert();
    echo(2, 4);
    Connect();
    echo(3, 4);
    vector<string> ret = FindContigs();
    echo(4, 4);
    cout << endl << endl;
    return ret;
}