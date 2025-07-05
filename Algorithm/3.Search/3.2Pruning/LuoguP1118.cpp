#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve() {
    int n, sum;
    cin >> n >> sum;
    vector<int> C(n);
    C[0] = 1;
    for(int j = 1; j <= n - 1; j++) {
        C[j] = C[j - 1] * (n - 1 - j + 1) / j;
    }    
    vector<int> path(n);
    vector<int> vis(n + 1, false);
    bool ok = false;
    auto dfs = [&](auto &&dfs, int cnt) -> void {
        if(ok) return;
        if(cnt == n) {
            int cur = 0;
            for(int i = 0; i < n; i++) {
                cur += path[i] * C[i];
            }
            if(cur == sum) ok = true ;
            return ;
        }
        for(int i = 0, cur = 0; i < cnt; i++) {
            cur += C[i] * path[i];
            if(cur > sum) return;
        }
        for(int i = 1; i <= n && !ok; i++) {
            if(!vis[i]) {
                path[cnt] = i;
                vis[i] = true;
                dfs(dfs, cnt + 1);
                vis[i] = false;
            }
        }
    };
    dfs(dfs, 0);
    if(ok) {
        for(int i = 0; i < n; i++) {
            cout << path[i] << " \n"[i == n - 1];
        }
    } 
}   

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

