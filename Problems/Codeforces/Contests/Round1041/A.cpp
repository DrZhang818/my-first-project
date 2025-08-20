#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2127/problem/A
/*
    构造
    题意:
        给定一个长度为N的数组a, 其中部分元素缺失, 用-1表示
        定义数组a为合法数组, 当且仅当对于每个1 <= i <= n - 2, 满足:
            mex(a[i],a[i+1],a[i+2]) = max(a[i],a[i+1],a[i+2]) - min(a[i],a[i+1],a[i+2])
        判断是否可以通过将a中的每个-1替换为非负整数, 使得a成为合法数组
        范围: N∈[3,100], a[i]∈[-1,100]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        观察题目性质, 由于涉及mex函数, 这种结构就要求我们从0开始往大考虑
        考虑a[i]~a[i+2]中是否存在0
        (1)存在0:
            此时min = 0, 因此mex = max
            但这是不可能的, 我们设x = mex
            那么max只可能 <= x - 1或者 >= x + 1
            这很显然, 如果max = x, 那么数组中就出现x了, mex就不是x而是x + 1了
        (2)不存在0:
            此时mex = 0, 因此min = max
            此时数组元素必须全部相等, 并且不为0
        归纳两种情况, 我们得到了判断逻辑:
        (1)数组不含0
        (2)数组除了-1外, 元素种类 <= 1
*/
void solve() {
    int n;
    cin >> n;
    int c = 0;
    vector<int> vis(105);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x == 0) {
            c = inf;
        } else if(x >= 1 && !vis[x]) {
            c++;
            vis[x] = true;
        }
    }
    if(c <= 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }    
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
