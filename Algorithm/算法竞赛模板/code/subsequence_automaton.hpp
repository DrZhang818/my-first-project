#pragma once
#include <bits/stdc++.h>
using namespace std;
struct SeqAM {
    int n, sigma;
    char base;
    vector<vector<int>> nxt; // nxt[i][c]：从位置 i（含）起第一个字符 c，无则 n + 1
    SeqAM(const string& s, int sigma_, char offset = 'a')
        : n(int(s.size())), sigma(sigma_), base(offset),
          nxt(n + 2, vector<int>(sigma_, n + 1)) {
        for(int i = n; i >= 1; i--) {
            nxt[i] = nxt[i + 1];
            nxt[i][s[i - 1] - offset] = i;
        }
    }
    bool check(const string& t) const {
        int cur = 0;
        for(char c : t) {
            int x = c - base;
            if(x < 0 || x >= sigma) {
                return false;
            }
            cur = nxt[cur + 1][x];
            if(cur == n + 1) {
                return false;
            }
        }
        return true;
    }
};
