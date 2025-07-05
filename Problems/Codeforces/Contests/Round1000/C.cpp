#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//StarSilk代码
void solve1(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    map<int,int> mp;
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    auto getmpval = [&]() -> int{
        while(1){
            if(mp.empty()) return INT_MIN;
            auto it = mp.end();
            it--;
            if((*it).second == 0){
                mp.erase(it);
                continue;
            }
            return (*it).first;
        }
        return INT_MIN;
    };
    int ans = 0, mx1, mx2;
    for(auto c : deg) mp[c]++;
    for(int i = 0; i < n; i++){
        mp[deg[i]]--;
        mx1 = 0;
        for(auto j : adj[i]){
            mx1 = max(mx1, deg[j]);
            mp[deg[j]]--;
        }
        mx2 = getmpval();
        ans = max(ans, deg[i] + mx1 - 2);
        ans = max(ans, deg[i] + mx2 - 1);
        mp[deg[i]]++;
        for(auto j : adj[i]) mp[deg[j]]++;
    }
    cout << ans << "\n";
}

//优化代码
void solve(){
    int n;
    cin >> n;
    
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1);
    int mx = -1, nmx = -1, cm = 0, ncm = 0;
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    } 
    sort(deg.begin() + 1, deg.end(), greater<int>());
    for(int i = 1; i <= n; i++){
        if(i == 1) mx = deg[i];
        if(i == 2) nmx = deg[i];
        if(deg[i] == mx) cm++;
        if(deg[i] == nmx) ncm++;
    }
    for(int i = 1; i <= n; i++){
        auto &cur = adj[i];
        int cur_cnt_nmx = 0;
        if(cur.size() == mx){
            for(auto c : cur){
                if(adj[c].size() == nmx){
                    cur_cnt_nmx++;
                }
            }
            if(cur_cnt_nmx < ncm){
                cout << mx + nmx - 1 << "\n";
                return;
            }
        }
    }
    cout << mx + nmx - 2 << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    int t;
    cin >> t;
    while(t--){
        solve1();
    }
    return 0;
}