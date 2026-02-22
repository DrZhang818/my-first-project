#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<ll>> a(n + 1, vector<ll>(m + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }   

    auto calc = [&](int x, int y) {
        ll res = 0;
        for(int i = x - 2; i <= x + 2; i++) {
            for(int j = y - 2; j <= y + 2; j++) {
                if(i < 1 || i > n || j < 1 || j > m) continue;
                if(abs(x - i) + abs(y - j) > 2) continue;
                res += a[i][j];
            }
        }
        return res;
    };

    ll ans = 0;

    int X = 0, Y = 0;

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            int cur = calc(i, j);
            if(cur > ans) {
                ans = cur;
                X = i;
                Y = j;
            }
        }
    }

    while(q--) {
        int x, y, z;
        cin >> x >> y >> z;
        a[x][y] += z;

        for(int i = x - 2; i <= x + 2; i++) {
            for(int j = y - 2; j <= y + 2; j++) {
                if(i < 1 || i > n || j < 1 || j > m) continue;
                if(abs(x - i) + abs(y - j) > 2) continue;
                ll cur = calc(i, j);
                if(cur > ans) {
                    ans = cur;
                    X = i;
                    Y = j;
                }
            }
        }

        cout << X << " " << Y << "\n";
    }

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
