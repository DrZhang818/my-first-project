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
    vector<int> a(n + 1);
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    ll mx = -1;
    auto [w, c] = *mp.rbegin();
    bool ok = c % 2 == 0;
    mx = w;
    for(int i = 1; i <= n; i++) {
        if(ok) {
            if(a[i] == mx) {
                cout << 0;
            } else {
                cout << 1;
            }
        } else {
            if(a[i] == mx) {
                cout << 1;
            } else {
                cout << 0;
            }
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
