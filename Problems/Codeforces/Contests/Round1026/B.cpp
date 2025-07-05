#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2110/problem/B
/*
    构造 || 贪心
    题意:
        给定一个长度为N的合法括号序列, 判断能否删除恰好1个左括号和1个右括号, 使得括号序列
        不再合法, 空串被认为是合法的
        范围: N∈[2,2e5]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 我们可以把'('设为1, ')'设为-1
        则题目等价于删除一个1和-1, 使得存在某个前缀和小于0
        显然有个贪心策略, 选第一个1和最后一个-1
        删掉第一个1可以使得有更多的前缀和减小1
        删最后一个-1可以使得有更少的前缀和补回了这个1
        而题目保证输入的是合法序列, 因此第一个1就是s[1], 最后一个-1就是s[n]
        我们只需判断是否存在pre[i] - pre[1] < 0即可
*/
void solve() {
    string s;
    cin >> s;
    int n = s.size(), cur = 0;
    bool ok = false;
    for(int i = 1; i < n - 1; i++) {
        if(s[i] == '(') {
            cur++;
        } else {
            cur--;
        }
        if(cur < 0) {
            ok = true;
        }
    }
    if(!ok) {
        cout << "NO\n"; 
    } else {
        cout << "YES\n";
    }
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
