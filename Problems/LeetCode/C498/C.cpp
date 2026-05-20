#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

int dir[] = {-1, 0, 1, 0, -1};

class Solution {
public:
    vector<vector<int>> colorGrid(int n, int m, vector<vector<int>>& a) {
        sort(a.begin(), a.end(),
            [&](auto& x, auto& y) {
                return x[2] > y[2];
            });

        vector<vector<int>> ans(n, vector<int>(m));
        queue<pair<int,int>> q;
        for(auto& vec : a) {
            q.emplace(vec[0], vec[1]);
            ans[vec[0]][vec[1]] = vec[2];
        }

        while(!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for(int i = 0; i < 4; i++) {
                int nx = x + dir[i], ny = y + dir[i + 1];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m || ans[nx][ny]) continue;
                ans[nx][ny] = ans[x][y];
                q.emplace(nx, ny);
            }
        }

        return ans;
    }
};