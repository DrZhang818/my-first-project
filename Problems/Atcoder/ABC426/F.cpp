#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    const int B = ceil(sqrt(n));
    
    vector<int> bid(n + 1);
    for(int i = 1; i <= n; i++) {
        bid[i] = (i + B - 1) / B;
    }

    int sz = (n + B - 1) / B;

    vector<int> L(sz + 1), R(sz + 1), cnt(sz + 1);
    vector<ll> mn(sz + 1, inf), d(sz + 1);
    for(int i = 1; i <= sz; i++) {
        L[i] = (i - 1) * B + 1;
        R[i] = i * B;
        for(int j = L[i]; j <= R[i]; j++) {
            mn[i] = min(mn[i], a[j]);
            cnt[i]++;
        }
    }

    int q;
    cin >> q;

    auto update = [&](int l, int r, int k, int id) -> ll {
        for(int i = L[id]; i <= R[id]; i++) {
            if(a[i] == 0) continue;
            a[i] -= d[id];
            if(a[i] == 0) {
                cnt[id]--;
            }
        }
        d[id] = 0;
        ll sum = 0;
        for(int i = l; i <= r; i++) {
            if(a[i] > k) {
                sum += k;
                a[i] -= k;
            } else if(a[i] > 0) {
                sum += a[i];
                a[i] = 0;
                cnt[id]--;
            }
        }
        if(cnt[id]) {
            ll M = inf;
            for(int i = L[id]; i <= R[id]; i++) {
                if(a[i] == 0) continue;
                M = min(M, a[i]);
            }
            mn[id] = M;
        }
        return sum;
    };  

    while(q--) {
        int l, r, k;
        cin >> l >> r >> k;
        int lid = bid[l], rid = bid[r];
        ll ans = 0;
        if(lid == rid) {
            ans = update(l, r, k, lid);            
        } else {
            if(cnt[lid]) {
                ans += update(l, R[lid], k, lid);
            }
            if(cnt[rid]) {
                ans += update(L[rid], r, k, rid);
            }
            for(int i = lid + 1; i < rid; i++) {
                if(cnt[i] == 0) continue;
                if(mn[i] > k) {
                    d[i] += k;
                    mn[i] -= k;
                    ans += 1LL * k * cnt[i];
                } else {
                    ans += update(L[i], R[i], k, i);
                }
            }
        }
        cout << ans << "\n";
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
