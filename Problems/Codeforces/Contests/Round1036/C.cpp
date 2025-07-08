#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2124/problem/C
/*
    数论 || 贪心
    题意:
        起初有一个长度为N的数组a, 满足∀i∈[1,n-1], a[i+1] % a[i] = 0
        现在给定一个长度为N的数组b, 数组b是由a中某些元素乘上一个共同元素x得到的
        请你输出一个合法的x, 使得存在一个数组a满足某些元素乘上x后能够得到b
        数据保证一定有解
        范围: N∈[2,6e5], b[i]∈[1,1e9]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        考虑数组b中的两个相邻位置b[i]和b[j], j = i+1
        如果b[j] % b[i] = 0, 那么没有必要更改
        如果b[j] % b[i] ≠ 0, 则有以下结论:
        首先说明一点: 两个数只能改其中一个, 否则如果两个数都改, (b[j]/x)%(b[i]/x)仍然≠0
        我们把b[i]和b[j]都进行质因数分解, 得到两个集合S和T
        这样b[j]%b[i]=0, 等价于S⊆T
        因此我们只能更改S, 即让S = S⋂T的子集, 也即让b[i]变为gcd(b[i],b[j])的因子
        那么选择的x就至少是b[i] / gcd(b[i],b[j])
        由于其他不合法的对也需要通过x调整为合法的对, 因此需要让x成为这些不合法的b[i]的公因子
        所以贪心地想, x应该尽可能小, 这样才有更大的机会成为公因子
        由于题目保证一定有解, 因此这样的机会必然是有的, 只需要不断取lcm即可得到合法解
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll x = 1;
    for(int i = 1; i < n; i++) {
        if(a[i + 1] % a[i]) {
            x = lcm(x, a[i] / gcd(a[i], a[i + 1]));
        }
    }
    cout << x << "\n";
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
