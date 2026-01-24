#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, h, l;
    cin >> n >> h >> l;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    int lo = 1, hi = n;
    int ans = 0;
    while(lo < hi) {
        if(a[hi] > h && a[lo] > l) hi--;
        if(a[hi] <= h && a[lo] <= l) {
            ans++;
            hi--;
            lo++;
        } else if(a[hi] <= l && a[lo] <= h) {
            ans++;
            hi--;
            lo++;
        } else {
            hi--;
        }
    }
    cout << ans << "\n";
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
