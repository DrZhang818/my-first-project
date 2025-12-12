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
    string s;
    cin >> s;
    s = "#" + s + s;
    vector<ll> a(2 * n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i + n] = a[i];
    }
    const int N = 19;
    vector<array<int,N>> go(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        fill(go[i].begin(), go[i].end(), 2 * n + 1);
    }
    array<int,26> las {};
    for(int i = 2 * n - 1; i >= 1; i--) {
        int x = s[i] - 'A';
        if(las[x]) {
            go[i][0] = las[x] + 1;
        }
        las[x] = i;
    }
    for(int s = 1; s < N; s++) {
        for(int i = 1; i <= 2 * n; i++) {
            if(go[i][s - 1] <= 2 * n) {
                go[i][s] = go[go[i][s - 1]][s - 1];
            }
        }
    }
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x, y;
            cin >> x >> y;
            a[x] = a[x + n] = y;
        } else {
            int l, r;
            cin >> l >> r;
            if(r < l) {
                r += n;
            }
            ll ans = 0;
            int cur = l;
            while(cur <= r) {
                int nxt = cur;
                for(int s = N - 1; s >= 0; s--) {
                    if(go[nxt][s] <= r + 1) {
                        nxt = go[nxt][s];
                    }
                }
                if(nxt == cur) {
                    ans += a[cur];
                    cur++;
                } else {
                    cur = nxt;
                }
            }
            cout << ans << "\n";
        }
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
