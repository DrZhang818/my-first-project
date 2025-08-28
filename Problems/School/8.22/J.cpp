#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<int> x(n + 1), a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<array<int,61>> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        dp[i][0] = x[i];
    }
    for(int s = 1; s <= 60; s++) {
        for(int i = 1; i <= n; i++) {
            dp[i][s] = dp[dp[i][s - 1]][s - 1];
        }
    }
    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    for(int s = 60; s >= 0; s--) {
        if(k > (1LL << s)) {
            k -= (1LL << s);
            for(int i = 1; i <= n; i++) {
                p[i] = dp[p[i]][s];
            }
        }
    }
    if(k) {
        k--;
        for(int i = 1; i <= n; i++) {
            p[i] = dp[p[i]][0];
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << a[p[i]] << " \n"[i == n];
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
