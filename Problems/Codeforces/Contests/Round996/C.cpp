#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2055/problem/C
/*
    构造
    题意:
        给定一个n行m列的矩阵, 矩阵中有一条连接起点和终点的特殊路径, 给定一个字符串指示路径方向
        要求给路径上的每个格子填数, 使得矩阵满足每行与每列的和都相等
    关键思考:
        由于每次操作都是向右或向下, 可以发现一个关键性质
        (1)当向下走时, 这一行不会再回来, 意味着这一行已经被确定下来
           当向右走时, 这一列不会再回来, 意味着这一列已经被确定下来
        而由由于矩阵每一行和每一列的和都相等
        因此, 这个定值x就完全取决于第一步怎么走, 第一步定下来, 后面的状态完全确定
        这意味着这个动态系统的自由度只有1
        问题就转化成给(0,0)填一个合适的数, 使得矩阵存在合法解
        从局部看, 问题是很复杂的, 因为相当于要解开n+m-1个方程的公共解
        但从整体上看, 考虑整个矩阵的和可以表达为
        sum == n*x == m*x
        显然x = 0一定是一个解, 并且当矩阵为非方阵的时候, x = 0是唯一解
        这样问题进一步转化为在路径上填数, 使得路径上的每行每列的和都是0
        可谓是不识庐山真面目, 只缘身在此山中
*/
//优化解法
void solve1(){
    int n, m;
    string s;
    cin >> n >> m >> s;
    vector<vector<ll>> grid(n, vector<ll>(m));
    for(auto &r : grid){
        for(auto &c : r){
            cin >> c;
        }
    }
    int x = 0, y = 0;
    for(auto c : s){
        if(c == 'D'){
            for(int j = 0; j < m; j++){
                if(j == y) continue;
                grid[x][y] -= grid[x][j];
            }
        }else{
            for(int i = 0; i < n; i++){
                if(i == x) continue;
                grid[x][y] -= grid[i][y];
            }
        }
        x += c == 'D';
        y += c == 'R';
    }
    for(int i = 0; i < n - 1; i++){
        grid[n - 1][m - 1] -= grid[i][m - 1];
    }
    for(auto &r : grid){
        for(auto &c : r){
            cout << c << " ";
        }
        cout << "\n";
    }
}
//比赛时写法
void solve(){
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<vector<ll>> grid(n, vector<ll>(m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
        }
    }
    int tot = s.size();
    int dx[2] = {1, 0};
    int dy[2] = {0, 1};
    ll sum = 0;
    int x = 0, y = 0;
    for(int i = 0; i < tot; i++){
        int dir = s[i] == 'D' ? 0 : 1;
        if(i == 0){
            if(dir == 0){
                for(int j = 0; j < m; j++){
                    sum += grid[0][j];
                }
                grid[0][0] = -sum;
                sum = 0;
            }
            else{
                for(int j = 0; j < n; j++){
                    sum += grid[j][0];
                }
                grid[0][0] = -sum;
                sum = 0;
            }
            x += dx[dir];
            y += dy[dir];
            continue;
        }
        ll cur = 0;
        if(i < tot){
            if(s[i] == 'D'){
                for(int j = 0; j < m; j++){
                    if(j == y) continue;
                    cur += grid[x][j];
                }
                grid[x][y] = sum - cur;
            }
            else{
                for(int j = 0; j < n; j++){
                    if(j == x) continue;
                    cur += grid[j][y];
                }
                grid[x][y] = sum - cur;
            }
        }
        x += dx[dir];
        y += dy[dir];
    }
    ll cur = 0;
    if(s[tot-1] == 'D'){
        for(int i = 0; i < m - 1; i++){
            cur += grid[n - 1][i];
        }
        /*int idx = tot - 1;
        while(s[idx] == 'D'){
            idx--;
            x -= 1;
        }
        ll t = 0;
        for(int i = 0; i < n - 1; i++){
            t += grid[i][m - 1];
        }
        ll del = cur - */
    }
    else{
        for(int i = 0; i < n - 1; i++){
            cur += grid[i][m - 1];
        }
    }

    grid[n - 1][m - 1] = sum - cur;
    for(auto &r : grid){
        for(auto &c : r){
            cout << c << " ";
        }
        cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve1();
    }
    return 0;
}