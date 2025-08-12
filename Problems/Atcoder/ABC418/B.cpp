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
    s = "#" + s;
    vector<int> pre(n + 1);
    vector<int> pos;
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1];
        if(s[i] == 't') {
            pre[i]++;
            pos.push_back(i);
        }
    }
    db ans = 0;
    int sz = pos.size();
    for(int i = 0; i < sz; i++) {
        for(int j = i + 1; j < sz; j++) {
            if(pos[j] - pos[i] + 1 < 3) continue;
            ans = max(ans, (db)(pre[pos[j]] - pre[pos[i] - 1] - 2) / (pos[j] - pos[i] - 1));
        }
    }
    cout << fixed << setprecision(12) << ans << "\n";
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
