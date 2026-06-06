#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);

    i64 ans = 0;
    i64 c1 = 0, c4 = 0, seg = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x == 1) {
            c1++;
        } else {
            seg++;
            ans += x;
            if(x >= 4) {
                c4 += x / 2 - 1;
            }
        }
    }

    if(seg == 1) {
        c4++;
    } 
    ans += min(c1, c4);
    if(ans < 3) ans = 0;

    cout << ans << "\n";
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