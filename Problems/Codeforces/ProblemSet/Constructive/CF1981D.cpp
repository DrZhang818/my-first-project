#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1981/problem/D
/*
    构造 || 贪心 || 欧拉路径
    题意:
        构造出一个长度为N的序列, 使得任意相邻两项的乘积互不相同
        最小化序列中不同元素的个数
        范围: N∈[2,1e6], 序列元素∈[1,3e5]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        由于要最小化不同元素个数, 我们先尝试研究下决策函数, 显然是个与长度有关的一元函数
        定义f(x) := 长度为x的合法序列最少有f(x)个不同元素
        f(x)的单调性是显而易见的, 并且是不严格单调上升的
        这意味着一个f(x)可以对应着多个x, 可以用f(x)的值进行分块
        简单来说, 我们可以反向思考, 有f(x)个不同元素的时候, 最大支持的序列长度是多少
        这是本题真正要解决的问题, 我们不妨先想一想这些不同元素应该怎么取
        由于条件约束是乘积互不相同, 乘积相同当且仅当两个数唯一分解后得到的质因数及次数相同
        那么我们就能很自然地想到选取质数列中的元素了, 因为两对不同质数的乘积分解后得到的
        质因数一定不同, 这意味着乘积一定不同
        可以很简单地利用反证法证明选择质数一定是最优的
        那么如何用合理排列这些质数呢?
        我们可以把这个问题建模为图论问题, 假设要研究p个质数能得到的最大序列长度
        那么把这p个质数之间两两连边, 问题就变为在不走重复边的情况下最多能访问多少条边
        这是经典的无向图最长迹问题, 本身是个NP-hard问题, 但由于本题是无向完全图
        因此可以转为求解欧拉通路问题, 这个问题可以在O(E)时间内解决
        首先需要进行分类讨论:
        (1)如果p是奇数, 那么完全图中每个点的度数为偶数
           因此此时的图已经是一个欧拉图, 存在欧拉回路
        (2)如果p是偶数, 那么完全图中每个点的度数为奇数
           此时需要进行删边操作, 删除n/2-1条边后就可以转为半欧拉图, 找到欧拉通路
        注意: 本题的完全图是包含自环的完全图, 因此在算边总数的时候要加上p个自环
        此外, x条边对应x+1个点, 因此我们算出的边数要+1后再与n进行比较
*/
vector<int> minp, primes;
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    for(int i = 2; i <= n; i++) {
        if(minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > n) {
                break;
            }
            minp[i * p] = p;
            if(p == minp[i]) {
                break;
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    auto ck = [&](int x) -> bool {
        if(x & 1) {
            return x * (x + 1) / 2 + 1 >= n; 
        } else {
            return x * x / 2 + 2 >= n; 
        }
    };
    int l = 0, r = primes.size();
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    int m = r;
    vector<int> g(m);
    vector vis(m, vector<bool>(m));
    if(m % 2 == 0) {
        for(int i = 2; i < m; i += 2) {
            vis[i - 1][i] = true;
            vis[i][i - 1] = true;
        }
    }
    vector<int> path;
    auto dfs = [&](this auto &&self, int u) -> void {
        for(; g[u] < m; g[u]++) {
            int v = g[u];
            if(!vis[u][v]) {
                vis[u][v] = true;
                vis[v][u] = true;
                self(v);
            }
        }
        path.push_back(primes[u]);
    };
    dfs(0);
    reverse(path.begin(), path.end());
    for(int i = 0; i < n; i++) {
        cout << path[i] << " \n"[i == n - 1];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve(50000);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
