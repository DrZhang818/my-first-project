#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void chmax(int &x, int y) {
    if(x < y) {
        x = y;
    }
}
void solve() {
    int n, k;
    cin >> n >> k;
    map<int,int> cnt;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    vector<PII> a(cnt.begin(), cnt.end());
    int mx = 0;
    for(auto [x, c] : a) {
        chmax(mx, c);
    }
    vector<int> val;
    for(auto [x, c] : a) {
        if(c == mx) {
            val.push_back(x);
        }
    }
    ll ans = val[0] - val.back() + 1LL * (n - mx) * k;
    for(int i = 1; i < val.size(); i++) {
        ans = max(ans, val[i] - val[i - 1] + 1LL * (n - mx - 1) * k);
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
