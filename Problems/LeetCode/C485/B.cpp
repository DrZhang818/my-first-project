#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

inline int lowbit(int o) { return o & -o; }
struct FenwickTree {
    int n;
    vector<int> tr;
    FenwickTree(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        tr.assign(n, {});
    }
    void add(int o, int x) {
        for(; o < n; o += lowbit(o)) {
            tr[o] = max(tr[o], x);
        }
    }
    int query(int o) {
        int res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res = max(res, tr[o]);
        }
        return res;
    }
};

class Solution {
public:
    int maxCapacity(vector<int>& a, vector<int>& b, int k) {
        FenwickTree fen(k + 1);
        int ans = 0;
        for(int i = 0; i < a.size(); i++) {
            if(a[i] >= k) {
                continue;
            }
            ans = max(ans, b[i] + fen.query(k - 1 - a[i]));
            fen.add(a[i], b[i]);
        }
        return ans;
    }
};
