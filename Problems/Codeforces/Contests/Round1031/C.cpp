#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2113/problem/C
/*
    构造 || 贪心 || 二维前缀和
    题意:
        给定一个N×M的矩形, 每个格子有'.''#''g'三种状态, '.'表示空格, '#'表示石头
        'g'表示金子, 你有无限个爆炸半径为k的炸药, 你可以利用炸药来获得金子, 操作如下:
        op: 选择一个空格子(x,y)作为爆炸中心, 放置炸药后, i∈[x-k,x+k], j∈[y-k,y+k]
            的格子将全部变为空格子'.', 爆炸边缘的金子会被收集, 不在边缘的金子由于
            爆炸威力过大而被摧毁
            形式化地, 坐标(i,j)满足i=x+k || i=x-k || j=y+k || j=y-k的金子会被收集
        求出最多能收集多少个金子
        范围: n,m,k∈[1,500], a[i]∈{'.', '#', 'g'}
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 由于每次操作会改变地图的结构, 这意味着引爆顺序至关重要
        思考暴力方法: 枚举第一个炸药的位置, 第二个炸药的位置,... 时间复杂度为O(nm!)
        显然, 这是个状态量爆炸的优化问题, 我们有三种方式来解决:
        (1)二分答案 (2)划分等价类 (3)贪心剪枝
        二分答案不能成立, 因为我们并没有简单的方式能够验证答案是否合法, 仍需要枚举
        划分等价类在这里并不奏效, 因为不同的操作顺序得到的答案之间没有什么联系, 无法划分
        于是我们往贪心剪枝上进行思考:
        首先有个很显然的性质: 如果某种操作序列结束后得到的地图上还有金子, 那么一定是不优的
        因为继续引爆炸药消除这个金子, 得到的贡献一定∈[0,1], 这保证了全部消除是不劣的
        由于得到的答案 = 总金子 - 被摧毁的金子
        因此我们可以把问题转化问最小化被摧毁的金子
        这指导我们有以下贪心策略: 在引爆时尽量避免爆炸内部有太多金子
        关键观察:
        我们发现, 引爆(x,y)后, 会形成一个大坑, 这样下一次引爆的时候可以将坐标设置为
        (x+1,y),(x-1,y),(x,y+1),(x,y-1), 这样可以保证爆炸内部没有金子
        这意味着, 第一次引爆之后, 我们就可以无损地得到其余地所有金子
        因此只需要做二维前缀和, 并枚举第一次引爆的位置即可
*/
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector a(n + 1, vector<char>(m + 1));
    vector pre(n + 1, vector<int>(m + 1));
    int tot = 0, ans = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            cin >> a[i][j];
            if(a[i][j] == 'g') {
                pre[i][j] = 1;
                tot += 1;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }
    }
    auto get = [&](int x1, int y1, int x2, int y2) -> int {
        x1 = min(n, x1), y1 = min(m, y1), x2 = max(1, x2), y2 = max(1, y2);
        return pre[x1][y1] - pre[x1][y2 - 1] - pre[x2 - 1][y1] + pre[x2 - 1][y2 - 1]; 
    };
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(a[i][j] != '.') continue;
            int cur = get(i + k - 1, j + k - 1, i - k + 1, j - k + 1);
            ans = max(ans, tot - cur);
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
