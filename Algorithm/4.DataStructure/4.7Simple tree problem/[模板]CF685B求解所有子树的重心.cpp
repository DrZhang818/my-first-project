#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/problemset/problem/685/B
/*
    

*/
void solve(){ 
    int n, q;
    cin >> n >> q;
    vector<int> fa(n, -1);
    vector<vector<int>> son(n);
    for(int i = 1; i < n; i++) {
        int v;
        cin >> v;
        v -= 1;
        fa[i] = v;
        son[v].push_back(i);
    }
    vector<int> ans(n), siz(n, 1), weight(n, 0);
    iota(ans.begin(), ans.end(), 0);
    auto dfs = [&](this auto &&dfs, int u) -> void {
        for(int v : son[u]) {
            dfs(v);
            siz[u] += siz[v];
            weight[u] = max(weight[u], siz[v]);
        }
        for(int v : son[u]) {
            int p = ans[v];
            while(p != u) {
                if(max(weight[p], siz[u] - siz[p]) <= siz[u] / 2) {
                    ans[u] = p;
                    break;
                } else {
                    p = fa[p];
                }
            }
        }
    };
    dfs(0);
    for(int i = 0; i < q; i++) {
        int u;
        cin >> u;
        u -= 1;
        cout << ans[u] + 1 << "\n";
    }
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
       
    solve();
    return 0;
}
    
