#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2107/problem/A
void solve() {
    int n, mn = inf, mx = -inf;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i], mn = min(mn, a[i]), mx = max(mx, a[i]);
    if(mn == mx) { cout << "No\n"; return; }
    cout << "Yes\n";
    for(int i = 1; i <= n; i++) cout << "12"[a[i] == mx] << " \n"[i == n];
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
