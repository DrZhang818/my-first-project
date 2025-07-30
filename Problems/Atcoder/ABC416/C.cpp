#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    vector<string> ss;
    auto dfs = [&](auto &&self, int cnt, string cur) -> void {
        if(cnt == k) {
            ss.push_back(cur);
            return;
        }
        for(int i = 1; i <= n; i++) {
            self(self, cnt + 1, cur + s[i]);
        }
    };
    dfs(dfs, 0, "");
    sort(ss.begin(), ss.end());
    cout << ss[x - 1] << "\n";
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
