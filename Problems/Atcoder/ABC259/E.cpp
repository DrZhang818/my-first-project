#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
struct info {
    int p, e;
};
void solve() {
    int n;
    cin >> n;
    vector<vector<info>> a(n);
    vector<int> b;
    for(int i = 0; i < n; i++) {
        int m;
        cin >> m;
        a[i].resize(m);
        for(int j = 0; j < m; j++) {
            cin >> a[i][j].p >> a[i][j].e;
            b.push_back(a[i][j].p);
        }
    }
    if(n == 1) {
        cout << 1 << "\n";
        return;
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int sz = b.size();
    vector<int> mx(sz), cnt(sz);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < a[i].size(); j++) {
            auto [p, e] = a[i][j];
            auto it = lower_bound(b.begin(), b.end(), p) - b.begin();
            if(e == mx[it]) {
                cnt[it]++;
            } else if(e > mx[it]) {
                mx[it] = e;
                cnt[it] = 1;
            }
        }
    }
    int ans = 0, t = 0;
    for(int i = 0; i < n; i++) {
        bool ok = true;
        for(int j = 0; j < a[i].size(); j++) {
            auto [p, e] = a[i][j];
            auto it = lower_bound(b.begin(), b.end(), p) - b.begin();
            if(e == mx[it] && cnt[it] == 1) {
                ans += 1;
                ok = false;
                break;
            }
        }
        if(ok) {
            t = 1;
        }   
    }
    cout << ans + t << "\n";
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
