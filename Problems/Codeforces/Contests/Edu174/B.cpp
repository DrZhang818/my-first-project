#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2069/problem/B
/*
    贪心 || 并查集
    题意:
        给定一个N × M的矩阵, a[i][j]的值表示该单元格的颜色
        定义一对单元格是合法的, 当且仅当两个格子不相邻
        定义一个单元格集合是合法的, 当且仅当集合内任意一对单元格都是合法的
        规定只包含一个单元格的集合是合法的集合
        你可以进行以下操作:
        op: 选择一个颜色全部相同的合法单元格集合, 并将该集合中的所有单元格修改成任意颜色
        求使得矩阵所有单元格颜色相同所需要的最小操作次数
        范围: N,M∈[1,700], a[i][j]∈[1,N×M]
    关键思考:
        本题是决策类问题, 常用思考方式为: 暴力->贪心||DP, 常用优化手段为: 前缀和、双指针、数据结构...
        我们可以定义函数F(x) := 把所有颜色为x的格子转化成其他颜色需要的最小次数
        那么由于不同颜色之间是独立的, 因此我们可以考虑计算出所有颜色的F(x)
        贪心地想, 我们希望把转化目标定为F最大的那个颜色
        这样答案就是 ΣF(x) - max{F(x)}, x ∈ set(a)
        问题就转化为如何高效计算每种颜色的F值
        这可以用并查集思想解决
        初始假定所有相同颜色的节点{x1,x2,...,xs}单独成块
        枚举过程中如果发现x[i]与某个块的所有节点都不相邻, 那么就合并到那个块中
        这里贪心地想, 如果发现xi和xk相邻, 那么它们一定不能在同一个块中
        而其他任意节点x至多与{xi,xk}中的一个相邻, 显然除了xi,xk本身外, 不存在任何节点可以与两个同时相邻
        那么我们就证明了F(x)的上确界为2
        则问题转化为判断每种颜色x是否存在两个相邻的节点
*/
void solve(){ 
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> F(n * m + 1);
    int dir[3] = {-1, 0, -1};
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int x = a[i][j];
            if(F[x] == 2) {
                continue;
            }
            F[x] = 1;
            for(int k = 0; k < 2; k++) {
                int nx = i + dir[k];
                int ny = j + dir[k + 1];
                if(nx < 0 || nx >= n || ny < 0 || ny >= m) {
                    continue;
                }
                if(a[nx][ny] == a[i][j]) {
                    F[x] = 2;
                    break;
                }
            }
        }
    }
    int ans = accumulate(F.begin(), F.end(), 0) - *max_element(F.begin(), F.end());
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
