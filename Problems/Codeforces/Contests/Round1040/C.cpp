#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, y, id;
    friend bool operator < (const info &a, const info &b) {
        return a.x < b.x;
    }
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
        a[i].id = i;
    }
    sort(a.begin() + 1, a.end());
    vector<info> ans;
    int l = 0, r = 0;
    for(int i = 1; i <= n; i++) {
        auto [x, y, id] = a[i];
        if(x >= r) {
            ans.push_back(a[i]);
            l = x;
            r = y;
        } else {
            if(y <= r) continue;
            while(!ans.empty() && x == ans.back().x) {
                ans.pop_back();
            }
            ans.push_back(a[i]);
            r = y;
        }
    }
    cout << ans.size() << "\n";
    for(auto [x,y,id] : ans) {
        cout << id << " ";

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
