#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;
constexpr int N = 1E5;

vector<int> minp, primes;

auto init = []() {
    minp.resize(N + 1);
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }

    return 1;
}();

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> vis(N + 1);
    for(int i = 1; i <= n; i++) {
        int x = a[i];
        while(x > 1) {
            int p = minp[x];
            vis[p] = true;
            while(minp[x] == p) {
                x /= p;
            }
        }
    }

    for(auto p : primes) {
        if(p > m || !vis[p]) continue;
        for(int i = 1; i * p <= m; i++) {
            vis[i * p] = true;
        }
    }

    int cnt = 0;
    for(int i = 1; i <= m; i++) {
        if(!vis[i]) {
            cnt++;
        }
    }
    cout << cnt << "\n";
    for(int i = 1; i <= m; i++) {
        if(!vis[i]) {
            cout << i << "\n";
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
