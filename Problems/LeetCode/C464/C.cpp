#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class FenwickTree {
private:
    vector<int> tr;
    int n;
public:
    FenwickTree(int x) {
        tr.resize(x + 1);
        n = x;
    }
    void add(int i, int x) {
        while(i <= n) {
            tr[i] = max(tr[i], x);
            i += i & -i;
        }
    }
    int query(int i) {
        int res = 0;
        while(i > 0) {
            res = max(res, tr[i]);
            i -= i & -i;
        }
        return res;
    }
};

class Solution {
public:
    vector<int> maxValue(vector<int>& a) {
        int n = a.size();
        vector<int> ans(a);
        vector<int> val(a);
        sort(val.begin(), val.end());
        val.erase(unique(val.begin(), val.end()), val.end());
        vector<int> na(n);
        for(int i = 0; i < n; i++) {
            na[i] = lower_bound(val.begin(), val.end(), a[i]) - val.begin() + 1;
        }
        for(int p = 0; p < 3; p++) {
            for(int i = 0, mx = 0; i < n; i++) {
                mx = max(mx, ans[i]);
                ans[i] = mx;
            }
            int sz = val.size();
            FenwickTree tr(sz + 1);
            for(int i = n - 1; i >= 0; i--) {
                int pre = tr.query(na[i] - 1);
                ans[i] = max(ans[i], pre);
                tr.add(na[i], ans[i]);
            }
        }
        return ans;
    }
};