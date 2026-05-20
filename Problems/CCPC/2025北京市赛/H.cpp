#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

using B = bitset<1000>;

void solve() {
    int n, m, p;
    cin >> n >> m >> p;

    vector<vector<int>> A(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> A[i][j];
        }
    }

    vector<B> b(n);
    vector<B> msk(n);
    for(int j = 0; j < m; j++) {
        B cur;
        B from;
        from.set(j);
        for(int i = 0; i < n; i++) {
            if(A[i][j]) {
                cur.set(i);
            }
        }
        for(int i = 0; i < n; i++) {
            if(cur[i] == 0) continue;
            if(b[i].none()) {
                b[i] = cur;
                msk[i] ^= from;
                break;
            }
            cur ^= b[i];
            from ^= msk[i];
        }
    }

    vector<vector<int>> C(n, vector<int>(p));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < p; j++) {
            cin >> C[i][j];
        }
    }

    vector<vector<int>> ans(m, vector<int>(p));
    for(int j = 0; j < p; j++) {
        B cur;
        B from;
        for(int i = 0; i < n; i++) {
            if(C[i][j]) {
                cur.set(i);
            }
        }
        for(int i = 0; i < n; i++) {
            if(cur[i] == 0) continue;
            if(b[i].none()) {
                cout << "No\n";
                return;
            }
            cur ^= b[i];
            from ^= msk[i];
        }
        for(int i = 0; i < m; i++) {
            if(from[i]) {
                ans[i][j] = 1;
            }
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