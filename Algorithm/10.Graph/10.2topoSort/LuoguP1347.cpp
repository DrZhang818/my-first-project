#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve() { 
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> adj(n);
    vector<int> deg(n + 1);
    vector<int> ans(n);
    unordered_set<int> st;
    auto bfs = [&]() -> int {
        queue<int> q;
        vector<int> temp = deg;
        bool ok = true;
        for(int i = 0; i < n; i++) {
            if(st.find(i) != st.end() && temp[i] == 0) {
                q.push(i);
            }
        }
        int idx = 0;
        while(!q.empty()) {
            if(q.size() != 1) {
                ok = false;
            }
            int u = q.front();
            q.pop();
            ans[idx++] = u;
            for(int v : adj[u]) {
                if(--temp[v] == 0) {
                    q.push(v);
                }
            }
        }
        if(idx != st.size()) return 0;
        if(ok) return 1;
        return 2;
    };
    bool ok = false;
    for(int i = 1; i <= m; i++) {
        string s;
        cin >> s;
        int u = s[0] - 'A';
        int v = s[2] - 'A';
        adj[u].push_back(v);
        deg[v]++;
        st.insert(u);
        st.insert(v);
        int flag = bfs();
        if(flag == 0) {
            printf("Inconsistency found after %d relations.\n", i);
            return ;
        } else if(flag == 1 && st.size() == n) {
            printf("Sorted sequence determined after %d relations: ", i);
            for(int i = 0; i < n; i++) {
                printf("%c", ans[i] + 'A');
            }
            printf(".\n");
            return ;
        }
    }   
    printf("Sorted sequence cannot be determined.\n");
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);

    solve();
    return 0;
}

