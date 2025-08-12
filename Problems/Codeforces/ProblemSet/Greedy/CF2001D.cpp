#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2001/problem/D
/*
    反悔贪心
    题意:
        给定一个长度为N的数组a, 你需要找到最长的不包含重复元素的子序列
        如果有多个答案, 将每个子序列奇数下标元素取相反数, 并输出字典序最小的答案
        范围: N∈[1,3e5], a[i]∈[1,N]
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 我们要求子序列最长, 那么显然长度是a去重后的元素个数
        因此我们可以记录每个元素的出现次数, 如果位置i是a[i]的最后一次出现, 并且前面未选a[i], 这个位置
        就必须选上a[i]了
        因此我们可以从后向前预处理这些"特殊"位置, 对于位置i, 用二分找到下一个必选的位置j, 然后问题就变成
        RMQ问题了, 根据奇偶性查询[i,j]内有没有比a[i]更大/更小的元素, 这可以用线段树来完成
        当然我们还有更高明的线性做法: 反悔贪心!
        类似于单调栈/单调队列的思路, 我们不去管后面有没有更优的, 我们只管前面有没有更劣的
        这样就避免了去查询rmq
        那么我们怎么去写判断逻辑呢?
        由于所有数都要恰好出现一次, 因此我们需要用cnt数组维护每个数字还剩多少, 如果后面没有了就不能移除
        我们还要处理去重, 如果一个数已经在数组中了, 我们就不能再加进去, 这可以用vis来标记
        那如何写反悔逻辑呢?
        我们记当前填了m个数, 如果m是奇数, 那么我们希望最后一个数尽量大, 反之希望尽量小
        除了最后一个数外, 我们还要看倒数第二个数, 因为奇数和偶数的处理逻辑不一样, a[i]可能比最后一个数劣
        但比倒数第二个数优, 根据字典序比较逻辑, 我们要让前面尽可能优, 因此此时也要进行更新
        更新时注意时刻关注被pop元素的剩余次数, 如果剩余次数是0了就不能pop了
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> cnt(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    vector<int> stk;
    vector<bool> vis(n + 1);
    for(int v : a) {
        cnt[v]--;
        if(vis[v]) {
            continue;
        }
        while(!stk.empty() && cnt[stk.back()] > 0) {
            int m = stk.size();
            int top = stk.back();
            if(m & 1) {
                if(v < top && (m == 1 || v > stk[m - 2] || cnt[stk[m - 2]] == 0)) {
                    break;
                }
            } else {
                if(v > top && (v < stk[m - 2] || cnt[stk[m - 2]] == 0)) {
                    break;
                }
            }
            stk.pop_back();
            vis[top] = false;
        }
        stk.push_back(v);
        vis[v] = true;
    }
    cout << stk.size() << "\n";
    for(int i = 0; i < stk.size(); i++) {
        cout << stk[i] << " \n"[i == stk.size() - 1];
    }
}




// inline int ls(int o) { return o << 1; }
// inline int rs(int o) { return o << 1 | 1; } 
// class SegmentTree {
// private:
//     int n;
//     vector<int> mx, mn;
// public:
//     SegmentTree(int x) : mx(x << 2, -inf), mn(x << 2, inf) {}
//     void push_up(int o) {
//         mx[o] = max(mx[ls(o)], mx[rs(o)]);
//         mn[o] = min(mn[ls(o)], mn[rs(o)]);
//     }
//     void add(int i, int o, int l, int r, int d, int flag) {
//         if(l == r) {
//             if(flag) {
//                 mx[o] = d;
//                 mn[o] = d;
//             } else {
//                 mx[o] = -inf;
//                 mn[o] = inf;                
//             }
//             return ;
//         }
//         int mid = l + r >> 1;
//         if(i <= mid) add(i, ls(o), l, mid, d, flag);
//         else add(i, rs(o), mid + 1, r, d, flag);
//         push_up(o);
//     }
//     int query_max(int L, int R, int o, int l, int r) {
//         if(L <= l && r <= R) return mx[o];
//         int res = -inf;
//         int mid = l + r >> 1;
//         if(L <= mid) res = max(res, query_max(L, R, ls(o), l, mid));
//         if(R > mid) res = max(res, query_max(L, R, rs(o), mid + 1, r));
//         return res;
//     }
//     int query_min(int L, int R, int o, int l, int r) {
//         if(L <= l && r <= R) return mn[o];
//         int res = inf;
//         int mid = l + r >> 1;
//         if(L <= mid) res = min(res, query_min(L, R, ls(o), l, mid));
//         if(R > mid) res = min(res, query_min(L, R, rs(o), mid + 1, r));
//         return res;
//     }
// };


// void solve() {
//     int n;
//     cin >> n;
//     vector<int> a(n + 1);
//     for(int i = 1; i <= n; i++) {
//         cin >> a[i];
//     }
//     vector<int> vis(n + 1);
//     set<int> pos;
//     SegmentTree tr(n);
//     vector<vector<int>> adj(n + 1);
//     for(int i = n; i >= 1; i--) {
//         if(!vis[a[i]]) {
//             pos.insert(i);
//             vis[a[i]] = i;
//         }
//         adj[a[i]].push_back(i);
//         tr.add(i, 1, 1, n, a[i], 1);
//     }
//     vector<int> ans;
//     for(int i = 1, tag = 1; i <= n; i++) {
//         if(!vis[a[i]]) continue;
//         auto it = pos.lower_bound(i);
//         int j = (*it);
//         if(tag == 0) {
//             if(tr.query_min(i, j, 1, 1, n) < a[i]) continue;
//             ans.push_back(a[i]);
//         } else {
//             if(tr.query_max(i, j, 1, 1, n) > a[i]) continue;
//             ans.push_back(a[i]);
//         }
//         tag ^= 1;
//         pos.erase(vis[a[i]]);
//         vis[a[i]] = 0;
//         for(int i : adj[a[i]]) {
//             tr.add(i, 1, 1, n, 0, 0);
//         }
//     }
//     cout << ans.size() << "\n";
//     for(int i = 0; i <= ans.size() - 1; i++) {
//         cout << ans[i] << " \n"[i == ans.size() - 1];
//     }
// }

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
