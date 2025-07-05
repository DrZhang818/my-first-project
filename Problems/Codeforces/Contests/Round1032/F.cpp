#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2121/problem/F
void solve() {
    int n;
    ll s, x;
    cin >> n >> s >> x;
    vector<ll> a(n + 1), pre(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }
    ll ans = 0;
    map<ll,int> mp;
    mp[0]++;
    for(int i = 1; i <= n; i++) {
        if(a[i] != x) {
            if(a[i] > x) mp.clear();
        } else {
            for(int j = i; j <= n && (j == i || a[j] < x); j++) {
                ans += mp[pre[j] - s];
            }
        }
        mp[pre[i]]++;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
