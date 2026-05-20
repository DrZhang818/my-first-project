#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    i64 tot = 0;
    int h = inf;
    vector<int> tag(n + 1);
    for(int i = n; i >= 1; i--) {
        if(a[i] < h) {
            tag[i] = true;
            h = a[i];
        }
        tot += a[i] - h;
    }

    i64 ans = tot;
    int las = 0;
    for(int i = 1; i <= n; i++) {
        if(tag[i]) {
            ans = max(ans, tot + i - las - 1);
            las = i;
        }
    }

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