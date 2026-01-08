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
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto b = a;
    sort(b.begin() + 1, b.end());
    for(int i = 1; i <= n; i++) {
        ll x = 1LL * a[i] * b[i];
        ll t = sqrt(x);
        if(t * t != x && (t + 1) * (t + 1) != x) {
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
