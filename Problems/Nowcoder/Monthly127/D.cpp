#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    s = "#" + s;
    int ans = inf;
    for(int l = 1, r = 1, c = 0, f = 0, g = 0; r <= n; r++) {
        if(s[r] == 'r') {
            f += 2;
            g += 1;
        } else if(s[r] == 'y') {
            f += 1;
            g += 2;
        } else {
            c++;
        }

        int cur = max(f, g) + min(m, c) * 2;
        while(l <= r && cur >= k) {
            if(s[l] == 'r') {
                f -= 2;
                g -= 1;
            } else if(s[l] == 'y') {
                f -= 1;
                g -= 2;
            } else {
                c--;
            }
            l++;
            cur = max(f, g) + min(m, c) * 2;
        }

        if(l > 1) {
            ans = min(ans, r - l + 2);
        }
    }
    if(ans == inf) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
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
