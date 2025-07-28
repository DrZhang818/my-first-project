#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2128/problem/E1
/*
    二分 || 中位数trick
    题意:
        给定一个长度为N的数组和一个整数K, 定义S为所有长度大于等于K的子数组的中位数组成的集合
        你需要求出S的最大元素x, 以及任意一个中位数为x且长度大于等于K的子数组左端点和右端点(l,r)
        范围: N∈[1,3e5], K∈[1,N], a[i]∈[1,N]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        本题十分简单
        我们考虑中位数trick, 把 >= x的数赋值为1, < x的数赋值为-1
        如果存在某个长度为K的子数组的总和非负, 那么说明答案 >= x, 否则答案 < x
        二分答案即可
*/
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto ck = [&](int x) -> PII {
        vector<int> b(n + 1);
        for(int i = 1; i <= n; i++) {
            b[i] = a[i] >= x ? 1 : -1;
        }
        vector<int> s(n + 1);
        for(int i = 1; i <= n; i++) {
            s[i] = s[i - 1] + b[i];
        }
        set<int> st;
        int mn = 0, idx = 1;
        for(int i = k; i <= n; i++) {
            int cur = s[i];
            if(cur - mn >= 0) {
                return {idx, i};
            }
            if(s[i - k + 1] < mn) {
                mn = s[i - k + 1];
                idx = i - k + 2;
            }
        }
        return {-1,-1};
    };
    int l = 0, r = n + 1;
    PII cur, ans;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        cur = ck(mid);
        if(cur.first != -1) {
            l = mid;
            ans = cur;
        } else {
            r = mid;
        }
    }
    cout << l << " " << ans.first << " " << ans.second << "\n"; 
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
