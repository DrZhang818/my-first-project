#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, L;
    cin >> n >> L;
    vector<int> cnt(L);
    cnt[0]++;
    for(int i = 1, pos = 0; i < n; i++) {
        int d;
        cin >> d;
        pos = (pos + d) % L;
        cnt[pos]++;
    }
    if(L % 3 != 0) {
        cout << 0 << "\n";
        return;
    }
    ll ans = 0;
    for(int i = 0; i < L / 3; i++) {
        ans += 1LL * cnt[i] * cnt[i + L / 3] * cnt[i + L / 3 * 2];
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
