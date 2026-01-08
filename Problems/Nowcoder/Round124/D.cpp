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
    vector<int> deg(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        deg[u]++;
        deg[v]++;
    }
    int cnt = 0;
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 1) {
            cnt++;
        }
    }
    cout << (cnt + 1) / 2 << "\n";
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
