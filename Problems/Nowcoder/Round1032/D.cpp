#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    int c0 = 0, c1 = 0;
    i64 sum = 0, pre = 0;
    for(int i = 1; i <= n; i++) {
        sum += pre + 1LL * a[i] * (i - 1);
        pre += a[i];
        if(a[i] & 1) {
            sum -= c0;
            c1++;
        } else {
            sum -= c1;
            c0++;
        }
    }
    cout << sum / 2 << "\n";
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
