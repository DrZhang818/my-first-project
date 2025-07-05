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
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = (a[i] <= k ? 1 : -1);
    }
    int cur = 0, cnt = 0;
    for(int i = 1; i <= n; i++) {
        cur += a[i];
        if(cur >= 0) {
            cnt++;
            while(cur > 0 && i < n) {
                cur += a[++i];
                if(cur > 0) cnt++;
                else break;
            }
        }
    }
    if(cnt >= 2) {
        cout << "YES\n";
        return ;
    }
    cur = 0, cnt = 0;
    for(int i = n; i >= 1; i--) {
        cur += a[i];
        if(cur >= 0) {
            cnt++;
            while(cur > 0 && i > 1) {
                cur += a[--i];
                if(cur > 0) cnt++;
                else break;
            }
        }
    }
    if(cnt >= 2) {
        cout << "YES\n";
        return ;
    }
    cur = 0, cnt = 0;
    int r = 1;
    for(; r <= n; r++) {
        cur += a[r];
        if(cur >= 0) {
            cnt++;
            break;
        }
    }
    cur = 0;
    for(int i = n; i >= r + 2; i--) {
        cur += a[i];
        if(cur >= 0) {
            cnt++;
            break;
        }
    }
    if(cnt >= 2) {
        cout << "YES\n";
        return ;
    }
    cout << "NO\n";
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
