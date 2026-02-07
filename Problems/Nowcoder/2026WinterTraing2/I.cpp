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
    int c0 = 0, c1 = 0;
    vector<string> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        c0 += count(a[i].begin(), a[i].end(), '0');
        c1 += count(a[i].begin(), a[i].end(), '1');
    }

    int t0 = (c0 >= 2 ? 1 : 0);
    int t1 = (c1 >= 2 ? 1 : 0);

    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '0') {
                cout << (t0 ? 'Y' : 'N');
            } else {
                cout << (t1 ? 'Y' : 'N');
            }
        }
        cout << "\n";
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
