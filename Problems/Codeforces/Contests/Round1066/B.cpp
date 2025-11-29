#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, x, y;
    cin >> n >> x >> y;
    string s;
    cin >> s;
    int cnt = 0;
    for(char c : s) {
        if(c == '4') {
            cnt++;
        }
    }
    x = abs(x), y = abs(y);
    if(x > n || y > n || x + y > 2 * n - cnt) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
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
