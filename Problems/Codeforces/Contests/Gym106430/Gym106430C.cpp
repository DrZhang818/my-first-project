#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int res = 0;
    for(int i = 1; i <= n / 2; i++) {
        if(a[i] != a[n - i + 1]) {
            res++;
        }
    }

    bool ok = false;
    sort(a.begin() + 1, a.end());
    for(int i = 2; i <= n; i++) {
        if(a[i] == a[i - 1]) {
            ok = true;
            break;
        }
    }

    while(q--) {
        int k;
        cin >> k;
        if(k < res) {
            cout << "NO\n";
            continue;
        }
        if(ok || k % 2 == res % 2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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
