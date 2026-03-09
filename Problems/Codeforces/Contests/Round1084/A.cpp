#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int tot = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        tot += a[i];
    }

    auto calc = [&](int x) {
        auto cnt = a;
        int sum = tot;
        while(sum > 0) {
            if(cnt[x] > 0) {
                sum--;
                cnt[x]--;
            }
            if(sum == 0) {
                break;
            }
            x = x % n + 1;
        }
        return x;
    };

    vector<bool> ok(n + 1);
    for(int i = 1; i <= n; i++) {
        ok[calc(i)] = true;
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(ok[i]) {
            ans++;
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
