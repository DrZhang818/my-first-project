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
    string s;
    cin >> s;

    auto calc = [&](string& cur) -> int {
        int m = cur.size();
        int res = 0, c0 = 0, c1 = 0;
        for(int i = 0; i < m; i++) {
            if(cur[i] == '0') {
                if(c1 > 0) {
                    c1--;
                    c0++;
                } else {
                    res++;
                    c0++;
                }
            } else {
                if(c0 > 0) {
                    c0--;
                    c1++;
                } else {
                    res++;
                    c1++;
                }
            }
        }
        return res;
    };

    int ans = inf;

    string t;
    for(int i = 0; i < n; i++) {
        if((s[i] - '0') != (i & 1)) {
            t += s[i];
        }
    }

    ans = min(ans, calc(t));

    t = "";
    for(int i = 0; i < n; i++) {
        if((s[i] - '0') != (~i & 1)) {
            t += s[i];
        }
    }
    ans = min(ans, calc(t));

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
