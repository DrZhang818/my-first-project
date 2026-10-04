#pragma once
#include <bits/stdc++.h>
using namespace std;
int minRotation(const string& s) {
    int n = int(s.size());
    if(n == 0) {
        return 0;
    }
    string t = s + s;
    int i = 0, j = 1, k = 0;
    while(i < n && j < n && k < n) {
        unsigned char a = t[i + k];
        unsigned char b = t[j + k];
        if(a == b) {
            k++;
            continue;
        }
        if(a > b) {
            i += k + 1;
            if(i == j) {
                j++;
            }
        } else {
            j += k + 1;
            if(i == j) {
                j++;
            }
        }
        k = 0;
    }
    return min(i, j);
}
