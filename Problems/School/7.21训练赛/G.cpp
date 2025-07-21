#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P8022
/*
    数论 || 前缀和 || 暴力枚举
    题意:
        给定一个长度为N的数字字符串S, 你需要把S划分成恰好三段非空子串, 使得第一段被p整除,
        第二段被q整除, 第三段被r整除, 子串不能存在前导零, 单个0除外
        范围: N∈[1,1e6], p,q,r∈(2015, 1e5], p,q,r为质数
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先思考暴力方法, 枚举两个分割点, 利用后缀和判断第三段, 可以做到O(n^2), 超时
        很自然的想法是, 我们能否优化掉枚举次数, 例如只枚举第一个分割点, 利用一些方法直接得到有多少个
        合法的第二个分割点
        也就是, 我们找到第一个分割点i之后, 要快速知到[i+1,n]中有多少个j, 满足[i+1,j]被q整除
        且[j+1,n]被r整除
        其中[j+1,n]被r整除是很好预处理的, 难点在于[i+1,j]被q整除如何判断
        我们把式子拆开来看
        q | ∑a[t]*10^{j-t}, t∈[i+1,j]
        ==> q | 10^{j}*∑a[t]*10^{-t}
        由于q≠2∧q≠5
        因此等价于q | ∑a[t]*10^{-t}
        这个式子只与t有关, 因此就可以预处理前缀和S了
        那么[i+1,j]被q整除就简洁地转化成(S[j] - S[i]) % q = 0了
        因此我们只需要预处理[i+1,n]中有多少个j, 满足S[j] = S[i]且[j+1,n]被r整除
        注意: 要加入前导零的判断
*/
ll fast_pow(ll a, ll b, ll mod) {
    ll res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % mod;
        a = 1LL * a * a % mod;
        b >>= 1;
    }
    return res;
}
void solve() {
    int n, p, q, r;
    cin >> n >> p >> q >> r;
    string s;
    cin >> s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        a[i] = s[i - 1] - '0';
    }
    vector<ll> S(n + 1);
    ll inv10 = fast_pow(10, q - 2, q);
    ll cur = 1;
    for(int i = 1; i <= n; i++) {
        ll x = a[i] * cur % q;
        S[i] = (S[i - 1] + x) % q;
        cur = cur * inv10 % q;
    }
    vector<ll> suf(n + 2), cnt(q);
    vector<bool> ok(n + 2);
    cur = 1;
    for(int i = n; i >= 3; i--) {
        ll x = a[i] * cur % r;
        suf[i] = (suf[i + 1] + x) % r;
        cur = cur * 10 % r;
        if(suf[i] == 0 && (a[i] != 0 || i == n)) {
            ok[i] = true;
            cnt[S[i - 1]]++;
        }
    }
    ll ans = 0, x = 0;
    for(int i = 1; i <= n - 2; i++) {
        x = (x * 10 + a[i]) % p;
        if(ok[i + 1]) {
            cnt[S[i]]--;
        }
        if(x == 0 && (a[1] != 0 || i == 1)) {
            if(a[i + 1] != 0) {
                ans += cnt[S[i]];
            } else {
                if(suf[i + 2] == 0 && (a[i + 2] != 0 || i + 2 == n)) {
                    ans++;
                }
            }
        }
    }
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
