#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    array<int, 2> mn {inf, inf}, mx{-inf, -inf};
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        int p = a[i] & 1;
        mn[p] = min(mn[p], a[i]);
        mx[p] = max(mx[p], a[i]);
    }

    for(int p : {0, 1}) {
        int q = p ^ 1;

        int x = -inf;
        for(int i = 1; i <= n; i++) {
            int y = a[i];
            if((y & 1) != p) continue;
            if(x > y && y < mn[q]) {
                cout << "NO\n";
                return;
            }
            if(y > mx[q]) {
                x = max(x, y);
            }
        }
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