#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    vector<int> pre(n + 1, inf), suf(n + 2);
    for(int i = 1; i <= n; i++) {
        pre[i] = min(pre[i - 1], p[i]);
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = max(suf[i + 1], p[i]);
    }
    for(int i = 1; i < n; i++) {
        if(pre[i] > suf[i + 1]) {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
    vector<int> vis(n + 1);
    for(int i = n - 1; i >= 1; i--) {
        if(vis[p[i]]) {
            cout << p[i] << " " << vis[p[i]] << "\n";
            continue;
        }
        if(p[i] <= suf[i + 1]) {
            cout << p[i] << " " << suf[i + 1] << "\n";
        } else {
            cout << p[i] << " " << pre[i] << "\n";
            if(!vis[pre[i]]) {
                vis[pre[i]] = suf[i + 1];
            }
        }
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
