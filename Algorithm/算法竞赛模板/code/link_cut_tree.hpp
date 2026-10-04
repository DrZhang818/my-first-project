#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct LCT {
    struct Node {
        int ch[2]{}, fa = 0;
        i64 val = 0, sum = 0;
        bool rev = false;
    };
    vector<Node> tr;
    LCT(int n = 0) : tr(n + 1) {
    }
    bool isRoot(int x) const {
        int f = tr[x].fa;
        return !f || (tr[f].ch[0] != x && tr[f].ch[1] != x);
    }
    void pull(int x) {
        tr[x].sum = tr[tr[x].ch[0]].sum ^ tr[x].val ^ tr[tr[x].ch[1]].sum;
    }
    void applyRev(int x) {
        if(!x) {
            return;
        }
        swap(tr[x].ch[0], tr[x].ch[1]);
        tr[x].rev ^= 1;
    }
    void push(int x) {
        if(!tr[x].rev) {
            return;
        }
        applyRev(tr[x].ch[0]);
        applyRev(tr[x].ch[1]);
        tr[x].rev = false;
    }
    void rotate(int x) {
        int y = tr[x].fa, z = tr[y].fa;
        int k = tr[y].ch[1] == x;
        if(!isRoot(y)) {
            tr[z].ch[tr[z].ch[1] == y] = x;
        }
        tr[x].fa = z;
        tr[y].ch[k] = tr[x].ch[k ^ 1];
        if(tr[x].ch[k ^ 1]) {
            tr[tr[x].ch[k ^ 1]].fa = y;
        }
        tr[x].ch[k ^ 1] = y;
        tr[y].fa = x;
        pull(y);
        pull(x);
    }
    void splay(int x) {
        vector<int> st{x};
        for(int y = x; !isRoot(y); y = tr[y].fa) {
            st.push_back(tr[y].fa);
        }
        while(!st.empty()) {
            push(st.back());
            st.pop_back();
        }
        while(!isRoot(x)) {
            int y = tr[x].fa, z = tr[y].fa;
            if(!isRoot(y)) {
                if((tr[y].ch[1] == x) == (tr[z].ch[1] == y)) {
                    rotate(y);
                } else {
                    rotate(x);
                }
            }
            rotate(x);
        }
    }
    int access(int x) {
        int y = 0;
        for(int z = x; z; z = tr[z].fa) {
            splay(z);
            tr[z].ch[1] = y;
            pull(z);
            y = z;
        }
        splay(x);
        return y;
    }
    void makeRoot(int x) {
        access(x);
        applyRev(x);
    }
    int findRoot(int x) {
        access(x);
        while(tr[x].ch[0]) {
            push(x);
            x = tr[x].ch[0];
        }
        splay(x);
        return x;
    }
    bool connected(int x, int y) {
        return x == y || findRoot(x) == findRoot(y);
    }
    bool link(int x, int y) {
        makeRoot(x);
        if(findRoot(y) == x) {
            return false;
        }
        tr[x].fa = y;
        return true;
    }
    bool cut(int x, int y) {
        makeRoot(x);
        access(y);
        if(tr[y].ch[0] != x || tr[x].ch[1]) {
            return false;
        }
        tr[y].ch[0] = tr[x].fa = 0;
        pull(y);
        return true;
    }
    void setValue(int x, i64 value) {
        access(x);
        tr[x].val = value;
        pull(x);
    }
    i64 pathXor(int x, int y) {
        makeRoot(x);
        access(y);
        return tr[y].sum;
    }
};
