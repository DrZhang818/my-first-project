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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> vis(n + 1);
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            for(int j = i; j <= n; j <<= 1) {
                vis[j] = true;
            }
            for(int j = i; j <= n; j <<= 1) {
                if(!vis[a[j]]) {
                    cout << "NO\n";
                    return;
                }
            }
        }
    }

    cout << "YES\n";
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
