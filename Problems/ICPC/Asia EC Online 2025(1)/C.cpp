#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int l, r;
};
void solve() {
    int m, n;
    cin >> m >> n;
    vector<info> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i].l >> a[i].r;
    }
    sort(a.begin() + 1, a.end(), 
        [&](auto x, auto y) {
            return x.l < y.l;
        });
    priority_queue<int, vector<int>, greater<int>> pq;
    int i = 1, R = 1, ans = n;
    while(i <= m || !pq.empty()) {
        while(i <= m && a[i].l < R) {
            pq.push(a[i].r);
            i++;
        }
        while(!pq.empty() && pq.top() < R) {
            pq.pop();
        }
        if(!pq.empty()) {
            pq.pop();
            ans--;
            R++;
        } else if(i <= m) {
            R = a[i].l + 1;
        }
    }
    cout << ans << "\n";
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
