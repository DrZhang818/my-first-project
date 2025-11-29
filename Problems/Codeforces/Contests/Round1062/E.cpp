#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());

    auto ck = [&](int d) -> bool {
        if(d == 0) return true;
        d--;
        int cnt = x + 1;
        int L = -1, R = -1;
        for(int i = 1; i <= n; i++) {
            L = max(R + 1, a[i] - d);
            R = min(x, a[i] + d);
            cnt -= R - L + 1;
        }
        return cnt >= k;
    };

    int l = -1, r = x + 2;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    int d = l;
    if(d == 0) {
        for(int i = 0; i < k; i++) {
            cout << i << " \n"[i == k - 1];
        }
        return;
    }
    int cur = 0, i = 1;
    while(k) {
        while(i <= n && cur > a[i] - d) {
            cur = a[i] + d;
            i++;
        }
        cout << cur << " ";
        k--;
        cur++;
    }
    cout << "\n";
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
