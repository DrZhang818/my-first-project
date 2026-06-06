#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

auto query(int x) {
    cout << x << endl;
    int res;
    cin >> res;
    return res;
}

void solve() {
    int n;
    cin >> n;

    int l = 0, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        int res = query(mid);
        if(res == -1) {
            r = mid;
        } else if(res == 1) {
            l = mid;
        } else {
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}