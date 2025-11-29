#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    vector<int> w(31);
    int n = 0;
    for(int i = 0; i < 30; i += 2) {
        n |= 1 << i;
    }
    cout << n << endl;
    ll v;
    cin >> v;
    for(int i = 1; i < 30; i += 2) {
        if(v >> i & 1) {
            if(v >> (i + 1) & 1) {
                w[i] = 2;
            } else {
                w[i] = 0;
            }
        } else {
            w[i] = 1;
        }
    }
    n = 0;
    for(int i = 1; i < 30; i += 2) {
        n |= 1 << i;
    }
    cout << n << endl;
    cin >> v;
    w[0] = v % 4;
    for(int i = 2; i < 30; i += 2) {
        if(v >> i & 1) {
            if(v >> (i + 1) & 1) {
                w[i] = 2;
            } else {
                w[i] = 0;
            }
        } else {
            w[i] = 1;
        }
    }
    cout << "!" << endl;
    int m;
    cin >> m;
    ll ans = 0;
    for(int i = 0; i < 30; i++) {
        if(m >> i & 1) {
            ans += 2LL << i;
        } else {
            ans += w[i] << i;
        }
    }
    cout << ans << endl;
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
