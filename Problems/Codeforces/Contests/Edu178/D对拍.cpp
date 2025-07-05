#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2104/problem/D
/*
    数论 || 贪心
    题意:
        给定一个长度为N的数组, 你可以执行任意次下述操作:
        op1: 支付一枚硬币, 并将数组中任意元素 + 1(必须至少有一枚硬币才能执行此操作)
        op2: 获得一枚硬币, 并将数组中任意元素 - 1
        一个数组是合法的, 当且仅当数组最小值 >= 2, 且任意两个元素互质
        求解至少需要删除数组中几个元素, 才能通过操作使得数组变成合法数组
        范围: n∈[1,4e5], a[i]∈[2,1e9]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先估算状态数量, 显然至少是指数级的, 且无法用简单的方式描述状态, 这使得
        搜索和DP变得十分困难, 我们必须考虑利用贪心来求解
        由"两两互质"这个条件, 显然质数序列天然满足两两互质, 我们思考能否把数组往质数列
        上进行转化
        由于op1操作依赖于op2操作, 因此我们可以统一先进行op2再进行op1
        考虑把数组往[2,3,5,7,...]上转化
        我们可以利用op2把数组清零, 获得sum枚硬币
        然后从前往后使用op1构造, 直到硬币不足为止
        假设填充了k个数字, 则n - k必然是答案
        因为剩余的硬币无法得到更大的质数, 则由唯一分解定理, 可以证明分解后得到的质数
        必然与前k中的一个相同, 不满足两两互质
        这样得到的一定是最优的, 我们可以假设第i个质数, i∈[1,k]没有使用, 反而使用了
        第j个质数, j >= k+1, 此时op1的消耗量更大, 会导致构造出的数字更少, 必然更劣

*/
const int N = 6000000;
vector<int> primes;
vector<bool> vis(N);
void sieve() {
    primes.push_back(-1);
    for(int i = 2; i < N; i++) {
        if(!vis[i]) {
            primes.push_back(i);
            for(int j = 1; j * i < N; j++) {
                vis[j * i] = true;
            }
        }
    }
}
vector<int> a;
int n = 4;
int solve1() {
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        tot += a[i] - 2;
    }
    int ans = n;
    for(int i = 1; i <= n; i++) {
        if(tot >= primes[i] - 2) {
            tot -= primes[i] - 2;
            ans -= 1;
        } 
    }
    return ans;
}
int solve2() {
    sort(a.begin() + 1, a.end(), greater<int>());
    ll cur = 0, ans = 0;;
    for(int i = 1; i <= n; i++) {
        if(a[i] >= primes[i]) {
            cur += a[i] - primes[i];
        } else if(primes[i] - a[i] <= cur) {
            cur -= primes[i] - a[i];
        } else {
            ans = n - i + 1;
            break;
        }
    }
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve();
    srand(time(0));
    a.resize(n + 1);
    for(int i = 1; i < 100000; i++) {
        for(int j = 1; j <= n; j++) {
            int t = 0;
            while(t < 2) t = rand() % 15; 
            a[j] = t;
        }
        int ans1 = solve1();
        int ans2 = solve2();
        if(ans1 != ans2) {
            cerr << "WA!\n";
            for(int j = 1; j <= n; j++) {
                cerr << a[j] << " \n"[j == n];
            }
            cerr << ans1 << " : " << ans2 << "\n";
        } 
    }
    return 0;
}
