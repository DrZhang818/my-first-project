#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> idx(n + 1);
    for(int i = 1; i <= n; i++) {
        idx[a[i]] = i;
    }
    auto dfs = [&](this auto &&self, vector<int> &a) -> vector<int> {
        vector<int> ans = a;
        vector<int> id(a.size());
        for(int i = 1; i <= n; i++) {
            id[a[i]] = i;
        }
        for(int i = 1; i <= n; i++) {
            int x = a[i], y = x - 1, z = x - 2;
            if(y < 1 || z < 1 || id[y] < id[x] || id[z] < id[x]) {
                continue;
            }
            a[i] = z;
            a[id[y]] = x;
            a[id[z]] = y;
            ans = min(ans, self(a));
            a[i] = x;
            a[id[y]] = x - 1;
            a[id[z]] = x - 2;
        }
        return ans;
    };
    auto ans = dfs(a);
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }

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
    