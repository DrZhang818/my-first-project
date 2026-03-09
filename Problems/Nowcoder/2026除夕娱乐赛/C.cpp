#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    vector<i64> a(n + 1), b(m + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int j = 1; j <= m; j++) {
        cin >> b[j];
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            auto g = gcd(a[i], b[j]);
            a[i] /= g;
            b[j] /= g;
            cout << g << " \n"[j == m];
        }
    }

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
