#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    std::vector<int> nums(n);
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    vector<bool> vis(n, false);
    int ans = 0;
    auto dfs = [&](auto&& dfs, int i){
        if(vis[i]) return;
        vis[i] = true;
        int ni = nums[i] - 1;
        if(vis[ni]){
            ans++;
            return;
        }else{
            dfs(dfs, ni);
        }

    };
    for(int i = 0; i < n; i++){
        dfs(dfs, i);
    }
    cout << ans - 1 << endl;
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
