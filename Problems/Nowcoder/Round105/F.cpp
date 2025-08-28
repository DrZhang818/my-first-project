#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m, x;
    cin >> n >> m >> x;
    vector vis(n + 1, vector(m + 1, vector<bool>(x + 1)));
    vector<int> path(n + 1);
    vector<vector<int>> fac(m + 1);
    for(int i = 1; i <= m; i++) {
        for(int j = i; j <= m; j += i) {
            fac[j].push_back(i);
        }
        fac[0].push_back(i);
    }
    auto dfs = [&](auto &&self, int pos, int g, int sum) -> bool {
        if(pos == n + 1) {
            if(sum == x) {
                for(int i = 1; i <= n; i++) {
                    cout << path[i] << " \n"[i == n];
                }
                return true;
            }
            return false;
        }
        vis[]
        for(int y : fac[g]) {
            int ng = y;
            int nsum = sum + y;
            if(nsum > x) break;
            path[pos] = y;
            if(self(self, pos + 1, ng, nsum)) {
                return true;
            }
        }
        return false;
    };
    if(!dfs(dfs, 1, 0, 0)) {
        cout << -1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
