#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(2 * n + 1, vector<char>(m + 1));
    for(int i = 1; i <= 2 * n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    auto get = [&](char x, char y) {
        if(x == y) return 0;
        if(x == 'G' && y == 'C' || x == 'C' && y == 'P' || x == 'P' && y == 'G') {
            return 1;
        } 
        return -1;
    };

    vector<int> w(2 * n + 1);
    vector<int> p(2 * n + 1);
    iota(p.begin(), p.end(), 0);

    for(int j = 1; j <= m; j++) {
        for(int i = 1; i <= 2 * n; i += 2) {
            int tag = get(a[p[i]][j], a[p[i + 1]][j]);
            if(tag == 1) {
                w[p[i]]++;
            } else if(tag == -1) {
                w[p[i + 1]]++;
            }
        }
        sort(p.begin() + 1, p.end(),
            [&](int x, int y) {
                if(w[x] != w[y]) return w[x] > w[y];
                return x < y;
            });
    }

    for(int i = 1; i <= 2 * n; i++) {
        cout << p[i] << "\n";
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