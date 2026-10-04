#pragma once
#include <bits/stdc++.h>
using namespace std;
template <class Info> struct Seg {
    int n;
    vector<Info> tr;
    Seg(int n_ = 0) : n(n_), tr(2 * n_) {
    }
    Seg(const vector<Info>& a) : Seg(int(a.size()) - 1) {
        for(int i = 1; i <= n; i++) {
            tr[n + i - 1] = a[i];
        }
        for(int p = n - 1; p > 0; p--) {
            pull(p);
        }
    }
    void pull(int p) {
        tr[p] = tr[p << 1] + tr[p << 1 | 1];
    }
    void modify(int p, const Info& v) {
        tr[p += n - 1] = v;
        while(p > 1) {
            p >>= 1;
            pull(p);
        }
    }
    Info query(int l, int r) const {
        Info a, b;
        for(l += n - 1, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) {
                a = a + tr[l++];
            }
            if(r & 1) {
                b = tr[--r] + b;
            }
        }
        return a + b;
    }
    template <class F> int first(int l, int r, F pred) const {
        int a[64], b[64], ca = 0, cb = 0;
        for(l += n - 1, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) {
                a[ca++] = l++;
            }
            if(r & 1) {
                b[cb++] = --r;
            }
        }
        Info cur;
        auto work = [&](int p) {
            Info nxt = cur + tr[p];
            if(!pred(nxt)) {
                cur = nxt;
                return -1;
            }
            while(p < n) {
                p <<= 1;
                nxt = cur + tr[p];
                if(!pred(nxt)) {
                    cur = nxt;
                    p |= 1;
                }
            }
            return p - n + 1;
        };
        for(int i = 0; i < ca; i++) {
            int p = work(a[i]);
            if(p != -1) {
                return p;
            }
        }
        for(int i = cb - 1; i >= 0; i--) {
            int p = work(b[i]);
            if(p != -1) {
                return p;
            }
        }
        return -1;
    }
    template <class F> int last(int l, int r, F pred) const {
        int a[64], b[64], ca = 0, cb = 0;
        for(l += n - 1, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) {
                a[ca++] = l++;
            }
            if(r & 1) {
                b[cb++] = --r;
            }
        }
        Info cur;
        auto work = [&](int p) {
            Info nxt = tr[p] + cur;
            if(!pred(nxt)) {
                cur = nxt;
                return -1;
            }
            while(p < n) {
                p = p << 1 | 1;
                nxt = tr[p] + cur;
                if(!pred(nxt)) {
                    cur = nxt;
                    p ^= 1;
                }
            }
            return p - n + 1;
        };
        for(int i = 0; i < cb; i++) {
            int p = work(b[i]);
            if(p != -1) {
                return p;
            }
        }
        for(int i = ca - 1; i >= 0; i--) {
            int p = work(a[i]);
            if(p != -1) {
                return p;
            }
        }
        return -1;
    }
};
