#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> cnt(105);
    for(int i = 1; i <= n; i++) {
        int ti = i;
        for(int j = 2; j * j <= ti; j++) {
            while(ti % j == 0) {
                cnt[j]++;
                ti /= j;
            }
        }
        if(ti != 1) cnt[ti]++;
    }
    int c2 = 0, c4 = 0, c14 = 0, c24 = 0, c74 = 0;
    for(int i = 2; i <= 100; i++) {
        if(cnt[i] >= 2) {
            c2++;
        }
        if(cnt[i] >= 4) {
            c4++;
        }
        if(cnt[i] >= 14) {
            c14++;
        }
        if(cnt[i] >= 24) {
            c24++;
        }
        if(cnt[i] >= 74) {
            c74++;
        }
    }
    ll ans = 0;
    if(c4 >= 2) {
        ans += c4 * (c4 - 1) / 2 * (c2 - 2);
    }
    if(c14 >= 1) {
        ans += c14 * (c4 - 1);
    }
    if(c24 >= 1) {
        ans += c24 * (c2 - 1);
    }
    if(c74 >= 1) {
        ans += c74;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
