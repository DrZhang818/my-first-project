#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());
    sort(c.begin() + 1, c.end());
    ll ans = 0;
    vector<ll> pre(n + 2);
    for(int i = n; i >= 1; i--) {
        pre[i] = pre[i + 1];
        auto it = upper_bound(c.begin() + 1, c.end(), b[i]);
        pre[i] += c.end() - it;
    }
    for(int i = 1; i <= n; i++) {
        auto it = upper_bound(b.begin() + 1, b.end(), a[i]) - b.begin();
        ans += pre[it];
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
