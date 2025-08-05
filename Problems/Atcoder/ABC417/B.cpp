#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        mp[x]--;
    }
    for(auto [x, c] : mp) {
        while(c > 0) {
            cout << x << " ";
            c--;
        }
    }
    cout << "\n";
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
