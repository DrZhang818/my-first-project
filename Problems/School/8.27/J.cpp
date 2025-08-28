#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000007;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }    
    int mn = inf;
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        if(a[i] > b[i]) {
            mn = min(mn, b[i]);
        }
    }
    if(mn == inf) {
        cout << 0 << "\n";
        return;
    }
    sum -= mn;
    cout << sum << "\n";
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
