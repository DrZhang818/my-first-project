#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    vector<bool> vis(14, false);
    vector<int> path(14);
    ll ans = 0;
    function<void(int)> dfs = [&](int cnt) -> void {
        if(cnt > 3 && path[1] + path[2] != path[3]) return;
        if(cnt > 6 && path[4] - path[5] != path[6]) return;
        if(cnt > 9 && path[7] * path[8] != path[9]) return;
        if(cnt > 12 && (path[10] % path[11] != 0 || path[10] / path[11] != path[12])) return;
        if(cnt == 13) {
            ans++;
            for(int i = 1; i <= 12; i++) {
                cout << path[i] << " ";
            }
            cout << "\n";
            return;
        }
        for(int i = 1; i <= 13; i++) {
            if(vis[i]) continue;
            vis[i] = true;
            path[cnt] = i;
            dfs(cnt + 1);
            vis[i] = false;
            path[cnt] = 0;
        }
    };
    dfs(1);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

