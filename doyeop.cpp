#pragma once
#include "doyeop.h"
#include <bits/stdc++.h>
using namespace std;

DoYeop::DoYeop(const char * REFER_FILE, const char * SHORT_FILE) : FileManager(REFER_FILE, SHORT_FILE) {
    ac = new AhoCorasick();
}

DoYeop::~DoYeop() {
    delete ac;
}

std::string DoYeop::Solve() {
    //
}