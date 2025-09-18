#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
    }
    vector<vector<int>> adj(n + 1);
    vector<int> stk;
    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && a[stk.back()] <= a[i]) {
            stk.pop_back();
        }
        stk.push_back(i);
    }
    stk.insert(stk.begin(), 0);
    sort(b.begin() + 1, b.end(), greater<int>());
    for(int i = 1, j = 1; i <= m; i++) {
        while(j < stk.size() && a[stk[j]] >= b[i]) {
            j++;
        }
        adj[stk[j - 1]].push_back(b[i]);
    }
    for(int i = 0; i <= n; i++) {
        if(i) {
            cout << a[i] << " ";
        }
        for(int x : adj[i]) {
            cout << x << " ";
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
