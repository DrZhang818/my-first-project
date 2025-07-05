#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/problemset/problem/1540/A
void solve() { 
    int n;
    cin >> n;
    ll tot = 0;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    vector<ll> dp(n + 1);
    for(int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + (a[i] - a[i - 1]) * (i - 3) + (a[i] - a[i - 2]);
        tot += -dp[i];
    }
    cout << tot << "\n";
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
    
