#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://atcoder.jp/contests/arc058/tasks/arc058_c
/*
    状压DP || 刷表法
    题意:
        给定一个整数n(n <= 40)和三个整数x,y,z(x <= 5, y <= 7, z <= 5),
        定义一个数组是合法的, 当且仅当数组中存在一组四元组下标(i,j,k,w)
        满足0 <= i < j < k < w <= n-1, 且∑ai->aj = x, ∑aj->ak = y, ∑ak->aw = z
        数组中每个位置的值∈[1, 10]
        求所有长度为n的数组中的合法数组数量, 结果对1e9 + 7取模
    关键思考:
        本题关键在于要发现正向思考不能进行
        这是因为"合法"这个信息是不好去维护的, 任何一个位置出现合法那么整个就合法了, 因此无论是使用
        动态规划还是组合计数, 都难以实现去重(例如n很大, 我们要让A区间合法, 此时后面的B区间也可能合法, 
        那么后面计算B的时候, 如何知道应该删除多少个重复计算的状态? 这很难维护)
        因此本题最关键的一步是使用反向思考, 计算不合法的数量
        "不合法"这个信息是可以高效转移的, 因为它只需要满足"前面不合法" & "当前位置也不合法", 这样即可维护下来
        因此我们有个初步的想法, 定义dp[i] := 前i个位置不合法的数量
        但显然一个状态i并不能决定dp值, 必须多个状态来确定"当前位置也不合法"这个条件
        问题就转化成了: 如何确定当前位置不合法
        以下就是状压DP最核心的部分了
        引入msk掩码, 利用二进制表示"当前能够组成的数字"
        下面是一个例子: x = 1, y = 2, z = 3, 我们有个数组是[2,1,1,1,2,1], 怎么判断是否合法呢
        我们可以把数组改写成01串： 1 0 1 1 1 1 0 1  //这里的改写方式是把x改写为1 << x - 1
        对于x,y,z我们改写成           1 1 0 1 0 0 
        这样只要满足x,y,z连接成的串是数组连接成的串的一个子串, 就说明符合条件
        注意: 尾部不能与改写后的二进制中间部分对齐
        如[2,2] : 1 0 1 0
                  1 0 1  这样对齐就是错的, 我们并不能从[2,2]中得到[2,1]
        这是因为一段连续数和这段数的和分别转化成01串后, 一定是包含关系
        那么只要我们的序列转化成01串后的所有位置都不包含x+y+z所代表的01串, 这个序列就是不合法的
        到这里, 核心问题就解决了
        问题就变成如何进行状态转移了
        定义dp[i][msk] := 考虑第i个位置, 前面状态为msk时的不合法数量
        考虑进行到位置i, 我们要枚举当前位置取的值, 然后把这个值加入之前的状态, 判断加入后是否依然不合法
        我们可以记之前的状态为msk, 那么加入操作就是(msk << j) | (1 << j - 1)
        这里涉及到利用msk更改(msk << j) | (1 << j - 1), 这里是或运算, 不可逆
        因此不能用查表法, 只能用刷表法, 也就是不是从后往前找, 而是直接从前往后推
        这样我们就只需要判断(msk << j) | (1 << j - 1) & ok 是否等于 ok
        这里为了避免溢出, 需要把(msk << j) | (1 << j - 1)与tot做位与运算
        因为我们只关心1 << x + y + z - 1之后的数字(由ok最高位决定)


*/
const int MOD = 1e9 + 7;
ll power_pow(ll a, ll b){
    ll res = 1;
    a %= MOD;
    while(b > 0){
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
//DP法1
void solve(){
    int n, x, y, z;
    cin >> n >> x >> y >> z;
    ll ans = power_pow(10, n);
    int sum = x + y + z;
    int tot = (1 << sum) - 1;
    int ok = (1 << z - 1) | (1 << y + z - 1) | (1 << x + y + z - 1); 
    vector<vector<int>> dp(n + 1, vector<int>(1 << sum));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++){
        for(int msk = 0; msk < tot; msk++) {
            for(int j = 1; j <= 10; j++) {
                int temp = (msk << j) | (1 << j - 1);
                temp &= tot;
                if((temp & ok) != ok) {
                    dp[i][temp] = (dp[i][temp] + dp[i - 1][msk]) % MOD;
                }
            }
        }
    }
    for(int msk = 0; msk < tot; msk++) {
        ans = (ans - dp[n][msk] + MOD) % MOD;
    }
    cout << ans << "\n";
}

//记忆化搜索
void solve1() {
    int n, x, y, z;
    cin >> n >> x >> y >> z;
    ll ans = power_pow(10, n);
    int sum = x + y + z;
    int tot = (1 << sum) - 1;
    int ok = (1 << z - 1) | (1 << y + z - 1) | (1 << x + y + z - 1);
    vector<vector<int>> memo(n, vector<int>(1 << sum, -1));
    auto dfs = [&](auto &&dfs, int i, int msk) -> int {
        if(i == n) return 1;
        int &res = memo[i][msk];
        if(res != -1) return res;
        res = 0;
        for(int j = 1; j <= 10; j++) {
            int nmsk = (msk << j) | (1 << j - 1);
            nmsk &= tot;
            if((nmsk & ok) != ok) {
                res = (res + dfs(dfs, i + 1, nmsk)) % MOD;
            }
        }
        return res;
    };
    ans = (ans - dfs(dfs, 0, 0) + MOD) % MOD;
    cout << ans << "\n";
}
//DP法2
void solve2() {
    int n, x, y, z;
    cin >> n >> x >> y >> z;
    ll ans = power_pow(10, n);
    int sum = x + y + z;
    int tot = (1 << sum) - 1;
    int ok = (1 << z - 1) | (1 << y + z - 1) | (1 << x + y + z - 1);
    vector<vector<int>> dp(n + 1, vector<int>(1 << sum, 0));
    for(int i = 0; i < tot; i++) dp[n][i] = 1;
    for(int i = n - 1; i >= 0; i--) {
        for(int msk = 0; msk < tot; msk++) {
            for(int j = 1; j <= 10; j++) {
                int nmsk = (msk << j) | (1 << j - 1);
                nmsk &= tot;
                if((nmsk & ok) != ok) {
                    dp[i][msk] = (dp[i][msk] + dp[i + 1][nmsk]) % MOD;
                }
            }
        }
    }
    ans = (ans - dp[0][0] + MOD) % MOD;
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve2();
    return 0;
}

