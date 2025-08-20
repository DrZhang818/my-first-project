#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/633/D
/*
    枚举 || 数学
    题意:
        定义类斐波那契序列为:
        (1)序列至少包含2个元素
        (2)f[0]和f[1]可以是任意值
        (3)对于所有的n >= 0, 满足f[n + 2] = f[n + 1] + f[n]
        给定一个长度为N的数组, 你需要重新排列该数组, 使其尽可能长的前缀构成类斐波那契数列
        输出最大长度
        范围: N∈[2,1000], a[i]∈[-1e9, 1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力方法, 枚举f[0]和f[1], 验证能生成的前缀长度, 时间复杂度为O(N^2 * 平均长度)
        我们需要考察一下期望平均长度是多少
        我们知道斐波那契数列的通项公式为:
            F(n) = A * ((1 + sqrt(5)) / 2)^n + B * ((1 - sqrt(5)) / 2)^n
        于是有:
            F[0] = A + B
            F[1] = (A + B) / 2 + (A - B) * sqrt(5) / 2
        解得:
            A = (f[1] - f[0]*(1-sqrt5)/2) / sqrt5
            B = (f[0]*(1+sqrt5)/2 - f[1]) / sqrt5
        我们研究F(n)的性质, 不难发现
            A * ((1 + sqrt(5)) / 2)^n 这一项是决定项
            因为这一项的公比绝对值 > 1, 而后边的公比绝对值 < 1
            因此当系数A ≠ 0时, 我们可以近似认为F(n)的增长速度是O(((1 + sqrt(5)) / 2)^n)
        而a[i]∈[-1e9, 1e9], 最多有O(logM)项就会超出a[i]的范围
        因此期望的时间复杂度为O(N^2 * logM)
        此外要特判A = 0的情况
        由于A = (f[1] - f[0]*(1-sqrt5)/2) / sqrt5, 而f[0],f[1]均为整数
        因此A = 0, 当且仅当f[0] = f[1] = 0
        此时由递推式 f[n + 2] = f[n + 1] + f[n]可知, 所有元素均为0
        因此这是个全0前缀, 最大长度是0的个数, 特判即可
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    int ans = mp[0];
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(j == i || a[i] == 0 && a[j] == 0) continue;
            vector<int> cur = {a[i], a[j]};  
            mp[a[i]]--;
            mp[a[j]]--;
            while(1) {
                int v = cur[cur.size() - 2] + cur.back();
                if(mp[v] > 0) {
                    cur.push_back(v);
                    mp[v]--;
                } else {
                    break;
                }
            }
            ans = max(ans, (int)cur.size());
            for(int v : cur) {
                mp[v]++;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
