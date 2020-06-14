#ifndef __utils__
#define __utils__ 1

// #include <iostream>
// #include <string>
// #include <vector>
// #include <Windows.h>
// #include <assert.h>
#include <bits/stdc++.h>

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
    AhoCorasick() {
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


/////////////////////////////////////// Euler Path ///////////////////////////////

class Euler {
    std::vector<std::vector<Edge*>> G;
    std::vector<bool> visit;
    std::vector<int> indegree, outdegree;
    std::vector<int> find(int cur) {
        std::vector<int> ret;
        for (int i = 0; i < G[cur].size(); i++) {
            if (G[cur][i]->go) {
                G[cur][i]->go = false;
                if (G[cur][i]->back != nullptr) G[cur][i]->back->go = false;
                std::vector<int> e = find(G[cur][i]->to);
                for (int j = 0; j < e.size(); j++) ret.push_back(e[j]);
            }
        }
        ret.insert(ret.begin(), cur);
        return ret;
    }
public:
    Euler(const std::vector<std::vector<int>> &g) {
        G.resize(g.size());
        visit.resize(G.size());
        indegree.resize(G.size());
        outdegree.resize(G.size());
        std::cout << "g\n";
        for (int i = 0; i < g.size(); i++) {
            std::cout << i << " : ";
            for (int j = 0; j < g[i].size(); j++) {
                std::cout << g[i][j] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
        for (int i = 0; i < g.size(); i++) {
            for (int j = 0; j < g[i].size(); j++) {
                indegree[g[i][j]]++;
                outdegree[i]++;
                Edge * a = new Edge(g[i][j]), * b = new Edge(i);
                b->back = a;
                G[i].push_back(a);
                G[j].push_back(b);
            }
        }
    }
    std::vector<int> find() {
        int start = 0, __min = 1 << 29;
        for (int i = 0; i < G.size(); i++) {
            if (indegree[i] < __min) {
                __min = indegree[i];
                start = i;
            }
        }
        return find(start);
    }
};

#endif // !__utils__