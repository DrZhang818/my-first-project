#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    ll L;
    cin >> n >> m >> L;
    vector<ll> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    vector<ll> pos {0};
    {
        ll cur = 0;
        for(int i = 1; i <= n; i++) {
            pos.push_back(cur + a[i]);
            cur += a[i];
        }
    }

    ll cur = 0;
    int l = 0, r = 0;
    for(int i = 1; i <= m + 1; i++) {
        ll lo = cur, hi = cur + L;

        while(l < pos.size() && pos[l] <= lo) {
            l++;
        }

        while(r + 1 < pos.size() && pos[r + 1] < hi) {
            r++;
        }

        if(l <= r) {
            cout << "YES\n";
            return;
        }

        if(i <= m) {
            cur += b[i];
        }
    }

    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
