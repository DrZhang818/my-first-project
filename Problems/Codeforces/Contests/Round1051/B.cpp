#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        q.push(x);
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    ll ans = 0;
    int L = 1;
    while(!q.empty()) {
        int len = q.top(); q.pop();
        int R = L + len - 1;
        if(R > n) {
            break;
        }
        while(L < R) {
            ans += a[L];
            L++;
        }
        L++;
    }
    while(L <= n) {
        ans += a[L];
        L++;
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
