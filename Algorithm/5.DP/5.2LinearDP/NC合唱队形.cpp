#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    vector<int> pre(n + 1, 1), suf(n + 1, 1);
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j < i; j++) {
            if(a[i] > a[j]) {
                pre[i] = max(pre[i], pre[j] + 1);
            }
        }
    }
    for(int i = n - 1; i >= 1; i--) {
        for(int j = i + 1; j <= n; j++) {
            if(a[i] > a[j]) {
                suf[i] = max(suf[i], suf[j] + 1);
            }
        }
    }
    int ans = inf;
    for(int i = 1; i <= n; i++) {
        ans = min(ans, n - pre[i] - suf[i] + 1);
    }
    cout << ans << "\n";
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
