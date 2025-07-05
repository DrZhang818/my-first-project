#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://acm.hdu.edu.cn/showproblem.php?pid=2610
void solve(int n, int p){
    vector<int> a(n);
    vector<vector<int>> ans;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    } 
    vector<int> path;
    bool ok = false;
    auto dfs = [&](auto &&dfs, int idx, int cnt, int len) -> void {
        if(ans.size() > p) return;
        if(cnt >= 2 && path[cnt - 1] < path[cnt - 2]) {
            return;
        }
        if(cnt == len) {
            ans.emplace_back(path);
            ok = true;
            return ;
        }
        if(idx >= n) return ; 
        unordered_map<int,int> mp;
        for(int i = idx; i < n; i++) {
            if(mp[a[i]]) continue;
            path.push_back(a[i]);
            dfs(dfs, i + 1, cnt + 1, len);
            path.pop_back();
            mp[a[i]]++;
        }
    };
    for(int len = 1; len <= n && ans.size() < p; len++) {
        ok = false;
        dfs(dfs, 0, 0, len);
        if(!ok) break;
    }
    for(int i = 0; i < min(p, (int)ans.size()); i++) {
        for(int x : ans[i]) {
            cout << x << " ";
        }
        cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, p;
    while(cin >> n >> p){
        solve(n, p);
        cout << "\n";
    }
    return 0;
}

