#include <bits/stdc++.h>
using namespace std;
struct SAM {
    struct Node {
        int len, fa, ch[26];
        long long cnt;
        Node() : len(0), fa(-1), cnt(0) {
            fill(ch, ch + 26, -1);
        }
    };
    vector<Node> t;
    vector<int> ord;
    int last, n;
    bool done;
    SAM() : t(1), last(0), n(0), done(false) {
    }
    void add(char c) {
        assert(!done);
        int x = c - 'a', u = t.size(), p = last;
        t.push_back(Node());
        t[u].len = ++n;
        t[u].cnt = 1;
        while(p != -1 && t[p].ch[x] == -1) {
            t[p].ch[x] = u, p = t[p].fa;
        }
        if(p == -1) {
            t[u].fa = 0;
        } else {
            int q = t[p].ch[x];
            if(t[p].len + 1 == t[q].len) {
                t[u].fa = q;
            } else {
                int v = t.size();
                t.push_back(t[q]);
                t[v].len = t[p].len + 1;
                t[v].cnt = 0;
                while(p != -1 && t[p].ch[x] == q) {
                    t[p].ch[x] = v, p = t[p].fa;
                }
                t[q].fa = t[u].fa = v;
            }
        }
        last = u;
    }
    void build(const string& s) {
        for(size_t i = 0; i < s.size(); i++) {
            add(s[i]);
        }
    }
    void count() {
        if(done) {
            return;
        }
        done = true;
        vector<int> c(n + 1);
        ord.resize(t.size());
        for(size_t i = 0; i < t.size(); i++) {
            ++c[t[i].len];
        }
        for(int i = 1; i <= n; i++) {
            c[i] += c[i - 1];
        }
        for(int i = int(t.size()) - 1; i >= 0; i--) {
            ord[--c[t[i].len]] = i;
        }
        for(int i = int(ord.size()) - 1; i > 0; i--) {
            int u = ord[i];
            t[t[u].fa].cnt += t[u].cnt;
        }
    }
    long long occ(const string& s) {
        count();
        int u = 0;
        for(size_t i = 0; i < s.size(); i++) {
            int x = s[i] - 'a';
            if(x < 0 || x >= 26 || t[u].ch[x] < 0) {
                return 0;
            }
            u = t[u].ch[x];
        }
        return s.empty() ? n + 1 : t[u].cnt;
    }
    long long distinct() const {
        long long ans = 0;
        for(size_t i = 1; i < t.size(); i++) {
            ans += t[i].len - t[t[i].fa].len;
        }
        return ans;
    }
    int lcs(const string& s) const {
        int u = 0, len = 0, ans = 0;
        for(size_t i = 0; i < s.size(); i++) {
            int x = s[i] - 'a';
            if(x < 0 || x >= 26) {
                u = len = 0;
                continue;
            }
            while(u && t[u].ch[x] < 0) {
                u = t[u].fa, len = t[u].len;
            }
            if(t[u].ch[x] >= 0) {
                u = t[u].ch[x], ++len;
            } else {
                u = len = 0;
            }
            ans = max(ans, len);
        }
        return ans;
    }
};
