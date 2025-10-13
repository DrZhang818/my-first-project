#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }

    int offset = 0;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int c;
            cin >> c;
            offset += c;
            offset %= n;    
        } else {
            int l, r;
            cin >> l >> r;
            l = (l + offset - 1) % n + 1;
            r = (r + offset - 1) % n + 1;
            if(l <= r) {
                cout << pre[r] - pre[l - 1] << "\n";
            } else {
                cout << pre[n] - pre[l - 1] + pre[r] << "\n";
            }
        }
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
