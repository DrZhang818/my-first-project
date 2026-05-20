#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int x;
    cin >> x;
    array<int, 3> a {};
    for(int i = 2; i >= 0; i--) {
        a[i] = x % 60;
        x /= 60;
    }
    for(int i = 0; i < 3; i++) {
        cout << a[i] << " \n"[i == 2];
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
