#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1733/D1

void solve() {
    int n;
    ll x, y;
    cin >> n >> x >> y;
    string s, t;
    cin >> s >> t;
    s = "#" + s, t = "#" + t;
    vector<int> a{0};
    for(int i = 1; i <= n; i++) if(s[i] != t[i]) a.push_back(i);
    int m = a.size() - 1;
    if(m % 2) { cout << -1 << "\n"; return ; }
    if(m == 2 && a[1] + 1 == a[2]) {
        cout << min(x, 2 * y) << "\n";
    } else {
        cout << m / 2 * y << "\n";
    }
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
