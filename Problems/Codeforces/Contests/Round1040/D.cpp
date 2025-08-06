#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2130/problem/D
/*
    贪心
    题意:
        给定一个1~N的排列, 你需要按照以下方式构建数组a:
            对于每个1 <= i <= N, 令a[i] = p[i] 或 a[i] = 2N - p[i]
        求数组a的逆序对数量最小是多少
        范围: N∈[2,5e3]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 对于逆序对问题我们可以倒序来思考
        考虑倒序枚举到位置i, 我们先钦定j : 1~i-1都是a[j] = p[j]
        (1)如果我们让a[i] = p[i]
            对于j∈[1,i-1]的部分, 所有满足a[j] > a[i]的都会贡献逆序对数量
            对于j∈[i+1,N]的部分, 由于a[i] = p[i]符合钦定, 因此这部分在遍历到i前就已经算过了
        (2)如果我们让a[i] = 2N - p[i]
            对于j∈[1,i-1]的部分, 都有a[j] = p[j] <= N <= a[i], 因此贡献为0
            对于j∈[i+1,N]的部分, 所有a[j] < p[i]的部分已经被统计过了
                因此我们要统计的是a[i] > a[j] > p[i]的数量
                我们发现此时有个关键不等式:
                2N - p[i] > 2N - p[j] > p[j] > p[i]
                这意味着无论a[j]定为p[j]还是2N - p[j], 只要满足p[j] > p[i]都会做贡献
                因此这部分答案是固定的, 就是满足p[j] > p[i]的j的数量
        综上可得
        如果a[i] = p[i], 带来的贡献是j∈[1,i-1]中 p[j] > p[i]的数量
        如果a[i] = 2N - p[i], 带来的贡献是j∈[i+1,N]中 p[j] > p[i]的数量
        而总共有n - i个j满足p[j] > p[i]
        因此我们从前向后扫, 并用树状数组维护即可
*/
class FenwickTree {
private:
    vector<int> tree;
    int n;
public:
    FenwickTree(int x) {
        tree.resize(x + 1);
        n = x;
    }
    void add(int i, int x) {
        while(i <= n) {
            tree[i] += x;
            i += i & -i;
        }
    }
    int query(int i) {
        int res = 0;
        while(i > 0) {
            res += tree[i];
            i -= i & -i;
        }
        return res;
    }
    int range_query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    FenwickTree tr(n);
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int x = tr.query(n - a[i] + 1);
        ans += min(x, n - a[i] - x);
        tr.add(n - a[i] + 1, 1);
    }
    cout << ans << "\n";
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
