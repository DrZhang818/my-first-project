#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


int n;
vector<int> a, b, path;
vector<bool> vis;
void dfs(int pos) {
    if(pos == n) {
        int res = 0;
        for(int i = 0; i < n; i++) {
            res = res * 10 + path[i];
        }
        b.push_back(res);
        return ;
    }
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            vis[i] = true;
            path.push_back(a[i]);
            dfs(pos + 1);
            vis[i] = false;
            path.pop_back();
        }
    }
}
ll tot;
bool ok = false;
void dfs2(int pos, ll sum, int cnt) {
    if(ok) return;
    if(sum * 2 == tot && cnt == n / 2) {
        for(int i = 0; i < path.size(); i++) {
            cout << (int)sqrt(path[i]) << "\n";
        }
        ok = true;
        return ;
    }
    if(pos == n) return;
    dfs2(pos + 1, sum, cnt);
    path.push_back(b[pos]);
    dfs2(pos + 1, sum + b[pos], cnt + 1);
    path.pop_back();
}
void solve() { 
    cin >> n;
    a.resize(n + 1);
    vis.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dfs(0);
    for(int i = 0; i < b.size(); i++) {
        b[i] = b[i] * b[i];
        tot += b[i];
    }
    n = b.size();
    path.clear();
    dfs2(0, 0, 0);
}

int main()
{

    solve();
    return 0;
}
    
