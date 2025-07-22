#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    vector<int> b{0};
    b.reserve(n / 2);
    for(int i = n / 2 + 1; i <= n; i++) {
        b.push_back(a[i]);
    }
    n = b.size() - 1;
    auto ck = [&](int x) -> bool {
        ll cnt = 0;
        for(int i = 1; i <= n; i++) {
            if(b[i] < x) {
                cnt += x - b[i];
            }
        }
        return cnt <= k;
    };
    int l = 0, r = 2e9 + 1;
    while(l + 1 < r) {
        int mid = l + (r - l) / 2;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";
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
