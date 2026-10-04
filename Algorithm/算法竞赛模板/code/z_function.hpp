#pragma once
#include <bits/stdc++.h>
using namespace std;
vector<int> zFunction(const string& s) {
    string t = " " + s;
    int n = int(s.size());
    vector<int> z(n + 1);
    if(n == 0) {
        return z;
    }
    z[1] = n;
    for(int i = 2, l = 0, r = 0; i <= n; i++) {
        if(i <= r) {
            z[i] = min(z[i - l + 1], r - i + 1);
        }
        while(i + z[i] <= n && t[1 + z[i]] == t[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
vector<int> exKmp(const string& text, const string& pattern) {
    vector<int> z = zFunction(pattern);
    string t = " " + text;
    string p = " " + pattern;
    int n = int(text.size());
    int m = int(pattern.size());
    vector<int> ext(n + 1);
    for(int i = 1, l = 0, r = 0; i <= n; i++) {
        if(i <= r) {
            ext[i] = min(z[i - l + 1], r - i + 1);
        }
        while(i + ext[i] <= n && ext[i] < m && p[1 + ext[i]] == t[i + ext[i]]) {
            ext[i]++;
        }
        if(i + ext[i] - 1 > r) {
            l = i;
            r = i + ext[i] - 1;
        }
    }
    return ext;
}
