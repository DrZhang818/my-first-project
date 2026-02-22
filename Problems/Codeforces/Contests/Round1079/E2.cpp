#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

using B = bitset<500005>;

B h[26], F, G, H;

void solve() {  
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;

    for(int i = 0; i < n; i++) {
        h[s[i] - 'a'].set(i);
        H.set(i);        
    }

    int ans = 0;
    for(int l = 0, r = 0; l < m; l = r) {
        F = G = H;
        for(; r < m; r++) {
            int len = r - l;
            F.reset(n - len);
            B msk = h[t[r] - 'a'] >> len;

            G &= msk;
            G |= F;

            if(G.none()) {
                break;
            }

            F &= msk;
        }
        ans++;
    }

    cout << ans << "\n";

    for(int i = 0; i < 26; i++) {
        h[i].reset();
    }
    F.reset();
    G.reset();
    H.reset();
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
