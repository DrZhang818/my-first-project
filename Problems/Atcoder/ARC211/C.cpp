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
    string s;
    cin >> s;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<array<int,2>> val;
    for(int i = 0, j = 0; i < n; i = j) {
        int mx = 0, cnt = 0;
        while(j < n && s[j] == s[i]) {
            if(a[j] > mx) {
                mx = a[j];
                cnt = 1;
            } else if(a[j] == mx) {
                cnt++;
            }
            j++;
        }
        if(s[i] == '#' && (i == 0 || j == n)) {
            continue;
        }
        val.push_back({mx, cnt});
    }
    int mx = 0;
    for(auto [x, c] : val) {
        mx = max(mx, x);
    }
    ll ans = 0;
    for(int i = 2; i < val.size(); i += 2) {
        int x = val[i - 2][0], y = val[i - 1][0], z = val[i][0];
        if(max({x, y, z}) == mx) {
            ans += 1LL * val[i - 2][1] * val[i][1];
        }
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
