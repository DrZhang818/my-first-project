#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    while(q--) {
        int s;
        cin >> s;
        int ans = 0;
        priority_queue<int> q;
        for(int i = 1; i <= n && i <= 30; i++) {
            q.push(a[i]);
        }
        q.push(0);
        while(s) {
            int x = q.top();
            q.pop();
            if(x >= s) {
                break;
            }
            if(x == 0) {
                ans += s;
                s ^= s;
            }
            int t = 1 << __lg(s);
            if(x < t) {
                ans += t - x;
                s ^= t;
            } else {
                s ^= t;
                q.push(x ^ t);
            }
        }
        cout << ans << "\n";
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
