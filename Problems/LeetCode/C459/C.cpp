#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

inline int lowbit(int o) { return o & -o; }
class BIT {
private:
    vector<int> tr;
    int n;
public:
    BIT(int x) : tr(x + 1), n(x){}
    void add(int o, int d) {
        for(; o <= n; o += lowbit(o)) {
            tr[o] += d;
        }
    }
    int query(int o) {
        int res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }
    int range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
int cal(ll x) {
    int d = 0;
    while(x != 1) {
        x = __builtin_popcountll(x);
        d++;
    }
    return d;
}
class Solution {
public:
    vector<int> popcountDepth(vector<ll>& a, vector<vector<ll>>& Q) {
        int n = a.size();
        vector<BIT> tr(6, BIT(n));
        for(int i = 0; i < n; i++) {
            int d = cal(a[i]);
            if(d > 5) continue;
            tr[d].add(i + 1, 1);
        }
        int q = Q.size();
        vector<int> ans;
        for(int i = 0; i < q; i++) {
            int op = Q[i][0];
            if(op == 1) {
                int l = Q[i][1] + 1, r = Q[i][2] + 1, k = Q[i][3];
                ans.push_back(tr[k].range_query(l, r));
            } else {
                int id = Q[i][1] + 1;
                ll v = Q[i][2];
                int d = cal(a[id - 1]);
                if(d <= 5) tr[d].add(id, -1);
                a[id - 1] = v;
                d = cal(v);
                if(d <= 5) tr[d].add(id, 1);
            }
        }
        return ans;
    }
};