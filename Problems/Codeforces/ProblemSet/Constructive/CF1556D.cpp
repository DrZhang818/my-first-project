#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

auto query(int i, int j) {
    i64 res = 0, x;
    cout << "or " << i + 1 << " " << j + 1 << endl;
    cin >> x;
    res += x;
    cout << "and " << i + 1 << " " << j + 1 << endl;
    cin >> x;
    res += x;
    return res;
}

auto answer(int x) {
    cout << "finish " << x << endl;
}

void solve() {
    int n, k;
    cin >> n >> k;

    vector<i64> x(n), y(n);
    y[0] = query(1, 2);
    for(int i = 1; i < n; i++) {
        y[i] = query(0, i);
    }
    x[0] = (y[0] + y[1] + y[2]) / 2 - y[0];
    for(int i = 1; i < n; i++) {
        x[i] = y[i] - x[0];
    }
    sort(x.begin(), x.end());
    answer(x[k - 1]);
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
