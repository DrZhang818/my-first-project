#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int N = 1e6 + 5;
void solve() {
    int n; 
    cin >> n;
    vector<int> cnt(N + 1), t(N + 1);
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        cnt[x]++;
    }
    ll ans = 0;
    vector<ll> P;
    for(int i = N; i >= 1; i--) {
        int tot = cnt[i] + t[i];
        int sz = tot / 2;
        for(int j = 0; j < sz; j++) P.push_back(i);
        if(cnt[i] >= t[i]) t[i - 1] += (cnt[i] - t[i]) % 2;
    }
    for(int i = 0; i + 1 < P.size(); i += 2) {
        ans += P[i] * P[i + 1];
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
