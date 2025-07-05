#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    struct info {
        int x, y, s, w;
    };
    int dir[5] = {0, 1, 0, -1, 0};
    int minMoves(vector<string>& a, int k) {
        int x = -1, y = -1, n = a.size(), m = a[0].size();
        vector<vector<int>> id(n, vector<int>(m, -1));
        int cnt = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) { 
                if(a[i][j] == 'S') {
                    x = i, y = j;
                } else if(a[i][j] == 'L') {
                    id[i][j] = cnt++;
                }
            }
        }
        vector max_w(n, vector(m, vector<int>(1 << cnt, -1)));
        vector<info> q = {{x, y, 0, k}};
        max_w[x][y][0] = k;
        for(int ans = 0; !q.empty(); ans++) {
            auto tmp = q;
            q.clear();
            for(auto &[x, y, s, w] : tmp) {
                if(s == (1 << cnt) - 1) return ans;
                if(w == 0) continue;
                for(int i = 0; i < 4; i++) {
                    int nx = x + dir[i], ny = y + dir[i + 1];
                    if(nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] == 'X') continue;
                    int ns = s, nw = w - 1;
                    if(a[nx][ny] == 'L') {
                        ns |= 1 << id[nx][ny];
                    } else if(a[nx][ny] == 'R') {
                        nw = k;
                    }
                    if(nw > max_w[nx][ny][ns]) {
                        max_w[nx][ny][ns] = nw;
                        q.emplace_back(nx, ny, ns, nw); 
                    }
                }
            }
        }
        return -1;
    }
};