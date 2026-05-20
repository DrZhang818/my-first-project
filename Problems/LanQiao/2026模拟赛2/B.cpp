#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;


void solve() {
    vector<vector<int>> grid(2, vector<int>(4));

    map<vector<vector<int>>, int> memo;

    auto dfs = [&](this auto&& self, auto& cur) -> int {
        if(memo.contains(cur)) {
            return memo[cur];
        }
        int res = 0;

        set<int> st;
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 4; j++) {
                if(!cur[i][j]) {
                    cur[i][j] = 1;
                    st.insert(self(cur));
                    cur[i][j] = 0;
                }
            }
        }
        for(int i = 0; i < 2; i++) {
            for(int j = 0; j < 3; j++) {
                if(!cur[i][j] && !cur[i][j + 1]) {
                    cur[i][j] = cur[i][j + 1] = 1;
                    st.insert(self(cur));
                    cur[i][j] = cur[i][j + 1] = 0;
                }
            }
        }

        if(st.contains(0) || st.empty()) {
            res = 1;
        } else {
            res = 0;
        }

        return memo[cur] = res;
    };

    grid[0][1] = grid[0][2] = 1;
    cout << dfs(grid) << "\n";

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