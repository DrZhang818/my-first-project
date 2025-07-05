#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://atcoder.jp/contests/abc383/tasks/abc383_b
/*
    网格图遍历
    题意:  选择两点最大化被覆盖地板数
        实际上是一个在离散点集上选择两个点, 使得覆盖的点数(满足一定距离条件)最大化的优化问题。
    思路:
        枚举两个不同地板位置作为加湿器的摆放点。
        对每个地板格子，检查是否被加湿(距离判断)。
        记录被加湿数量，更新最大值。    
*/
void solve(){
    int H, W, D;
    cin >> H >> W >> D;
    vector<string> grid(H);
    for(int i = 0; i < H; i++) cin >> grid[i];
    vector<PII> floors;
    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(grid[i][j] == '.'){
                floors.push_back({i, j});
            }
        }
    }
    int F = floors.size();
    int ans = 0;
    for(int a = 0; a < F; a++){
        for(int b = a + 1; b < F; b++){
            int count = 0;
            int x1 = floors[a].first, y1 = floors[a].second;
            int x2 = floors[b].first, y2 = floors[b].second;
            for(int k = 0; k < F; k++){
                int x = floors[k].first, y = floors[k].second;
                int dis1 = abs(x - x1) + abs(y - y1);
                int dis2 = abs(x - x2) + abs(y - y2);
                if(dis1 <= D || dis2 <= D) count++;
            }
            ans = max(ans, count);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    solve();
    
    return 0;
}