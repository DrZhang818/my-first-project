#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2123/problem/G
/*
    循环群 || 数论 || 贪心
    题意:
        给定一个长度为N的数组和一个整数m, 保证a[i] < m, 你需要回答Q次询问
        Q1: 给定i,x, 令a[i] = x
        Q2: 给定k, 你可以进行以下操作:
                op: 选择一个i, 令a[i] = (a[i] + k) % m
            判断能否通过任意次操作使得数组非递减
        Q2是一次独立的询问, 并不会真的修改数组元素
        范围: N∈[2,1e5], m∈[2,5e5], Q∈[1,1e5], a[i]∈[0,m-1]
    关键思考:
        本题为构造+数据结构类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先考虑不带修的情况下, 我们如何快速回答Q2
        根据循环群的知识, 在模m加法群中, 通过循环加k的方式能得到gcd(m,k)个子群
        因此能够得到m / gcd(m,k)个块, 每个块都是一组连续的整数, 后一个块所有元素大于前一个块
        基于以上分析, 我们有一个显然的贪心思路:
        我们要尽可能地让元素在同一个块内, 迫不得已时才启用下一个块
        如果用到了最后一个块还无法解决单调性问题, 没有下一个块可用了, 此时就是无解了
        因此关键在于, 如何快速得出需要多少个块
        对于一个给定的k:
        每个块有gcd(m,k)个元素, 因此第一个块的元素范围是[0,gcd(m,k) - 1]
        我们把数组a所有元素 mod gcd(m,k)
        然后遍历元素, 如果a[i] < a[i-1], 那么i这个点一定要开一个新的块, 因为无论在哪个块中
        都有a[i] < a[i-1], 这个相对关系是确定的
        到这里就可以回答询问了, 如果cnt < m / gcd(m,k)就是可以的, 否则不可以
        对于一个整数m, 它的因子个数大约是O(m^(1/3)), 那么预处理就需要O(N*M^(1/3)), 可以接受
        下面考虑如何维护修改操作
        由于修改a[i]只会影响a[i]与a[i-1]的关系和a[i]与a[i+1]的关系, 因此这可以O(1)完成修改
        对于m的所有因子都进行修改, 时间复杂度为O(m^(1/3))
        综上, 总时间复杂度为O(N*M^(1/3) + Q * m^(1/3) + Q) 
*/
vector<int> fac[500001];
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    map<int,int> val;
    int sz = fac[m].size();
    for(int i = 0; i < sz; i++) {
        int x = fac[m][i];
        int cnt = 1, pre = -inf;
        for(int j = 1; j <= n; j++) {
            int cur = a[j] % x;
            if(cur < pre) {
                cnt++;
            }
            pre = cur;
        }
        val[x] = cnt;
    }
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int i, x;
            cin >> i >> x;
            for(int j = 0; j < sz; j++) {
                int d = 0, mod = fac[m][j];
                if(i > 1) {
                    d -= (a[i] % mod < a[i - 1] % mod);
                    d += (x % mod < a[i - 1] % mod);
                }
                if(i < n) {
                    d -= (a[i + 1] % mod < a[i] % mod);
                    d += (a[i + 1] % mod < x % mod);
                }
                val[fac[m][j]] += d;
            } 
            a[i] = x;
        } else {
            int k;
            cin >> k;
            int x = gcd(m, k);
            if(val[x] <= m / x) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= 500000; i++) {
        for(int j = i; j <= 500000; j += i) {
            fac[j].push_back(i);
        }
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}

