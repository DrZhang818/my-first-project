#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(m + 1);
    int _xor = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        _xor ^= a[i];
    }
    int _or = 0;
    for(int i = 1; i <= m; i++) {
        cin >> b[i];
        _or |= b[i];
    }

    if(n & 1) {
        cout << _xor << " " << (_xor | _or) << "\n";
    } else {
        cout << (_xor & ~_or) << " " << _xor << "\n";
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}