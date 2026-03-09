#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int g = 0;
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        g = gcd(g, x);
    }

    vector<i64> sum(g);
    vector<int> mn(g, inf);
    vector<int> tag(g);
    for(int i = 1; i <= n; i++) {
        int rem = i % g;
        sum[rem] += abs(a[i]);
        mn[rem] = min(mn[rem], abs(a[i]));
        if(a[i] < 0) {
            tag[rem] ^= 1;
        }
    }

    i64 ans1 = 0, ans2 = 0;
    for(int i = 0; i < g; i++) {
        if(tag[i] == 0) {
            ans1 += sum[i];
            ans2 += sum[i] - 2 * mn[i];
        } else {
            ans1 += sum[i] - 2 * mn[i];
            ans2 += sum[i];
        }
    }

    cout << max(ans1, ans2) << "\n";
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
