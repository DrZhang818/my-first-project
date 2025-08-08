#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

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
    vector<bool> in_stk(n + 1);
    for(int v : a) {
        cnt[v]--;
        if(in_stk[v]) {
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
            in_stk[top] = false;
        }
        stk.push_back(v);
        in_stk[v] = true;
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
