#pragma once
#include <bits/stdc++.h>
using namespace std;
vector<int> getNext(const string& pattern) {
    int m = int(pattern.size());
    string p = " " + pattern;
    vector<int> next(m + 1, 0);
    for(int i = 2; i <= m; i++) {
        int j = next[i - 1];
        while(j && p[i] != p[j + 1]) {
            j = next[j];
        }
        if(p[i] == p[j + 1]) {
            j++;
        }
        next[i] = j;
    }
    return next;
}
vector<int> kmpMatch(const string& text, const string& pattern) {
    vector<int> next = getNext(pattern);
    int n = int(text.size());
    int m = int(pattern.size());
    vector<int> result;
    if(m == 0) {
        return result;
    }
    string t = " " + text;
    string p = " " + pattern;
    int j = 0;
    for(int i = 1; i <= n; i++) {
        while(j && t[i] != p[j + 1]) {
            j = next[j];
        }
        if(t[i] == p[j + 1]) {
            j++;
        }
        if(j == m) {
            result.push_back(i - m + 1);
            j = next[j];
        }
    }
    return result;
}
