#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int mx = 0, sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
        sum += a[i];
    }
    sort(a.begin(), a.end(), greater<int>());
    bool ok;
    int tar;
    vector<int> vis(n + 1, 0);
    auto dfs = [&](auto &&dfs, int x, int cnt, int pre) -> void {
        if(ok) return;
        if(cnt == n + 1) {
            ok = true;
            return;
        }
        if(x < a.back()) return;
        unordered_map<int,int> mp;
        for(int i = 1; i <= n && !ok; i++) {
            if(vis[i] || mp[a[i]] != 0) continue;
            if(x == tar) {
                vis[i] = true;
                int nx = x == a[i] ? tar : x - a[i];
                dfs(dfs, nx, cnt + 1, nx == tar ? 1000000 : a[i]);
                vis[i] = false;
                if(!ok) return;
            } 
            else if(x >= a[i] && a[i] <= pre) {
                vis[i] = true;
                mp[a[i]]++;
                int nx = x == a[i] ? tar : x - a[i];
                dfs(dfs, nx, cnt + 1, nx == tar ? 1000000 : a[i]);
                vis[i] = false;
                if(x == a[i] && !ok) return;
            }
        }
    };
    for(int i = mx; i <= sum; i++) {
        if(sum % i == 0) {
            ok = false;
            tar = i;
            dfs(dfs, tar, 1, 1000000);
            if(ok) {
                cout << i << "\n";
                return;
            }
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

