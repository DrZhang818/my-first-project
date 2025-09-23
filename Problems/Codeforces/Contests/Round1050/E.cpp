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
    vector<int> a(n + 1), cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    for(int i = 1; i <= n; i++) {
        if(cnt[i] % k) {
            cout << 0 << "\n";
            return;
        }
    }
    vector<int> cur(n + 1);
    ll ans = 0;
    for(int L = 1, R = 1; R <= n; R++) {
        int x = a[R];
        cur[x]++;
        while(cur[x] > cnt[x] / k) {
            cur[a[L++]]--;
        }
        ans += R - L + 1;
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
