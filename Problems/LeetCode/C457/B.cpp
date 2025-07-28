#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    fa[u] = v;
}
//懒删除堆写法
class Solution {
public:
    vector<int> processQueries(int n, vector<vector<int>>& e, vector<vector<int>>& Q) {
        fa.assign(n + 1, 0);
        iota(fa.begin(), fa.end(), 0);
        for(int i = 0; i < e.size(); i++) {
            int u = e[i][0], v = e[i][1];
            merge(u, v);
        }
        vector<priority_queue<int, vector<int>, greater<int>>> q(n + 1);
        for(int i = 1; i <= n; i++) {
            int f = find(i);
            q[f].push(i);
        }
        vector<int> ans;
        vector<bool> vis(n + 1);
        for(int i = 0; i < Q.size(); i++) {
            int op = Q[i][0], x = Q[i][1];
            int f = find(x);
            if(op == 1) {
                if(!vis[x]) {
                    ans.push_back(x);
                    continue;
                }
                auto &t = q[f];
                while(!t.empty() && vis[t.top()]) {
                    t.pop();
                }
                if(!t.empty()) {
                    ans.push_back(t.top());
                } else {
                    ans.push_back(-1);
                }
            } else {
                vis[x] = true;
            }
        }
        return ans;
    }
};




// class Solution {
// public:
//     vector<int> processQueries(int n, vector<vector<int>>& e, vector<vector<int>>& Q) {
//         fa.assign(n + 1, 0);
//         iota(fa.begin(), fa.end(), 0);
//         for(int i = 0; i < e.size(); i++) {
//             int u = e[i][0], v = e[i][1];
//             merge(u, v);
//         }
//         unordered_map<int,set<int>> st;
//         for(int i = 1; i <= n; i++) {
//             int f = find(i);
//             st[f].insert(i);
//         }
//         int q = Q.size();
//         vector<int> ans;
//         for(int i = 0; i < q; i++) {
//             int op = Q[i][0], x = Q[i][1];
//             int f = find(x);
//             if(op == 1) {
//                 if(!st[f].empty()) {
//                     if(st[f].count(x)) ans.push_back(x);
//                     else ans.push_back(*st[f].begin());
//                 } else {
//                     ans.push_back(-1);
//                 }
//             } else {
//                 st[f].erase(x);
//             }
//         }
//         return ans;
//     }
// };