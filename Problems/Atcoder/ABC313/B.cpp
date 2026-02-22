#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<int> in(n + 1);
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        in[v]++;
    }
    int cnt = 0, x = -1;
    for(int i = 1; i <= n; i++) {
        if(in[i] == 0) {
            cnt++;
            x = i;
        }
    }
    if(cnt == 1) {
        cout << x << "\n";
    } else {
        cout << -1 << "\n";
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
