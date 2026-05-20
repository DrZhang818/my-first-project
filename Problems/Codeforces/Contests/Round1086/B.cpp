#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, k, p, m;
    cin >> n >> k >> p >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> b(n + 1);
    iota(b.begin(), b.end(), 0);

    int ans = 0;
    while(m > 0) {
        int idx = 1;
        for(int i = 1; i <= k; i++) {
            if(a[b[i]] <= a[b[idx]]) {
                idx = i;
            }
            if(b[i] == p) {
                idx = i;
                break;
            }
        }
        if(m < a[b[idx]]) {
            break;
        }
        if(b[idx] == p) {
            ans++;
        }
        m -= a[b[idx]];
        int t = b[idx];
        for(int i = idx; i < n; i++) {
            b[i] = b[i + 1];
        }
        b[n] = t;
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
