#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, t, a;
    cin >> n >> t >> a;
    a *= 1000;
    vector<int> h(n + 1);
    int id = -1;
    int mx = inf;
    for(int i = 1; i <= n; i++) {
        cin >> h[i];
        int cur = t * 1000 - h[i] * 6;
        if(abs(cur - a) < abs(mx - a)) {
            mx = cur;
            id = i;
        }
    }
    cout << id << "\n";
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
