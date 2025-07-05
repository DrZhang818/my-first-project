#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/1513/problem/B
constexpr int MOD = 1000000007; 
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    int s = a[1];
    for(int i = 2; i <= n; i++) {
        s &= a[i];
    }
    ll c = 0;
    for(int i = 1; i <= n; i++) {
        c += a[i] == s;
    }
    ll ans = c * (c - 1) % MOD;
    for(int i = 1; i <= n - 2; i++) {
        ans = ans * i % MOD;
    }
    cout << ans << "\n";
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
    
