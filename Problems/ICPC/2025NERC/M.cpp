#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    string x, y;
    cin >> x >> y;
    int n = x.size();
    string s(n, '0');
    s[0] = y[0];
    for(int i = 1; i < n; i++) {
        s[i] = '0' + (y[i] ^ y[i - 1]);
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] != x[i]) {
            ans++;
            if(i + 1 < n && s[i + 1] != x[i + 1]) {
                i++;
            }
        }
    }
    cout << ans << "\n";
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
