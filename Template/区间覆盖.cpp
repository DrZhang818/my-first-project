#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/U380778
/*
    贪心
    题意:
        给定N个区间[Li,Ri], 以及目标区间[L,R], 要求选出最少的区间, 使得区间的并集
        能够覆盖目标区间, 输出最少选取的区间数量, 无解输出-1
        范围: N∈[1,2e5], L,R∈[1,2e5]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 我们发现如果一个区间与目标区间没有交集, 那一定不会选
        于是我们的决策范围就缩小为"与目标区间有交集"的区间集合
        接下来我们继续探寻性质
        我们从左到右考虑, 由于目标区间的每个点都要被覆盖, 因此L这一个点一定要被覆盖
        那么我们的第一步决策就是选择一个区间, 使其能够覆盖点L
        贪心地想, 在能够覆盖点L的区间中, 选择右端点最大的那一个一定是最优的
        因为我们的选择是相互独立的, 选择这个区间不会影响到任何其他区间的选择
        这意味着, 我们的贪心选择至少是不劣的
        那么在这基础上, 我们的贪心选择只有增益效果, 那显然这样选就是最优的方案
        代码实现时, 需要按照区间左端点来排序, 后续通过不断更新L(需要被覆盖的点)来实现筛选
*/
const int inf = 1000000000;
struct info {
    int l, r;
    friend bool operator < (const info &a, const info &b) {
        return a.l < b.l;
    }
};
void solve() { 
    int L, R;
    cin >> L >> R;
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
    }    
    sort(a.begin() + 1, a.end());
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int j = i, mx = -inf;
        while(j <= n && a[j].l <= L) {
            mx = max(mx, a[j].r);
            j++;
        }
        if(mx < L) break;
        ans++;
        if(mx >= R) {
            cout << ans << "\n";
            return ;
        }
        L = mx;
        i = j - 1;
    }
    cout << -1 << "\n"; 
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
