#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc407/tasks/abc407_d
/*
    记忆化搜索 || 二进制状压
    题意:
        给定一个N × M的矩阵, 你可以使用任意数量的1 × 2的矩形覆盖一些数, 矩形可以横向或纵向摆放
        必须保证矩形之间无重叠且完全在矩阵内部
        操作过后, 你的得分为未被覆盖的数字的异或和, 求你能得到的最大得分是多少
        范围: NM∈[1,20], a[i][j]∈[0,2^60]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 由于矩阵总格数不超过20, 且每个格子只有覆盖和不覆盖两种状态
        因此可以保证总状态数 <= 2^20, 这提示我们考虑使用暴力方法解决问题
        一种思路是枚举矩阵的所有状态, 对其中的合法状态进行统计答案
        但我们很快发现一个问题: 验证一个状态是否合法是很困难的, 需要使用二分图匹配等知识点
        因此我们换个思路, 直接按照规则构造所有的合法方案, 避免生成不合法的方案
        朴素的想法是: 枚举每个点, 有不放/横着放/竖着放三种方式, 复杂度为3^20
        然后我们会发现, 最后一行和最后一列可以省一些状态, 且由于放了一个矩形后会产生约束
        因此复杂度可以降到3^11~3^12左右
        进一步观察, 由于我们只关心哪些区域被覆盖, 而不关心是如何覆盖的
        因此上述方式会有很多重复访问的状态, 我们考虑使用记忆化进行剪枝
        关键问题就是如何方便存储状态
        我们可以把N×M的矩阵用一个二进制数表示, 第(i,j)个格子对应与i*m+j位
        如果某位为1代表被覆盖, 为0代表未被覆盖
        这样做还有个好处: 格子的摆放也很容易表示了
        如果是横向摆放, 对应的位信息就是1 << 1 | 1
        如果是纵向摆放, 对应的位信息就是1 << m | 1
        这样检测某个状态s能否摆放, 就只需要做 & 运算看结果是否为0即可
        经过这样转化, 状态数被严格限制在2^20以内, 经测验4×5的实际状态数为2^16左右
        总时间复杂度为O(nm2^(nm))
*/
void solve() {
    int n, m;
    cin >> n >> m;
    const int r = 1 << 1 | 1;
    const int c = 1 << m | 1;
    vector a(n, vector<ll>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector<int> vis(1 << (n * m));
    ll ans = 0;
    auto dfs = [&](auto &&self, int s) -> void {
        ll cur = 0;
        vis[s] = true;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(s >> (i * m + j) & 1) continue;
                cur ^= a[i][j];
                int ns = s | r << (i * m + j);
                if(j + 1 < m && (s & r << (i * m + j)) == 0 && !vis[ns]) {
                    self(self, ns);
                }
                ns = s | c << (i * m + j);
                if(i + 1 < n && (s & c << (i * m + j)) == 0 && !vis[ns]) {
                    self(self, ns);
                }
            }
        }
        ans = max(ans, cur);
    };
    dfs(dfs, 0);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
