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
    string s;
    cin >> s;
    int x, y;
    cin >> x >> y;
    int dis = abs(x) + abs(y);
    if(n < dis || (n - dis) % 2 == 1) {
        cout << -1 << "\n";
        return;
    }
    vector<int> prex(n + 1), prey(n + 1);
    s = "#" + s;
    for(int i = 1; i <= n; i++) {
        prex[i] = prex[i - 1];
        prey[i] = prey[i - 1];
        prex[i] += s[i] == 'R' ? 1 : s[i] == 'L' ? -1 : 0;
        prey[i] += s[i] == 'U' ? 1 : s[i] == 'D' ? -1 : 0;
    }

    if(prex[n] == x && prey[n] == y) {
        cout << 0 << "\n";
        return;
    }

    auto ck = [&](int t) -> bool {
        for(int i = t; i <= n; i++) {
            int R = i, L = i - t + 1;
            int cx = prex[L - 1] + prex[n] - prex[R];
            int cy = prey[L - 1] + prey[n] - prey[R];
            int needx = abs(x - cx);
            int needy = abs(y - cy);
            if(needx + needy <= t) {
                return true;
            }
        }
        return false;
    };

    int l = 0, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
