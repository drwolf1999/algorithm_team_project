#ifndef __utils__
#define __utils__ 1

#include <bits/stdc++.h>

class Utility {
    public:
    static inline int getACGTToInt(const char ACGT); // Mapping 'A'=0, 'C'=1, 'G'=2, 'T'=3
};

//////////////////////////////////////// Aho-Corasick /////////////////////////////////////

template <class T> class AhoCorasick {
    AhoCorasick * child[4]; // child (0=>'A', 1=>'C', 2=>'G', 3=>'T')
    bool terminal; // this position is end
    std::vector<T> identifiers;
    void insert(const char * s, const T ident);
    std::vector<T> find(const char * s);
    public:
    AhoCorasick();
    ~AhoCorasick();
    void insert(const std::string &s, T ident);
    std::vector<T> find(const std::string &s);
};

//////////////////////////////////////// Pair ////////////////////////////////

template <class T1, class T2> class Pair {
  public:
    T1 x;
    T2 y;
    Pair(T1 x_ = T1(), T2 y_ = T2());
    bool operator<(const Pair &p) const;
    bool operator>(const Pair &p) const;
    bool operator!=(const Pair &p) const;
    bool operator==(const Pair &p) const;
    friend istream &operator>>(istream &stream, Pair &p);
    friend ostream &operator<<(ostream &stream, const Pair &p);
};

#endif // !__utils__