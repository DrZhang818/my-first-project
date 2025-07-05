#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;

int n;
vector<bool> vis(100005, false);
vector<int> path(100005);
void dfs(int cnt) {
    for(int i = 1; i <= n; i++) {
        if(cnt == n) {
            for(int j = 0; j < n; j++) {
                cout << path[j] << " \n"[j == n - 1];
            }
            return;
        }
        if(vis[i]) continue;
        path[cnt] = i;
        vis[i] = true;
        dfs(cnt + 1);
        vis[i] = false;
    }
}

void solve() { 
    cin >> n;
    dfs(0);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
