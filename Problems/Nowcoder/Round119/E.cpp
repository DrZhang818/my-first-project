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
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        int x, cnt;
        cin >> x >> cnt;
        mp[x] += cnt;
        mp[x] = min(mp[x], 3);
    }
    ll ans = 0;
    vector<PII> a(mp.begin(), mp.end());
    for(int i = 0; i < a.size(); i++) {
        auto &[x, cx] = a[i];
        int k = 0;
        for(int j = 0; j <= i; j++) {
            auto &[y, cy] = a[j];
            if(i == j && cy <= 1) {
                continue;
            }
            if(a[k].first + y <= x) {
                k++;
                continue;
            }
            while(k > 0 && a[k - 1].first + y > x) {
                k--;
            }
            ans += j - k;
            if(k <= j && j < i && cy >= 2) {
                ans++;
            }
            if(k <= j && j == i && cy == 3) {
                ans++;
            }
        }
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
