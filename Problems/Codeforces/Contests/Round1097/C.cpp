#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;

    int x = 0, y = 0;
    for(int i = 0; i < n; i++) {
        auto [a, b] = pair{s[i], t[i]};
        if(a == '(' && b == '(') {
            x++;
            y++;
        } else if(a == ')' && b == ')') {
            x--;
            y--;
        } else {
            if(x <= y) {
                x++;
                y--;
            } else {
                x--;
                y++;
            }
        }
        if(y < 0) {
            cout << "NO\n";
            return;
        }
    }

    if(x != 0 || y != 0) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
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