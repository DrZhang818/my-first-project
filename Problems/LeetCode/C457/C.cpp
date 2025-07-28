#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

vector<int> fa;
int sz;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    fa[u] = v;
    sz--;
}
void init(int n) {
    fa.resize(n + 1);
    iota(fa.begin(), fa.end(), 0);
    sz = n;
}
class Solution {
public:
    int minTime(int n, vector<vector<int>>& e, int k) {
        auto ck = [&](int x) -> int {
            init(n);
            for(int i = 0; i < e.size(); i++) {
                int u = e[i][0], v = e[i][1], t = e[i][2];
                if(t > x) merge(u, v);
            }
            return sz >= k;
        };
        int l = -1, r = inf;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(ck(mid)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        return r;
    }
};