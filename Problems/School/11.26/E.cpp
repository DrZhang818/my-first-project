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
    using T = array<ll,5>;
    T dp {};
    for(int i = 1; i <= n; i++) {
        T ndp {};
        T f = dp;
        for(int j = 1; j < 5; j++) {
            f[j] = min(f[j], f[j - 1]); 
        }
        ndp[0] = f[0] + a[i];
        ndp[1] = f[1] + (a[i] == 0 ? 2 : a[i] % 2);
        ndp[2] = f[2] + (a[i] % 2 == 0);
        ndp[3] = f[3] + (a[i] == 0 ? 2 : a[i] % 2);
        ndp[4] = f[4] + a[i];
        swap(dp, ndp);
    }
    cout << *min_element(dp.begin(), dp.end()) << "\n";
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
