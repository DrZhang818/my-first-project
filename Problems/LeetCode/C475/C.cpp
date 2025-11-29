#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
int dp[201][201][1001];
PII dir[] = {{1, 0}, {0, 1}};
class Solution {
public:
    int maxPathScore(vector<vector<int>>& a, int k) {
        int n = a.size(), m = a[0].size();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                for(int c = 0; c <= k; c++) {
                    dp[i][j][c] = -1;
                }
            }
        }
        dp[0][0][0] = 0;
        for(int x = 0; x < n; x++) {
            for(int y = 0; y < m; y++) {
                for(auto [dx, dy] : dir) {
                    int nx = x + dx, ny = y + dy;
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m) {
                        continue;
                    }
                    int nw = a[nx][ny];
                    int nc = a[nx][ny] != 0;
                    for(int c = 0; c + nc <= k; c++) {
                        if(dp[x][y][c] == -1) {
                            continue;
                        }
                        dp[nx][ny][nc + c] = max(dp[nx][ny][nc + c], dp[x][y][c] + nw);
                    }
                }
            }
        }
        int ans = -1;
        for(int c = 0; c <= k; c++) {
            ans = max(ans, dp[n - 1][m - 1][c]);
        }
        return ans;
    }
};