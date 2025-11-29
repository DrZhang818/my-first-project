#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    array<int,4> a {};
    array<int,6> b {};
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if(s[1] == 'D') a[0]++;
        else if(s[1] == 'C') a[1]++;
        else if(s[1] == 'H') a[2]++;
        else a[3]++;
    }
    int ans = 0;
    for(int i = 0; i < 4; i++) {
        ans += a[i] / 5;
        a[i] %= 5;
    }
    for(int i = 0; i < 6; i++) {
        cin >> b[i];
    }
    int x = 0;
    for(int s = 0; s < 1 << 4; s++) {
        int need1 = 0, need2 = 0, has = 0;
        for(int i = 0; i < 4; i++) {
            if(s >> i & 1) {
                if(b[i]) {
                    if(a[i] >= 2) {
                        need1 += 5 - a[i];
                    } else {
                        need1 += 3;
                        need2 += 2 - a[i];
                    }
                } else {
                    need2 += 5 - a[i];
                }
            } else {
                has += a[i];
            }
        }
        if(need2 <= b[4] + b[5] && need1 + need2 <= has) {
            x = max(x, __builtin_popcount(s));
        }
    }
    cout << ans + x << "\n";
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
