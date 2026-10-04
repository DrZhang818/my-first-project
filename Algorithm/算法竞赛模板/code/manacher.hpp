#pragma once
#include <bits/stdc++.h>
using namespace std;
vector<int> manacherRadius(const string& s) {
    vector<int> t = {257, 256};
    for(char c : s) {
        t.push_back((unsigned char)c);
        t.push_back(256);
    }
    t.push_back(258);
    int n = int(t.size());
    vector<int> P(n);
    int R = 0, C = 0;
    for(int i = 1; i < n - 1; i++) {
        P[i] = i < R ? min(P[2 * C - i], P[C] + C - i) : 1;
        while(t[i + P[i]] == t[i - P[i]]) {
            P[i]++;
        }
        if(P[i] + i > R) {
            R = P[i] + i;
            C = i;
        }
    }
    return P;
}
int longestPal(const string& s) {
    vector<int> P = manacherRadius(s);
    int ans = 1;
    for(int x : P) {
        ans = max(ans, x);
    }
    return ans - 1;
}
