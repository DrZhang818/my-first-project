#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    int B = max(1.0, 2e7 / sqrt(max(1, n)));

    vector<int> x(n), y(n);
    for(int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);

    sort(p.begin(), p.end(), 
        [&](int i, int j) {
            int bi = x[i] / B;
            int bj = x[j] / B;
            if(bi != bj) {
                return bi < bj;
            }
            return (bi & 1) ? y[i] < y[j] : y[i] > y[j];
        });

    auto it = find(p.begin(), p.end(), 0);
    rotate(p.begin(), it, p.end());

    for(int i = 0; i < n; i++) {
        cout << p[i] + 1 << " \n"[i == n - 1];
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
