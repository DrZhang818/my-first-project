#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;
constexpr int N = 1E5;

vector<int> fac[N + 1];

int T[N + 1];
int timer = 0;

void solve() {
    int n, x;
    cin >> n >> x;

    int ans = 1;
    for(int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        if(x % v) continue;
        for(int i = fac[x].size() - 1; i >= 0; i--) {
            int d = fac[x][i];
            if(1LL * d * v > x || T[d] != timer) continue;
            T[d * v] = timer;
        }
        if(T[x] == timer) {
            ans++;
            timer++;
        }
        T[v] = timer;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            fac[j].push_back(i);
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        timer++;
        solve();
    }
    return 0;
}
