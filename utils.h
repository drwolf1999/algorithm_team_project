#pragma once
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

class AhoCorasick {
    AhoCorasick * child[4]; // child (0=>'A', 1=>'C', 2=>'G', 3=>'T')
    int position; // Save where pattern appeared
    void insert(const char * s, const int p);
    int find(const char * s);
    public:
    AhoCorasick();
    void insert(const std::string &s, int p);
    int find(const std::string &s);
};