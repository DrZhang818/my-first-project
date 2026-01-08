#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int w, h, d;
    cin >> w >> h >> d;
    int n;
    cin >> n;
    if(1LL * w * h % n * d % n != 0) {
        cout << -1 << "\n";
        return;
    }
    int x = gcd(w, n);
    n /= x;
    int y = gcd(h, n);
    n /= y;
    int z = gcd(d, n);
    n /= z;
    cout << x - 1 << " " << y - 1 << " " << z - 1 << "\n";
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
