#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


vector<int> fac[500001];
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    map<int,int> val;
    int sz = fac[m].size();
    for(int i = 0; i < sz; i++) {
        int x = fac[m][i];
        int cnt = 1, pre = -inf;
        for(int j = 1; j <= n; j++) {
            int cur = a[j] % x;
            if(cur < pre) {
                cnt++;
            }
            pre = cur;
        }
        val[x] = cnt;
    }
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i, x;
            cin >> i >> x;
            for(int j = 0; j < sz; j++) {
                int d = 0, mod = fac[m][j];
                if(i > 1) {
                    d -= (a[i] % mod < a[i - 1] % mod);
                    d += (x % mod < a[i - 1] % mod);
                }
                if(i < n) {
                    d -= (a[i + 1] % mod < a[i] % mod);
                    d += (a[i + 1] % mod < x % mod);
                }
                val[fac[m][j]] += d;
            } 
            a[i] = x;
        } else {
            int k;
            cin >> k;
            int x = gcd(m, k);
            if(val[x] <= m / x) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= 500000; i++) {
        for(int j = i; j <= 500000; j += i) {
            fac[j].push_back(i);
        }
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

