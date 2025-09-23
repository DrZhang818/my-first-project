        // }
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
    vector<int> cnt(n + 2);
    for(int l = 1, r = 1; l <= n; l = r) {
        while(r <= n && a[r] == a[l]) {
            r++;
        }
        cnt[1]++;
        cnt[r - l + 1]--;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        cnt[i] += cnt[i - 1];
        ans = max(ans, cnt[i] * i);
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
