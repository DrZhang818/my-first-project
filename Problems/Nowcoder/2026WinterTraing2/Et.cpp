#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<vector<int>> solve(int n) {  
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for(int i = 2; i <= n; i += 2) {
        for(int j = 1; j <= n - i + 1; j++) {
            a[i][j] = 1;
        }
        for(int k = i + 1; k <= n; k++) {
            a[k][n - i + 1] = 1;
        }
    }

    return a;
}

int dir[] = {-1, 0, 1, 0, -1};

bool ck(vector<vector<int>>& a) {
    int n = a.size() - 1;
    set<int> st_row, st_col;

    int num = 0;
    vector<vector<int>> vis(n + 1, vector<int>(n + 1));
    auto dfs = [&](this auto&& self, int i, int j) -> void {
        vis[i][j] = true;
        for(int k = 0; k < 4; k++) {
            int ni = i + dir[k];
            int nj = j + dir[k + 1];
            if(ni < 1 || ni > n || nj < 1 || nj > n || vis[ni][nj]) continue;
            if(a[ni][nj] != a[i][j]) continue;
            self(ni, nj);
        }
    };

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(!vis[i][j]) {
                num++;
                dfs(i, j);
            }
        }
    }
    if(num != n) {
        cerr << n << " " << num << "\n";
        return false;
    }

    for(int i = 1; i <= n; i++) {
        int s = 0;
        for(int j = 1; j <= n; j++) {
            s += a[i][j];
        }
        if(s >= n) return false;
        if(st_row.contains(s)) return false;
        st_row.insert(s);
    }
    for(int j = 1; j <= n; j++) {
        int s = 0;
        for(int i = 1; i <= n; i++) {
            s += a[i][j];
        }
        if(s >= n) return false;
        if(st_col.contains(s)) return false;
        st_col.insert(s);   
    }   
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= 1000; i++) {
        auto a = solve(i);
        if(!ck(a)) {
            cerr << "WA\n";
            cerr << i << "\n";
        } else {
        }
    }

    return 0;
}
