#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/description/
/*
    黑白染色法

*/
void solve(){
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj1(n, vector<int>());
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }
    vector<vector<int>> adj2(m, vector<int>());
    for(int i = 0; i < m - 1; i++){
        int u, v;
        cin >> u >> v;
        adj2[u].push_back(v);
        adj2[v].push_back(u);
    }
    auto count = [](vector<vector<int>>& adj){
        array<int, 2> cnt{};
        auto dfs = [&](auto&& dfs, int x, int fa, int d) -> void{
            cnt[d]++;
            for(int y : adj[x]){
                if(y != fa){
                    dfs(dfs, y, x, d ^ 1);
                }
            }
        };  
        dfs(dfs, 0, -1, 0);
        return cnt;
    };
    array<int, 2> cnt2 = count(adj2);
    int max2 = max(cnt2[0], cnt2[1]);

    array<int, 2> cnt1 = count(adj1);
    vector<int> ans(n, max2);
    auto dfs = [&](auto&& dfs, int x, int fa, int d) -> void{
        ans[x] += cnt1[d];
        for(int y : adj1[x]){
            if(y != fa){
                dfs(dfs, y, x, d ^ 1);
            }
        }
    };
    dfs(dfs, 0, -1, 0);
    for(auto num : ans){
        cout << num << " ";
    }
    cout << "\n";
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}