#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1203/problem/F2

struct info {
    int u, v;
    friend bool operator < (const info &a, const info &b) {
        if(a.v >= 0 && b.v < 0) return 1;
        if(a.v < 0 && b.v >= 0) return 0;
        if(a.v >= 0 && b.v >= 0) return a.u < b.u;
        return a.u + a.v > b.u + b.v;
    }
};
void solve() {
    int n, r;
    cin >> n >> r;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].u >> a[i].v;
    }
    sort(a.begin() + 1, a.end());
    vector<int> dp(n + 1, -inf);
    dp[0] = r;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j >= 1; j--) {
            if(dp[j - 1] >= a[i].u) {
                dp[j] = max(dp[j], dp[j - 1] + a[i].v);
            }
        }
    }
    for(int i = n; i >= 0; i--) {
        if(dp[i] >= 0) {
            cout << i << "\n";
            return;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
