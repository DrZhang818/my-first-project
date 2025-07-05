#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/grid-teleportation-traversal/description/
class Solution {
public:
    struct info {
        int x, y;
    };
    struct node {
        int x, y, w;
    };
    int dir[5] = {-1, 0, 1, 0, -1};
    int minMoves(vector<string>& a) {
        int n = a.size(), m = a[0].size();
        if(a[n - 1][m - 1] == '#') return -1;
        deque<node> q;
        q.push_back({0, 0, 0});
        vector<vector<info>> idx(26);
        vector<bool> vis1(26);
        vector<vector<bool>> vis2(n, vector<bool>(m));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(isalpha(a[i][j])) {
                    idx[a[i][j] - 'A'].push_back({i, j});
                }
            }
        }
        while(!q.empty()) {
            auto [x, y, w] = q.front(); q.pop_front();
            if(vis2[x][y]) continue;
            vis2[x][y] = true;
            if(x == n - 1 && y == m - 1) return w;
            if(a[x][y] != '.' && !vis1[a[x][y] - 'A']) {
                vis1[a[x][y] - 'A'] = true;
                for(auto [nx, ny] : idx[a[x][y] - 'A']) {
                    if(nx == x && ny == y) continue;
                    q.push_front({nx, ny, w});
                }
            } 
            for(int i = 0; i < 4; i++) {
                int nx = x + dir[i], ny = y + dir[i + 1];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] == '#' || vis2[nx][ny]) continue;
                q.push_back({nx, ny, w + 1});
            }
        }
        return -1;
    }
};