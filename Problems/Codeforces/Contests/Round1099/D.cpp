#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;

    vector<i64> a(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    if(!is_sorted(c.begin() + 1, c.end())) {
        cout << "No\n";
        return;
    }

    if(s[1] == '0') {
        a[1] = c[1];
    }
    if(a[1] != c[1]) {
        cout << "No\n";
        return;
    }

    int las = -1;
    i64 cur = c[1];
    for(int i = 2; i <= n; i++) {
        if(s[i] == '1') {
            if(c[i] > c[i - 1]) {
                i64 d = c[i] - cur - a[i];
                if(d > 0 || d < 0 && las == -1) {
                    cout << "No\n";
                    return;
                }
                if(d != 0) {
                    a[las] += d;
                }
                las = -1;
                cur = c[i];
            } else {
                cur += a[i];
                if(cur > c[i]) {
                    i64 d = cur - c[i];
                    if(las == -1) {
                        cout << "No\n";
                        return;
                    }
                    a[las] -= d;
                    cur = c[i];
                }
            }
        } else {
            a[i] = c[i] - cur;
            cur = c[i];
            if(c[i] > c[i - 1]) {
                las = -1;
            } else {
                las = i;
            }
        }
    }

    cout << "Yes\n";
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}