#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    vector<array<int, 7>> cnt(3);
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 6; j++) {
            int x;
            cin >> x;
            cnt[i][x]++;
        }
    }

    db ans = 0;
    array<int, 3> p {4, 5, 6};

    do {
        ans += (db(cnt[0][p[0]]) / 6) * (db(cnt[1][p[1]]) / 6) * (db(cnt[2][p[2]]) / 6);  
    } while (next_permutation(p.begin(), p.end()));

    cout << fixed << setprecision(12) << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}