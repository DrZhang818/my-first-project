#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int p;
    cin >> p;
    int x = a[p];
    int l = 1, r = n, s = 0;
    int ans = 0;
    while(l < p || r > p) {
        while(l < p && (a[l] ^ s) == x) l++;
        while(r > p && (a[r] ^ s) == x) r--;
        if(l == r) {
            ans += s == 1;
        } else {
            ans++;
            s ^= 1;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}