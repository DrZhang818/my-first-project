#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


/*
    数学 || 整除分块
    题意:
        给定一个整数n, 计算∑(i=1->n) n//i
    关键思考:
        本题属于计算类问题, 常用思考方式为数学公式推导, 常用优化方法为前缀和 + 数学
        本题是整除分块模板
        考虑把n // i按相同值分块, 相同块合并计算, 可以把时间复杂度降低到O(sqrt(n))
        这是因为n // i 最多有2sqrt(n)种取值
        如何遍历块呢?
        当我们知道块的左端点L, 右端点R = n / (n / L)
        计算后, 更新L = R + 1, 即可完成遍历块
*/
void solve(){ 
    ll n, L, R, ans = 0;
    cin >> n;
    for(L = 1; L <= n; L = R + 1) { 
        R = n / (n / L);
        ans += (R - L + 1) * (n / L);
        cout << L << "->" << R << ": " << n / R << "\n";
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

