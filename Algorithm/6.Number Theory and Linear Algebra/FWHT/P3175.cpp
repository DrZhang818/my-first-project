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

    const int U = (1 << n) - 1;

    vector<db> p(1 << n);
    for(int i = 0; i < 1 << n; i++) {
        cin >> p[i];
    }

    if(p[U] == 0) {
        cout << "INF\n";
        return;
    }

    for(int i = 0; i < n; i++) {
        for(int s = 0; s < 1 << n; s++) {
            s |= 1 << i;
            p[s] += p[s ^ (1 << i)];
        }
    }

    db ans = 0;
    for(int s = 1; s < 1 << n; s++) {
        db x = 1 / (1 - p[U ^ s]);
        if(__builtin_popcount(s) & 1) {
            ans += x;
        } else {
            ans -= x;
        }
    }

    cout << fixed << setprecision(12) << ans << "\n";
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
