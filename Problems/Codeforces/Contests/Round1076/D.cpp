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
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end());
    ll ans = 0;
    for(int i = 1, j = n, cnt = 0; i <= n; i++) {
        while(j > 0 && cnt < b[i]) {
            j--;
            cnt++;
        }
        if(cnt >= b[i]) {
            ans = max(ans, 1LL * i * a[j + 1]);
        } else {
            break;
        }
        cnt -= b[i];
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
