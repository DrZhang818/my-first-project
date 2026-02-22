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
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    for(int i = 1, j = 1; i <= n; i = j) {
        while(j <= n && a[j] == a[i]) {
            j++;
        }
        int cnt = j - 2;
        if(5 * cnt >= 4 * (n - 1)) {
            ans += 1LL * a[i] * (j - i);
        }
    }

    cout << ans << "\n";
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
