#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> pre(200005);
    for(int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;
        pre[l]++;
        pre[r + 1]--;
    }
    for(int i = 1; i <= 200000; i++) {
        pre[i] += pre[i - 1];
    }
    vector<int> t(200005);
    for(int i = 1; i <= 200000; i++) {
        if(pre[i] >= k) {
            t[i] = 1;
        }
        t[i] += t[i - 1];
    }
    while(q--) {
        int a, b;
        cin >> a >> b;
        cout << t[b] - t[a - 1] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
