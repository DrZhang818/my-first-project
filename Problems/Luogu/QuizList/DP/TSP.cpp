#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    }
    vector<vector<int>> memo(1 << n - 1, vector<int>(n, -1));
    auto dfs = [&](auto&& dfs, int msk, int i) -> int {
        if(msk == (1 << n - 1) - 1) {
            return a[i][0];
        }
        int &res = memo[msk][i];
        if(res != -1) return res;
        res = INT_MAX;
        for(int j = 0, cur; j < n - 1; j++) {
            if((msk & (1 << j)) == 0) {
                cur = a[i][j + 1] + dfs(dfs, msk | (1 << j), j + 1);
                res = min(res, cur);
            }
        }
        return res;
    };
    int ans = dfs(dfs, 0, 0);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

