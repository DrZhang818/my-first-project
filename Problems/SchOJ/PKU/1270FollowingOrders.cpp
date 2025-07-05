#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(string &ss){
    string tt;
    getline(cin, tt);
    string s, t;
    for(auto c : ss) if(c != ' ') s += c;
    for(auto c : tt) if(c != ' ') t += c;
    sort(s.begin(), s.end());
    int n = s.size();
    unordered_map<char, int> mp;
    for(int i = 0; i < s.size(); i++) {
        char c = s[i];
        mp[c] = i;
    }
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    for(int i = 0; i < t.size(); i += 2) {
        int u = mp[t[i]], v = mp[t[i + 1]];
        adj[u].push_back(v);
        deg[v]++;
    } 
    vector<int> res(n);
    vector<int> vis(n, 0);
    auto dfs = [&](auto &&dfs, int u, int cnt) -> void {
        res[cnt] = u;
        if(cnt == n - 1) {
            for(int i = 0; i < n; i++) {
                cout << s[res[i]];
            }
            cout << "\n";
            return ;
        }
        vis[u] = 1;
        for(int v : adj[u]) {
            if(!vis[v]) {
                deg[v]--;
            }
        }
        for(int i = 0; i < n; i++) {
            if(!vis[i] && !deg[i]) {
                dfs(dfs, i, cnt + 1);
            }
        }
        for(int v : adj[u]) {
            if(!vis[v]) {
                deg[v]++;
            }
        }
        vis[u] = 0;
    };
    for(int i = 0; i < n; i++) {
        if(!deg[i]) {
            dfs(dfs, i, 0);
        }
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s;
    while(getline(cin, s) && s != "end") {
        solve(s);
    }
    return 0;
}

