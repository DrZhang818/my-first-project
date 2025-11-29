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
    vector<int> cnt(3 * n + 5); 
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int ans = 0;
    for(int i = 1, j = 0; i <= 3 * n; i++) {
        if(cnt[i] > k) {
            cnt[i + 1] += cnt[i] - 1;
            ans = max(ans, cnt[i] - k + j);
            j++;
        } else {
            j = 0;
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
