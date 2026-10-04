#pragma once
#include <bits/stdc++.h>
using namespace std;
template <class T, class Compare = less<T>> struct Cartesian {
    int root = 0;
    vector<int> parent, left, right;
    Cartesian(const vector<T>& a, Compare cmp = Compare())
        : parent(a.size()), left(a.size()), right(a.size()) {
        vector<int> st;
        for(int i = 1; i < int(a.size()); i++) {
            int last = 0;
            while(!st.empty() && cmp(a[i], a[st.back()])) {
                last = st.back();
                st.pop_back();
            }
            if(!st.empty()) {
                parent[i] = st.back();
                right[st.back()] = i;
            }
            if(last) {
                parent[last] = i;
                left[i] = last;
            }
            st.push_back(i);
        }
        if(!st.empty()) {
            root = st.front();
        }
    }
};
