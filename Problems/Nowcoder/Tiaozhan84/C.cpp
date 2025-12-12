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
    vector<int> a(1 << n);
    for(int i = 0; i < 1 << n; i++) {
        cin >> a[i];
    }
    const int N = 1 << n;
    vector<int> p(N);
    iota(p.begin(), p.end(), 0);
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        int p0 = 0, p1 = 0;
        ll cur = 0;
        for(int j = 0; j < N; j++) {
            while(p0 < N && (p[p0] >> i & 1) != 0) {
                p0++;
            }
            while(p1 < N && (p[p1] >> i & 1) != 1) {
                p1++;
            }
            if(a[j] >> i & 1) {
                cur += abs(j - p1);
                p1++;
            } else {
                cur += abs(j - p0);
                p0++;
            }
        }
        ans += cur / 2;
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
