#ifndef __utils__
#define __utils__ 1

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <assert.h>
#include <queue>
// #include <bits/stdc++.h>

class Utility {
    public:
    static inline int getACGTToInt(const char ACGT) { // Mapping 'A'=0, 'C'=1, 'G'=2, 'T'=3
        switch (ACGT)
        {
        case 'A':
            return 0;
            break;
        case 'C':
            return 1;
            break;
        case 'G':
            return 2;
            break;
        case 'T':
            return 3;
            break;
        default:
            break;
        }
        return -1;
    }
};

//////////////////////////////////////// Aho-Corasick /////////////////////////////////////

template <class T> class AhoCorasick {
    AhoCorasick * child[4]; // child (0=>'A', 1=>'C', 2=>'G', 3=>'T')
    bool terminal; // this position is end
    std::vector<T> identifiers;
    void insert(const char * s, const T ident) { // Save the appearance of the pattern string s in the p position of the reference
        if (*s == '\0') { // end pattern string
            terminal = true;
            identifiers.push_back(ident);
            return;
        }
        int next = Utility::getACGTToInt(*s);
        if (child[next] == nullptr) child[next] = new AhoCorasick(); // Create new if child[next] is empty
        child[next]->insert(s + 1, ident); // Insert from child[next]
    }
    std::vector<T> find(const char * s) {
        if (*s == '\0') return identifiers; // return position if found
        int next = Utility::getACGTToInt(*s);
        if (child[next] == nullptr) return std::vector<T>({}); // return empty {} if child[next] is empty ==> not found
        return child[next]->find(s + 1); // return find(s + 1) from child[next]
    }
    public:
    AhoCorasick() : terminal(false) {
        terminal = false;
        for (int i = 0; i < 4; i++) child[i] = nullptr;
    }
    ~AhoCorasick() {
        for (int i = 0; i < 4; i++) delete child[i];
    }
    void insert(const std::string &s, T ident) {
        insert(s.c_str(), ident);
    }
    std::vector<T> find(const std::string &s) {
        return find(s.c_str());
    }
    bool EndNode() {
        return terminal;
    }
    AhoCorasick * GetChild(int idx) {
        return child[idx];
    }
    std::vector<T> GetIdentifier() {
        return identifiers;
    }
};

//////////////////////////////////////// Pair ////////////////////////////////

template <class T1, class T2> class Pair {
  public:
    T1 x;
    T2 y;
    Pair(T1 x_ = T1(), T2 y_ = T2()) : x(x_), y(y_) {}
    bool operator<(const Pair &p) const {
        if (x == p.x) return y > p.y;
        return x < p.x;
    }
    bool operator>(const Pair &p) const {
        if (x == p.x) return y > p.y;
        return x > p.x;
    }
    bool operator!=(const Pair &p) const { return x != p.x || y != p.y; }
    bool operator==(const Pair &p) const { return x == p.x && y == p.y; }
    friend std::istream &operator>>(std::istream &stream, Pair &p) {
        stream >> p.x >> p.y;
        return stream;
    }
    friend std::ostream &operator<<(std::ostream &stream, Pair p) {
        stream << p.x << ' ' << p.y;
        return stream;
    }
};

/////////////////////////////////////// Edge ////////////////////////////////////
class Edge {
public:
    int to;
    Edge * back;
    bool go;
    Edge(int _to = -1, bool g = true, Edge * b = nullptr) : to(_to), go(g), back(b) {}
};


/////////////////////////////////////// Traversal ///////////////////////////////

class Traversal {
    std::vector<std::vector<Edge*>> G;
    std::vector<int> max_visit;
    std::vector<int> visit;
    std::vector<int> indegree;
    std::vector<int> find_recurse(int cur) {
        std::vector<int> ret;
        if (visit[cur] >= max_visit[cur]) return ret;
        visit[cur]++;
        for (int i = 0; i < (int)G[cur].size(); i++) {
            Edge *& next = G[cur][i]; // caching
            if (next->go) {
                next->go = false;
                if (next->back != nullptr) next->back->go = false;
                std::vector<int> e = find_recurse(next->to);
                for (int j = 0; j < (int)e.size(); j++) ret.push_back(e[j]);
            }
        }
        ret.insert(ret.begin(), cur);
        return ret;
    }
public:
    Traversal(const std::vector<std::vector<int>> &g, const std::vector<int> &visit_counter) {
        assert(visit_counter.size() == g.size());
        G.resize(g.size());
        max_visit = visit_counter;
        visit.resize(G.size());
        indegree.resize(G.size());
        // std::cout << "g\n";
        // for (int i = 0; i < (unsigned int)g.size(); i++) {
        //     std::cout << i << " : ";
        //     for (int j = 0; j < (unsigned int)g[i].size(); j++) {
        //         std::cout << g[i][j] << ' ';
        //     }
        //     std::cout << '\n';
        // }
        // std::cout << '\n';
        for (int i = 0; i < (int)g.size(); i++) {
            for (int j = 0; j < (int)g[i].size(); j++) {
                indegree[g[i][j]]++;
                Edge * a = new Edge(g[i][j]), * b = new Edge(i);
                b->back = a;
                G[i].push_back(a);
                G[j].push_back(b);
            }
        }
    }
    void reset() {
        for (int i = 0; i < G.size(); i++) {
            for (int j = 0; j < G[i].size(); j++) {
                if (!G[i][j]->go) G[i][j]->go = true;
            }
        }
        visit.clear();
        visit.resize(G.size());
    }
    std::vector<int> find(int start) {
        int __min__ = 1 << 29;
        if (start == -1) {
            for (int i = 0; i < G.size(); i++) {
                if (indegree[i] <= __min__) start = i;
            }
        }
        return find_recurse(start);
    }
};


///////////////////////////////////////////// KMP ///////////////////////////////////
class KMP {
    std::vector<int> getPI(const std::string &k) {
        int m = k.size();
        int j = 0;
        std::vector<int> ret(m + 1);
        for (int i = 1; i < m; i++) {
            while (j > 0 && k[i] != k[j])
                j = ret[j - 1];
            if (k[i] == k[j])
                ret[i] = ++j;
        }
        return ret;
    }
public:
    std::vector<int> run(const std::string& text, const std::string& pattern) {
        int j = 0;
        std::vector<int> pi = getPI(pattern);
        std::vector<int> ret;
        int m = (int)pattern.size();
        int n = (int)text.size();
        for (int i = 0; i < n; i++) {
            while (j > 0 && text[i] != pattern[j])
                j = pi[j - 1];
            if (text[i] == pattern[j]) {
                if (j == m - 1) {
                    ret.push_back(i - m + 1);
                    j = pi[j];
                }
                else j++;
            }
        }
        return ret;
    }
};

#endif // !__utils__