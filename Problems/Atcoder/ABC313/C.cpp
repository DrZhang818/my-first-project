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
    
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    sort(a.begin() + 1, a.end());

    ll x = sum / n;
    ll y = sum - x * n;
    ll ans = 0;

    for(int i = 1; i <= n - y; i++) {
        ans += abs(a[i] - x);
    }
    for(int i = n - y + 1; i <= n; i++) {
        ans += abs(a[i] - (x + 1));
    }

    ans /= 2;
    cout << ans << "\n";
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
