#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    ll sum = 0;
    int f = 0, g = 0, h = 0, w = 0;
    for(int i = 1; i < n; i++) {
        if(s[i - 1] == '?' && (s[i] == 'X' || s[i] == 'V')) {
            f++;
        }
        if(s[i - 1] == 'I' && s[i] == '?') {
            g++;
        }
        if(i + 1 < n && s[i] == '?' && s[i - 1] == 'I' && (s[i + 1] == 'V' || s[i + 1] == 'X')) {
            f--;
            g--;
            w++;
        } 
        if(s[i - 1] == 'X') {
            sum += 10;
        } else if(s[i - 1] == 'V') {
            sum += 5;
        } else if(s[i - 1] == 'I') {
            if(s[i] == 'X' || s[i] == 'V') {
                sum--;
            } else {
                sum++;
            }
        }
        if(i == n - 1) {
            if(s[i] == 'X') {
                sum += 10;
            } else if(s[i] == 'V') {
                sum += 5;
            } else if(s[i] == 'I') {
                sum += 1;
            }
        }
    }
    if(n == 1) {
        if(s[0] == 'X') {
            sum = 10;
        } else if(s[0] == 'V') {
            sum = 5;
        } else if(s[0] == 'I') {
            sum = 1;
        }
    }
    int cnt = count(s.begin(), s.end(), '?');
    for(int i = 0; i < n; ) {
        if(s[i] != '?' || i > 0 && s[i - 1] == 'I') {
            i++;
            continue;
        }
        int j = i;
        while(j + 1 < n && s[j + 1] == '?') {
            j++;
        }
        int len = j - i + 1;
        if(j + 1 < n && s[j + 1] != 'I') {
            len--;
        }
        h += len >> 1;
        i = j + 1;
    }
    while(q--) {
        int x, y, z;
        cin >> x >> y >> z;
        int ci = min(z, cnt);
        int rem = cnt - ci;
        int cv = min(y, rem);
        rem -= cv;
        int cx = min(x, rem);
        rem -= cx;
        assert(rem == 0);

        ll ans = sum + cx * 10 + cv * 5 + ci;
        ans -= min(ci, f) * 2;
        ci -= min(ci, f);

        int tot = cx + cv;
        ans -= min(tot, g) * 2;
        tot -= min(tot, g);

        ans -= w * 2;
        int p;
        if(ci - w >= tot) {
            p = tot;
        } else if(tot - w >= ci) {
            p = ci;
        } else {
            p = (ci + tot - w) / 2;
        }

        ans -= min(h, p) * 2;
        
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
