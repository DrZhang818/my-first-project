#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
inline int lowbit(int o) { return o & -o; }

class BIT {
    int n;
    vector<int> tr;
public:
    BIT(int x) : n(x), tr(x + 1) {}
    void add(int o, int d) {
        for(; o <= n; o += lowbit(o)) {
            tr[o] += d;
        }
    }
    int query(int o) {
        int res = 0;
        for(; o > 0; o -= lowbit(o)) {
            res += tr[o];
        }
        return res;
    }
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

vector<int> fac;
int id[496];
void solve() {
    int n, q;
    cin >> n >> q;
    int m = fac.size();
    vector<int> a(n + 1);
    vector<BIT> tr(m, BIT(n));
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = gcd(a[i], 495);
        tr[id[a[i]]].add(i, 1);
    }
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x, y;
            cin >> x >> y;
            tr[id[a[x]]].add(x, -1);
            a[x] = gcd(y, 495);
            tr[id[a[x]]].add(x, 1);
        } else {
            int l, r;
            cin >> l >> r;
            vector<int> cnt(m);
            for(int i = 0; i < m; i++) {
                cnt[i] = tr[i].rangeQuery(l, r);
            }
            ll ans = 0;
            for(int i = 0; i < m; i++) {
                for(int j = 0; j < i; j++) {
                    if(fac[i] * fac[j] % 495 == 0) {
                        ans += 1LL * cnt[i] * cnt[j];
                    }
                }
            }
            for(int i = 0; i < m; i++) {
                if(fac[i] * fac[i] % 495 == 0) {
                    ans += 1LL * cnt[i] * (cnt[i] - 1) / 2;
                }
            }
            cout << ans << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= 495; i++) {
        if(495 % i == 0) {
            fac.push_back(i);
        }
    }
    for(int i = 0; i < fac.size(); i++) {
        id[fac[i]] = i;
    }
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
