#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2127/problem/B
/*
    贪心 || 枚举 || 博弈
    题意:
        Alice把Bob困在一个1 × N的网格中, 初始时网格部分单元格是墙壁, 其余为空, Bob位于某个空格x中
        每天按以下顺序发生事件:
            (1)Alice选择一个空格建造墙壁(不能在Bob当且位置建墙)
            (2)Bob选择移动方向(左或右):
                若该方向无墙壁, 他将成功逃脱
                否则, 他会移动到该方向最近的墙壁并摧毁它, 当天结束时Bob位于被摧毁的墙所在位置
        Bob始终知晓所有墙壁位置, 他希望最小化逃脱天数, 而Alice希望最大化这个天数
        假设双方以最优策略进行, Bob最少需要几天逃脱
        范围: N∈[2,2e5], x∈[1,N]
    关键思考:
        本题为决策类题目, 常用思考方式为暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        观察题目性质, 我们很容易得出: Bob最优策略下, 全程只会沿着一个方向移动
        这个性质用交换论证可以证明, 假设一个移动序列是10110111, 最后逃脱方向是1
        那么我们把所有的0替换为1, 得到的结果一定更优
        因此我们就可以枚举两个方向Bob逃脱的最小天数, Alice会选择其中较大的一个, 因此二者取max就是答案
        然而Bob选择哪个方向又由Alice的第一次操作决定
        Alice的操作有一个性质: 贪心地想, 必然放置在Bob当前位置 - 1或当前位置 + 1
        (1)如果Alice第一次在x - 1的位置建墙
            那么Bob的逃脱天数是min(x, n - r), r为 > x的第一个墙壁位置
        (2)如果Alice第一次在x + 1的位置建墙
            那么Bob的逃脱天数是min(l + 1, n - 1 - x), l为 < x的第一个墙壁位置
*/
void solve() {
    int n, x;
    cin >> n >> x;
    string s;
    cin >> s;
    x--;
    int l = x, r = x;
    while(l >= 0 && s[l] == '.') l--;
    while(r < n && s[r] == '.') r++;
    cout << 1 + max(min(x, n - r), min(n - 1 - x, l + 1)) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
