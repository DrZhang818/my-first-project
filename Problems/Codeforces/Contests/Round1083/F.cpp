#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

vector<int> fa;
vector<i64> W;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if(u == v) return;
    W[u] += W[v];
    fa[v] = u;
}   

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    vector<vector<int>> b(n + 1, vector<int>(m + 1));
    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < m; j++) {
            cin >> b[i][j];
        }
    }

    const int N = (n - 1) * (m - 1);
    fa.resize(N + 1);
    iota(fa.begin(), fa.end(), 0);
    W.resize(N + 1);

    auto getId = [&](int i, int j) {
        if(i < 1 || i >= n || j < 1 || j >= m) {
            return 0;
        }
        return (i - 1) * (m - 1) + j;
    };

    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++) {
            W[getId(i, j)] = i64(a[i][j]) + b[i][j] - a[i][j + 1] - b[i + 1][j];
        }
    }
    
    for(int i = 1; i < n; i++) {
        string s;
        cin >> s;
        for(int j = 1; j <= m; j++) {
            if(s[j - 1] == '0') {
                merge(getId(i, j - 1), getId(i, j));
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        for(int j = 1; j < m; j++) {
            if(s[j - 1] == '0') {
                merge(getId(i - 1, j), getId(i, j));
            }            
        }
    }

    i64 ans = 0;
    int root0 = find(0);
    for(int i = 1; i <= N; i++) {
        if(find(i) == i && i != root0) {
            ans += max(0LL, W[i]);
        }
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
