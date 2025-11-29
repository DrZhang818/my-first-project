#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int a, b, n, p;
    info() : a{-1}, b{-1}, n{-1}, p{-1} {}
    info(int q, int w, int e, int r) : a(q), b(w), n(e), p(r) {}
};

info pre[201][201][22][2];

void dfs(int a, int b, int n, int p) {
    if(n == 0) return;
    info cur = info(a, b, n, p);
    if(pre[a][b][n][p ^ 1].a == -1) {
        pre[a][b][n][p ^ 1] = cur;
        dfs(a, b, n, p ^ 1);
    }
    if(n > 6) {
        if(p == 0) {
            if(pre[a + 1][b][n - 1][p ^ 1].a == -1) {
                pre[a + 1][b][n - 1][p ^ 1] = cur;
                dfs(a + 1, b, n - 1, p ^ 1);
            }
            for(int i = 3; i <= 8; i++) {
                if(pre[a + i][b][n - 1][p].a == -1) {
                    pre[a + i][b][n - 1][p] = cur;
                    dfs(a + i, b, n - 1, p);
                }
            }
        } else {
            if(pre[a][b + 1][n - 1][p ^ 1].a == -1) {
                pre[a][b + 1][n - 1][p ^ 1] = cur;
                dfs(a, b + 1, n - 1, p ^ 1);
            }
            for(int i = 3; i <= 8; i++) {
                if(pre[a][b + i][n - 1][p].a == -1) {
                    pre[a][b + i][n - 1][p] = cur;
                    dfs(a, b + i, n - 1, p);
                }
            }
        }
    } else {
        int x = 8 - n;
        if(p == 0) {
            if(pre[a + x][b][n - 1][p].a == -1) {
                pre[a + x][b][n - 1][p] = cur;
                dfs(a + x, b, n - 1, p);
            }    
        } else {
            if(pre[a][b + x][n - 1][p].a == -1) {
                pre[a][b + x][n - 1][p] = cur;
                dfs(a, b + x, n - 1, p);
            }
        }
    }
}

void solve() {
    int a, b, n, p;
    cin >> a >> b >> n >> p;
    if(pre[a][b][n][p].a == -1) {
        cout << "NA\n";
        return;
    }
    string s;
    while(a != 0 || b != 0 || n != 21 || p != 0) {
        auto [na, nb, nn, np] = pre[a][b][n][p];
        if(p != np) s += '/';
        if(na == a && nb == b) {
            a = na, b = nb, n = nn, p = np;
            continue;
        }
        int x = max(a - na, b - nb);
        if(nn > 6) {
            if(x == 1) s += '1';
            else s += to_string(x - 1) + "1";
        } else {
            s += to_string(x);
        }
        a = na, b = nb, n = nn, p = np;
    }
    reverse(s.begin(), s.end());
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    pre[0][0][21][0] = {0, 0, 21, 0};
    dfs(0, 0, 21, 0);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
