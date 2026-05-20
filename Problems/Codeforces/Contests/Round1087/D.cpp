#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int r, g, b;
    cin >> r >> g >> b;
    vector<pair<int, char>> v = {
        {r, 'R'}, {g, 'G'}, {b, 'B'}
    };
    sort(v.begin(), v.end());

    auto [x, cx] = v[0];
    auto [y, cy] = v[1];
    auto [z, cz] = v[2];

    z = min(z, x + y + 1);

    int L = x + y + z;
    int l0 = (L + 1) / 2;
    int l1 = L / 2;

    string E(l0 - z, cx);
    E.append(z, cz);

    string O(y, cy);
    O.append(l1 - y, cx);

    string ans;
    for(int i = 0; i < l1; i++) {
        ans += E[i];
        ans += O[i];
    }
    if(l0 > l1) {
        ans += E.back();
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
