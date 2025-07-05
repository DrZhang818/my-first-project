#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://www.marscode.cn/practice/vkjwp462l6q75q?problem_id=7414004855076864044
/*
    图论dfs || bfs
    迷宫中危险位置的判定与统计
    1.建立反向图
        反向边定义:
            普通地板('.'): 可以从相邻的四个方向移动到当前位置
            传送器: 可以从被传送到当前位置的相邻格子移动到当前位置
        反向图优点:
            从出口位置出发, 在反向图中进行搜索, 可以一次性标记所有可达的位置
    2.搜索算法
        DFS或BFS:
            从出口位置开始, 遍历反向图, 标记所有可达的位置vis[i][j] = true
    3.危险位置统计:
        计算不可达的位置数量:
            遍历整个迷宫矩阵, 对于每个可站立的位置, 检查其可达性标记vis[i][j]
            累加所有vis[i][j] == false 的位置数量
*/
const int maxn = 105;
int N, M;
char maze[maxn][maxn];
bool vis[maxn][maxn];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
char rdir[4] = {'D', 'U', 'R', 'L'};

//DFS写法
void dfs(int x, int y){
    vis[x][y] = true;
    for(int k = 0; k < 4; k++){
        int nx = x + dx[k], ny = y + dy[k];
        if(nx < 0 || nx >= N || ny < 0 || ny >= M || vis[nx][ny]) continue;
        char cell = maze[nx][ny];
        if(cell == '.' || cell == rdir[k]){
            dfs(nx, ny);
        }
    }
}

//BFS写法
void bfs(int ex, int ey){
    queue<PII> q;
    q.push({ex, ey});
    vis[ex][ey] = true;
    while(!q.empty()){
        int x = q.front().first, y = q.front().second;
        q.pop();
        for(int k = 0; k < 4; k++){
            int nx = x + dx[k], ny = y + dy[k];
            if(nx < 0 || nx >= N || ny < 0 || ny >= M || vis[nx][ny]) continue;
            char cell = maze[nx][ny];
            if(cell == '.' || cell == rdir[k]){
                q.push({nx, ny});
                vis[nx][ny] = true;
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    int ex = -1, ey = -1;
    for(int i = 0; i < N; i++){
        string s; cin >> s;
        for(int j = 0; j < M; j++){
            maze[i][j] = s[j];
            if(maze[i][j] == 'O'){
                ex = i; ey = j;
            }
            vis[i][j] = false;
        }
    }
    dfs(ex, ey);
    int danger = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            char c = maze[i][j];
            if(c != 'O' && !vis[i][j]){
                danger++;
            }
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(vis[i][j]){
                cout << 1 << ' ';
            }
            else{
                cout << 0 << ' ';
            }
        }
        cout << '\n';
    }
    cout << danger << endl;
    return 0;
}
