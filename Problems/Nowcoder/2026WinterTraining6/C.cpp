#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
  
    vector<int> fa {-1};
    vector<int> lson {-1}, rson {-1};
    vector<int> L {1}, R {n};
    int id = 1;
    map<PII,int> mp;
    mp[{1, n}] = 0;
    for(int i = 0; i < id; i++) {
        if(L[i] == R[i]) continue;
        int mid = L[i] + R[i] >> 1;
        fa.push_back(i);
        lson.push_back(-1);
        rson.push_back(-1);
        L.push_back(L[i]);
        R.push_back(mid);
        lson[i] = id;
        mp[{L[id], R[id]}] = id;
        id++;

        fa.push_back(i);
        lson.push_back(-1);
        rson.push_back(-1);
        rson[i] = id;
        L.push_back(mid + 1);
        R.push_back(R[i]);
        mp[{L[id], R[id]}] = id;
        id++;
    }  

    int m = id;
    vector<int> vis(m);
    vector<int> dp(m, 1);

    int q = n;
    while(q--) {
        int op, l, r;
        cin >> op >> l >> r;
        if(op == 1) {
            id = mp[{l, r}];
            if(!vis[id]) {
                vis[id] = true;
                while(id != -1 && vis[id]) {
                    if(lson[id] != -1) {
                        dp[id] = dp[lson[id]] + dp[rson[id]];
                    } else {
                        dp[id] = 0;
                    }
                    id = fa[id];
                }
            }
        } else {
            auto dfs = [&](auto&& self, int o, int l, int r) -> int {
                if(o == -1 || l > R[o] || r < L[o]) return 0;
                if(l <= L[o] && R[o] <= r) {
                    return dp[o];
                }
                return self(self, lson[o], l, r) + self(self, rson[o], l, r) + (vis[o] ? 0 : 1);
            };
            int ans = dfs(dfs, 0, l, r);
            cout << ans << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
