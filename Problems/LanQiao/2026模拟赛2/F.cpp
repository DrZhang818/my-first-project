#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, C;
    cin >> n >> C;
    vector<int> a(n + 1);
    a[0] = 2 * C;
    vector<int> H(n + 1);
    for(int i = 1; i < n; i++) {
        cin >> H[i];
    }
    H[n] = 2 * inf;
    int ans = 0;
    for(int i = 1, j = 0; i <= n; i++) {
        if(H[i] == 0) continue;
        while(j < i && a[j] == 0) j++;
        ans = max(ans, i - j);
        while(j < i && a[i] < H[i]) {
            int d = min(a[j], H[i] - a[i]);
            a[j] -= d;
            a[i] += d;
            if(a[j] == 0) j++;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}