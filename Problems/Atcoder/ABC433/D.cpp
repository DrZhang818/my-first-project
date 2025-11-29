#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pow_10(11);
    pow_10[0] = 1;
    for(int i = 1; i <= 10; i++) {
        pow_10[i] = 1LL * pow_10[i - 1] * 10 % m;
    }
    using T = map<int,int>;
    vector<T> mp(11);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= 10; j++) {
            int x = 1LL * a[i] * pow_10[j] % m;
            mp[j][x]++;
        }
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        string s = to_string(a[i]);
        int len = s.size();
        int x = ((-a[i]) % m + m) % m;
        ans += mp[len][x];
    }
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
