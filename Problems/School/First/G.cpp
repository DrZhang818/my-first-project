#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/1766/problem/D
/*
    数论
    题意:
        有n组询问
        每组询问给定两个正整数x,y, 定义由这两个整数产生的二元组生成序列G(x,y)为
        G(x,y) := (x,y), (x+1,y+1), (x+2,y+2),...
        定义一个二元组的权值为gcd(x,y)
        问在这个无限序列中第一个权值不等于1的下标是多少(下标从0开始计数)
        如果不存在, 输出-1
        范围: n∈[1,1e6], x,y∈[1,1e7] 且 x < y
    关键思考:
        本题为计算类题目, 常用思考方式为: 暴力->DP||数学, 常用优化手段为: 数学、双指针、数据结构
        题目本质是求出min{k | gcd(x + k, y + k) != 1}
        对于这个式子我们可以用更相减损术来处理, 转化成gcd(x + k, y - x) != 1
        直白地说, 要让x + k与y - x存在相同质因子
        因此我们可以把y - x的质因子求出来, 然后枚举质因子求出最小的k
        核心就在于如何快速求出y - x的质因子
        常见的试除法时间为sqrt级别, 总时间复杂度为O(n * sqrt(n)), 超时
        我们可以用线性筛在O(n)时间内预处理出所有1e7范围内所有数的最小质因子
        然后就可以在log时间内计算出一个数的所有质因子
        具体流程见代码实现
*/
constexpr int N = 10000000;
vector<int> spf(N + 1, 0);
vector<int> primes;       
void sieve(int n) {
    for (int i = 2; i <= n; i++) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && primes[j] <= spf[i] && i * primes[j] <= n; j++) {
            spf[i * primes[j]] = primes[j];
        }
    }
}
vector<int> get(int x) {
    vector<int> factors;
    while (x > 1) {
        factors.push_back(spf[x]);
        x /= spf[x];
    }
    return factors;
}
void solve() { 
    int x, y;
    cin >> x >> y;
    if(y == x + 1) {  
        cout << -1 << "\n";
        return;
    }
    int p = y - x;
    if(__gcd(x, p) != 1) {
        cout << 0 << "\n";
    } else {
        if(p % 2 == 0) {
            cout << 1 << "\n";
        } else {
            auto pm = get(p);
            int ans = 1000000000;
            for(int j : pm) {
                int t = x % j;
                if(t == 0) {
                    ans = 0;
                    break;
                } else {
                    ans = min(ans, j - t);
                }
            }
            cout << ans << "\n";
        }
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve(N);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
