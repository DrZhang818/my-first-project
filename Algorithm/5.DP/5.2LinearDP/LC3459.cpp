#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int dx[4] = {-1, -1, 1, 1};
int dy[4] = {-1, 1, 1, -1};
class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& a) {
        int n = a.size(), m = a[0].size();
        int dp[n][m][4][2]{};
        auto dfs = [&](this auto &&self, int x, int y, int dir, int tag) -> int {
            int ans = 1;
            if(dir == -1) {
                int mx = 0;
                for(int i = 0; i < 4; i++) {
                    int nx = x + dx[i], ny = y + dy[i];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] != 2) continue;
                    mx = max(mx, self(nx, ny, i, 1));
                }
                ans += mx;
                return ans;
            }
            int &res = dp[x][y][dir][tag];
            if(res) return res;
            int nx = x + dx[dir], ny = y + dy[dir];
            int num = a[x][y] == 2 ? 0 : 2;
            if(nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] == num) {
                ans += self(nx, ny, dir, tag);
            }
            if(tag == 1) {
                int ndir = (dir + 1) % 4;
                nx = x + dx[ndir], ny = y + dy[ndir];
                if(nx >= 0 && nx < n && ny >= 0 && ny < m && a[nx][ny] == num) {
                    ans = max(ans, 1 + self(nx, ny, ndir, 0));
                }
            }
            return res = ans;
        };
        int ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j] == 1) {
                    ans = max(ans, dfs(i, j, -1, 1));
                }
            }
        }
        return ans;
    }
};