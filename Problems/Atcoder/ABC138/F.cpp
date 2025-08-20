#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

//https://atcoder.jp/contests/abc138/tasks/abc138_f
/*
    DP
    题意:
        给定L,R, 求有多少个点对(x,y), 满足L <= x <= y <= R 且 y % x = y xor x
        结果对1e9 + 7取模
        范围: 1 <= L <= R <= 1e18
    关键思考:
        本题为计数类问题, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力做法, 枚举每个点对并验证, 时间复杂度为O(N^2), 超时
        由于是静态计数问题, 我们可以打表找下规律
        打表发现, 当x和y最高位不同时, 一定不满足条件
        当x和y最高位相同时, y < 2 * x, 因此y % x = y - x
        原条件等价于y - x = y xor x ==> y - x = y + x - 2y&x ==> x = y & x
        归纳得, x和y的最高位1要相同, 并且x二进制位中为1的位置在y中也为1
        如何统计这些数呢? 
        我们可以枚举x,y的最高位, 枚举只会带来O(logN)的小常数
        接下来思考如何同时满足 L <= x <= y <= R 和 x = y & x
        我们可以用数位dp的思想解决, 只不过本题比较特别, 需要同时维护x和y, 是个带上下界的数位dp
        首先考虑y的第i位:
            y要保证不超过R, 因此我们需要记录y前面填过的位 与 R前面的位是否相同
            如果相同, 那么我们当前位必须 <= R的当前位
            否则, 我们可以填0/1
        接着考虑x的第i位:
            x要保证不小于L, 并且x = x & y
            因此我们需要记录x前面填过的位 与 L前面的位是否相同
            如果相同, 那么我们当前位必须 >= L的当前位
            否则, 我们可以填0/1
            同时, 由于要满足x = x & y, 因此x当前位必须 <= y当前位
        小细节:
            为什么即使limL = true 或 limR = true, 我们仍可以用记忆化的结果?
            因为本题只有单组数据, 同一组数据的limL和limR状态唯一
*/
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int numL[64], numR[64];
int dp[64][2][2];
int dfs(int pos, bool limL, bool limR) {
    if(pos == 0) return 1;
    int &res = dp[pos][limL][limR];
    if(res != -1) return res;
    res = 0;
    int down = limL ? numL[pos] : 0, up = limR ? numR[pos] : 1;
    for(int y = down; y <= up; y++) {
        for(int x = down; x <= y; x++) {
            add(res, dfs(pos - 1, limL && x == down, limR && y == up));
        }
    }
    return res;
}
void solve() {
    ll l, r;
    cin >> l >> r;
    int lenL = 0, lenR = 0;
    while(l) {
        numL[++lenL] = l & 1;
        l >>= 1;
    }
    while(r) {
        numR[++lenR] = r & 1;
        r >>= 1;
    }
    int ans = 0;
    for(int i = lenL; i <= lenR; i++) {
        add(ans, dfs(i - 1, i == lenL, i == lenR));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(dp, -1, sizeof(dp));
    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
