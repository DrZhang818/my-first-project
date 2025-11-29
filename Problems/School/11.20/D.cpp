#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;



void solve() {
    int K, A, B;
    cin >> K >> A >> B;
    if(B - A <= 2) {
        cout << 1 + K << "\n";
        return;
    }
    ll ans = 1;
    int need = A - 1;
    if((K - need) & 1) {
        need++;
    }
    ans += min(K, need);
    K -= min(K, need);
    ans += 1LL * (B - A) * (K / 2);
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
