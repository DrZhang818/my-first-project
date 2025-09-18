#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    if(pre[n] <= s) {
        cout << 0 << "\n";
        return;
    }
    int mx = 0, idx = 0;
    for(int i = 1; i <= n && s >= 0; i++) {
        int l = i, r = n + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(pre[mid] - pre[i] <= s) {
                l = mid;
            } else {
                r = mid;
            }
        }
        if(i - 1 + l - i > mx) {
            mx = l - 1;
            idx = i;
        }
        s -= a[i];
    }
    cout << idx << "\n";
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
