#pragma once
#include "utils.h"
#include <bits/stdc++.h>

void AhoCorasick::insert(const char * s, const int p) { // Save the appearance of the pattern string s in the p position of the reference
    if (*s == '\0') { // end pattern string
        position = p;
        return;
    }
    int next = Utility::getACGTToInt(*s);
    if (child[next] == nullptr) child[next] = new AhoCorasick(); // Create new if child[next] is empty
    child[next]->insert(s + 1, p); // Insert from child[next]
}

int AhoCorasick::find(const char * s) {
    if (*s == '\0') return position; // return position if found
    int next = Utility::getACGTToInt(*s);
    if (child[next] == nullptr) return -1; // return -1 if child[next] is empty ==> not found
    return child[next]->find(s + 1); // return find(s + 1) from child[next]
}

AhoCorasick::AhoCorasick() : position(0) {
    for (int i = 0; i < 4; i++) child[i] = nullptr;
}

void AhoCorasick::insert(const std::string &s, int p) {
    insert(s.c_str(), p);
}

int AhoCorasick::find(const std::string &s) {
    return find(s.c_str());
}