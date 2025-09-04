#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef unsigned int ui;
const int inf = 1000000000;

struct Hash {
    ull operator()(const vector<int> &a) const {
        ull res = 0;
        for(int i = 0; i < a.size(); i++) {
            res = res * 31 + a[i];
        }
        return res;
    }
};

void solve(int n) {
    vector<int> a(n);
    int tot = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        tot += a[i];
    }
    unordered_map<vector<int>,ll,Hash> dp;
    auto dfs = [&](auto &&self, vector<int> &cur, int x) -> ll {
        if(x == tot + 1) {
            return 1;
        }
        if(dp.find(cur) != dp.end()) {
            return dp[cur];
        }
        ll res = 0;
        for(int i = 0; i < n; i++) {
            if((i == 0 || cur[i] < cur[i - 1]) && cur[i] != a[i]) {
                cur[i]++;
                res += self(self, cur, x + 1);
                cur[i]--;                
            }
        }
        return dp[cur] = res;
    };
    vector<int> num(n);
    cout << dfs(dfs, num, 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while(cin >> n) {
        if(n == 0) break;
        solve(n);
    }
    return 0;
}
