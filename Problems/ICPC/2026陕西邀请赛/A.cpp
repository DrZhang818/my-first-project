#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    i64 sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    if(sum % n) {
        cout << -1 << "\n";
        return;
    }

    i64 x = sum / n; 

    array<i64, 2> las {};
    i64 ans = 0;
    sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += a[i];
        if(x * i < sum) {
            cout << -1 << "\n";
            return;
        }
        i64 d = x * i - sum;
        ans += max(0LL, d - las[i & 1]);
        las[i & 1] = d;
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