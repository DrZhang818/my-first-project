#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
typedef long double ldb;
const int inf = 1000000000;
const ldb phi = (1 + sqrt(5)) / 2;
const ldb logphi = log(phi);
const ldb lg10 = log(10.0L);
const ull P = ull(1E18) + 9;

ull Hash(string &s) {
    ull res = 0;
    for(char c : s) {
        res = (res * 10ULL + ull(c - '0')) % P;
    }
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end(), 
        [&](auto &x, auto &y) {
            if(x.size() != y.size()) {
                return x.size() < y.size();
            }
            return x < y;
        });
    
    map<ull,int> mp;

    ll ans = 0;
    int z = 0;
    ull f = 0, g = 1;

    for(int i = 1; i <= n; i++) {
        int len = a[i].size();
        ull x = Hash(a[i]);
        int m;
        if(len <= 18) {
            m = log((ldb)sqrt(5) * stoll(a[i])) / logphi;
        } else {
            m = (log((ldb)sqrt(5) * stoll(a[i].substr(0, 18))) + (len - 18) * lg10) / logphi;
        }

        m = max(0, m - 1);

        while(z < m) {
            tie(f, g) = pair {g, (f + g) % P};
            z++;
        }

        auto cf = f, cg = g;
        for(int j = 0; j < 4; j++) {
            ull v = (cf + P - x) % P;
            if(mp.contains(v)) {
                ans += mp[v];
            }
            tie(cf, cg) = pair {cg, (cf + cg) % P};
        }

        mp[x]++;
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
