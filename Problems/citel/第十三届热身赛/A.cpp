#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, x;
    cin >> n >> x;
    vector<int> nums(n);
    for(auto &num : nums){
        cin >> num;
    }
    vector<int> vis(n, -1);
    int curMIN = INT_MAX;
    function<int(int)> dfs = [&](int i) -> int{
        if(vis[i] != -1){
            return vis[i];
        }
        curMIN = min(curMIN, nums[i]);
        vis[i] = curMIN;
        int nx = (i + x) % n;
        return vis[i] = min(dfs(nx), vis[i]);
    };
    int num = 0;
    int cost = 0;
    for(int i = 0; i < n; i++){
        curMIN = INT_MAX;
        if(vis[i] == -1){
            num++;
            cost += dfs(i);
        }
        else continue;
    }
    int maxC = max(vis[0], vis[num - 1]);
    cout << (ll)(num - 1) * (cost - maxC) << "\n";
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