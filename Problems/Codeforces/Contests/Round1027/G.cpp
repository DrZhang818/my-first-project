#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2114/problem/G
/*
    构造 || 前后缀分解 || 贪心
    题意:
        起初有一个空数组, 每次操作可以向当前数组的左端或右端加入一个任意整数, 然后数组中
        相邻且相同的数会合并为两数之和
        现在给定一个长度为N的数组, 问该数组能否通过恰好k次操作生成
        范围: n∈[1,1e5], k∈[n,1e6], a[i]∈[1,1e9], a[i - 1] != a[i]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 我们发现合并后的数字必然是偶数, 因此每个数字贡献的次数与其被2整除
        的次数有关
        我们把数字x写成2^t * odd的形式, 则x最多能贡献的次数就是2^t(连续加入2^t个odd)
        并且我们会发现, 可以通过添加odd的2^k倍而非odd使得贡献次数变小
        不难证明贡献次数[1,2^t]都是可达的
        本题的难点在于, 合并操作是自动进行的, 这意味着如果我们拼出了a[i], 那么在拼a[i + 1]
        以及a[i - 1]的时候不能出现某个中间值与a[i]相邻相等
        这样第一个数拼哪个就非常关键了, 当我们把a[i]拼好后, i前面的a[j]都要避免a[j+1]
        i后面的a[j]都要避免a[j-1]
        当我们确定了第一个数拼哪个的时候, 整个过程也就确定了, 就是向前向后两个方向依次拼数
        因此朴素的思路就是枚举第一个数的位置, 算出前面的贡献, 当前的贡献, 后面的贡献
        这样就变成了经典的前后缀分解问题, 利用前缀和/后缀和优化即可
        最后, 只差一个最关键的问题没有解决: 如何求解x避免y的情况下最多能贡献几次
        我们把x写为2^s * odd_x, y写为2^t * odd_y
        (1)当odd_x != odd_y时, y对x是无影响的, 因为不可能出现2^p * odd_x = 2^t * odd_y
            证明: 当p != t时, 一边是奇数一边是偶数, 一定不成立
                  当p = t时, 由于odd_x != odd_y, 故不成立
        (2)当x < y时, y对x无影响
            证明: 2^s * odd_x < 2^t * odd_y, 故2^p * odd_x < 2^t * odd_y (p <= s)
        (3)当x >= y 且odd_x = odd_y时: 
            令odd = odd_x = odd_y
            与y相邻的数至少是2^(t+1) * odd, 这意味着我们把2^(t+1)步变成了1步
            因此贡献减少了2^(t+1)-1
            注意, 当我们放上2^(t+1) * odd之后, y对x就无影响了, 因为这个数插在中间形成了阻隔
        trick: 如何快速分解x = 2^t * odd
            t就是x二进制中末尾连续0的个数, 而2^t = 1 << t = lowbit(x)
            2^t = x & -x
            odd = x / (x & -x)
*/
int cal(int x, int y) {
    int lx = x & -x;
    int ly = y & -y;
    if(x / lx != y / ly || x < y) {
        return lx;
    } else {
        return lx - 2 * ly + 1;
    }
}
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1), suf(n + 1);
    for(int i = 2; i <= n; i++) {   
        pre[i] = pre[i - 1] + cal(a[i - 1], a[i]); 
    }
    for(int i = n - 1; i >= 1; i--) {
        suf[i] = suf[i + 1] + cal(a[i + 1], a[i]);
    }
    for(int i = 1; i <= n; i++) {
        if(pre[i] + (a[i] & -a[i]) + suf[i] >= k) {
            cout << "YES\n";
            return ;
        }
    }
    cout << "NO\n";
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
