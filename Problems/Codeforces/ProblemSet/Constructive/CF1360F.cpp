#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1360/F
void solve() {
    int n, m;
    cin >> m >> n;
    vector<string> a(m);
    vector<vector<char>> adj(n);
    for(int i = 0; i < m; i++) {
        cin >> a[i];
        for(int j = 0; j < n; j++) {
            adj[j].push_back(a[i][j]);
        }
    }
    string ans = a[0];
    auto ck = [&](string s) -> bool {
        for(int i = 0; i < m; i++) {
            int cnt = 0;
            for(int j = 0; j < n; j++) {
                if(s[j] != a[i][j]) {
                    cnt++;
                }
                if(cnt > 1) return false;
            }
        }
        return true;
    };
    for(int i = 0; i < n; i++) {
        if(i) ans[i - 1] = a[0][i - 1];
        for(char c : adj[i]) {
            ans[i] = c;
            if(ck(ans)) {
                cout << ans << "\n";
                return;
            }
        }
    }    
    cout << -1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
