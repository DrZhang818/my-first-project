#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int s, k, id;
};
void solve() {
    int n, q;
    cin >> n >> q;
    const int B = sqrt(n);
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<vector<info>> Q(B);
    vector<ll> ans(q + 1);
    for(int i = 1; i <= q; i++) {
        int s, d, k;
        cin >> s >> d >> k;
        if(d < B) {
            Q[d].emplace_back(s, k, i);
        } else {
            int pos = s;
            for(int j = 1; j <= k; j++) {
                ans[i] += a[pos] * j;
                pos += d;
            }
        }
    }
    vector<ll> suf(n + 2), ssuf(n + 2);
    for(int d = 1; d < B; d++) {
        if(Q[d].empty()) {
            continue;
        }
        for(int j = n; j >= 1; j--) {
            suf[j] = a[j];
            if(j + d <= n) {
                suf[j] += suf[j + d];
            }
            ssuf[j] = suf[j];
            if(j + d <= n) {
                ssuf[j] += ssuf[j + d];
            }
        }
        for(auto [s, k, id] : Q[d]) {
            ans[id] = ssuf[s];
            int R = s + d * k;
            if(R <= n) {
                ans[id] -= ssuf[R] + suf[R] * k;
            }
        }
    }
    for(int i = 1; i <= q; i++) {
        cout << ans[i] << " \n"[i == q];
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
