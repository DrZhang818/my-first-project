#pragma once
#include <bits/stdc++.h>
using namespace std;
template <int SIGMA = 26, char BASE = 'a'> struct Trie {
    struct Node {
        array<int, SIGMA> ch{};
        int cnt = 0;
        int end = 0;
    };
    vector<Node> tr;
    Trie(int n = 0) {
        if(n) {
            tr.reserve(n);
        }
        tr.emplace_back();
    }
    int newNode() {
        tr.emplace_back();
        return int(tr.size()) - 1;
    }
    int id(char c) const {
        return c - BASE;
    }
    int size() const {
        return int(tr.size());
    }
    void clear() {
        tr.clear();
        tr.emplace_back();
    }
    int go(int u, char c) {
        int x = id(c);
        if(!tr[u].ch[x]) {
            tr[u].ch[x] = newNode();
        }
        return tr[u].ch[x];
    }
    int next(int u, char c) const {
        int x = id(c);
        int v = tr[u].ch[x];
        return v ? v : -1;
    }
    int insert(const string& s) {
        int u = 0;
        tr[u].cnt++;
        for(char c : s) {
            u = go(u, c);
            tr[u].cnt++;
        }
        tr[u].end++;
        return u;
    }
    int find(const string& s) const {
        int u = 0;
        for(char c : s) {
            int x = id(c);
            if(!tr[u].ch[x]) {
                return -1;
            }
            u = tr[u].ch[x];
        }
        return u;
    }
    int count(const string& s) const {
        int u = find(s);
        return u == -1 ? 0 : tr[u].end;
    }
    int countPrefix(const string& s) const {
        int u = find(s);
        return u == -1 ? 0 : tr[u].cnt;
    }
    bool contains(const string& s) const {
        return count(s) > 0;
    }
    bool erase(const string& s) {
        int u = find(s);
        if(u == -1 || tr[u].end == 0) {
            return false;
        }
        tr[0].cnt--;
        u = 0;
        for(char c : s) {
            u = tr[u].ch[id(c)];
            tr[u].cnt--;
        }
        tr[u].end--;
        return true;
    }
};
