#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int l, r, id;
    friend bool operator < (const info &a, const info &b) {
        return a.l < b.l;
    };
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].l >> a[i].r;
        a[i].id = i;
    }
    sort(a.begin() + 1, a.end());
    vector<int> ans(n + 1);
    int R = 0, c = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i].l > R) {
            c++;
        }
        ans[a[i].id] = c;
        R = max(R, a[i].r);
    }
    if(c == 1) {
        cout << -1 << "\n";
        return;
    }
    for(int i = 1; i <= n; i++) {
        cout << min(2, ans[i]) << " \n"[i == n];
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
