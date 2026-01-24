#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, q;
    cin >> n >> q;
    vector<int> a(1 << n);
    for(int i = 0; i < 1 << n; i++) {
        cin >> a[i];
    }
    vector<int> fa(1 << n, -1);
    vector<int> siz(1 << n, 1);
    for(int i = 0; i + 1 < a.size(); i += 2) {
        a.push_back(a[i] ^ a[i + 1]);
        fa.push_back(-1);
        siz.push_back(-1);
        fa[i] = fa[i + 1] = a.size() - 1;
        siz[fa[i]] = siz[i] + siz[i + 1];
    }
    while(q--) {
        int u, c;
        cin >> u >> c;
        u--;
        c ^= a[u];
        int ans = 0;
        while(fa[u] != -1) {
            int x, y;
            if(u & 1) {
                x = a[u - 1];
                y = a[u] ^ c;
                if(y <= x) {
                    ans += siz[u];
                }
            } else {
                x = a[u] ^ c;
                y = a[u + 1];
                if(x < y) {
                    ans += siz[u];
                }
            }
            u = fa[u];
        }
        cout << ans << "\n";
    }
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
