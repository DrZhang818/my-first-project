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
    vector<int> a(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i];
    }
    int mx = ranges::max(a);
    bool ok = true;
    for(int i = 2; i <= m; i++) {
        if(a[i] <= a[i - 1]) {
            ok = false;
            break;
        }
    }
    if(!ok) {
        cout << 1 << "\n";
        return;
    }
    cout << n - mx + 1 << "\n";
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
