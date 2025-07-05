#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1503/A
/*
    构造 || 贪心
    题意:
        给定一个长度为N的01字符串, 你需要按照规则构造出两个长为N的合法的括号序列a,b
        (1)若s[i] = '1', 则a[i]  = b[i]
        (2)若s[i] = '0', 则a[i] != b[i]
        如果无解, 输出"NO", 否则输出"YES"和两个合法括号序列a,b
        范围: N∈[2,1e5], N是偶数
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先思考平凡情况, 如果s中没有'0', 我们是很容易构造的
        此时只需要前一半为'(', 后一半为')'即可
        在平凡情况的基础上, 我们思考'0'的作用, 实际上就是对字符做了flip操作
        根据异或性质可知, flip操作必须操作偶数次, 因此奇数个'0'的情况一定是无解的
        接着我们考虑把这'0'和'1'分开处理
        对于'1'的位置, 我们仍按上面的决策处理
        对于'0'的位置, 我们考虑两两配对处理
            此时序列a会得到()()...()
                序列b会得到)()(...)(
            显然, 若s[0]或s[n-1]为'0', 是一定无解的
            如果这两个位置都不为'0', 那么序列b开头的')'必然会被'1'产生的'('接住
            末尾的'('必然会被'1'产生的')'接住
            这点很容易证明, 按照上面对'1'的策略, 第一个位置一定是前一半, 最后一个
            位置一定是后一半
            那么我们相当于把原本开头和结尾配对的(   )换成( )  ( )
*/
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    int cnt = count(s.begin(), s.end(), '0');
    if(s[0] == '0' || s[n - 1] == '0' || cnt % 2 == 1) {
        cout << "NO\n";
        return ;
    }
    string x, y;
    int c = 0, tag = 1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            if(c < (n - cnt) / 2) {
                x += '(';
                y += '(';
            } else {
                x += ')';
                y += ')';
            }
            c += 1;
        } else {
            if(tag) {   
                x += '(';
                y += ')';
            } else {
                x += ')';
                y += '(';
            }
            tag ^= 1;
        }
    }
    cout << "YES\n";
    cout << x << "\n" << y << "\n";
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
