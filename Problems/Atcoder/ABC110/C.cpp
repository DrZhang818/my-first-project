#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s, t;
    cin >> s >> t;
    vector adj(26, vector<int>(26));
    int n = s.size();
    for(int i = 0; i < n; i++) {
        adj[s[i] - 'a'][t[i] - 'a'] = 1;
    }
    bool ok = true;
    for(int i = 0; i < 26; i++) {
        int cnt = 0;
        for(int j = 0; j < 26; j++) {
            cnt += adj[i][j];
        }
        if(cnt > 1) {
            ok = false;
        }
    }
    for(int j = 0; j < 26; j++) {
        int cnt = 0;
        for(int i = 0; i < 26; i++) {
            cnt += adj[i][j];
        }
        if(cnt > 1) {
            ok = false;
        }
    }
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
