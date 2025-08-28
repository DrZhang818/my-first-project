#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> path;
    auto dfs = [&](auto &&self, int pos, int rem) -> void {
        if(pos == n + 1) {
            if(rem == 0) {
                for(int x : path) {
                    cout << x << " ";
                }
                cout << "\n";
            }
            return;
        }
        for(int i = 1; i <= a[pos]; i++) {
            path.push_back(i);
            self(self, pos + 1, (rem + i) % k);
            path.pop_back();
        }
    };
    dfs(dfs, 1, 0);
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
