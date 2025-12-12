#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> pre(n + 1);
    iota(pre.begin(), pre.end(), 0);
    pre[r] = pre[l - 1];
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        a[i] = pre[i - 1] ^ pre[i];
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
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
