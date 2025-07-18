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
    int cur = a[k] + 1, h = 1;
    sort(a.begin() + 1, a.end());
    a.erase(unique(a.begin() + 1, a.end()), a.end());
    n = a.size() - 1;
    int pos = 1;
    while(a[pos] + 1 <= cur) {
        pos++;
    }
    for(; pos <= n; pos++) {
        int d = a[pos] + 1 - cur;
        if(h + d > cur) {
            cout << "NO\n";
            return;
        }
        cur += d;
        h += d;
    }
    cout << "YES\n";
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
