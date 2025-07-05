#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/1857/problem/E
/*
    前后缀分解
    题意:
        给定一个长度为N的坐标数组X, 它们位于一条数轴上
        对于每个s∈X, 回答以下询问:
        连接s与每个xi∈X, 共形成N条线段, 定义F(x) := 坐标为x的点被线段覆盖的次数
        回答ΣF(i) (i∈[1,1e9])
        范围: n∈[1,2e5], xi∈[1,1e9]
    关键思考:
        本题属于计算类题目, 常用思考方式为: 暴力->DP||数学, 常用优化手段为: 前缀和、数论分块、数学
        本题等价于计算∑(|s - xi| + 1) xi∈X
        首先思考暴力做法, 单次计算复杂度为O(n), 则总复杂度就是O(n^2), 超时
        经过画图分析, 我们发现可以对这N个坐标排个序
        排完序后, 我们发现可以把一条大线段分割成若干条小线段, 我们可以利用贡献法一次性
        计算出小线段做出的所有贡献, 这样就能预处理出任意xi∈X的前缀和后缀的贡献
        处理询问时, 只需要把前后缀加起来再减一(去重)即可
*/
struct info {
    ll x, id;
};
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x;
        a[i].id = i;
    }
    vector<ll> pre(n + 2), suf(n + 2), ans(n + 1);
    sort(a.begin(), a.end(), [](auto &a, auto &b) -> bool{
        return a.x < b.x;
    });
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + (a[i].x - a[i - 1].x) * (i - 1) + 1;
    }
    for(int i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] + (a[i + 1].x - a[i].x) * (n - i) + 1;
    }
    for(int i = 1; i <= n; i++) {
        ans[a[i].id] = pre[i] + suf[i] - 1;
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
