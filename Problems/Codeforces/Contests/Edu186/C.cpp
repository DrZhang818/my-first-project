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
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    ll c1 = 0, c2 = 0;
    for(int i = 1; i <= n; i++) {
        bool ok = true;
        for(int j = 1; j <= n; j++) {
            if(a[j] >= b[(i + j) % n + 1]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            c1++;
        }
    }
    for(int i = 1; i <= n; i++) {
        bool ok = true;
        for(int j = 1; j <= n; j++) {
            if(b[j] >= c[(i + j) % n + 1]) {
                ok = false;
                break;
            }
        }
        if(ok) {
            c2++;
        }
    }
    cout << n * c1 * c2 << "\n";
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
