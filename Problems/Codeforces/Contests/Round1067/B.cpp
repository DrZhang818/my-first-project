#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<int> cnt(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int ans = 0;
    vector<int> val;
    int x = 0, y = 0;
    for(int i = 1; i <= 2 * n; i++) {
        if(cnt[i] == 0) continue;
        if(cnt[i] & 1) {
            ans++;
            x++;
        } else {
            if((cnt[i] / 2) & 1) {
                ans += 2;
            } else {
                y++;
            }
        }
    }
    int p = y / 2 * 2;
    ans += p * 2;
    y -= p;
    if(x >= y) {
        ans += y * 2;
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
