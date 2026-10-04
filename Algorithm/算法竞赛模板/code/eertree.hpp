#pragma once
#include <bits/stdc++.h>
using namespace std;
struct PAM {
    struct Node {
        int len, link;
        array<int, 26> next{};
        int cnt = 0;
        Node() : len(0), link(0), cnt(0) {
        }
    };
    vector<Node> tr;
    string s;
    int last;
    bool propagated = false;
    PAM(const string& str) : s(str), last(1) {
        tr.resize(2);
        tr[0].len = -1;
        tr[0].link = 0;
        tr[1].len = 0;
        tr[1].link = 0;
        for(int i = 0; i < int(s.size()); i++) {
            extend(i);
        }
    }
    int extend(int pos) {
        assert(!propagated);
        int c = s[pos] - 'a';
        int cur = last;
        while(true) {
            int curlen = tr[cur].len;
            if(pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                break;
            }
            cur = tr[cur].link;
        }
        if(tr[cur].next[c]) {
            last = tr[cur].next[c];
            tr[last].cnt++;
            return last;
        }
        int now = int(tr.size());
        tr.emplace_back();
        tr[now].len = tr[cur].len + 2;
        tr[cur].next[c] = now;
        tr[now].cnt = 1;
        if(tr[now].len == 1) {
            tr[now].link = 1;
        } else {
            int link = tr[cur].link;
            while(true) {
                int linklen = tr[link].len;
                if(pos - 1 - linklen >= 0 && s[pos - 1 - linklen] == s[pos]) {
                    break;
                }
                link = tr[link].link;
            }
            tr[now].link = tr[link].next[c];
        }
        last = now;
        return now;
    }
    void count() {
        if(propagated) {
            return;
        }
        propagated = true;
        vector<int> order(tr.size());
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(),
             [&](int a, int b) { return tr[a].len > tr[b].len; });
        for(int v : order) {
            if(v >= 2) {
                tr[tr[v].link].cnt += tr[v].cnt;
            }
        }
    }
    int distinct() const {
        return int(tr.size()) - 2;
    }
    int size() const {
        return int(tr.size());
    }
};
