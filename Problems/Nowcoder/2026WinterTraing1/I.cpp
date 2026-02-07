#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int l, r;
    cin >> l >> r;

    int tl = l, tr = r;

    int ans = 0;

    int low = 0;
    for(int i = 29; i >= 0; i--) {
        if(~r >> i & 1) continue;
        if(l >> i & 1) {
            low += 1 << i;
            if(low > ans) {
                break;
            }
            l ^= 1 << i;
            r ^= 1 << i;
            continue;
        }

        int high = __lg(r);
        int nr = (1 << high) - 1;

        ans = max(ans, low + (r ^ (1 << high)) + 1);

        r = nr;
    }

    if(tl <= ans && ans <= tr) {
        ans = tr + 1;
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
