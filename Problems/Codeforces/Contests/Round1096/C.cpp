#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i] % 6 == 0 ? 6 : a[i] % 3 == 0 ? 3 : a[i] % 2 == 0 ? 2 : 1;
    }

    vector<int> p(n + 1);
    iota(p.begin(), p.end(), 0);
    sort(p.begin() + 1, p.end(), 
        [&](int x, int y) {
            return b[x] > b[y];
        });

    vector<int> L, M, R;
    for(int i = 1; i <= n; i++) {
        int x = b[p[i]];
        if(x == 6 || x == 3) {
            L.push_back(a[p[i]]);
        } else if(x == 1) {
            M.push_back(a[p[i]]);
        } else {
            R.push_back(a[p[i]]);
        }
    }

    for(auto& vec : {L, M, R}) {
        for(int x : vec) {
            cout << x << " ";
        }
    }

    cout << "\n";
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