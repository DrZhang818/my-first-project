#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x]++;
    }
    int ans = 0;
    for(int i = 0; i <= n; i++) {
        if(a[i] >= 1) {
            if(a[i] >= i) {
                ans += a[i] - i;
            } else {
                ans += a[i];
            }
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
