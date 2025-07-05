#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/853/problem/B
/*
    贪心 || 前缀和 || 差分 || 双指针(前后缀分解)
    题意:
        存在编号为0至n的n + 1个城市，每个非0城市恰有1人。需安排所有人前往0号城市参加为期k天的会议。
        会议开始于最后一人到达的后一天，结束后次日所有人返回。
        要求选择航班方案，使得总成本最小。若无可行方案，输出-1。
        接下来给定m条航班信息和一个整数k
        每条航班信息由时间、起点、终点、代价组成(起点与终点恰有一个为0)
        这里的时间既是出发时间也是到达时间, 可以认为出发当天即可到达
    关键思考:
        对于这种复杂问题, 首先要从简单的、特殊的情况思考
        思考单个人往返的最小值问题
        问题就变成从一堆出发点(flag1)中选一个, 从一堆返回点(flag2)中选一个, 两个点之间满足拓扑约束(位置差大于k)
        这可以用二分搜索解决, 即排序后枚举每个flag2, 二分搜索flag1
        另一个方法是使用前后缀分解, 预处理每个位置t前缀flag1最小和后缀flag2最小
        这样就可以用pre[i] + suf[i + k + 1]的最小值解决
        方法二在本题中可以很好的拓展到多人情况
        在第一个人处理完后如何扩展到第二个人呢?
        贪心的想, 每个位置所需的最小代价是否等于第一个人的最小代价 + 第二个人的最小代价？
        这是显然的, 这种数值相加的线性关系保证了贪心的正确性
        因此只需把第二个人算出来的前后缀与第一个人的相加在一起即可
        而由于上面用于加总每个最小值对应的是一段时间区间, 因此我们要进行的是区间加的操作, 可以通过差分后前缀和来实现。
        
*/
constexpr ll inf = 1e13;
constexpr int M = 1e6;
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<PII>> froms(n + 1), tos(n + 1);
    for(int i = 0; i < m; i++){
        int d, f, t, c;
        cin >> d >> f >> t >> c;
        if(f) froms[f].emplace_back(d, c);
        else tos[t].emplace_back(d, c);
    }
    vector<ll> ans1(M + 2, 0), ans2(M + 2, 0);
    for(int i = 1; i <= n; i++){
        sort(froms[i].begin(), froms[i].end());
        sort(tos[i].begin(), tos[i].end());
        int fk = froms[i].size(), tk = tos[i].size();
        if(fk == 0 || tk == 0){
            cout << -1 << "\n";
            return;
        }
        ll v = inf;
        ans1[0] += inf;
        ans1[froms[i][0].first] -= inf;
        for(int j = 0; j < fk - 1; j++){
            v = min(v, (ll)froms[i][j].second);
            ans1[froms[i][j].first] += v;
            ans1[froms[i][j + 1].first] -= v;
        }
        v = min(v, (ll)froms[i][fk - 1].second);
        ans1[froms[i][fk - 1].first] += v;
        ans1[M + 1] -= v;

        v = inf;
        ans2[tos[i][tk - 1].first + 1] += v;
        ans2[M + 1] -= v;
        for(int j = tk - 2; j >= 0; j--){
            v = min(v, (ll)tos[i][j + 1].second);
            ans2[tos[i][j].first + 1] += v;
            ans2[tos[i][j + 1].first + 1] -= v;
        }
        v = min(v, (ll)tos[i][0].second);
        ans2[0] += v;
        ans2[tos[i][0].first + 1] -= v;
    }
    for(int i = 0; i <= M; i++){
        ans1[i + 1] += ans1[i];
        ans2[i + 1] += ans2[i];
    }
    ll ans = inf;
    for(int i = 0; i <= M + 1; i++){
        if(i + k + 1 <= M){
            ans = min(ans, ans1[i] + ans2[i + k + 1]);
        }
    }
    cout << (ans < inf ? ans : -1) << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    solve();
    return 0;
}