#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int N = 100000;
int minp[N + 1];
vector<int> primes;
int init = []() {
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) {
                break;
            }
            minp[i * p] = p;
            if(p == minp[i]) {
                break;
            }
        }
    }
    return 0;
}();
inline int ls(int o) { return o << 1; };
inline int rs(int o) { return o << 1 | 1; }
class Solution {
public:
    vector<int> mx, tag;
    void push_up(int o) {
        mx[o] = max(mx[ls(o)], mx[rs(o)]);
    }
    void add_tag(int o, int d) {
        tag[o] += d;
        mx[o] += d;
    }
    void push_down(int o) {
        if(tag[o]) {
            add_tag(ls(o), tag[o]);
            add_tag(rs(o), tag[o]);
            tag[o] = 0;
        }
    }
    void update(int L, int R, int o, int l, int r, int d) {
        if(L <= l && r <= R) {
            add_tag(o, d);
            return;
        }
        push_down(o);
        int mid = l + r >> 1;
        if(L <= mid) update(L, R, ls(o), l, mid, d);
        if(R > mid) update(L, R, rs(o), mid + 1, r, d);
        push_up(o);
    }
    int query(int L, int R, int o, int l, int r) {
        if(L <= l && r <= R) return mx[o];
        push_down(o);
        int res = -inf;
        int mid = l + r >> 1;
        if(L <= mid) res = max(res, query(L, R, ls(o), l, mid));
        if(R > mid) res = max(res, query(L, R, rs(o), mid + 1, r));
        return res;
    }
    vector<int> maximumCount(vector<int>& a, vector<vector<int>>& Q) {
        int n = a.size();
        a.insert(a.begin(), 0);
        mx.resize(n << 2);
        tag.resize(n << 2);
        unordered_map<int, set<int>> mp;
        for(int i = 1; i <= n; i++) {
            if(a[i] == minp[a[i]]) {
                mp[a[i]].insert(i);
            }
        }
        for(auto &[p, st] : mp) {
            if(st.size() > 1) update(*st.begin() + 1, *st.rbegin(), 1, 1, n, 1);
        }
        vector<int> ans(Q.size());
        for(int i = 0; i < Q.size(); i++) {
            int o = Q[i][0] + 1, v = Q[i][1];
            if(a[o] == minp[a[o]]) {
                auto &st = mp[a[o]];
                if(st.size() > 1) {
                    update(*st.begin() + 1, *st.rbegin(), 1, 1, n, -1);
                }
                st.erase(o);
                if(st.size() > 1) {
                    update(*st.begin() + 1, *st.rbegin(), 1, 1, n, 1);
                } else if(st.empty()) {
                    mp.erase(a[o]);
                }
            }
            a[o] = v;
            if(a[o] == minp[a[o]]) {
                auto &st = mp[a[o]];
                if(st.size() > 1) {
                    update(*st.begin() + 1, *st.rbegin(), 1, 1, n, -1);
                }
                st.insert(o);
                if(st.size() > 1) {
                    update(*st.begin() + 1, *st.rbegin(), 1, 1, n, 1);
                }
            }
            ans[i] = mp.size() + query(1, n, 1, 1, n);
        }
        return ans;
    }
};