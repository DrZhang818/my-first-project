#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k, q;
    cin >> n >> k >> q;

    vector<vector<int>> a(k + 1, vector<int>(n + 1));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= k; j++) {
            int x;
            cin >> x;
            a[j][i] = x;
        }
    }

    for(int i = 1; i <= k; i++) {
        for(int j = 1; j <= n; j++) {
            a[i][j] |= a[i][j - 1];
        }
    }

    while(q--) {
        int m;
        cin >> m;

        int mn = 1, mx = n;

        while(m--) {
            int r, c;
            char o;
            cin >> r >> o >> c;

            int lo = 0, hi = n + 1;
            while(lo + 1 < hi) {
                int mid = lo + hi >> 1;
                if(o == '<') {
                    if(a[r][mid] < c) {
                        lo = mid; 
                    } else {
                        hi = mid;
                    }
                } else {
                    if(a[r][mid] > c) {
                        hi = mid;
                    } else {
                        lo = mid;
                    }
                }
            }

            if(o == '<') {
                mx = min(mx, lo);
            } else {
                mn = max(mn, hi);
            }
        }

        if(mn <= mx) {
            cout << mn << "\n";
        } else {
            cout << -1 << "\n";
        }
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
