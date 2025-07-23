#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2123/problem/C
/*
    构造 || 贪心
    题意:
        给定一个长度为N的数组, 数组所有元素互不相同, 你可以进行任意次以下操作:
        op1: 选取数组的某个非空前缀, 并将其替换为该前缀的最小值 
        op2: 选取数组的某个非空后缀, 并将其替换为该前缀的最大值
        对于每个元素a[i], 判断能否通过操作使得整个数组都变成a[i]
        如果可以输出1, 否则输出0
        范围: N∈[2,2e5], a[i]∈[1,1e6]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        由于数组所有元素都不相同, 因此如果想都变成a[i], 那么只能从i处做文章
        我们考虑最后一次操作:
        (1)最后一次操作是op1:
            那么等价于选取a[1:n], 使a[1:n] = a[i]
            此时a[i]必须是数组最小值
        (2)最后一次操作是op2:
            那么等价于选取a[1:n], 使a[1:n] = a[i]
            此时a[i]必须是数组最大值
        因此a[i]要么小于a[1:i-1], 要么大于a[i+1,n], 这是必要条件
        下面我们证明, 此条件也是充分条件
        由对称性, 我们只证明a[i] < min(a[1:i-1])时可构造
        1.利用op1, 将a[1:i]变成a[i]
        2.利用op2, 把a[i+1:n]变成max(a[i+1:n]), 记为x
            如果a[i] > x, 那么利用op2即可
            如果a[i] < x, 那么利用op1即可
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1, inf), suf(n + 2, -inf);
    pre[1] = a[1], suf[n] = a[n];
    for(int i = 2; i <= n; i++) {
        pre[i] = min(pre[i - 1], a[i]);
    }
    for(int i = n - 1; i >= 1; i--) {
        suf[i] = max(suf[i + 1], a[i]);
    }
    for(int i = 1; i <= n; i++) {
        if(a[i] > pre[i - 1] && a[i] < suf[i + 1]) {
            cout << 0;
        } else {
            cout << 1;
        }
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

