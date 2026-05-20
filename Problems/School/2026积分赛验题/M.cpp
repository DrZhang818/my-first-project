#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;

    i64 ans = 1LL * a * n;
    if(b >= 0) {
        ans += 1LL * b * n;
    } else {
        int c = 0;
        for(int l = 0, r = 0; l < n; l = r) {
            while(r < n && s[r] == s[l]) {
                r++;
            }
            c++;
        }
        ans += 1LL * (c / 2 + 1) * b;
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
