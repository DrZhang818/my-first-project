#pragma once
#include <bits/stdc++.h>
using namespace std;
struct AC {
    struct Node {
        array<int, 26> ch{};
        int fa = 0;
    };
    vector<Node> t;
    vector<int> ord;
    bool done = false;
    AC() : t(1) {
    }
    int add(const string& s) {
        assert(!done && !s.empty());
        int u = 0;
        for(char c : s) {
            int x = c - 'a';
            if(!t[u].ch[x]) {
                int v = t.size();
                t.emplace_back();
                t[u].ch[x] = v;
            }
            u = t[u].ch[x];
        }
        return u;
    }
    void build() {
        if(done) {
            return;
        }
        done = true;
        queue<int> q;
        for(int c = 0; c < 26; c++) {
            if(t[0].ch[c]) {
                q.push(t[0].ch[c]);
            }
        }
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            ord.push_back(u);
            for(int c = 0; c < 26; c++) {
                int v = t[u].ch[c];
                if(v) {
                    t[v].fa = t[t[u].fa].ch[c], q.push(v);
                } else {
                    t[u].ch[c] = t[t[u].fa].ch[c];
                }
            }
        }
    }
    // hits[end[i]] is the occurrence count of pattern i, allowing overlap.
    vector<long long> match(const string& s) {
        build();
        vector<long long> hit(t.size());
        int u = 0;
        for(char c : s) {
            u = t[u].ch[c - 'a'], ++hit[u];
        }
        for(int i = int(ord.size()) - 1; i >= 0; i--) {
            hit[t[ord[i]].fa] += hit[ord[i]];
        }
        return hit;
    }
};
