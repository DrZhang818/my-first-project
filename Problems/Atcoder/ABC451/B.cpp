#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> cnt(m + 1);
    for(int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        cnt[a]--;
        cnt[b]++;
    }
    for(int i = 1; i <= m; i++) {
        cout << cnt[i] << "\n";
    }
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
