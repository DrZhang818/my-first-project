#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1833/D
/*
    贪心 || 构造
    题意:
        给定一个1~N的排列, 你需要进行恰好一次操作, 最大化操作后得到的排列(字典序最大)
        op: 选择一个区间[l,r], 翻转区间 并 交换前后缀(交换a[:l-1]和a[r+1:])
        例如对于排列[2,3,1,5,4], 选择l=2,r=3, 得到的结果是[5,4,1,3,2]
        范围: n∈[1,2000]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 要让字典序最大, 显然我们要想尽办法从左到右最大化数字
        从操作的方式我们可以看出, 第一个位置的数字是一定要向后移动的
        因此, 我们的第一步就应该是从[2,n]中找到最大的数字, 想办法移动到第一个位置
        我们考虑最大的数字所在位置为i
        (1)当i < n时, 我们必须把r设置为i-1, 这样翻转后才能正好让i->1
        (2)当i = n时, 我们可以把r设置为i或者i-1, 贪心地想, 设置为i一定是更优的
            因为设置为i-1得到的所有结果都能由设置为i得到
            可以理解为: 设置为i-1就是r设置为i, 但l必须 <= i - 1
                       设置为i  就是r设置为i, 但l <= i
            显然设置为i更优
        下面我们考虑左端点l如何选取
        a[r+1:]已经被确定性地放在了排列的开头位置了, 确定左端点l其实就是最大化下面这个数组
        (a[r], a[r-1], ..., a[l], a[1], a[2], ..., a[l-1])
        a[r]是已经固定下来的, 那么问题就变成a[r-1],...,a[l] > a[1]
        只需要从r向左枚举, 遇到 < a[1]的停下即可
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    if(n == 1) {
        cout << 1 << "\n";
        return;
    }
    int r = -1, mx = -inf;
    for(int i = 2; i <= n; i++) {
        if(a[i] > mx) {
            mx = a[i];
            r = i;
        }
    }
    r = r == n ? r : r - 1;
    int l = r;
    while(l > 1 && a[l - 1] > a[1]) l--;
    for(int i = r + 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    for(int i = r; i >= l; i--) {
        cout << a[i] << " ";
    }
    for(int i = 1; i <= l - 1; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
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
