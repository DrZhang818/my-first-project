#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://atcoder.jp/contests/abc421/tasks/abc421_c
/*
    贪心 || 构造
    题意:
        给定一个长度为2N的字符串S, S中恰好有N个A和N个B, 你可以进行以下操作
        op: 选择一个下标i (1 <= i < 2N), 交换S[i]和S[i + 1]
        定义一个字符串是合法的, 当且仅当字符串中没有两个相邻的字符相同
        请你求出最少需要几次操作使得S变为合法字符串
        范围: N∈[1,5e5]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心||网络流, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先思考暴力做法, 由于答案只有两种: "ABAB..." 或 "BABA...", 因此我们考虑分别算出S转化成这两种
        形态的最小次数, 其中较小者就是答案
        不妨以"ABAB..."为例, 设T = "ABAB...", 从左到右考虑, 我们容易发现以下性质:
        (1)若 S[i] = T[i], 那么无需调整
        (2)若 S[i] ≠ T[i], 贪心地想, 我们需要找到后面离i最近的一个等于T[i]的字符, 将其移动过来
        直接模拟是 O(n^2)的, 我们可以用set来维护查询过程, 可以做到 O(nlogn)
        不过我们有更加巧妙的 O(n)做法
        我们把S中的 'A' 所在下标收集到pos数组中, 贪心地想, 一定有以下策略:
        pos[i]最终调整到 2 * i - 1
        因此, 其带来的代价最小是 |pos[i] - (2 * i - 1)|
        总代价 >= ∑ |pos[i] - (2 * i - 1)|
        下面证明以上不等式可以取等, 证明方式和上面调整策略一样:
        (1)若 S[i] = T[i], 那么无需调整
        (2)若 S[i] ≠ T[i] ∧ T[i] = 'A', 此时我们需要把当前pos数组中的第一个A直接移动到第i位, 相当于
            一次性做完了这个'A'的剩余贡献
        (3)若 S[i] ≠ T[i] ∧ T[i] = 'B', 那么我们把最近的B移动到第i位, 可以理解成把路径中的'A'
            从后向前依次向后移动一格, 相当于把这些'A'各自做了一次贡献
        不难发现, 调整过程中每个 'A' 都在向其正确方向移动, 因此最小代价可以取到
      */
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    vector<int> pos;
    for(int i = 0; i < 2 * n; i++) {
        if(s[i] == 'A') {
            pos.push_back(i);
        }
    }

    ll c0 = 0, c1 = 0;
    for(int i = 0; i < n; i++) {
        c0 += abs(pos[i] - 2 * i);
        c1 += abs(pos[i] - 2 * i - 1);
    }
    ll ans = min(c0, c1);

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
