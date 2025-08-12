#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc413/tasks/abc413_e
/*
    归并分治 || 贪心
    题意:
        给定一个1~2^N的排列P, 编号为0~2^N-1, 你可以进行任意次以下操作:
        op: 选择满足0 <= a × 2^b < (a + 1) × 2^b <= 2^N的非负整数a, b
            并翻转P[a×2^b],P[a×2^b + 1],...,P[(a+1)×2^b - 1]
        求出你能得到的字典序最小的排列P
        范围: N∈[1,18]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        我们首先观察操作性质:
        (1)操作的左端点a × 2^b一定是2的幂次的倍数
        (2)操作的长度2^b一定是2的幂次
        我们不妨列出N = 4的所有可交换区间, 探寻下规律:
        [0, 1] [2, 3], [4, 5], ..., [14, 15]
        [0, 3] [4, 7], [8, 11], [12, 15]
        [0, 7], [8, 15]
        [0, 15]
        这是个明显的二叉树结构, 于是我们往分治上思考
        我们现在要解决的是把[0, 15]的最优解算出来
        [0, 7]与[8, 15]完全独立
        那么[0, 15]的最优解能否由[0, 7]的最优解和[8, 15]的最优解合并得到呢?
        显然是可以的, 我们把[0, 7]的最优解和[8, 15]的最优解进行比较, 由于数组是个排列
        我们只需要比较最优解的开头元素即可
        然后把更优的一个作为全局最优解的开头, 另一个跟在后面
        两段各自独立, 并且各自都取到了最优解, 并且更优的一个在前面
        因此得到了全局最优解
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(1 << n);
    for(int i = 0; i < 1 << n; i++) {
        cin >> a[i];
    }
    auto dfs = [&](auto &&self, int l, int r) -> void {
        if(l == r) {
            return ;
        }
        int mid = l + r >> 1;
        self(self, l, mid);
        self(self, mid + 1, r);
        if(a[l] > a[mid + 1]) {
            for(int L = l, R = mid + 1; L <= mid; L++, R++) {
                swap(a[L], a[R]);
            }
        }
    };
    dfs(dfs, 0, (1 << n) - 1);
    for(int i = 0; i < 1 << n; i++) {
        cout << a[i] << " \n"[i == (1 << n) - 1];
    }
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
