#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dir[5] = {-1, 0, 1, 0, -1}; 
class Solution {
public:
    int countIslands(vector<vector<int>>& a, int k) {
        int n = a.size(), m = a[0].size();
        vector vis(n, vector<bool>(m));
        auto dfs = [&](this auto &&self, int x, int y) -> int {
            vis[x][y] = true;
            int rem = a[x][y] % k;
            for(int i = 0; i < 4; i++) {
                int nx = x + dir[i], ny = y + dir[i + 1];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m || !a[nx][ny] || vis[nx][ny]) continue;
                rem = (rem + self(nx, ny)) % k;
            }
            return rem;
        };
        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j] && !vis[i][j]) {
                    int rem = dfs(i, j);
                    ans += rem == 0;
                }
            }
        }
        return ans;
    }
};