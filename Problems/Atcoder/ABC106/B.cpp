#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<vector<int>> fac;
void solve() {
    int n;
    cin >> n;
    int ans = 0;
    for(int i = 1; i <= n; i += 2) {
        if(fac[i].size() == 8) {
            ans++;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    fac.resize(201);
    for(int i = 1; i <= 200; i++) {
        for(int j = i; j <= 200; j += i) {
            fac[j].push_back(i);
        }
    }
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
