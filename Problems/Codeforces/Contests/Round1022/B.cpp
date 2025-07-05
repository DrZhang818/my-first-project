#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2108/problem/B
/*
    构造 || 贪心 || 位运算
    题意:
        给定一个n和x, 你需要构造出一个长度为n的正整数数组，使得数组的异或和等于x，
        且数组的累加和最小，输出最小值，不存在任何方案输出-1
        范围: n∈[1,1e9], x∈[0,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 由于是位运算构造, 我们可以按位独立思考
        由于异或是不带进位的加法, 因此最小值显然要大于等于x
        为了总和更小, 我们尽量让每个元素成为组成x的一部分, 减少冗余元素
        假设x有k个1, 那么当n <= k的时候显然最小值就是x
        当n > k的时候, 我们必有n - k个冗余元素, 这些冗余元素的异或和要为0
        设m = n - k, 显然若m为偶数的情况很简单, 只需要把冗余元素设为m个1即可
        若m为奇数, 则情况有些复杂:
            我们必须借助之前填好的k个元素
            (1)考虑让其中一个元素a的最后一位变成1
            这样我们填写m个1, 其中m-1个自我配对, 剩下的单独一个与a的最后一位配对
            (2)但这里就牵扯一个问题, 如果x = 1, 那么前面k个元素中就只有1
            这意味着a的最后一位本身就是1, 我们不能与它配对
            此时我们必须利用倒数第二位来进行配对, 此时答案就是m-1+4(两个倒数第二位)
        此时通过样例, 我们发现了一个特殊情况: x = 0
        此时k = 0, 意味着我们这m个元素不能借助之前的元素, 必须依靠自己组成0
        (1)m为偶数的情况同上, 只需要m个1即可
        (2)m为奇数的时候, 我们会发现单独一个m就不可行了
           当m >= 3时, 我们可以取出3个构成11,10,01, 其余元素全部为1
           可以证明这样得到的就是最小的, 因为我们必须借助倒数第二位
*/
void solve() {
    ll n, x;
    cin >> n >> x;
    if(x == 0) {
        if(n % 2 == 0) {
            cout << n << "\n";
        } else if(n == 1) {
            cout << -1 << "\n";
        } else {
            n -= 3;
            cout << n + 6 << "\n";
        }
        return;
    }
    ll ans = 0, low = x == 1 ? 4 : 2;
    for(int i = 30; i >= 0; i--) {
        if(n && (x >> i & 1)) {
            ans += (1 << i);
            x -= (1 << i);
            n -= 1;
        } 
    }
    if(n == 0) {
        ans += x;
    } else {
        if(n % 2 == 0) {
            ans += n;
        } else {
            ans += low + n - 1;
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
