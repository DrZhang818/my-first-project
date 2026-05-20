#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n, m;
    cin >> n >> m;

    auto ck = [&](int x) -> bool {
        int rem = m - 1;
        i64 S = 1;

        while(S < n && rem > 0 && x > S + 1) {
            S += S + 1;
            rem--;
        }

        S += 1LL * x * rem;
        return S >= n;
    };

    int l = 0, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    if(r == n + 1) {
        r = -1;
    }

    cout << r << "\n";
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