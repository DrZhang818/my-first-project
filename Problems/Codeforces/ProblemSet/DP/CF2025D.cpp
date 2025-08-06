#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2025/problem/D
/*
    DP || 差分
    题意:
        你有两个等级为0的属性: "力量"和"智力"
        在游戏过程中, 你将获得m个属性点用于提升属性, 每消耗一个属性点可以将其中一个属性提升一级
        除了"获得属性点"这一事件外, 你还会遇到"属性检定"事件: 如果对应属性等级达到要求则通过, 否则失败
        经过整理, 你按照时间线列出了包含所有"获得属性点"和遇到的"属性检定"的记录列表, 其中共有n条记录
        每条记录的格式为一个整数r
        若r = 0, 表示该条记录是获得一个属性点, 可自由分配给力量或智力
        若r > 0, 表示智力检定, 当智力等级 >= |r| 时通过
        若r < 0, 表示力量检定, 当力量等级 >= |r| 时通过
        n条记录中, 恰有m条记录为r = 0
        你想知道: 通过合理分配属性点, 最多能通过多少次"属性检定"? 你不能改变记录的发生顺序
        范围: m∈[1,5000], n∈(m, 2e6], r∈[-m,m]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        本题状态定义是很好想的, 我们设前i条记录共得到sum个属性点, 那么智力 + 力量 = sum, 因此我们枚举其中
        一个, 就可以通过等式推导出另一个, 这是本题的关键性质
        dp[i][j] := 考虑前i条记录, 智力等级为j时最多能通过的次数
        我们分类讨论状态转移
        (1)r > 0, 智力检定
            dp[i + 1][r : sum] = dp[i][r : sum] + 1
        (2)r < 0, 力量检定
            sum - j >= -r -> j <= sum + r
            dp[i + 1][0 : sum + r] = dp[i][0 : sum + r] + 1
        (3)r = 0, 获得属性点, 此时sum = sum + 1
            1.如果把属性点加到力量上:
                dp[i + 1][0 : sum - 1] = dp[i][0 : sum - 1]
            2.如果把属性点加到智力上:
                dp[i + 1][1 : sum] = dp[i][0 : sum - 1]
            故dp[i + 1][j] = max(dp[i][j], dp[i][j - 1])
        这样状态转移的时间复杂度为O(nm), 显然无法接受, 考虑如何优化
        由于(1)(2)的状态转移只涉及区间加, 因此我们可以用差分/树状数组/线段树维护
        (3)的处理很麻烦, 但好在m <= 5000, 我们暴力更新(3)的时间复杂度是O(m^2), 这是允许的
        因此就能得到正解了, 我们用差分维护(1)(2), 暴力更新(3), 可以得到O(n + m^2)的时间复杂度
*/
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> dp(m + 2), d(m + 2);
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        int r = a[i];
        if(r > 0) {
            if(r <= sum) {
                d[r]++;
                d[sum + 1]--;
            }
        } else if(r < 0) {
            if(sum + r >= 0) {
                d[0]++;
                d[sum + r + 1]--;
            }
        } else {
            for(int j = 1; j <= sum; j++) {
                d[j] += d[j - 1];
            }
            for(int j = 0; j <= sum; j++) {
                dp[j] += d[j];
            }
            sum++;
            for(int j = sum; j >= 1; j--) {
                dp[j] = max(dp[j - 1], dp[j]);
            }
            d.assign(m + 2, 0);
        }
    }
    for(int i = 1; i <= sum; i++) {
        d[i] += d[i - 1];
    }
    for(int i = 0; i <= sum; i++) {
        dp[i] += d[i];
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
