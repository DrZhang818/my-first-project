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
    vector<int> sg(n + 1);
    sg[0] = 0;
    for(int i = 1; i <= n; i++) {
        vector<bool> vis(m + 1);
        for(int j = 1; j <= m && j <= i; j++) {
            vis[sg[i - j]] = true;
        }
        int mex = 0;
        while(vis[mex]) mex++;
        sg[i] = mex;
    }
    for(int i = 0; i <= n; i++) {
        cerr << sg[i] << " \n"[i == n];
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
