#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

struct hero{
    ll w;
    int c;
};
void solve(){
    int n;
    cin >> n;
    vector<vector<hero>> nums(n, vector<hero>(5));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 5; j++){
            cin >> nums[i][j].w;
        }
        for(int j = 0; j < 5; j++){
            cin >> nums[i][j].c;
        }
    }
    vector<vector<vector<ll>>> memo(n + 1, vector<vector<ll>>(7, vector<ll>(71, -1)));
    function<ll(int, int, int)> dfs = [&](int i, int j, int c) -> ll{
        if(i >= n ){
            return 0;
        }
        if(j >= 5){
            return dfs(i + 1, 0, min(70, c + (c / 10) + 2));
        }
        ll &res = memo[i][j][c];
        if(res != -1){
            return res;
        }
        if(c < nums[i][j].c){
            return res = max(dfs(i, j + 1, c), dfs(i + 1, 0, min(70, c + (c / 10) + 2)));
        }
        return res = max({dfs(i, j + 1, c), dfs(i, j + 1, c - nums[i][j].c) + nums[i][j].w,
                    dfs(i + 1, 0, min(70, c + (c / 10) + 2))});
    };
    ll ans = dfs(0, 0, 24);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}