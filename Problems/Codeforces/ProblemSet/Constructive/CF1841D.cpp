#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

constexpr int inf = 1000000000;
int n, sz;
struct info {
    ll l, r;
    friend bool operator < (const info &a, const info &b) {
        if(a.l != b.l) return a.l < b.l;
        return a.r < b.r;
    }
};
void solve() { 
    cin >> n;
    vector<info> a(n + 1);
    vector<int> x;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
        x.push_back(a[i].l);
        x.push_back(a[i].r);
    }
    sort(a.begin() + 1, a.end());
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    sz = x.size();
    vector<int> L(n + 1), R(n + 1);
    for(int i = 1; i <= n; i++) {
        L[i] = lower_bound(x.begin(), x.end(), a[i].l) - x.begin() + 1;
        R[i] = lower_bound(x.begin(), x.end(), a[i].r) - x.begin() + 1;
    }
    vector<int> pre(sz + 1);
    for(int i = 1; i <= n; i++) {
        pre[L[i]] += 1;
    }
    for(int i = 1; i <= sz; i++) {
        pre[i] += pre[i - 1];
    }
    vector<vector<int>> dp(n + 1, vector<int>(2, inf));
    dp[n][1] = 1;
    for(int i = n - 1; i >= 1; i--) {
        for(int j = i + 1; j <= n && a[i].r >= a[j].l; j++) {
            int l = L[i], r = max(R[j], R[i]);
            int cnt = pre[r] - pre[l - 1] - 2;
            auto it = upper_bound(L.begin() + 1, L.end(), r);
            if(it != L.end()) {
                int nxt = it - L.begin();
                dp[i][0] = min(dp[i][0], cnt + min(dp[nxt][0], dp[nxt][1]));
            } else {
                dp[i][0] = min(dp[i][0], cnt);
            }
        }
        dp[i][1] = 1 + min(dp[i + 1][0], dp[i + 1][1]);
    }
    cout << min(dp[1][0], dp[1][1]) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
