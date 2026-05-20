#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
    }

    vector<int> L(n + 1), R(n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        if(L[a[i]] == 0) {
            L[a[i]] = i;
        } else {
            R[a[i]] = i;
        }
    }

    for(int i = 1; i < n; i++) {
        L[i] = min(L[i], L[i - 1]);
        R[i] = max(R[i], R[i - 1]);
    }

    auto work = [&](int l, int r) {
        for(int i = l; i <= r; i++) {
            if(a[i] != a[r - i + l]) {
                return false;
            }
        }
        return true;
    };


    auto ck = [&](int x) {
        bool ok = false;
        int l = L[x], r = R[x];

        ok |= work(l, r);
        int i = l + 1, j = r - 1;
        
        while(i < r && a[i] > x) i++;
        ok |= work(i, r);

        while(j > l && a[j] > x) j--;
        ok |= work(l, j);


        return ok;
    };

    int l = 0, r = n;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }

    cout << l + 1 << "\n";

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