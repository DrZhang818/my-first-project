#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;
const int MOD = 998244353;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> mx(n + 1), mn(n + 1);
    vector<int> cmx(n + 1), cmn(n + 1);
    cmx[0] = cmn[0] = 1;
    for(int i = 0; i < n; i++) {
        int x = a[i + 1];
        ll u = abs(mx[i] + x), v = abs(mn[i] + x);
        if(u > v) {
            if(mx[i] + x >= 0) {
                add(cmx[i + 1], cmx[i] * 2LL % MOD);
            } else {
                cmx[i + 1] = cmx[i];
            }
            mx[i + 1] = u;
        } else if(u < v) {
            if(mn[i] + x >= 0) {
                add(cmx[i + 1], cmn[i] * 2LL % MOD);
            } else {
                cmx[i + 1] = cmn[i];
            }
            mx[i + 1] = v;
        } else {
            if(mx[i] + x >= 0) {
                add(cmx[i + 1], cmx[i] * 2LL % MOD);
            } else {
                cmx[i + 1] = cmx[i];
            }
            mx[i + 1] = u;
            if(mn[i] != mx[i]) {
                if(mn[i] + x >= 0) {
                    add(cmx[i + 1], cmn[i] * 2LL % MOD);
                } else {
                    add(cmx[i + 1], cmn[i]);
                }
            }
        }
        mn[i + 1] = mn[i] + x;            
        if(mn[i + 1] >= 0) {
            add(cmn[i + 1], cmn[i] * 2LL % MOD);
        } else {
            cmn[i + 1] = cmn[i];
        }
    }   
    cout << cmx[n] << "\n";
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
