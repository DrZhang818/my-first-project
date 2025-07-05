#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    vector<vector<PII>> ord(16);
    ord[1] = {{1,6}, {2,5}, {3,4}};
    ord[2] = {{1,6}, {2,4}, {3,5}};
    ord[3] = {{1,5}, {2,6}, {3,4}};
    ord[4] = {{1,5}, {2,4}, {3,6}};
    ord[5] = {{1,4}, {2,6}, {3,5}};
    ord[6] = {{1,4}, {2,5}, {3,6}};
    ord[7] = {{1,6}, {2,3}, {4,5}};
    ord[8] = {{1,5}, {2,3}, {4,6}};
    ord[9] = {{1,3}, {2,6}, {4,5}};
    ord[10] = {{1,3}, {2,5}, {4,6}};
    ord[11] = {{1,4}, {2,3}, {5,6}};
    ord[12] = {{1,3}, {2,4}, {5,6}};
    ord[13] = {{1,2}, {3,6}, {4,5}};
    ord[14] = {{1,2}, {3,5}, {4,6}};
    ord[15] = {{1,2}, {3,4}, {5,6}};
    vector e(17, vector<int>(17));
    for(int i = 1; i <= 15; i++) {
        for(int j = i + 1; j <= 16; j++) {
            cin >> e[i][j];
        }
    }
    vector<set<int>> adj(17);
    vector<int> vis(17), win(17), lose(17), id(17), cnt(17);
    iota(id.begin(), id.end(), 0);
    int tag; 
    auto add = [&](int u, int v) {
        win[u]++;
        lose[v]++;
        adj[u].insert(v);
        adj[v].insert(u);
    };
    auto update = [&]() {
        for(int u = 1; u <= 16; u++) {
            vis[u] = false;
            int c = 0;
            for(int v : adj[u]) {
                c += win[v] - lose[v];
            }
            cnt[u] = c;
        }
        sort(id.begin() + 1, id.end(), [&](auto a, auto b){
            if(win[a] != win[b]) return win[a] > win[b];
            if(cnt[a] != cnt[b]) return cnt[a] > cnt[b];
            return a < b; 
        });  
    };
    auto work = [&](int l, int r) {
        for(int i = l; i <= r; i++) {
            if(vis[i]) continue;
            int j = r;
            while(vis[j] || adj[id[i]].count(id[j])) j--;
            vis[i] = vis[j] = true;
            int x = min(id[i], id[j]), y = max(id[i], id[j]);
            tag = e[x][y];
            if(tag) {
                add(x, y);
            } else {
                add(y, x);
            }
        }
    };
    auto work2 = [&](int l, int r) {
        l--, r--;
        for(int i = 1; i <= 15; i++) {
            auto [u1, v1] = ord[i][0];
            auto [u2, v2] = ord[i][1];
            auto [u3, v3] = ord[i][2];
            if(adj[id[l + u1]].count(id[l + v1])) continue;
            if(adj[id[l + u2]].count(id[l + v2])) continue;
            if(adj[id[l + u3]].count(id[l + v3])) continue;
            int x = min(id[l + u1], id[l + v1]), y = max(id[l + u1], id[l + v1]);
            tag = e[x][y];
            if(tag) {
                add(x, y);
            } else {
                add(y, x);
            }
            x = min(id[l + u2], id[l + v2]), y = max(id[l + u2], id[l + v2]);
            tag = e[x][y];
            if(tag) {
                add(x, y);
            } else {
                add(y, x);
            }            
            x = min(id[l + u3], id[l + v3]), y = max(id[l + u3], id[l + v3]);
            tag = e[x][y];
            if(tag) {
                add(x, y);
            } else {
                add(y, x);
            }
            break;
        }
    };
    for(int i = 1; i <= 8; i++) {
        tag = e[i][i + 8];
        if(tag) {
            add(i, i + 8);
        } else {
            add(i + 8, i);
        }
    }
    update();
    
    work(1, 8);
    work(9, 16);
    update();
    
    work(1, 4);
    work(5, 12);
    work(13,16);
    update();
    
    work2(3, 8);
    work2(9, 14);
    update();

    work2(6, 11);
    for(int i = 1; i <= 16; i++) {
        cout << win[i] << " " << lose[i] << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
