#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    int cnt = 0;
    int lo = n, hi = n;
    while(lo > 0) {
        if(lo == k || hi == k) {
            cout << cnt << "\n";
            return;
        }
        lo /= 2;
        hi = (hi + 1) / 2;
        cnt++;
    }
    cout << -1 << "\n";
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
