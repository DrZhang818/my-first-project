#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

auto solve(int n, int m, int k) {  
    vector<vector<int>> adj(n, vector<int>(m));

    if(m % k == 0) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j += k) {
                for(int p = j; p < j + k; p++) {
                    adj[i][p] = p - j + 1;
                    if(i & 1) {
                        adj[i][p] = k - adj[i][p] + 1;
                    }
                }
            }
        }
    } else {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                adj[i][j] = (i * m + j) % k + 1;
            }
        }
    }

    return adj;
}

auto ck(vector<vector<int>>& a) -> bool {
    int n = a.size(), m = a[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i - 1 >= 0 && a[i - 1][j] == a[i][j]) {
                return false;
            }
            if(j - 1 >= 0 && a[i][j - 1] == a[i][j]) {
                return false;
            }
        }
    }
    return true;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int n = 1; n <= 100; n++) {
        for(int m = 1; m <= 100; m++) {
            for(int k = 2; k <= n * m; k++) {
                if(n * m % k) continue;
                auto adj = solve(n, m, k);
                if(!ck(adj)) {
                    cerr << n << " " << m << " " << k << "\n";
                    return 0;
                }
            }
        }
    }

    return 0;
}
