#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://atcoder.jp/contests/abc363/tasks/abc363_d
/*
    构造
    题意:
        给定一个整数N, 求出自然数集中的第N个回文数
        范围: N∈[1,1e18]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先, 我们特判掉N = 1的情况, 然后将第一个回文数规定为1
        这时, 我们就能找到以下规律:
        1位回文数有9个, 2位有9个, 3位有90个, 4位有90个, 5位有900个, 6位有900个...
        我们发现增长速度是O(10^n)的, 因此

*/
void solve() {
    ll n;
    cin >> n;
    if(n == 1) {
        cout << 0 << "\n";
        return;
    }
    n -= 2;
    ll p = 9;
    while(n >= 2 * p) {
        n -= 2 * p;
        p *= 10;
    }
    string s = to_string(p / 9 + n % p);
    string t = s;
    if(n < p) {
        t.pop_back();
    }
    reverse(t.begin(), t.end());
    s += t;
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
