#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;

    vector<vector<ll>> a(n + 1, vector<ll>(n + 1));

    ll sum = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
            sum += a[i][j];
        }
    }

    if(sum % (n * n)) {
        cout << "No\n";
        return;
    }

    ll bias = -(sum / (n * n));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            a[i][j] += bias;
        }
    }

    ll c0 = 0, c1 = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if((i + j) & 1) {
                c1 += a[i][j];
            } else {
                c0 += a[i][j];
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        ll cur = 0;
        for(int j = 1; j <= n; j++) {
            cur += a[i][j];
        }
        if(cur & 1) {
            cout << "No\n";
            return;
        }
    }


    for(int j = 1; j <= n; j++) {
        ll cur = 0;
        for(int i = 1; i <= n; i++) {
            cur += a[i][j];
        }
        if(cur & 1) {
            cout << "No\n";
            return;
        }
    }

    if(c0 || c1) {
        cout << "No\n";
        return;
    }

    cout << "Yes\n";
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
