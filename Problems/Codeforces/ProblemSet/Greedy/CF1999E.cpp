#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 200000;

int cnt[N + 1];

void solve() {
    int l, r;
    cin >> l >> r;
    int ans = cnt[r] - cnt[l - 1] + cnt[l] - cnt[l - 1];
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= N; i++) {
        cnt[i] = cnt[i / 3] + 1;
    }
    for(int i = 1; i <= N; i++) {
        cnt[i] += cnt[i - 1];
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
