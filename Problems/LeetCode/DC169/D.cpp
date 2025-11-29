#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class FenwickTree {
private:
    vector<int> tree;
    int n;
public:
    FenwickTree(int x) {
        tree.resize(x + 1);
        n = x;
    }
    void add(int i, int x) {
        while(i <= n) {
            tree[i] += x;
            i += i & -i;
        }
    }
    int query(int i) {
        int res = 0;
        while(i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
    int range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};


class Solution {
public:
    ll countMajoritySubarrays(vector<int>& a, int k) {
        int n = a.size();
        a.insert(a.begin(), 0);
        vector<int> pre(n + 1);
        for(int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + (a[i] == k);
        }
        vector<int> val;
        for(int i = 0; i <= n; i++) {
            val.push_back(2 * pre[i] - i);
        }
        sort(val.begin(), val.end());
        val.erase(unique(val.begin(), val.end()), val.end());
        int sz = val.size();
        FenwickTree tr(sz + 1);
        ll ans = 0;
        for(int i = 0; i <= n; i++) {
            int rk = lower_bound(val.begin(), val.end(), 2 * pre[i] - i) - val.begin() + 1;
            ans += tr.range_query(1, rk - 1);
            tr.add(rk, 1);
        }
        return ans;
    }
};