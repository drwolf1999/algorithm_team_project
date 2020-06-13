#include "utils.h"
#include <bits/stdc++.h>

inline int Utility::getACGTToInt(const char ACGT) { // Mapping 'A'=0, 'C'=1, 'G'=2, 'T'=3
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

//////////////////////////////////////// Aho-Corasick /////////////////////////////////////
template <class T>
void AhoCorasick<T>::insert(const char * s, const T ident) { // Save the appearance of the pattern string s in the p position of the reference
    if (*s == '\0') { // end pattern string
        terminal = true;
        identifiers.push_back(ident);
        return;
    }
    int next = Utility::getACGTToInt(*s);
    if (child[next] == nullptr) child[next] = new AhoCorasick(); // Create new if child[next] is empty
    child[next]->insert(s + 1, ident); // Insert from child[next]
}

template <class T>
std::vector<T> AhoCorasick<T>::find(const char * s) {
    if (*s == '\0') return identifiers; // return position if found
    int next = Utility::getACGTToInt(*s);
    if (child[next] == nullptr) return std::vector<T>({}); // return empty {} if child[next] is empty ==> not found
    return child[next]->find(s + 1); // return find(s + 1) from child[next]
}

template <class T>
AhoCorasick<T>::AhoCorasick() {
    for (int i = 0; i < 4; i++) child[i] = nullptr;
}

template <class T>
AhoCorasick<T>::~AhoCorasick() {
    for (int i = 0; i < 4; i++) delete child[i];
}

template <class T>
void AhoCorasick<T>::insert(const std::string &s, T ident) {
    insert(s.c_str(), ident);
}

template <class T>
std::vector<T> AhoCorasick<T>::find(const std::string &s) {
    return find(s.c_str());
}



////////////////////////////// Pair /////////////////////////////////
template <class T1, class T2>
Pair<T1, T2>::Pair(T1 x_ = T1(), T2 y_ = T2()) : x(x_), y(y_) {}

template <class T1, class T2>
bool Pair<T1, T2>::operator<(const Pair<T1, T2> &p) const {
    if (x == p.x) return y > p.y;
    return x < p.x;
}

template <class T1, class T2>
bool Pair<T1, T2>::operator>(const Pair<T1, T2> &p) const {
    if (x == p.x) return y > p.y;
    return x > p.x;
}

template <class T1, class T2>
bool Pair<T1, T2>::operator!=(const Pair<T1, T2> &p) const { return x != p.x || y != p.y; }

template <class T1, class T2>
bool Pair<T1, T2>::operator==(const Pair<T1, T2> &p) const { return x == p.x && y == p.y; }

template <class T1, class T2>
std::istream &operator>>(std::istream &stream, Pair<T1, T2> &p) {
    stream >> p.x >> p.y;
    return stream;
}

template <class T1, class T2>
std::ostream &operator<<(std::ostream &stream, const Pair<T1, T2> &p) {
    stream << p.x << ' ' << p.y;
    return stream;
}