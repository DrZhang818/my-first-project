#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> tr(n / 2 + 1);
    int cnt = 0;
    queue<int> q;
    q.push(0);
    for(char c : s) {
        if(c == '(') {
            cnt++;
            tr[q.front()].push_back(cnt);
            q.push(cnt);
        } else {
            q.pop();
        }
    }
    auto dfs = [&](this auto &&self, int u) -> void {
        if(u != 0) {
            cout << "(";
        }
        for(int i = tr[u].size() - 1; i >= 0; i--) {
            self(tr[u][i]);
        }
        if(u != 0) {
            cout << ")";
        }
    };
    dfs(0);
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
