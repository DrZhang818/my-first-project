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
    ll sum = 0;
    for(int i = 1; i < n; i++) {
        sum += abs(a[i] - a[i + 1]);
    }
    ll ans = sum;
    for(int i = 1; i <= n; i++) {
        ll cur = sum;
        if(i == 1) {
            cur -= abs(a[i + 1] - a[i]);
        } else if(i == n) {
            cur -= abs(a[i] - a[i - 1]);
        } else {
            cur -= abs(a[i] - a[i - 1]) + abs(a[i + 1] - a[i]);
            cur += abs(a[i + 1] - a[i - 1]);
        }
        ans = min(ans, cur);
    }
    cout << ans << "\n";
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
