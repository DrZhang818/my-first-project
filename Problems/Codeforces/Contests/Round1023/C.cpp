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
    string s;
    cin >> s;
    s = "#" + s;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 2), suf(n + 2);
    bool have = false;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '0') pre[i] = 0, have = true;
        else pre[i] = max(pre[i - 1], 0LL) + a[i];
    }
    for(int i = n; i >= 1; i--) {
        if(s[i] == '0') suf[i] = 0;
        else suf[i] = max(suf[i + 1], 0LL) + a[i];
    }
    ll mx = 0;
    for(int i = 1; i <= n; i++) mx = max({mx, pre[i], suf[i]});
    if(mx > k) {
        cout << "NO\n";
        return;
    }
    if(!have && mx != k) {
        cout << "NO\n";
        return;
    }
    bool ok = false;
    for(int i = 1; i <= n; i++) {
        if(s[i] == '0' && !ok) {
            if(i == 1 && (i + 1 > n || s[i + 1] == '0')) {
                a[i] = k;
            } else {
                a[i] = k - (max(0LL, pre[i - 1]) + max(0LL, suf[i + 1]));
            }
            ok = true;
        } else if(s[i] == '0') {
            a[i] = -1e17;
        }
    }
    cout << "YES\n";
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
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
