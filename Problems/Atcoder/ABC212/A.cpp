#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int a, b;
    cin >> a >> b;
    if(a > 0 && b == 0) {
        cout << "Gold\n";
    } else if(a == 0 && b > 0) {
        cout << "Silver\n";
    } else {
        cout << "Alloy\n";
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
