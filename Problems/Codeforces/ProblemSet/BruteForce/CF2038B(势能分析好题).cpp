#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }

    auto ck = [&](int x) -> bool {
        auto b = a;
        for(int i = 1; i <= n; i++) {
            b[i] -= x;
        }
        for(int i = 1; i <= n; i++) {
            if(b[i] > 0) {
                int c = b[i] + 1 >> 1;
                b[i % n + 1] += c;
                b[i] -= c * 2;
            }
        }
        int i = 1;
        while(b[i] > 0) {
            int c = b[i] + 1 >> 1;
            b[i % n + 1] += c;
            b[i] -= c * 2;
            i = i % n + 1;
        }
        for(int i = 1; i <= n; i++) {
            if(b[i] != 0) {
                return false;
            }
        }
        return true;
    };

    int l = 0, r = sum / n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if(l == 0) {
        cout << -1 << "\n";
        return ;
    }
    cout << sum - 1LL * n * l << "\n";
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
