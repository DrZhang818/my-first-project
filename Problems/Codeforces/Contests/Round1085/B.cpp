#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, m, l;
    cin >> n >> m >> l;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int rem = n;
    vector<int> w(m + 1);
    for(int i = 1, j = 1; i <= l; i++) {
        w[min(m, rem + 1)]++;
        sort(w.begin() + 1, w.end(), greater());
        if(j <= n && i == a[j]) {
            w[1] = 0;
            j++;
            rem--;
            sort(w.begin() + 1, w.end(), greater());
        }
    }

    cout << w[1] << "\n";
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
