#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc105/tasks/abc105_c
/*
    数论
    题意:
        给定一个整数N, 求出它的-2进制表示
        形式化地, 将N表示为S = S[k]S[k-1]...S[1]S[0]
        其中∑S[i]*(-2)^i = N, 可以证明表示法唯一
        范围: N∈[-1e9,1e9]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        将任意数转化为p进制的方法为:
        不断对p取余数, 减掉余数后再除以p
        这里的核心点为:
        (1)余数要取绝对值
        (2)必须减掉余数后再除以p
*/
void solve() {
    ll n;
    cin >> n;
    if(n == 0) {
        cout << 0 << "\n";
        return;
    }
    string ans;
    while(n) {
        int pop = abs(n % (-2));
        ans += '0' + pop;
        n = (n - pop) / (-2);        
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
