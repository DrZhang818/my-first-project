#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
using i128 = __int128;

void solve() {
    int n;
    i64 k, T;
    cin >> n >> k >> T;
    vector<i64> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if(k == 1) {
        cout << 1 << "\n";
        return;
    }
    i128 tar = (i128)T * k * k;

    auto ck = [&](int x) {
        vector<i64> b(a.begin(), a.begin() + x);
        sort(b.begin(), b.end());

        i64 sum = 0, sq = 0;
        for(int i = 0; i < k; i++) {
            sum += b[i];
            sq += b[i] * b[i];
        }

        auto ok = [&]() {
            return (i128)k * sq - (i128)sum * sum < tar;
        };

        if(ok()) return true;
        for(int i = k; i < x; i++) {
            sum += b[i] - b[i - k];
            sq += b[i] * b[i] - b[i - k] * b[i - k];
            if(ok()) return true;
        }
        return false;
    };

    int l = k - 1, r = n + 1;
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
    while(t--) {
        solve();
    }
    return 0;
}