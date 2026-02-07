#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int query(int u, int v) {
    u++;
    v++;
    cout << u << " " << v << endl;
    int res;
    cin >> res;
    return res;
}

void solve() {  
    int n;
    cin >> n;
    for(int m = 1; m <= n - 1; m++) {
        for(int i = 0; i < n; i++) {
            if(query(i, (i + m) % n)) {
                return;
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
