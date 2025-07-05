#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


struct info{
    int l, r;
};
void solve(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    map<int,vector<int>> mp;
    vector<int> val(n + 1);
    val[0] = INT_MIN;
    for(int i = 1; i <= n; i++){
        int v;
        cin >> v;
        val[i] = v;
        mp[v].push_back(i);
    } 
    for(int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<bool> vis(n + 1, false);
    auto check = [&](int o, int v) -> bool{
        
        for(auto c : adj[o]){
            vis[c] = true;
        }
        int mx = INT_MIN, nmx = INT_MIN;
        for(int i = 1; i <= n; i++){
            if(vis[i]){
                continue;
            }
            if(val[i] > mx){
                nmx = mx;
                mx = val[i];
            }else if(val[i] > nmx){
                nmx = val[i];
            }
        }
        for(auto c : adj[o]){
            vis[c] = false;
        }
        return nmx == v;
    };
    for(auto it = mp.rbegin(); it != mp.rend(); ++it){
        int val = it->first;
        auto &vec = it->second;
        for(auto o : vec){
            if(check(o, it->first)){
                cout << o << "\n";
                return;
            }
        }
    }
    cout << 0 << "\n";
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