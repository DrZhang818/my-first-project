#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 2);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> p(k + 1);
    for(int i = 1; i <= k; i++) {
        cin >> p[i];
    }
    p.push_back(n + 1);

    int x = a[p[1]];
    a[0] = a[n + 1] = x;

    vector<int> d(n + 2);
    for(int i = 1; i <= n + 1; i++) {
        d[i] = a[i] ^ a[i - 1];
    }

    int S = 0, mx = 0, las = 0;
    for(int i = 1; i <= k + 1; i++) {
        int cur = p[i];
        int cnt = 0;
        for(int j = las + 1; j <= cur; j++) {
            if(d[j] == 1) {
                cnt++;
            }
        }
        S += cnt;
        mx = max(mx, cnt);
        las = cur;
    }

    cout << max(S / 2, mx) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}