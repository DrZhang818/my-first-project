#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


/*
    动态规划 || 二分
    本题是加权区间调度问题
    题意: 给定n个带权重的线段，每条线段由左端点l，右端点r和权值v组成。要去从这些线段
        中选择若干条不相交的线段（端点相连也被视为不相交），使得所选线段的权值之和最大。
        同时，需要输出所选线段的序号，要求按照端点递减排序输出。
    定义dp[i] := 前i条线段的最大权值和
    定义p[i] := 每条线段之前最后一条不重叠的线段的索引
        对于每条线段, 有选或不选两种方式
        不选:dp[i] = dp[i - 1]
        选:  dp[i] = v + dp[p[i]]
    于是可以得到状态转移方程
        dp[i] = max(dp[i - 1], v + dp[p[i]])
    关键点:
        p[i]如何获得?
        如果采用暴力枚举的话, 总时间复杂度为O(n^2), 超时
        但是当我们按照右端点排序之后, 就有了单调性, 可以使用二分查找优化
        最终时间复杂度降为O(nlogn)
*/
struct info{
    ll l, r, val, id;
};
void solve(){
    int n;
    cin >> n;
    //读入
    vector<info> seg(n);
    for(int i = 0; i < n; i++){
        cin >> seg[i].r >> seg[i].l >> seg[i].val;
        seg[i].id = i + 1;
    }
    //排序
    sort(seg.begin(), seg.end(), [](const info &a, const info &b){
        return a.r < b.r;
    });
    //二分查找
    auto bs = [&](int i) -> int {
        int l = -1, r = i;
        while(l + 1 < r){
            int mid = l + (r - l) / 2;
            if(seg[mid].r <= seg[i].l){
                l = mid;
            }else{
                r = mid;
            }
        }
        return l;
    };
    
    vector<ll> dp(n);
    vector<int> pre(n, -1);//上一个不重叠位置的右端点
    for(int i = 0; i < n; i++){
        pre[i] = bs(i);
        if(i == 0) dp[i] = seg[i].val;
        else dp[i] = max(dp[i - 1], (pre[i] == -1 ? 0 : dp[pre[i]]) + seg[i].val);
    }
    ll mx = n > 0 ? dp[n - 1] : 0;
    vector<int> sel;
    int i = n - 1;
    while(i >= 0){
        if(i > 0 && dp[i] == dp[i - 1]){
            i -= 1;
            continue;
        }
        sel.push_back(seg[i].id);
        i = pre[i];
    }
    cout << (int)sel.size() << " " << mx << "\n";
    for(auto c : sel){
        cout << c << " ";
    }
    cout << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}