#pragma once
#include <bits/stdc++.h>
using namespace std;
int lisLength(const vector<int>& a, bool strict = true) {
    vector<int> d;
    d.reserve(a.size());
    for(int x : a) {
        auto it = strict ? lower_bound(d.begin(), d.end(), x)
                         : upper_bound(d.begin(), d.end(), x);
        if(it == d.end()) {
            d.push_back(x);
        } else {
            *it = x;
        }
    }
    return int(d.size());
}
