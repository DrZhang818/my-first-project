#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> d(n + 1);
    for(int i = 1; i <= n; i++) {
        d[i] = a[i] - a[i - 1];
    }

    int _xor = 0;
    for(int i = n; i >= 1; i -= 2) {
        _xor ^= d[i];
    }

    if(_xor == 0) {
        cout << "NIE\n";
    } else {
        cout << "TAK\n";
    }
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
