#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 26;

struct Info {
    int v;
    string s;
    friend bool operator<(const Info& a, const Info& b) {
        return a.s < b.s;
    }
};

void solve() {  
    int n;
    cin >> n;
    
    vector<vector<Info>> adj(N);

    vector<int> indeg(N), outdeg(N);

    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        int u = s[0] - 'a';
        int v = s.back() - 'a';
        adj[u].push_back({v, s});
        outdeg[u]++;
        indeg[v]++;
    }

    int S = -1, T = -1;
    int cnt1 = 0, cnt2 = 0;
    bool ok = true;

    for(int i = 0; i < 26; i++) {
        if(indeg[i] != outdeg[i]) {
            if(outdeg[i] == indeg[i] + 1) {
                S = i;
                cnt1++;
            } else if(indeg[i] == outdeg[i] + 1) {
                T = i;
                cnt2++;
            } else {
                ok = false;
                break;
            }
        }
    }

    if(cnt1 > 1 || cnt1 != cnt2) {
        ok = false;
    }

    if(!ok) {
        cout << "***\n";
        return;
    }

    if(S == -1) {
        S = 0;
        for(int i = 0; i < N; i++) {
            if(outdeg[i] > 0) {
                S = i;
                break;
            }
        }
    }

    for(int i = 0; i < N; i++) {
        sort(adj[i].begin(), adj[i].end());
    }

    vector<string> ans;
    vector<int> cur(N);

    auto dfs = [&](this auto&& self, int u) -> void {
        while(cur[u] < adj[u].size()) {
            auto [v, s] = adj[u][cur[u]++];
            self(v);
            ans.push_back(move(s));
        }
    };

    dfs(S);

    if(ans.size() != n) {
        cout << "***\n";
        return;
    }

    reverse(ans.begin(), ans.end());

    for(int i = 0; i < n; i++) {
        cout << ans[i] << ".\n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
