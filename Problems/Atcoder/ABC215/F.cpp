#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct Info {
    int x, y;
    friend bool operator<(const Info& a, const Info& b) {
        return a.x < b.x;
    }
};
void solve() {
    int n;
    cin >> n;

    vector<Info> a(n + 1);

    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }

    sort(a.begin() + 1, a.end());

    vector<int> x(n + 1), y(n + 1);
    for(int i = 1; i <= n; i++) {
        x[i] = a[i].x;
        y[i] = a[i].y;
    }

    vector<int> mnY(n + 1, inf), mxY(n + 1, -inf);
    for(int i = 1; i <= n; i++) {
        mnY[i] = min(mnY[i - 1], y[i]);
        mxY[i] = max(mxY[i - 1], y[i]);
    }

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int lo = -1, hi = x[i] + 1;
        while(lo + 1 < hi) {
            int mid = lo + (hi - lo) / 2;
            auto it = upper_bound(x.begin() + 1, x.end(), x[i] - mid);
            int j = it - x.begin() - 1;
            if(j == 0) {
                hi = mid;
                continue;
            }            
            if(abs(y[i] - mnY[j]) >= mid || abs(y[i] - mxY[j]) >= mid) {
                lo = mid; 
            } else {
                hi = mid;
            }
        }
        ans = max(ans, lo);
    }
    cout << ans << "\n";
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
