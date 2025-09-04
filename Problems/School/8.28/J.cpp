#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> d(n + 1);
    d[1] = a[1] - a[n];
    for(int i = 2; i <= n; i++) {
        d[i] = a[i] - a[i - 1];
    }
    ll mx = *max_element(d.begin() + 1, d.end());
    vector<ll> b(n + 5);
    auto add = [&](int i, int j, ll x, ll y, ll c) -> void {
        b[i] += x * c;
        b[i + 1] += (1 - x) * c;
        b[j + 1] += (-y - 1) * c;
        b[j + 2] += y * c;
    };
    for(int i = 1; i <= n; i++) {
        if((mx - d[i]) % n != 0) {
            cout << "NO\n";
            return;
        }
        ll c = (mx - d[i]) / n;
        int j = n - i + 1;
        add(i, n, 1, j, c);
        if(i != 1) {
            add(1, i - 1, j + 1, n, c);
        }
    }
    for(int i = 1; i <= n; i++) {
        b[i] += b[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        b[i] += b[i - 1];
    }

    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += i;
    }
    ll t = (a[1] - b[1]) / sum;
    for(int i = 1; i <= n; i++) {
        if((a[i] - b[i]) % sum != 0 || a[i] < b[i]) {
            cout << "NO\n";
            return;
        }
        if(b[i] + t * sum != a[i]) {
            cout << "NO\n";
            return;
        }
    }

    cout << "YES\n";
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
