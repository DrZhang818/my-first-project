#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;

    int ans = 0;
    int mxlen = 0;
    for(int l = 0, r = 0; l < n; l = r) {
        while(r < n && s[r] == s[l]) {
            r++;
        }
        ans++;
        mxlen = max(mxlen, r - l);
    }

    if(ans > 1 && mxlen > 1 && s.front() != s.back()) {
        ans++;
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
