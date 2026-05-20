#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

using B = bitset<2005>;

void solve() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<B> a(n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int x;
            cin >> x;
            a[i][j] = x;
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            int x;
            cin >> x;
            a[i][m + j] = x;
        }
    }

    vector<int> where(m, -1);

    int r = 0;
    for(int c = 0; c < m && r < n; c++) {
        int s = -1;
        for(int i = r; i < n; i++) {
            if(a[i][c]) {
                s = i;
                break;
            }
        }

        if(s == -1) continue;

        swap(a[r], a[s]);
        where[c] = r;

        for(int i = 0; i < n; i++) {
            if(i != r && a[i][c]) {
                a[i] ^= a[r];
            }
        }
        r++;
    }

    for(int i = 0; i < n; i++) {
        bool lhs = false;
        bool rhs = false;
        for(int j = 0; j < m; j++) {
            lhs |= a[i][j];
        }
        for(int j = 0; j < p; j++) {
            rhs |= a[i][m + j];
        }
        if(!lhs && rhs) {
            cout << "No\n";
            return;
        }
    }

    vector<vector<int>> ans(m, vector<int>(p));
    for(int c = 0; c < m; c++) {
        if(where[c] == -1) continue;
        int r = where[c];
        for(int j = 0; j < p; j++) {
            ans[c][j] = a[r][m + j];
        }
    }

    cout << "Yes\n";
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < p; j++) {
            cout << ans[i][j] << " \n"[j == p - 1];
        }
    } 
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