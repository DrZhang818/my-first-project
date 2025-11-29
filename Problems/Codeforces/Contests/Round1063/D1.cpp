#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int query(int l, int r) {
    cout << "? " << l << " " << r << endl;
    int res;
    cin >> res;
    return res;
}
void answer(int x) {
    cout << "! " << x << endl;
}
struct info {
    int l, r;
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<info> Q(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> Q[i].l >> Q[i].r;
    }
    vector<int> mx(n + 1, -1);
    vector<info> t;
    for(int i = 1; i <= q; i++) {
        auto [l, r] = Q[i];
        mx[l] = max(mx[l], r);
    }
    int premx = -1;
    for(int i = 1; i <= n; i++) {
        if(mx[i] == -1 || mx[i] <= premx) continue;
        premx = mx[i];
        t.push_back({i, mx[i]});
    }
    int ans = 0;
    vector<int> vis(n + 2, 0);
    for(auto [l, r] : t) {
        if(l != r) {
            ans = max(ans, query(l, r));
            vis[l]++;
            vis[r + 1]--;
        }
    }
    for(int i = 1; i <= n; i++) {
        vis[i] += vis[i - 1];
    }
    int idx = -1;
    for(int i = 1; i <= n; i++) {
        if(vis[i]) continue;
        if(i == n || vis[i + 1]) {
            int x = query(i, i);
            if(x != 0) {
                idx = i;
                break;
            }
        } else {
            int x = query(i, i + 1);
            if(x != 0) {
                x = query(i, i);
                if(x != 0) {
                    idx = i;
                } else {
                    idx = i + 1;
                }
                break;
            } else {
                i++;
            }
        }
    }
    // assert(idx != -1);
    for(auto [l, r] : t) {
        if(l <= idx && idx <= r) {
            ans = max(ans, 1);
        }
    }
    answer(ans);
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
