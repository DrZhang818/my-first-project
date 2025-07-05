#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2070/problem/C
/*
    二分答案 || 贪心
    题意:
        给定一个N个单元格组成的长条, 初始颜色为红色, 你可以进行k次以下操作:
        op: 选择一段区间[l,r], 将区间内的单元格染成蓝色
        现给出长度为N的字符串S和数组A
        S[i]表示第i个单元格的正确颜色, B表示蓝色, R表示红色
        A[i]表示第i个单元格不是正确颜色时, 所受到的惩罚
        最终的惩罚为所有生效的A[i]中的最大值
        要求计算出最小惩罚为多少
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->二分->贪心||DP, 常用优化手段为: 前缀和、双指针、数据结构
        首先思考暴力的复杂度: 有k次操作, 每次操作有n^2种选法, 复杂度为O(k^(n^2))
        显然枚举是无法通过, 但我们有另一种暴力的想法
        我们可以逐一验证惩罚能否是x, 单次验证的时间是O(n), 总复杂度是O(MX * N)
        进一步地, 我们可以发现答案具有单调性
        当最大惩罚小于等于x的时候, 也会小于x+1, x+2,...
        这是典型的最大值最小化问题, 可以通过二分答案来优化复杂度, 时间为O(N * logMX)
*/
void solve() { 
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int r = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'B') {
            r = max(r, a[i]);
        }
    }
    auto check = [&](int x) -> bool {
        int cnt = 0;
        bool ok = false;
        for(int i = 0; i < n; i++) {
            if(s[i] == 'B') {
                if(a[i] > x && !ok) {
                    cnt++;
                    ok = true;
                }
            } else {
                if(a[i] > x && ok) {
                    ok = false;
                }
            }
        }
        return cnt <= k;
    }; 
    r += 1;
    int l = -1;
    while(l + 1 < r) {
        int mid = (l + r) / 2;
        if(check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
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
    
